#include "light.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"
#include "object.h"

//I ADDED THIS IN HERE
using namespace std;

vec3 Phong_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
    vec3 color;
    TODO; //determine the color
        
    //checklist Ia[X]   Id [ ]   Is[ ]  
    //I = Ia + Id + Is is phong shader
    //  = ambient + diffuse + specular
    //  = RaLa + RdLd * max(n * l, 0) + RsLs * max(v*r, 0)^alpha
    //  = color * light intensity
    //  + color * light intensity * max(normal to surface * vector towards light, 0)
    //  + color * light intensity * max(v*r, 0)^alpha
    //ambient is just applying matt color to the object
    //diffuse is adding darker and lighter areas
    //specular is adding specular lights which are really shiny small parts
    //view ray is the same as the intersecting ray but in the opposite direction, obv unit vector tho
    //light reflection equation is from class notes

    vec3 ambient, diffuse, specular, diffuse_intensity, specular_intensity;
    vec3 light_vector, view_ray, light_reflection, light_vector_normalized;
    //some var alpha, controls size of spec reflection, its actually specular_power

    ambient = color_ambient * world.ambient_color * world.ambient_intensity;

    for(unsigned int i = 0; i < world.lights.size(); i++){
        //for loop because there could be multiple light sources

        light_vector = world.lights.at(i)->position - intersection_point;
        light_vector_normalized = light_vector.normalized(); 
        diffuse_intensity = specular_intensity = world.lights.at(i)->Emitted_Light(light_vector * -1);
        light_reflection = (2 * (dot(normal,light_vector)) * normal) - light_vector;
        light_reflection = light_reflection.normalized();
        view_ray =  ray.direction.normalized() * -1;

        
        diffuse += color_diffuse * diffuse_intensity * max(dot(normal,light_vector_normalized), 0.0);
       specular += color_specular * specular_intensity * pow(max( dot(view_ray, light_reflection), 0.0), specular_power);

    }

    

    color = ambient + diffuse + specular;

    return color;
}
