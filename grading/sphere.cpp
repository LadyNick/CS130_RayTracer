#include "sphere.h"
#include "ray.h"

using namespace std;

// Determine if the ray intersects with the sphere
Hit Sphere::Intersection(const Ray& ray, int part) const
{
    TODO;
    //ray holds vec3 endpoint and direction
    //sphere holds vec3 center & double radius
    double b, c, t1, t2;
    b = dot( (ray.direction * 2), (ray.endpoint - center)) ;
    c = dot( (ray.endpoint - center), (ray.endpoint - center)) - pow(radius,2);
    t1 = (-b + sqrt( pow(b,2) - 4*c)) / 2;
    t2 = (-b - sqrt( pow(b,2) - 4*c)) / 2;

if((pow(b,2) - 4*c) > 0) {
  if(min(t1,t2) > 0) {
    return{this,min(t1,t2),part}; //what you have already
  }
  else if(t2 > 0) {
    return{this, t2, part}; //with t2
  }
  else if(t1 > 0) {
    return{this, t1, part}; //with t1
  }
}

    return {NULL,0.0,part};
}

vec3 Sphere::Normal(const vec3& point, int part) const
{
    vec3 normal;
    TODO; // compute the normal direction
    normal = (point - center);
    normal = normal.normalized();

    return normal;
}

Box Sphere::Bounding_Box(int part) const
{
    Box box;
    TODO; // calculate bounding box
    return box;
}
