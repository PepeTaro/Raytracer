#ifndef COLOR_H
#define COLOR_H

#include "vector3.h"

class Color : public Vector3{  
public:
  Color(float r=0,float g=0,float b=0);
  Color(const Vector3& vector):Vector3(vector){};
  
  float red() const;
  float green() const;
  float blue() const;
  
};//class Color

#endif// COLOR_H
