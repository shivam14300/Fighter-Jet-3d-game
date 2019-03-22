#include "main.h"

#ifndef ARROW_H
#define ARROW_H


class Arrow {
public:
    Arrow() {}
    Arrow(float x, float y, float z,color_t color);
    glm::vec3 position,rotation;
    glm::mat4 rotate;
    void draw(glm::mat4 VP,float rx,float ry, float rz);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object;
    VAO *object1;
};

#endif // ARROW_H
