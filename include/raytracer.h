#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "camera.h"
#include "vector3.h"

class RayTracer{
private:
  Camera camera_;
  float focal_length_;
  float left_edge_,right_edge_;
  float bottom_edge_,top_edge_;
  int num_col_pixels_,num_row_pixels_;
public:
  RayTracer(int num_col_pixels,int num_row_pixels,float left_edge,float right_edge,float bottom_edge,float top_edge);
  void attachCamera(const Camera& camera,float focal_length);
  Vector3 getDirection(int i,int j) const;
  
};//class RayTracer

#endif// RAYTRACER_H
