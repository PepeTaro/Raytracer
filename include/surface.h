#ifndef SURFACE_H
#define SURFACE_H

#include "vector3.h"
#include "color.h"

typedef struct records{
  float t;
  Color ambient;
  Color diffuse;
  Color specular;
  float phong_exponent;
  Vector3 normal;
  Vector3 pos;
}records;

class Surface{  
public:
  Surface(){}
  virtual ~Surface(){}
  virtual bool isHit(const Vector3& dir,const Vector3& eye,float t0,float t1,records& rec)=0;
};//class Surface

#endif// SURFACE_H
