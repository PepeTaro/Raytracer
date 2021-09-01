#include "raytracer.h"

RayTracer::RayTracer(int num_col_pixels,int num_row_pixels,float left_edge,float right_edge,float bottom_edge,float top_edge):
  num_col_pixels_(num_col_pixels),num_row_pixels_(num_row_pixels),
  left_edge_(left_edge),right_edge_(right_edge),
  bottom_edge_(bottom_edge),top_edge_(top_edge)
{
  
}

void RayTracer::attachCamera(const Camera& camera,float focal_length){
  camera_ = camera;
  focal_length_ = focal_length;
}

Vector3 RayTracer::getDirection(int i,int j) const{
  // Maybe I should store (right_edge_ - left_edge_)/num_col_pixles as a member variable.
  float u = left_edge_ + (right_edge_ - left_edge_)*(i + 0.5)/num_col_pixels_;
  float v = bottom_edge_ + (top_edge_ - bottom_edge_)*(j + 0.5)/num_row_pixels_;
  
  return (-focal_length_*camera_.getW() + u*camera_.getU() + v*camera_.getV());
}


Color RayTracer::AddShadowToColor(const Color& color,const Vector3& dir,const Light* light,const records& rec) const{
  bool is_shadow_hit = false;
  records tmp_rec;
  Color result_color;
  Vector3 light_direction = normalize(light->getPos() - rec.pos);
  
  for(auto shadow_surface : surfaces_){ // 影となるか否かチェック
    if(shadow_surface->isHit(light_direction,rec.pos,kEpsilon,kInfinity,tmp_rec)){
      is_shadow_hit = true;
      break;
    }	    
  }
	  
  if(not is_shadow_hit){ // 影とならない場合
    
    Vector3 view_direction = normalize(-1.0*dir);
    Vector3 half_vector = normalize(light_direction + view_direction);
    Vector3 light_intensity = light->getLightIntensity();
    
    result_color = color +
      rec.diffuse*light_intensity*max(0,dot(rec.normal,light_direction)) +
      rec.specular*light_intensity*powf(max(0,dot(rec.normal,half_vector)),rec.phong_exponent);	    
	    
  }else{ // 影となる場合
    result_color = rec.ambient;
  }

  return result_color;
}

Color RayTracer::AddMirrorReflection(const Color& color,const Vector3& dir,const records& rec,int recursion_depth) const{
  if(recursion_depth == 0) return color;
  
  Color result_color;
  Vector3 reflection_vector = dir - 2*(dot(dir,rec.normal))*rec.normal;
  result_color = color + rec.specular*Raycolor(reflection_vector,rec.pos,kEpsilon,kInfinity,recursion_depth-1);
  
  return result_color;
}

Color RayTracer::AddAmbientToColor(const Color& color,const Color& ambient_coeff,const Color* ambient_intensity) const{
  Color result_color;
  result_color = color + ambient_coeff * (*ambient_intensity);
  return result_color;
}

Color RayTracer::Raycolor(const Vector3& dir,const Vector3& eye,float t0,float t1,int recursion_depth) const{
  records rec;
  Color color;
  
  for(auto surface : surfaces_){
    if(surface->isHit(dir,eye,t0,t1,rec)){

      color = Color(0,0,0);      
      for(auto ambient : ambients_){
	color = AddAmbientToColor(color,rec.ambient,ambient);
      }     
      
      for(auto light : lights_){ // Diffuse,Specular,Shadowを追加
	color = AddShadowToColor(color,dir,light,rec);
      }
      
      color = AddMirrorReflection(color,dir,rec,recursion_depth);
	  
    }
  }
  
  return color;
}

void RayTracer::addSurface(Surface* surface){
  surfaces_.push_back(surface);
}

void RayTracer::addLight(Light* light){
  lights_.push_back(light);
}

void RayTracer::addAmbient(Color* ambient){
  ambients_.push_back(ambient);
}
