#ifndef SPHERE_H
#define SPHERE_H

#include "surface.h"
#include "vector3.h"
#include "color.h"
#include "utils.h"

class Sphere : public Surface{
private:
  Vector3 center_;
  float radius_;
  Color ambient_,diffuse_,specular_;
public:
  Sphere(const Vector3& center,float radius,const Color& ambient,const Color& diffuse,const Color& specular);
  bool isHit(const Vector3& dir,const Vector3& eye,float t0,float t1,records& rec);
  
};//class Sphere
  
#endif// SPHERE_H
