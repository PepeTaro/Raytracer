#ifndef UTILS_H
#define UTILS_H

inline float max(float a,float b){
  if(a < b) return b;
  else return a;
}

inline float min(float a,float b){
  if(a < b) return a;
  else return b;
}

#endif// UTILS_H
