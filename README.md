# Quadtree Spacial Detection
A CSPB2270 final projects by Nathan Hutchins - nahu7321


<hr>

### What is a Quadtree
Quadtrees are a data structure where each internal node has exactly four children nodes. They are often used to partition a two-dimensional space by recursivley subdividing the space into four regions. https://en.wikipedia.org/wiki/Quadtree

### What can a Quadtree be used for
As mentioned above, a Quadtree data structure can be used to represent a 2D space. This can then be used as a spatial detection data structure that allows for quick and efficent look up times of other objects within a defined region. This project file can be used to create a 2D region in space, populate that with particles that represent objects within the 2D space. Then query for objects within a user defined range. An interesting algorithm that can really take advantage of Quadtrees is the Boids Algorithm. Boids are a simple flocking simulation algorithm that needs information from all objects surronding a current object. Which can be effienctly found using a Quadtree. https://en.wikipedia.org/wiki/Boids

### Installation
Clone the git repo.
```bash
git clone https://github.com/cu-cspb-2270-Spring-2022/final-project-nhutchins96.git
```
Change into the final-project-nhutchins96/build/ directory and run cmake
```bash
cd final-project-nhutchins96/build/
cmake ..
```
Then run make
```bash
make
```
Lastly run the test file to see if all tests pass correctly and the installation was complete
```
./run_tests
```



### Usage
How to build a tree:
```c++
#include "code/QuadTree.h"

// Build a tree with a center point at x=5, y=6, and a width and height of 10x10
QuadTree myTree(5,6,10);
```

How to insert a particle into a tree:
```
// Create a particle at position 1,2
shared_ptr<particle> p(new particle);
p->x = 1;
p->y = 2;

// Insert your particle/object
myTree.insert(p);
```

How to query a range:
```
// First needs a range box (example creating a range around particle p with a 2x2 range
shared_ptr<BoundingBox> range(new BoundingBox(p.x, p.y, 2);
                              
// A vector to store the found objects within the range box                        
vector<shared_ptr<particle>> found;

// Query for objects within range and save in found                 
myTree.query(range, found);
```

### Reference
Cmake files provided my University of Colorado Boulder
