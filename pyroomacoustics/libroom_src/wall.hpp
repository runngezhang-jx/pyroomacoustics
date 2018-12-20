#ifndef __CWALL_H__
#define __CWALL_H__

#include <string>
#include <Eigen/Dense>

extern float libroom_eps;

#define WALL_ISECT_NONE        -1  // if there is no intersection
#define WALL_ISECT_VALID        0  // if the intersection striclty between the segment endpoints and in the polygon interior
#define WALL_ISECT_VALID_ENDPT  1  // if the intersection is at endpoint of segment
#define WALL_ISECT_VALID_BNDRY  2  // if the intersection is at boundary of polygon
#define ENDPOINT_BOUNDARY       3  // if both the above are true


template<size_t D>
class Wall
{
  public:
    enum Isect { // The different cases for intersections
      NONE = -1, // - There is no intersection
      VALID = 0, // - There is a valid intersection
      ENDPT = 1, // - The intersection is on the endpoint of the segment
      BNDRY = 2 // - The intersection is on the boundary of the wall
    };

    int dim;
    float absorption;
    std::string name;
    
    Eigen::Matrix<float, D, 1>  normal;
    Eigen::Matrix<float, D, Eigen::Dynamic> corners;

    /* for 3D wall, provide local basis for plane of wall */
    Eigen::Matrix<float, D, 1> origin;
    Eigen::Matrix<float, D, 2> basis;
    Eigen::Matrix<float, 2, Eigen::Dynamic> flat_corners;

    // Constructor
    Wall(
        const Eigen::Matrix<float, D, Eigen::Dynamic> &_corners,
        float _absorption,
        const std::string &_name
        );
    Wall(
        const Eigen::Matrix<float, D, Eigen::Dynamic> &_corners,
        float _absorption
        ) : Wall(_corners, _absorption, "") {}

    // methods
    float area();  // compute the area of the wall
    int intersection(  // compute the intersection of line segment (p1 <-> p2) with wall
        const Eigen::Matrix<float,D,1> &p1,
        const Eigen::Matrix<float,D,1> &p2,
        Eigen::Ref<Eigen::Matrix<float,D,1>> intersection
        );
    int intersects(
        const Eigen::Matrix<float,D,1> &p1,
        const Eigen::Matrix<float,D,1> &p2
        );

    int reflect(
        const Eigen::Matrix<float,D,1> &p,
        Eigen::Ref<Eigen::Matrix<float,D,1>> p_reflected
        );
    int side(const Eigen::Matrix<float,D,1> &p);
    bool same_as(const Wall & that);

  private:
    int _intersection_segment_3d( // intersection routine specialized for 3D
      const Eigen::VectorXf & a1,
      const Eigen::VectorXf & a2,
      Eigen::Ref<Eigen::VectorXf> intersection);

}; 

#include "wall.cpp"

#endif // __CWALL_H__
