#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <vector>
#include "camera.h"
#include "vector3.h"
#include "light.h"
#include "color.h"
#include "surface.h"
#include "const.h"
#include "utils.h"

static Color ambinet_intensity = 1.5*Color(1.0,1.0,1.0);

class RayTracer{
private:
  Camera camera_;
  float focal_length_;
  float left_edge_,right_edge_;
  float bottom_edge_,top_edge_;
  int num_col_pixels_,num_row_pixels_;
  std::vector<Surface*> surfaces_;
  std::vector<Light*> lights_;
  std::vector<Color*> ambients_;
  
public:
  RayTracer(int num_col_pixels,int num_row_pixels,float left_edge,float right_edge,float bottom_edge,float top_edge);
  void attachCamera(const Camera& camera,float focal_length);
  Vector3 getDirection(int i,int j) const;

  Color AddAmbientToColor(const Color& color,const Color& ambient_coeff,const Color* ambient_intensity) const;
  Color AddShadowToColor(const Color& color,const Vector3& dir,const Light* light,const records& rec) const;
  Color AddMirrorReflection(const Color& color,const Vector3& dir,const records& rec,int recursion_depth) const;
  Color Raycolor(const Vector3& dir,const Vector3& eye,float t0,float t1,int recursion_depth) const;
  
  void addSurface(Surface* surface);
  void addLight(Light* light);
  void addAmbient(Color* ambient);
  
};//class RayTracer

#endif// RAYTRACER_H
