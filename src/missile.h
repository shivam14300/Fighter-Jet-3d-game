#include "main.h"

#ifndef MISSILE_H
#define MISSILE_H


class Missile {
public:
    Missile() {}
    Missile(float x, float y, float z,float a,float b,float c,float cur_speed,color_t color);
    glm::vec3 position,rotation;
    glm::mat4 rotate;
    float a,b,c;
    float velo;
    float timer;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object;
    VAO *object1;
};

#endif // Missile_H
