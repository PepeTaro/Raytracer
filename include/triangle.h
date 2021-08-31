#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "surface.h"
#include "vector3.h"
#include "color.h"

class Triangle : public Surface{
private:
  Vector3 a_,b_,c_;
  Vector3 normal_;
  Color ambient_,diffuse_,specular_;
public:
  Triangle(const Vector3& a,const Vector3& b,const Vector3& c,const Color& ambient,const Color& diffuse,const Color& specular);
  bool isHit(const Vector3& dir,const Vector3& eye,float t0,float t1,records& rec);

};//class Triangle

#endif// TRIANGLE_H
