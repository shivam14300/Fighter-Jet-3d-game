#include "main.h"

#ifndef TREE_H
#define TREE_H


class Tree {
public:
    Tree() {}
    Tree(float x, float y, float z,color_t color);
    glm::vec3 position,rotation;
    glm::mat4 rotate;
    int val;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object;
    VAO *object1;
    VAO *object2;
};

#endif // TREE_H
