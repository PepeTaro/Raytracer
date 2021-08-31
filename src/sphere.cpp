#include "sphere.h"

Sphere::Sphere(const Vector3& center,float radius,const Color& ambient,const Color& diffuse,const Color& specular):
  center_(center),radius_(radius),
  ambient_(ambient),diffuse_(diffuse),specular_(specular)
{

}

bool Sphere::isHit(const Vector3& dir,const Vector3& eye,float t0,float t1,records& rec){
  Vector3 e_c = eye - center_;
  float B = dot(dir,e_c);
  float A = dot(dir,dir);
  float C = dot(e_c,e_c) - radius_*radius_;
  
  float has_solution = B*B - A*C;
  
  if(has_solution < 0){
    // 0 solution
    return false;
  }else if(has_solution == 0){
    // 1 solution
    float solution = -B/A;
    rec.t = solution;
    //rec = {solution,solution};
  }else{
    // 2 solutions
    float tmp = sqrtf(has_solution);
    
    if(tmp < 0){
      rec.t = (-B+tmp)/A;
      //rec = {(-B+tmp)/A,(-B-tmp)/A};
    }else{
      rec.t = (-B-tmp)/A;
      //rec = {(-B-tmp)/A,(-B+tmp)/A};
    }
    
  }
  
  rec.ambient = ambient_;
  rec.diffuse = diffuse_;
  rec.specular = specular_;
  rec.phong_exponent = 1;
  rec.pos = eye + rec.t*dir;
  rec.normal = (rec.pos - center_).getNormalize();

  return true;
}

