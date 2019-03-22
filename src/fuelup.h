#include "main.h"

#ifndef FUELUP_H
#define FUELUP_H


class Fuelup {
public:
    Fuelup() {}
    Fuelup(float x, float y, float z,color_t color);
    glm::vec3 position,rotation;
    glm::mat4 rotate;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object;
    VAO *object1;
    VAO *object2;
};

#endif // FUELUP_H
