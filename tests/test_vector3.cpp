#include "vector3.h"
#include <iostream>

inline void PrintVector(const Vector3& vec){
  std::cout << "(" << vec.x
	    << "," << vec.y
	    << "," << vec.z
	    << ")" << std::endl;
}

void test1(){
  Vector3 u(1,2,3);
  Vector3 v;
  v.x = 2;
  Vector3 w = u+v;
  Vector3 a = w*-1;
  Vector3 b = 2*w;
  Vector3 c = v + 2*u;
  
  PrintVector(u);
  PrintVector(v);
  PrintVector(w);
  PrintVector(a);
  PrintVector(b);
  PrintVector(c);

}

void test2(){
  Vector3 u(1,1,0);
  Vector3 v(1,0,1);

  Vector3 a(1,0,0);
  Vector3 b(0,1,0);

  PrintVector(u);
  std::cout << dot(u,v) << std::endl;
  PrintVector(cross(a,b));

}

int main(){
  //test1();
  test2();
}
