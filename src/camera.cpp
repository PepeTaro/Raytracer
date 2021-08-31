#include "camera.h"

Camera::Camera(const Vector3& eye,const Vector3& view,const Vector3& up){
  e_ = eye;
  w_ = -1.0*view.getNormalize();
  u_ = cross(up,w_).getNormalize();
  v_ = cross(w_,u_);
}

Vector3 Camera::getE() const{return e_;}
Vector3 Camera::getU() const{return u_;}
Vector3 Camera::getV() const{return v_;}
Vector3 Camera::getW() const{return w_;}
