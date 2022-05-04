#ifndef QuadTree_H__
#define QuadTree_H__

#include <string>
#include <memory>
#include <vector>

using namespace std;

// This will be the point on the screen where the object is located
struct particle {
  // Positions on the x and y axis of the screen
  float x = -1;
  float y = -1;
};

// Used to represent the 2D space this section is taking up
class BoundingBox {
public:
  // builds the box with the correct dimenisions
  BoundingBox(float x, float y, float width);
  ~BoundingBox();

  // The center of the box
  particle center;

  // The half distance of the cube
  float half_width = -1; 

  // Check if the particle is within this box
  bool contains(shared_ptr<particle> p);

  // Check if the range and current box overlap in anyway
  bool intersects(shared_ptr<BoundingBox> range);
};


class QuadTree{
public:
  QuadTree(float x, float y, float width);
  ~QuadTree();

  // How many particles are allowed in tree before splitting
  const int CAPACITY = 4;

  // The current particle amount in the node
  int particle_count = 0;

  // Represent the boundary of this quad tree node
  shared_ptr<BoundingBox> boundary;

  // Pointers to particles in this quad tree node
  vector<shared_ptr<particle>> particles;

  // Children nodes
  shared_ptr<QuadTree> top_left = NULL;
  shared_ptr<QuadTree> top_right = NULL;
  shared_ptr<QuadTree> bottom_left = NULL;
  shared_ptr<QuadTree> bottom_right = NULL;
    
  // Add and find nodes within the tree
  bool insert(shared_ptr<particle> p);
  void query(shared_ptr<BoundingBox> range, vector<shared_ptr<particle>>& found);
    
private:
  // Split the node when the capacity overflows
  void subdivide();
};

#endif // QuadTree_H__