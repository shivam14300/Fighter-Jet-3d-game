#include "main.h"

#ifndef CANNONBALL_H
#define CANNONBALL_H


class Cannonball {
public:
    Cannonball() {}
    Cannonball(float x, float y, float z,float a,float b,float c,color_t color);
    glm::vec3 position,rotation;
    glm::mat4 rotate;
    float a,b,c;
    float timer;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object;
};

#endif // Cannonball_H
