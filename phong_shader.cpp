#include "light.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"
#include "object.h"

vec3 Phong_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
    //TODO; //determine the color
    vec3 color;
    vec3 ambinet;
    vec3 diffuse;
    vec3 specular;
    vec3 view = -(ray.direction);//the view ray is the opposite of ray
    color = world.ambient_color * world.ambient_intensity * color_ambient;

    for (int i = 0; i < world.lights.size(); i++){

        //calculating light direction and reflected array
        vec3 lightDir = world.lights[i]->position - intersection_point;
        vec3 reflected = ((2 * dot(lightDir, normal) * normal) - lightDir).normalized();

        if(world.enable_shadows){
            Hit currObj = {0, 0, 0};
            Ray shadowRay(intersection_point, lightDir);
            currObj = world.Closest_Intersection(shadowRay);
            
            //This will return without diffuse or specular light
            if(currObj.object && currObj.dist < lightDir.magnitude()){
                return color;
            }
        }
        
        //calculation diffusion and specular light
        diffuse = world.lights[i]->Emitted_Light(lightDir) * color_diffuse * std::max(dot(normal, lightDir.normalized()), 0.0);
        specular = world.lights[i]->Emitted_Light(lightDir) * color_specular * std::pow(std::max(dot(view, reflected), 0.0), specular_power);
        //Phong Reflection Model = Ambient + Diffusion + Specular
        color += diffuse + specular;
    }

    return color;
}
