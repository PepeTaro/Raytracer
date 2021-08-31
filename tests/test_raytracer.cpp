#include "raytracer.h"
#include "camera.h"
#include <iostream>

void test1(){
  Vector3 view(-1,0,0);
  Vector3 up(0,0,1);
  Vector3 eye(0,0,0);

  Camera camera(eye,view,up);
  RayTracer raytracer(20,20,-10,10,-10,10);
  raytracer.attachCamera(camera,1.0);
  
}

int main(){
  test1();
}
