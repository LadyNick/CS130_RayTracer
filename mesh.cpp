#include "mesh.h"
#include <fstream>
#include <string>
#include <limits>

// Consider a triangle to intersect a ray if the ray intersects the plane of the
// triangle with barycentric weights in [-weight_tolerance, 1+weight_tolerance]
static const double weight_tolerance = 1e-4;

// Read in a mesh from an obj file.  Populates the bounding box and registers
// one part per triangle (by setting number_parts).
void Mesh::Read_Obj(const char* file)
{
    std::ifstream fin(file);
    if(!fin)
    {
        exit(EXIT_FAILURE);
    }
    std::string line;
    ivec3 e;
    vec3 v;
    box.Make_Empty();
    while(fin)
    {
        getline(fin,line);

        if(sscanf(line.c_str(), "v %lg %lg %lg", &v[0], &v[1], &v[2]) == 3)
        {
            vertices.push_back(v);
            box.Include_Point(v);
        }

        if(sscanf(line.c_str(), "f %d %d %d", &e[0], &e[1], &e[2]) == 3)
        {
            for(int i=0;i<3;i++) e[i]--;
            triangles.push_back(e);
        }
    }
    number_parts=triangles.size();
}

// Check for an intersection against the ray.  See the base class for details.
Hit Mesh::Intersection(const Ray& ray, int part) const
{
    TODO;
    //there is a vector of vertices and a vector of triangles in the base class
    //vector<vec3> vertices         this holds the vertices, x,y,z's for each point         
    //vector<ivec3> triangles       this holds the triangles, the points used for each triangle
    Hit returning_hit;
    returning_hit.object = NULL;
    returning_hit.dist = 0;
    returning_hit.part = -1;

    if(part >= 0){
        if(Intersect_Triangle(ray, part, returning_hit.dist)){
            returning_hit.object = this;
            returning_hit.part = part;
        }
    }
    else{
        returning_hit.dist = __DBL_MAX__;
        for (unsigned i = 0; i < triangles.size(); i++) {
            double temp;
            if (Intersect_Triangle(ray, i, temp)) {
                if (temp < returning_hit.dist) {
                    returning_hit.object = this;
                    returning_hit.dist = temp;
                    returning_hit.part = i;
                }
            }
        }        


    }
    return returning_hit;
}

// Compute the normal direction for the triangle with index part.
vec3 Mesh::Normal(const vec3& point, int part) const
{
    assert(part>=0);
    TODO;
    ivec3 tri_shape = triangles[part];   //part refers to which triangle I assume
    vec3 point_a = vertices[tri_shape[0]];  //this holds point A
    vec3 point_b = vertices[tri_shape[1]];  //point B
    vec3 point_c = vertices[tri_shape[2]];  //point C

    //from 1/27 notes
    vec3 seg_ab = point_b - point_a;
    vec3 seg_ac = point_c - point_a;
    vec3 normal = cross(seg_ab, seg_ac).normalized();

    return normal;
}

// This is a helper routine whose purpose is to simplify the implementation
// of the Intersection routine.  It should test for an intersection between
// the ray and the triangle with index tri.  If an intersection exists,
// record the distance and return true.  Otherwise, return false.
// This intersection should be computed by determining the intersection of
// the ray and the plane of the triangle.  From this, determine (1) where
// along the ray the intersection point occurs (dist) and (2) the barycentric
// coordinates within the triangle where the intersection occurs.  The
// triangle intersects the ray if dist>small_t and the barycentric weights are
// larger than -weight_tolerance.  The use of small_t avoid the self-shadowing
// bug, and the use of weight_tolerance prevents rays from passing in between
// two triangles.
bool Mesh::Intersect_Triangle(const Ray& ray, int tri, double& dist) const
{
    TODO;
    //tri is providing which triangle, and we want to make a vertice for each pt
    ivec3 tri_shape = triangles[tri];
    vec3 point_a = vertices[tri_shape[0]];
    vec3 point_b = vertices[tri_shape[1]];
    vec3 point_c = vertices[tri_shape[2]];
    vec3 intersect_point = ray.Point(dist); //P = e + tu  == endpoint + dist * direction

    //Hit test = Plane(point_a,Normal(point_a, tri)).Intersection(ray,tri);
    //if(!test.object){ return false; }


    vec3 ray_direction = ray.direction.normalized();
    vec3 seg_ab = point_b - point_a;
    vec3 seg_ac = point_c - point_a;
    vec3 normal = intersect_point - point_a;
    double area_abc = dot(cross(ray_direction,seg_ab), seg_ac); 

    if(area_abc == 0){
        return false;
    }

    double distance = -(dot(cross(seg_ab,seg_ac), normal) / dot(cross(seg_ab,seg_ac), ray_direction));

if(distance > small_t){
    double beta = dot(cross(seg_ac, ray_direction), normal) / area_abc;
    double gamma = dot(cross(ray_direction, seg_ab), normal) / area_abc;
    double alpha = 1 - gamma - beta;

    //Point P --> P = alpha * A + beta * B + gamma * C
    if( (beta > -weight_tolerance) && (gamma > -weight_tolerance) && (alpha > -weight_tolerance)){
        dist = distance;
        return true;
    }
}
    return false;
}

// Compute the bounding box.  Return the bounding box of only the triangle whose
// index is part.
Box Mesh::Bounding_Box(int part) const
{
    Box b;
    TODO;
    return b;
}
