#include "QuadTree.h"
#include <iostream>

// Constructor
QuadTree::QuadTree(float x, float y, float width){
    // Create and set the box
    shared_ptr<BoundingBox> new_boundary(new BoundingBox(x, y, width));
    this->boundary = new_boundary;
}

// Deconstructor
QuadTree::~QuadTree(){
    // Using shared_ptr so don't need
}

bool QuadTree::insert(shared_ptr<particle> p){
    /* Insert a new particle at position x, y in the correct quadtree */

    // Skip this node if not in boundary
    if (!this->boundary->contains(p)){
        return false;
    }

    // Directly insert into this node if room and if there are no children
    if (this->particle_count < CAPACITY && this->top_left == NULL){
        this->particles.push_back(p);
        this->particle_count++;
        return true;
    }
    else{
        // Check if need to split this node
        if (this->particle_count >= CAPACITY){
            this->subdivide();
        }

        // Try to insert into one of the new child nodes
        if (this->top_left->insert(p)){
            return true;
        }
        if (this->top_right->insert(p)){
            return true;
        }
        if (this->bottom_left->insert(p)){
            return true;
        }
        if (this->bottom_right->insert(p)){
            return true;
        }
    }
    // Should not reach here
    return false;
}

void QuadTree::subdivide(){
    /* Split the tree into four sub trees and moves all current particles into children */

    // Get current center position of box
    float x = this->boundary->center.x;
    float y = this->boundary->center.y;

    // Get new width of sub boxes 
    float new_width = this->boundary->half_width;
    float new_xy = new_width / 2; // Distance from new center

    // Split the current tree into 4 by creating 4 children nodes
    shared_ptr<QuadTree> top_left(new QuadTree(x - new_xy, y + new_xy, new_width));
    this->top_left = top_left;

    shared_ptr<QuadTree> top_right(new QuadTree(x + new_xy, y + new_xy, new_width));
    this->top_right = top_right;

    shared_ptr<QuadTree> bottom_left(new QuadTree(x - new_xy, y - new_xy, new_width));
    this->bottom_left = bottom_left;

    shared_ptr<QuadTree> bottom_right(new QuadTree(x + new_xy, y - new_xy, new_width));
    this->bottom_right = bottom_right;

    // Now loop through all the current nodes and move them to the children
    for (int i = 0; i < CAPACITY; i++)
    {
        // Get current particle
        shared_ptr<particle> p = this->particles[i];

        // Try to add to each child (skip the loop iteration once added)
        if (this->top_left->insert(p)){
            continue;
        }
        if (this->top_right->insert(p)){
            continue;
        }
        if (this->bottom_left->insert(p)){
            continue;
        }
        if (this->bottom_right->insert(p)){
            continue;
        }
    }
    // Now clear parent node vector
    this->particles.clear();
    this->particle_count = 0; // This is fine, because insert checks for children

    return;
}

void QuadTree::query(shared_ptr<BoundingBox> range, vector<shared_ptr<particle>>& found){
    /* Find all particles within the range given and save them in the found vector */

    // Return if the range does not intersect this node
    if (!this->boundary->intersects(range)){
        return;
    }

    // Loop through particles
    for(int i=0; i<this->particle_count; i++){
        // ignore self 
        if(range->center.x == this->particles[i]->x && range->center.y == this->particles[i]->y){
            continue;
        }

        // Add only the particles that contain within the range
        if(range->contains(this->particles[i])){
            found.push_back(this->particles[i]);
        }
    }

    // Return if no children
    if (!this->top_left){
        return;
    }

    // Keep searching down children paths
    this->top_left->query(range, found);
    this->top_right->query(range, found);
    this->bottom_left->query(range, found);
    this->bottom_right->query(range, found);

    // Return the final amount
    return;
}


/////////////////////////////
/// Bounding Box Functions///
/////////////////////////////
// Constructor
BoundingBox::BoundingBox(float x, float y, float width){
    // Populate the boundary with the correct details
    this->center.x = x;
    this->center.y = y;
    this->half_width = width / 2;
}

BoundingBox::~BoundingBox(){
}

bool BoundingBox::contains(shared_ptr<particle> p){
    /* Returns true if the particle is within the boundary of the current box */

    // Get the distance from all edges
    float right_edge = this->center.x + this->half_width;
    float left_edge = this->center.x - this->half_width;
    float up_edge = this->center.y + this->half_width;
    float bottom_edge = this->center.y - this->half_width;

    // Can't have negative
    if(p->x < 0 || p->y < 0){
        return false;
    }

    // Check bottom edge 
    if(p->y < bottom_edge){
        return false;
    }

    // Check top edge
    if(p->y > up_edge){
        return false;
    }

    // Check left edge 
    if(p->x < left_edge){
        return false;
    }

    // Check right edge
    if(p->x > right_edge){
        return false;
    }

    // It is within the boundary
    return true;
}

bool BoundingBox::intersects(shared_ptr<BoundingBox> range){
    /* Returns true if the range overlaps with the current box object */

    // Get each corner of the range box
    shared_ptr<particle> top_left(new particle);
    top_left->x = range->center.x - range->half_width;
    top_left->y = range->center.y + range->half_width;

    shared_ptr<particle> top_right(new particle);
    top_right->x = range->center.x + range->half_width;
    top_right->y = range->center.y + range->half_width;

    shared_ptr<particle> bottom_left(new particle);
    bottom_left->x = range->center.x - range->half_width;
    bottom_left->y = range->center.y - range->half_width;

    shared_ptr<particle> bottom_right(new particle);
    bottom_right->x = range->center.x + range->half_width;
    bottom_right->y = range->center.y - range->half_width;

    // Check if any range corner is within the current box
    if (this->contains(top_left) || this->contains(top_right) || 
    this->contains(bottom_left) || this->contains(bottom_right)){
        return true;
    }

    // Check if the range encompasses the current box
    // if y is above and below current box 
    if (top_right->y >= (this->center.y + this->half_width) && 
        bottom_right->y <= (this->center.y - this->half_width)){
        // At least one x has to be in range
        if (top_right->x <= (this->center.x + this->half_width) || 
            top_left->x >= (this->center.x - this->half_width)){
                return true;
            }
        
        // Check if x encompasses too
        if (top_right->x >= (this->center.x + this->half_width) && 
        top_left->x <= (this->center.x - this->half_width)){
            return true;
        }
    }
    
    // if x is left and right of the current box 
    if (top_right->x >= (this->center.x + this->half_width) && 
        top_left->x <= (this->center.x - this->half_width)){
        // At least one y has to be in range OR Y has to encompass too (but this has been checked above)
        if (top_right->y <= (this->center.y + this->half_width) || 
            bottom_right->y >= (this->center.y - this->half_width)){
                return true;
            }
    }
    return false;
}