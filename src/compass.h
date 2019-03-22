#include "main.h"

#ifndef COMPASS_H
#define COMPASS_H


class Compass {
public:
    Compass() {}
    Compass(float x, float y, float z,color_t color);
    glm::vec3 position;
    float rotation;
    glm::mat4 rotate;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(glm::vec3 v);
    double speed;
private:
    VAO *object;
    VAO *object1;
    VAO *object2;
};

#endif // COMPASS_H
