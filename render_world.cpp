#include "render_world.h"
#include "flat_shader.h"
#include "object.h"
#include "light.h"
#include "ray.h"

extern bool disable_hierarchy;

Render_World::Render_World()
    :background_shader(0),ambient_intensity(0),enable_shadows(true),
    recursion_depth_limit(3)
{}

Render_World::~Render_World()
{
    delete background_shader;
    for(size_t i=0;i<objects.size();i++) delete objects[i];
    for(size_t i=0;i<lights.size();i++) delete lights[i];
}

// Find and return the Hit structure for the closest intersection.  Be careful
// to ensure that hit.dist>=small_t.
Hit Render_World::Closest_Intersection(const Ray& ray)
{
    double min_t = std :: numeric_limits<double>::max();
    Hit currentObjHit = {0,0,0};
    //iterating through objects vector
    for (auto currObj : objects){
        Hit tempObjHit = currObj->Intersection(ray, -1);//Calling the intersection function of corresponding object
        //Ensures the object exists and the distance >= small_t, as well as making sure the distance is in the set boundary of min_t
        if (((tempObjHit.dist >= small_t) && tempObjHit.object) && tempObjHit.dist < min_t){
            min_t = tempObjHit.dist;
            currentObjHit = tempObjHit;
        }
    }
    return currentObjHit;
}

// set up the initial view ray and call
void Render_World::Render_Pixel(const ivec2& pixel_index)
{
    //TODO; // set up the initial view ray here
    Ray ray;
    ray.endpoint = camera.position;
    vec3 worldPos = camera.World_Position(pixel_index);
    ray.direction = (worldPos - ray.endpoint).normalized();
    vec3 color=Cast_Ray(ray,1);
    camera.Set_Pixel(pixel_index,Pixel_Color(color));
    /*Ray ray(camera.position, camera.World_Position(pixel_index) - ray.endpoint);
    vec3 color = Cast_Ray(ray, 1);
    camera.Set_Pixel(pixel_index, Pixel_Color(color));*/
}

void Render_World::Render()
{
    if(!disable_hierarchy)
        Initialize_Hierarchy();

    for(int j=0;j<camera.number_pixels[1];j++)
        for(int i=0;i<camera.number_pixels[0];i++)
            Render_Pixel(ivec2(i,j));
}

// cast ray and return the color of the closest intersected surface point,
// or the background color if there is no object intersection
vec3 Render_World::Cast_Ray(const Ray& ray,int recursion_depth)
{
    vec3 color;
    //TODO; // determine the color here
    Hit closestObjHit = {0, 0, 0};
    closestObjHit = Closest_Intersection(ray);
    vec3 normVec;
    if(closestObjHit.object != 0){
        //ray.Point(closestObjHit.dist) gives the intersection point
        normVec = closestObjHit.object->Normal(ray.Point(closestObjHit.dist), closestObjHit.part);
        color = closestObjHit.object->material_shader->Shade_Surface(ray, ray.Point(closestObjHit.dist), normVec, recursion_depth);
    }
    else{
        //no need for intersection point, only color
        color = background_shader->Shade_Surface(ray, color, color, recursion_depth);
    }
    return color;
}

void Render_World::Initialize_Hierarchy()
{
    TODO; // Fill in hierarchy.entries; there should be one entry for
    // each part of each object.

    hierarchy.Reorder_Entries();
    hierarchy.Build_Tree();
}
