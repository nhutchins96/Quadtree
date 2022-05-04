#include <gtest/gtest.h>
#include "../code/QuadTree.h"
#include "build_tests.cpp"
#include <string>

using namespace std;

class test_QuadTree : public ::testing::Test {
};

TEST_F(test_QuadTree, TestConstructor){
	// Create tree
    QuadTree myTree(5,6,10);

	// Test box was created correctly
    ASSERT_EQ(5, myTree.boundary->center.x);
    ASSERT_EQ(6, myTree.boundary->center.y);
    ASSERT_EQ(5, myTree.boundary->half_width);
	ASSERT_EQ(0, myTree.particle_count);
	ASSERT_EQ(4, myTree.CAPACITY);

    // All children should be NULL
	ASSERT_FALSE(myTree.top_left);
	ASSERT_FALSE(myTree.top_left);
	ASSERT_FALSE(myTree.top_left);
	ASSERT_FALSE(myTree.top_left);
}

TEST_F(test_QuadTree, TestInsert){
	// Test inserting into empty node
    shared_ptr<QuadTree> myTree = build_empty_tree();
    ASSERT_EQ(myTree->particle_count, 0);

    // Test with 4 particles added (just before split)
    myTree = build_tree1();
    ASSERT_EQ(myTree->particle_count, 4);
}

TEST_F(test_QuadTree, TestContain){
    // Test if a particle would be in the tree boundary
    QuadTree myTree(2,2,3);
	shared_ptr<particle> p(new particle);
	p->y = 2;
	p->x = 2;
	bool test = myTree.boundary->contains(p);
    ASSERT_EQ(test, true);
}

TEST_F(test_QuadTree, Intersection){
    // Test if the range interescts with the node bounding box
    QuadTree myTree(2,2,2);
    shared_ptr<BoundingBox> range(new BoundingBox(2,4,4));

    bool answer = myTree.boundary->intersects(range);
    ASSERT_EQ(answer, true);
}

/* Insert 5 particles which causes a subdivide. Then query "bubbles the shark" for
    other particles ("fish") within a 4x4 range */
TEST_F(test_QuadTree, Image1){
    shared_ptr<QuadTree> myTree = build_tree2();
    ASSERT_EQ(myTree->particle_count, 0);
    ASSERT_EQ(myTree->top_left->particle_count, 2);
    ASSERT_EQ(myTree->top_right->particle_count, 1);
    ASSERT_EQ(myTree->bottom_left->particle_count, 1);
    ASSERT_EQ(myTree->bottom_right->particle_count, 1);

    // Get bubbles the shark, then query for fish in his food range (4x4)
    shared_ptr<particle> bubbles_the_shark = myTree->top_left->particles[1];
    ASSERT_EQ(bubbles_the_shark->x, 4);
    ASSERT_EQ(bubbles_the_shark->y, 9);

    shared_ptr<BoundingBox> bubblesRange(new BoundingBox(bubbles_the_shark->x, bubbles_the_shark->y, 4));
    vector<shared_ptr<particle>> food;
    myTree->query(bubblesRange, food);
    ASSERT_EQ(food.size(), 1);
}

/* Build a tree with a second layer of subdivision in the bottom right.
    Then move bubbles down to the busy area and querey 
    for "fish" (particles) in range. */
TEST_F(test_QuadTree, Image2){
    shared_ptr<QuadTree> myTree = build_tree3();
    ASSERT_EQ(myTree->bottom_right->particle_count, 0);
    ASSERT_EQ(myTree->bottom_right->top_left->particle_count, 3);
    ASSERT_EQ(myTree->bottom_right->top_right->particle_count, 1);
    ASSERT_EQ(myTree->bottom_right->bottom_left->particle_count, 1);

    // Now add bubbles and see what food (particles) are within range
    shared_ptr<particle> bubbles(new particle);
    bubbles->x = 7;
    bubbles->y = 6;
    myTree->insert(bubbles);

    // Give bubbles a food range and see what's in it
    shared_ptr<BoundingBox> bubblesRange(new BoundingBox(bubbles->x, bubbles->y, 4));
    vector<shared_ptr<particle>> food;
    myTree->query(bubblesRange, food);
    ASSERT_EQ(food.size(), 4);
}

/* Build a tree with a third layer of subdivision in the bottom left.
    Then move bubbles down to the busy area and querey 
    for "fish" (particles) in range. */
TEST_F(test_QuadTree, Image3){
    // Build tree
    shared_ptr<QuadTree> myTree = build_tree4();
    
    // First layer should have no particles
    ASSERT_EQ(myTree->bottom_left->particle_count, 0);

    // Second layer should have particles except the bottom left->bottom_right tree
    ASSERT_EQ(myTree->bottom_left->top_left->particle_count, 2);
    ASSERT_EQ(myTree->bottom_left->top_right->particle_count, 1);
    ASSERT_EQ(myTree->bottom_left->bottom_left->particle_count, 1);

    // Check the third layer (bottom_left->bottom_right)
    ASSERT_EQ(myTree->bottom_left->bottom_right->particle_count, 0);
    ASSERT_EQ(myTree->bottom_left->bottom_right->bottom_left->particle_count, 1);
    ASSERT_EQ(myTree->bottom_left->bottom_right->bottom_right->particle_count, 2);
    ASSERT_EQ(myTree->bottom_left->bottom_right->top_left->particle_count, 1);
    ASSERT_EQ(myTree->bottom_left->bottom_right->top_right->particle_count, 1);

    // Now add bubbles at (2,2) and querey for fish within a 4x4 range
    shared_ptr<particle> bubbles(new particle);
    bubbles->x = 2;
    bubbles->y = 2;
    myTree->insert(bubbles);
    shared_ptr<BoundingBox> bubblesRange(new BoundingBox(bubbles->x, bubbles->y, 4));
    vector<shared_ptr<particle>> food;
    myTree->query(bubblesRange, food);
    ASSERT_EQ(food.size(), 9);
}