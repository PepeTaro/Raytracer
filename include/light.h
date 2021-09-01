#ifndef LIGHT_H
#define LIGHT_H

#include "vector3.h"
#include "color.h"

class Light{
private:
  Color light_intensity_;
  Vector3 pos_;
public:
  Light(const Vector3& pos,const Color& light_intensity);
  Vector3 getPos() const;
  Color getLightIntensity() const;
  
};//class Light

#endif// LIGHT_H
