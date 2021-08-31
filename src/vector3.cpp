#include "vector3.h"

Vector3::Vector3(float x,float y,float z):x(x),y(y),z(z){
  
}

Vector3 Vector3::operator+(const Vector3& vec) const{
  return Vector3(x+vec.x,y+vec.y,z+vec.z);
}

Vector3 Vector3::operator-(const Vector3& vec) const{
  return Vector3(x-vec.x,y-vec.y,z-vec.z);
}

Vector3 Vector3::operator*(float t) const{
  return Vector3(x*t,y*t,z*t);
}

void Vector3::normalize(){
  float norm = sqrtf(x*x + y*y + z*z);
  assert(norm != 0);
  
  x /= norm;
  y /= norm;
  z /= norm;  
}

Vector3 Vector3::getNormalize() const{
  float norm = sqrtf(x*x + y*y + z*z);
  assert(norm != 0);
  return Vector3(x/norm,y/norm,z/norm);  
}

Vector3 operator*(float t,const Vector3& vec){
  return Vector3(vec.x*t,vec.y*t,vec.z*t);
}

float dot(const Vector3& a,const Vector3& b){
  return (a.x*b.x + a.y*b.y + a.z*b.z);
}

Vector3 cross(const Vector3& a,const Vector3& b){
  return Vector3(a.y*b.z - a.z*b.y,
		 a.z*b.x - a.x*b.z,
		 a.x*b.y - a.y*b.x);
}

Vector3 HadamardProduct(const Vector3& a,const Vector3& b){
  return Vector3(a.x*b.x,a.y*b.y,a.z*b.z);
}
