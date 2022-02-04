#include "reflective_shader.h"
#include "ray.h"
#include "render_world.h"

vec3 Reflective_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
    vec3 color = shader->Shade_Surface(ray, intersection_point, normal, recursion_depth);
    TODO; // determine the color
    //from notes, reflectivity is the variable k
    //for recursion we do
        //return color = (1-k) * color + k * cast_ray(reflected ray)
    //if we reach the recusion depth, we want to stop, only return color
        //which means -> return color = (1-k * color)
    vec3 u_vector = ray.direction;
    vec3 reflected_dir = -2 * dot(normal,u_vector) * normal + u_vector;
    Ray reflected_ray = Ray(intersection_point, reflected_dir.normalized()); 

    if(recursion_depth >= world.recursion_depth_limit){
        //only return the first part
        return color = (1 - reflectivity) * color;
    }
    //otherwise we can continue the recursion
    else{
        return color = (1-reflectivity) * color + reflectivity * world.Cast_Ray(reflected_ray, ++recursion_depth);
    }
}
