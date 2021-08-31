#include "triangle.h"

Triangle::Triangle(const Vector3& a,const Vector3& b,const Vector3& c,const Color& ambient,const Color& diffuse,const Color& specular):
  a_(a),b_(b),c_(c),
  ambient_(ambient),diffuse_(diffuse),specular_(specular)
{
  normal_ = cross(b_ - a_,c_ - a_).getNormalize();
}

bool Triangle::isHit(const Vector3& dir,const Vector3& eye,float t0,float t1,records& rec){
  float a = a_.x - b_.x;
  float b = a_.y - b_.y;
  float c = a_.z - b_.z;

  float d = a_.x - c_.x;
  float e = a_.y - c_.y;
  float f = a_.z - c_.z;

  float g = dir.x;
  float h = dir.y;
  float i = dir.z;
  
  float j = a_.x - eye.x;
  float k = a_.y - eye.y;
  float l = a_.z - eye.z;

  float ei_hf = e*i - h*f;
  float gf_di = g*f - d*i;
  float dh_eg = d*h - e*g;

  float det = a*(ei_hf) + b*(gf_di) + c*(dh_eg);
  if(det == 0) return false;
  
  float t = f*(a*k - j*b) + e*(j*c - a*l) + d*(b*l - k*c);
  t /= -det;
  if(t < t0 or t > t1) return false;

  float gamma = i*(a*k - j*b) + h*(j*c - a*l) + g*(b*l - k*c);
  gamma /= det;
  if(gamma < 0 or gamma > 1) return false;
    
  float beta = j*ei_hf + k*gf_di + l*dh_eg;
  beta /= det;
  if(beta < 0 or beta > 1 - gamma) return false;

  rec.t = t;
  rec.ambient = ambient_;
  rec.diffuse = diffuse_;
  rec.specular = specular_;
  rec.phong_exponent = 1;
  rec.normal = normal_;
  rec.pos = a_ + beta*(b_ - a_) + gamma*(c_ - a_);
  
  return true;  
}
