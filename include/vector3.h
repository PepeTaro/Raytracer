#ifndef VECTOR3_H
#define VECTOR3_H

#include <cmath>
#include <cassert>

struct Vector3{
  float x;
  float y;
  float z;

  Vector3(float x=0,float y=0,float z=0);
  Vector3 operator+(const Vector3& vec) const;
  Vector3 operator-(const Vector3& vec) const;
  Vector3 operator*(float t) const;
  friend Vector3 operator*(float t,const Vector3& vec);
  
  void normalize();
  Vector3 getNormalize() const;
};//struct Vector3

float dot(const Vector3& a,const Vector3& b);
Vector3 cross(const Vector3& a,const Vector3& b);
Vector3 HadamardProduct(const Vector3& a,const Vector3& b);

#endif// VECTOR3_H
