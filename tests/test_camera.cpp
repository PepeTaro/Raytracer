#include "camera.h"
#include "vector3.h"
#include <iostream>

inline void PrintVector(const Vector3& vec){
  std::cout << "(" << vec.x
	    << "," << vec.y
	    << "," << vec.z
	    << ")" << std::endl;
}

void test1(){
  Vector3 view(-1,0,0);
  Vector3 up(0,0,1);
  Vector3 eye(0,0,0);

  Camera camera(eye,view,up);
  PrintVector(camera.getE());
  PrintVector(camera.getU());
  PrintVector(camera.getV());
  PrintVector(camera.getW());
}

int main(){
  test1();
}
