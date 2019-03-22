#include "main.h"

#ifndef Altitude_H
#define Altitude_H


class Altitude {
public:
    Altitude() {}
    Altitude(float x, float y, float z,color_t color);
    glm::vec3 position;
    glm::vec3 p;
    float rotation;
    float val;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object;
    VAO *object1;
};

#endif // Altitude_H
