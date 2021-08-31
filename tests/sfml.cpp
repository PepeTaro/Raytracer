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

int block_size = 1;
int row_block = 480;
int col_block = 640;

int height = block_size*row_block;
int width  = block_size*col_block;

std::vector<Surface*> surfaces;

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
  records rec;
  Color color;
  static Color ambinet_intensity(0.5,0.5,0.5);
  static Color light_intensity(0,1,0);
  static Vector3 light_pos(-2,2,2);

  Vector3 light_direction,view_direction,half_vector;
  
  Clear(window,0,0,0);      
  for(int i=0;i<col_block;++i){
    for(int j=0;j<row_block;++j){
      dir = raytracer.getDirection(i,j);
      
      for(auto surface : surfaces){
	if(surface->isHit(dir,eye,0,100,rec)){
	  color = HadamardProduct(rec.ambient,ambinet_intensity);
	  
	  light_direction = (light_pos - rec.pos).getNormalize();
	  view_direction = (eye - rec.pos).getNormalize();
	  half_vector = (light_direction + view_direction).getNormalize();
	    
	  color = color +
	    HadamardProduct(rec.diffuse,light_intensity)*max(0,dot(rec.normal,light_direction)) +
	    HadamardProduct(rec.specular,light_intensity)*max(0,dot(rec.normal,half_vector));
	  
	  DrawPixel(window,i,j,color.red(),color.green(),color.blue());
	}
      }
      
    }
  }

  window.display();
}

void InitSurfaces(){  
  //surfaces.push_back(new Sphere(Vector3(-10,0,0),8));
  //surfaces.push_back(new Sphere(Vector3(-20,100,0),8));
  surfaces.push_back(new Triangle(Vector3(-20,-50,0),
				  Vector3(-10,50,0),
				  Vector3(-10,50,50),
				  Color(1,0,0),
				  Color(0,1,0),
				  Color(0,0,1)));
}

int main(int argc,char **argv){  
  sf::RenderWindow window(sf::VideoMode(width,height), "RayTracer");  

  Vector3 view(-1,0,0);
  Vector3 up(0,0,1);
  Vector3 eye(0,0,0);

  Camera camera(eye,view,up);
  RayTracer raytracer(col_block,row_block,-10,10,-10,10);
  raytracer.attachCamera(camera,1.0);

  InitSurfaces();
  RayTrace(window,raytracer,camera);
  
  while(window.isOpen()){
    Keyboard(window);
  }
}
