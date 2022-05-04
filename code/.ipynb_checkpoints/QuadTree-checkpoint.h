#ifndef QuadTree_H__
#define QuadTree_H__

#include <string>
#include <memory>
#include <vector>

class QuadTree{
public:
  QuadTree();
  ~QuadTree();
    
  int EmptyFunc();
    
private:
  int empty_count;
};

#endif // QuadTree_H__