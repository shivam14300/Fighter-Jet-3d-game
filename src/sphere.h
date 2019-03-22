#include "main.h"

#ifndef SPHERE_H
#define SPHERE_H


class Sphere {
public:
    Sphere() {}
    Sphere(float x, float y, float z,color_t color);
    glm::vec3 position,rotation;
    glm::mat4 rotate;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object;
};

#endif // SPHERE_H
