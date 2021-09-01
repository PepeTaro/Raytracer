#include <iostream>
#include <cmath>
#include <string>
#include <array>
#include <vector>
#include <SFML/Graphics.hpp>

#include "raytracer.h"
#include "camera.h"
#include "vector3.h"
#include "sphere.h"
#include "surface.h"
#include "triangle.h"
#include "color.h"
#include "utils.h"

const float kEpsilon = 1e-8;
const float kInfinity = 1e20;

int window_height = 480;
int window_width  = 640;

std::vector<Surface*> surfaces;
static Color ambinet_intensity(2.0,2.0,2.0);
static Color light_intensity(1.0,1.0,1.0);
static Vector3 light_pos(-70,20,-10);

void DrawPixel(sf::RenderWindow& window,int i,int j,float r,float g,float b){  
    if(r > 1.0) r = 1.0;
    if(g > 1.0) g = 1.0;
    if(b > 1.0) b = 1.0;
    
    sf::RectangleShape rectangle(sf::Vector2f(1,1)); // Pixel単位で描写
    rectangle.setPosition(sf::Vector2f(i,j));
    rectangle.setFillColor(sf::Color((int)255*r,
				     (int)255*g,
				     (int)255*b));
    
    window.draw(rectangle);
}

void DrawPixel(sf::RenderWindow& window,int i,int j,const Color& color){
  DrawPixel(window,i,j,color.red(),color.green(),color.blue());
}

void Clear(sf::RenderWindow& window,float r,float g,float b){
  for(int x=0;x<window_width;++x){
    for(int y=0;y<window_height;++y){            
      DrawPixel(window,x,y,r,g,b);
    }
  }
}

void Draw(sf::RenderWindow& window){  
  Clear(window,0,0,0);    
  window.display();  
}

void Keyboard(sf::RenderWindow& window){
  sf::Event event;
      
  while (window.pollEvent(event)){
    switch(event.type)
    case sf::Event::Closed:
      window.close();
    break;
  }
}

Color AddShadowToColor(const Color& color,const Vector3& dir,const Vector3& light_direction,const records& rec){
  bool is_shadow_hit = false;
  records tmp_rec;
  Color result_color;
  
  for(auto shadow_surface : surfaces){ // 影となるか否かチェック
    if(shadow_surface->isHit(light_direction,rec.pos,kEpsilon,kInfinity,tmp_rec)){
      is_shadow_hit = true;
      break;
    }	    
  }
	  
  if(not is_shadow_hit){ // 影とならない場合
    
    Vector3 view_direction = normalize(-1.0*dir);
    Vector3 half_vector = normalize(light_direction + view_direction);
    
    result_color = color +
      rec.diffuse*light_intensity*max(0,dot(rec.normal,light_direction)) +
      rec.specular*light_intensity*powf(max(0,dot(rec.normal,half_vector)),rec.phong_exponent);	    
	    
  }else{ // 影となる場合
    result_color = rec.ambient;
  }

  return result_color;
}

void Raytrace(sf::RenderWindow& window,const RayTracer& raytracer,const Camera& camera){
  Vector3 dir;
  Vector3 eye = camera.getE();
  records rec;
  Color color;
  float t0,t1;
  t0 = 0;
  t1 = kInfinity;
  
  Vector3 light_direction;
  
  Clear(window,0,0,0);      
  for(int i=0;i<window_width;++i){
    for(int j=0;j<window_height;++j){
      dir = raytracer.getDirection(i,j);
      
      for(auto surface : surfaces){
	if(surface->isHit(dir,eye,t0,t1,rec)){
	  
	  color = rec.ambient*ambinet_intensity;
	  light_direction = normalize(light_pos - rec.pos);
	  
	  color = AddShadowToColor(color,dir,light_direction,rec);
	  
	  DrawPixel(window,i,j,color);
	  
	}
      }      
    }
  }

  window.display();
}

void InitSurfaces(){
  
  surfaces.push_back(new Triangle(Vector3(0,0,8),
				  Vector3(-500,300,8),
				  Vector3(-500,-300,8),
				  Color(0.6,0.6,0.6),
				  Color(0.9,0.9,0.9),
				  Color(0.9,0.9,0.9),
				  1)
		     );
  
  surfaces.push_back(new Sphere(Vector3(-100,-18,0),8,
				Color(0.0,0.5,0),
				Color(0.0,0.1,0),
				Color(0.3,0.3,0.3),
				1)
		     );
  
  
  surfaces.push_back(new Sphere(Vector3(-100,0,0),8,
				Color(0.5,0.0,0.0),
				Color(0.1,0.1,0.1),
				Color(0.9,0.9,0.9),
				100)
		     );
  
  /*
  // light
  surfaces.push_back(new Sphere(light_pos,5,
				Color(1,1,1),
				Color(0.0,0,0),
				Color(0.0,0,0)));
  */
  //surfaces.push_back(new Sphere(Vector3(-20,100,0),8));
  /*
  surfaces.push_back(new Triangle(Vector3(-20,-50,0),
				  Vector3(-10,50,0),
				  Vector3(-10,50,50),
				  Color(1,0,0),
				  Color(0,1,0),
				  Color(0,0,1)));
  */
}

int main(int argc,char **argv){  
  sf::RenderWindow window(sf::VideoMode(window_width,window_height), "RayTracer");
  
  float fov = 45.0;  
  float focal_length = sqrtf(powf(window_width,2) + powf(window_height,2))/(2.f*tanf(fov/2.0));
  Vector3 view(-1,0,0);
  Vector3 up(0,0,1);
  Vector3 eye(0,0,0);
  
  Camera camera(eye,view,up);
  Vector3 u = camera.getU();
  Vector3 v = camera.getV();
  Vector3 w = camera.getW();
  
  RayTracer raytracer(window_width,window_height,-window_width/2,window_width/2,-window_height/2,window_height/2);
  raytracer.attachCamera(camera,focal_length);
  
  InitSurfaces();
  Raytrace(window,raytracer,camera);
  
  while(window.isOpen()){
    Keyboard(window);
  }
}
