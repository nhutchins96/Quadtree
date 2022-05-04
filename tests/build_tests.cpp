#include <gtest/gtest.h>
#include "../code/QuadTree.h"
#include <string>

using namespace std;

shared_ptr<QuadTree> build_empty_tree(){
    // Build a 10x10 tree with a center around the (5,5) position
    shared_ptr<QuadTree> empty_tree(new QuadTree(5,5,10));
    return empty_tree;
}

shared_ptr<QuadTree> build_tree1(){
    // A tree with 4 points, one in each section, no children
    shared_ptr<QuadTree> tree1 = build_empty_tree();

    // Create the 4 particles
    shared_ptr<particle> p1(new particle);
    p1->x = 3;
    p1->y = 3;
    tree1->insert(p1); // Bottom Left

    shared_ptr<particle> p2(new particle);
    p2->x = 7;
    p2->y = 3;
    tree1->insert(p2); // Bottom right

    // Create the 4 particles
    shared_ptr<particle> p3(new particle);
    p3->x = 3;
    p3->y = 7;
    tree1->insert(p3); // Top Left

    // Create the 4 particles
    shared_ptr<particle> p4(new particle);
    p4->x = 7;
    p4->y = 7;
    tree1->insert(p4); // Top right

    return tree1;
}

shared_ptr<QuadTree> build_tree2(){
    // A tree with 4 points, one in each section, no children
    shared_ptr<QuadTree> tree2 = build_tree1();

    // Add a 5th particle (named bubbles for our fish example) which will cause a subdivision
    shared_ptr<particle> bubbles_the_shark(new particle);
    bubbles_the_shark->x = 4;
    bubbles_the_shark->y = 9;
    tree2->insert(bubbles_the_shark); // Top Left

    return tree2;
}

shared_ptr<QuadTree> build_tree3(){
    // A tree with 4 particles, one in each section, no children, no bubbles the shark
    shared_ptr<QuadTree> tree3 = build_tree1();

    // Insert new fish (all going bottom right to cause a subdivide)
    shared_ptr<particle> p(new particle);
    p->x = 6;
    p->y = 4.5;
    tree3->insert(p); // Bottom right

    shared_ptr<particle> p1(new particle);
    p1->x = 7;
    p1->y = 4;
    tree3->insert(p1); // Bottom right

    shared_ptr<particle> p2(new particle);
    p2->x = 9;
    p2->y = 4;
    tree3->insert(p2); // Bottom right

    shared_ptr<particle> p3(new particle);
    p3->x = 6;
    p3->y = 2;
    tree3->insert(p3); // Bottom right

    return tree3;
}

shared_ptr<QuadTree> build_tree4(){
    // Continue with the full tree above
    shared_ptr<QuadTree> tree4 = build_tree3();

    // Insert new fish (all going bottom left to cause a subdivide, the bottom right of left)
    shared_ptr<particle> p(new particle);
    p->x = 1;
    p->y = 1.5;
    tree4->insert(p); 

    shared_ptr<particle> p1(new particle);
    p1->x = 1.5;
    p1->y = 3;
    tree4->insert(p1); 

    shared_ptr<particle> p2(new particle);
    p2->x = 2;
    p2->y = 4;
    tree4->insert(p2); 

    shared_ptr<particle> p3(new particle);
    p3->x = 3;
    p3->y = 0.5;
    tree4->insert(p3);

    shared_ptr<particle> p4(new particle);
    p4->x = 3;
    p4->y = 2;
    tree4->insert(p4);

    shared_ptr<particle> p5(new particle);
    p5->x = 4;
    p5->y = 0.5;
    tree4->insert(p5);

    shared_ptr<particle> p6(new particle);
    p6->x = 4;
    p6->y = 1;
    tree4->insert(p6);

    shared_ptr<particle> p7(new particle);
    p7->x = 4;
    p7->y = 2;
    tree4->insert(p7);

    return tree4;
}
