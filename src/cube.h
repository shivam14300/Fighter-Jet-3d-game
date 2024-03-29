#include "main.h"

#ifndef Cube_H
#define Cube_H


class Cube {
public:
    Cube() {}
    Cube(float x, float y, float z,color_t color);
    glm::vec3 position,rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object;
};

#endif // Cube_H
