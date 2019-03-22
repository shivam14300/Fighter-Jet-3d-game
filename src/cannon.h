#include "main.h"

#ifndef CANNON_H
#define CANNON_H


class Cannon {
public:
    Cannon() {}
    Cannon(float x, float y, float z,color_t color);
    glm::vec3 position,rotation;
    glm::mat4 rotate;
    float a,b,c;
    float timer;
    int flag;
    void draw(glm::mat4 VP,float a,float b,float c);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object;
};

#endif // Cannon_H
