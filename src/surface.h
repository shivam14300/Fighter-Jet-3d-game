#include "main.h"

#ifndef Surface_H
#define Surface_H


class Surface {
public:
    Surface() {}
    Surface(float x, float y, float z,color_t color);
    glm::vec3 position,rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object;
    VAO *object1;
    VAO *object2;
};

#endif // Surface_H
