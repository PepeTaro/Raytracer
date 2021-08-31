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

/*
int block_size = 20;
int row_block = 24;
int col_block = 32;
*/

const float kEpsilon = 1.0;
const float kInfinity = 1e20;
int block_size = 1;
int row_block = 480;
int col_block = 640;

int height = block_size*row_block;
int width  = block_size*col_block;

std::vector<Surface*> surfaces;
static Color ambinet_intensity(1.0,1.0,1.0);
static Color light_intensity(0.6,0.5,0.4);
static Vector3 light_pos(-100,10,-10);

void DrawPixel(sf::RenderWindow& window,int i,int j,float r,float g,float b){  
    float w,h;

    w = block_size*i;
    h = block_size*j;
    
    sf::RectangleShape rectangle(sf::Vector2f(block_size,block_size));
    rectangle.setPosition(sf::Vector2f(w,h));
    rectangle.setFillColor(sf::Color((int)255*r,
				     (int)255*g,
				     (int)255*b));
    
    window.draw(rectangle);
}

void Clear(sf::RenderWindow& window,float r,float g,float b){
  for(int x=0;x<col_block;++x){
    for(int y=0;y<row_block;++y){            
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

void RayTrace(sf::RenderWindow& window,const RayTracer& raytracer,const Camera& camera){
  Vector3 dir;
  Vector3 eye = camera.getE();
  records rec,srec;
  Color color;
  float t0,t1;
  t0 = 0;
  t1 = kInfinity;
  
  Vector3 light_direction,view_direction,half_vector;
  
  Clear(window,0,0,0);      
  for(int i=0;i<col_block;++i){
    for(int j=0;j<row_block;++j){
      dir = raytracer.getDirection(i,j);
      
      //std::cout << dir.x << "," << dir.y << "," << dir.z << std::endl,exit(-1);
      
      for(auto surface : surfaces){
	if(surface->isHit(dir,eye,t0,t1,rec)){
	  color = HadamardProduct(rec.ambient,ambinet_intensity);
	  light_direction = (light_pos - rec.pos).getNormalize();
	  
	  if(not surface->isHit(light_direction,rec.pos,kEpsilon,kInfinity,srec)){
	    view_direction = (-1.0*dir).getNormalize();
	    half_vector = (light_direction + view_direction).getNormalize();
	    
	    color = color +
	      HadamardProduct(rec.diffuse,light_intensity)*max(0,dot(rec.normal,light_direction)) +
	      HadamardProduct(rec.specular,light_intensity)*powf(max(0,dot(rec.normal,half_vector)),rec.phong_exponent);	  
	  }
	  
	  DrawPixel(window,i,j,color.red(),color.green(),color.blue());
	  
	}
      }
      
    }
  }

  window.display();
}

void InitSurfaces(){
  /*
  surfaces.push_back(new Triangle(Vector3(0,0,10),
				  Vector3(-50,50,20),
				  Vector3(-50,-50,0),
				  Color(0.3,0.3,0.3),
				  Color(0.2,0,0),
				  Color(0.9,0.9,0)));
  */
  
  surfaces.push_back(new Sphere(Vector3(-100,0,8),8,
				Color(0.3,0,0),
				Color(0.0,0,0),
				Color(1.0,0,0)));
  
  
  // light
  surfaces.push_back(new Sphere(light_pos,5,
				Color(1,1,1),
				Color(0.0,0,0),
				Color(0.0,0,0)));
  
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
  sf::RenderWindow window(sf::VideoMode(width,height), "RayTracer");  

  Vector3 view(-1,0,0);
  Vector3 up(0,0,1);
  Vector3 eye(0,0,0);
  float focal_length;
  float fov = 45.0;
  
  Camera camera(eye,view,up);
  //RayTracer raytracer(col_block,row_block,-10,10,-10,10);
  RayTracer raytracer(col_block,row_block,-col_block/2,col_block/2,-row_block/2,row_block/2);

  focal_length = sqrtf(powf(col_block,2) + powf(row_block,2))/(2.f*tanf(fov/2.0));
  raytracer.attachCamera(camera,focal_length);

  InitSurfaces();
  RayTrace(window,raytracer,camera);
  
  while(window.isOpen()){
    Keyboard(window);
  }
}
