#pragma once
#include <la.h>
#include <scene/geometry/geometry.h>
#include <scene/geometry/bbox.h>

class Geometry;
class Material;

class Intersection
{
public:
    Intersection();

    glm::vec3 point;      //The place at which the intersection occurred
    glm::vec3 normal;     //The surface normal at the point of intersection
    glm::vec3 tangent;    //The surface tangent at the POI
    glm::vec3 bitangent;  //The surface bitangent at the POI
    float t;              //The parameterization for the ray (in world space) that generated this intersection.
                          //t is equal to the distance from the point of intersection to the ray's origin if the ray's direction is normalized.
    Geometry* object_hit; //The object that the ray intersected, or NULL if the ray hit nothing.

    glm::vec3 texture_color;

    glm::vec3 ToLocalNormalCoordinate(const glm::vec3& w_world);

    glm::vec3 ToWorldNormalCoordinate(const glm::vec3& w_local);
};

class BVHNode
{
public:
    BVHNode();

    BBox bBox;
    BVHNode *left;
    BVHNode *right;

    int depth;
    QList<Geometry*> geometryAttached;//sorted!!

    void createBVH(int dep);

    static bool compareNodeX(Geometry* &a, Geometry* &b);
    static bool compareNodeY(Geometry* &a, Geometry* &b);
    static bool compareNodeZ(Geometry* &a, Geometry* &b);

    static BVHNode* buildBVHTree(QList<Geometry*> objects);
    static void releaseTree(BVHNode* root);

    Intersection getIntersection(const Ray &r);

    ~BVHNode(){}
};