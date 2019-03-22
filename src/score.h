#include "main.h"

#ifndef SCORE_H
#define SCORE_H


class Score {
public:
    Score() {}
    Score(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    float timer;
    int x;
    void draw(glm::mat4 VP, int n);
    void set_position(float x, float y);
    void tick();
private:
    VAO *object;
    VAO *object1;
    VAO *object2;
    VAO *object3;
    VAO *object4;
    VAO *object5;
    VAO *object6;
    VAO *object7;
    VAO *object8;
    VAO *object9;
};

#endif // SCORE_H
