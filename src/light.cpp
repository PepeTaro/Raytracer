#include "light.h"

Light::Light(const Vector3& pos,const Color& light_intensity):
  pos_(pos),light_intensity_(light_intensity)
{
  
}

Vector3 Light::getPos() const{return pos_;}
Color Light::getLightIntensity() const{return light_intensity_;};
