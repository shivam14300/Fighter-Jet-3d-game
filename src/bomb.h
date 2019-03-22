#include "main.h"

#ifndef BOMB_H
#define BOMB_H


class Bomb {
public:
    Bomb() {}
    Bomb(float x, float y, float z,color_t color);
    glm::vec3 position,rotation;
    glm::mat4 rotate;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    float timer;
    double speed;
private:
    VAO *object;
    VAO *object1;
};

#endif // BOMB_H
