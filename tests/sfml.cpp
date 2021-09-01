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
#include "light.h"
#include "const.h"

int window_height = 480;
int window_width  = 640;

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

void Raytrace(sf::RenderWindow& window,const RayTracer& raytracer,const Camera& camera){
  Vector3 dir;
  Vector3 eye = camera.getE();
  Color color;
  float t0,t1;
  t0 = 0;
  t1 = kInfinity;
    
  for(int i=0;i<window_width;++i){
    for(int j=0;j<window_height;++j){
      dir = raytracer.getDirection(i,j);
      color = raytracer.Raycolor(dir,eye,t0,t1,1);
      DrawPixel(window,i,j,color);      
    }
  }

}

void InitSurfaces(RayTracer& raytracer){
  
 raytracer.addLight(new Light(Vector3(-70,20,-1),
			    Color(1.0,1.0,1.0))
		  );

 raytracer.addLight(new Light(Vector3(-70,-20,-20),
			    Color(2.0,2.0,2.0))
		  );

 
 raytracer.addSurface(new Triangle(Vector3(-200,-100,0),
				  Vector3(-200,100,0),
				  Vector3(-200,0,-100),
				  Color(0.6,0.0,0.6),
				  Color(0.5,0.5,0.5),
				  Color(0.9,0.9,0.9),
				  1)
		     );

 raytracer.addSurface(new Triangle(Vector3(0,0,8),
				  Vector3(-500,300,8),
				  Vector3(-500,-300,8),
				  Color(0.6,0.6,0.6),
				  Color(0.0,0.0,0.0),
				  Color(0.9,0.9,0.9),
				  1)
		     );
  
 raytracer.addSurface(new Sphere(Vector3(-100,-18,0),8,
				Color(0.0,0.5,0),
				Color(0.0,0.1,0),
				Color(0.3,0.3,0.3),
				1)
		     );
  
  
  raytracer.addSurface(new Sphere(Vector3(-100,0,0),8,
				Color(0.5,0.0,0.0),
				Color(0.1,0.1,0.1),
				Color(0.9,0.9,0.9),
				100)
		     );

  raytracer.addAmbient(new Color(1.5,1.5,1.5));
}


void Draw(sf::RenderWindow& window,const RayTracer& raytracer,const Camera& camera){  
  Clear(window,0,0,0);
  Raytrace(window,raytracer,camera);
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

int main(int argc,char **argv){  
  sf::RenderWindow window(sf::VideoMode(window_width,window_height), "RayTracer");
  
  float fov = 45.0;  
  float focal_length = sqrtf(powf(window_width,2) + powf(window_height,2))/(2.f*tanf(fov/2.0));
  Vector3 view(-1,0,0);
  Vector3 up(0,0,1);
  Vector3 eye(0,0,0);
  
  Camera camera(eye,view,up);
  
  RayTracer raytracer(window_width,window_height,-window_width/2,window_width/2,-window_height/2,window_height/2);
  raytracer.attachCamera(camera,focal_length);  
  InitSurfaces(raytracer);
  
  Draw(window,raytracer,camera);  
  while(window.isOpen()){
    Keyboard(window);
  }
}
