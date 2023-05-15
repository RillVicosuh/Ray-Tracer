#include "sphere.h"
#include "ray.h"

// Determine if the ray intersects with the sphere
Hit Sphere::Intersection(const Ray& ray, int part) const
{
    //TODO;
    Hit sphereHit = {0, 0, 0};

    double a = dot(ray.direction, ray.direction);
    double b = 2 * dot(ray.direction, (ray.endpoint - center));
    double c = dot((ray.endpoint - center), (ray.endpoint - center)) - radius * radius;
    double d = (b * b) - (4 * a * c);

    if (d >= 0){
        double t1 = ((-b) - sqrt(d))/(2 * a);
        double t2 = ((-b) + sqrt(d))/(2 * a);
        if (t2 < t1 && t2 >= small_t){
            sphereHit.dist = t2;
            sphereHit.object = this;
        }
        else if (t1 <= t2 && t1 >= small_t){
            sphereHit.dist = t1;
            sphereHit.object = this;
        }
    }
    return sphereHit;
}

vec3 Sphere::Normal(const vec3& point, int part) const
{
    vec3 normal;
    TODO; // compute the normal direction
    normal = (point - center).normalized();
    return normal;
}

Box Sphere::Bounding_Box(int part) const
{
    Box box;
    TODO; // calculate bounding box
    return box;
}
