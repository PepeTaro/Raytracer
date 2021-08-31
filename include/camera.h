#ifndef CAMERA_H
#define CAMERA_H

#include "vector3.h"

class Camera{
private:
  Vector3 e_,u_,v_,w_;
public:
  Camera(const Vector3& eye=Vector3(0,0,0),const Vector3& view=Vector3(0,0,-1),const Vector3& up=Vector3(0,1,0));

  Vector3 getE() const;
  Vector3 getU() const;
  Vector3 getV() const;
  Vector3 getW() const;
  
};//class Camera

#endif// CAMERA_H
