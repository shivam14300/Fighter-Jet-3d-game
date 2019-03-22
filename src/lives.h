#include "main.h"

#ifndef LIVES_H
#define LIVES_H


class Lives {
public:
    Lives() {}
    Lives(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    float timer;
    int x;
    int flag;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
private:
    VAO *object;
    VAO *object1;
    VAO *object2;
    VAO *object3;
};

#endif // LIVES_H
