#include "main.h"

#ifndef Speedo_H
#define Speedo_H


class Speedo {
public:
    Speedo() {}
    Speedo(float x, float y, float z,color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object;
    VAO *object1;
};

#endif // Speedo_H
