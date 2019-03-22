#include "main.h"

#ifndef Fuelbar_H
#define Fuelbar_H


class Fuelbar {
public:
    Fuelbar() {}
    Fuelbar(float x, float y, float z,color_t color);
    glm::vec3 position;
    float rotation;
    float val;
    float timer;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object;
    VAO *object1;
    VAO *object2;
    VAO *object3;
    VAO *object4;
};

#endif // Fuelbar_H
