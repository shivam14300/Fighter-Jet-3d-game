#include "main.h"

#ifndef POINT_H
#define POINT_H


class Point {
public:
    Point() {}
    Point(float x, float y, float z,color_t color);
    glm::vec3 position,rotation;
    glm::mat4 rotate;
    int val;
    void draw(glm::mat4 VP,glm::vec3 v);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object;
    VAO *object1;
    VAO *object2;
};

#endif // POINT_H
