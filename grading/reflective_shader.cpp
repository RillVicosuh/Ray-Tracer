#include "reflective_shader.h"
#include "ray.h"
#include "render_world.h"

vec3 Reflective_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
    vec3 color;
    //TODO; // determine the color

    color = shader->Shade_Surface(ray, intersection_point, normal, recursion_depth);
    vec3 view = ray.direction;
    vec3 reflected = view + 2 * dot(-1.0 * view, normal) * normal;
    Ray reflectedRay(intersection_point, reflected);
    if(recursion_depth != world.recursion_depth_limit){
        return color = (color * (1 - reflectivity)) + reflectivity * world.Cast_Ray(reflectedRay, recursion_depth + 1);
    }

    return color = (1 - reflectivity) * color;
}
