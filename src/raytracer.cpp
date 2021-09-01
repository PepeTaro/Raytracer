#include "raytracer.h"

RayTracer::RayTracer(int num_col_pixels,int num_row_pixels,float left_edge,float right_edge,float bottom_edge,float top_edge):
  num_col_pixels_(num_col_pixels),num_row_pixels_(num_row_pixels),
  left_edge_(left_edge),right_edge_(right_edge),
  bottom_edge_(bottom_edge),top_edge_(top_edge)
{
  
}

void RayTracer::attachCamera(const Camera& camera,float focal_length){
  camera_ = camera;
  focal_length_ = focal_length;
}

#include <iostream>

Vector3 RayTracer::getDirection(int i,int j) const{
  // Maybe I should store (right_edge_ - left_edge_)/num_col_pixles as a member variable.
  float u = left_edge_ + (right_edge_ - left_edge_)*(i + 0.5)/num_col_pixels_;
  float v = bottom_edge_ + (top_edge_ - bottom_edge_)*(j + 0.5)/num_row_pixels_;
  
  return (-focal_length_*camera_.getW() + u*camera_.getU() + v*camera_.getV());
}
