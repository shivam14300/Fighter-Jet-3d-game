#include "fuelbar.h"
#include "main.h"

Fuelbar::Fuelbar(float x, float y, float z,color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0.0;
    this->val = 8.0;
    this->timer = 0.0;
    // speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[1000];
    GLfloat vertex_buffer_data1[100];
    GLfloat vertex_buffer_data2[100];
    GLfloat vertex_buffer_data3[100];
    GLfloat vertex_buffer_data4[100];
    int ptr = 0;
    vertex_buffer_data[ptr++] = 2.0;vertex_buffer_data[ptr++] = 4.0;vertex_buffer_data[ptr++] = 0.0;
    vertex_buffer_data[ptr++] = 2.0;vertex_buffer_data[ptr++] = 4.3;vertex_buffer_data[ptr++] = 0.0;
    vertex_buffer_data[ptr++] = -2.0;vertex_buffer_data[ptr++] = 4.0;vertex_buffer_data[ptr++] = 0.0;

    vertex_buffer_data[ptr++] = -2.0;vertex_buffer_data[ptr++] = 4.3;vertex_buffer_data[ptr++] = 0.0;
    vertex_buffer_data[ptr++] = 2.0;vertex_buffer_data[ptr++] = 4.3;vertex_buffer_data[ptr++] = 0.0;
    vertex_buffer_data[ptr++] = -2.0;vertex_buffer_data[ptr++] = 4.0;vertex_buffer_data[ptr++] = 0.0;

    vertex_buffer_data[ptr++] = 2.0;vertex_buffer_data[ptr++] = 4.3;vertex_buffer_data[ptr++] = 0.0;
    vertex_buffer_data[ptr++] = 2.3;vertex_buffer_data[ptr++] = 4.3;vertex_buffer_data[ptr++] = 0.0;
    vertex_buffer_data[ptr++] = 2.0;vertex_buffer_data[ptr++] = -4.3;vertex_buffer_data[ptr++] = 0.0;

    vertex_buffer_data[ptr++] = 2.3;vertex_buffer_data[ptr++] = -4.3;vertex_buffer_data[ptr++] = 0.0;
    vertex_buffer_data[ptr++] = 2.3;vertex_buffer_data[ptr++] = 4.3;vertex_buffer_data[ptr++] = 0.0;
    vertex_buffer_data[ptr++] = 2.0;vertex_buffer_data[ptr++] = -4.3;vertex_buffer_data[ptr++] = 0.0;

    vertex_buffer_data[ptr++] = 2.0;vertex_buffer_data[ptr++] = -4.0;vertex_buffer_data[ptr++] = 0.0;
    vertex_buffer_data[ptr++] = 2.0;vertex_buffer_data[ptr++] = -4.3;vertex_buffer_data[ptr++] = 0.0;
    vertex_buffer_data[ptr++] = -2.0;vertex_buffer_data[ptr++] = -4.0;vertex_buffer_data[ptr++] = 0.0;

    vertex_buffer_data[ptr++] = -2.0;vertex_buffer_data[ptr++] = -4.3;vertex_buffer_data[ptr++] = 0.0;
    vertex_buffer_data[ptr++] = 2.0;vertex_buffer_data[ptr++] = -4.3;vertex_buffer_data[ptr++] = 0.0;
    vertex_buffer_data[ptr++] = -2.0;vertex_buffer_data[ptr++] = -4.0;vertex_buffer_data[ptr++] = 0.0;

    vertex_buffer_data[ptr++] = -2.0;vertex_buffer_data[ptr++] = 4.3;vertex_buffer_data[ptr++] = 0.0;
    vertex_buffer_data[ptr++] = -2.3;vertex_buffer_data[ptr++] = 4.3;vertex_buffer_data[ptr++] = 0.0;
    vertex_buffer_data[ptr++] = -2.0;vertex_buffer_data[ptr++] = -4.3;vertex_buffer_data[ptr++] = 0.0;

    vertex_buffer_data[ptr++] = -2.3;vertex_buffer_data[ptr++] = -4.3;vertex_buffer_data[ptr++] = 0.0;
    vertex_buffer_data[ptr++] = -2.3;vertex_buffer_data[ptr++] = 4.3;vertex_buffer_data[ptr++] = 0.0;
    vertex_buffer_data[ptr++] = -2.0;vertex_buffer_data[ptr++] = -4.3;vertex_buffer_data[ptr++] = 0.0;

    vertex_buffer_data[ptr++] = 1.0;vertex_buffer_data[ptr++] = 4.3;vertex_buffer_data[ptr++] = 0.0;
    vertex_buffer_data[ptr++] = 1.0;vertex_buffer_data[ptr++] = 4.8;vertex_buffer_data[ptr++] = 0.0;
    vertex_buffer_data[ptr++] = -1.0;vertex_buffer_data[ptr++] = 4.3;vertex_buffer_data[ptr++] = 0.0;

    vertex_buffer_data[ptr++] = -1.0;vertex_buffer_data[ptr++] = 4.8;vertex_buffer_data[ptr++] = 0.0;
    vertex_buffer_data[ptr++] = 1.0;vertex_buffer_data[ptr++] = 4.8;vertex_buffer_data[ptr++] = 0.0;
    vertex_buffer_data[ptr++] = -1.0;vertex_buffer_data[ptr++] = 4.3;vertex_buffer_data[ptr++] = 0.0;

    ptr = 0;
    vertex_buffer_data1[ptr++] = 2.0;vertex_buffer_data1[ptr++] = 4.0;vertex_buffer_data1[ptr++] = 0.0;
    vertex_buffer_data1[ptr++] = 2.0;vertex_buffer_data1[ptr++] = -4.0;vertex_buffer_data1[ptr++] = 0.0;
    vertex_buffer_data1[ptr++] = -2.0;vertex_buffer_data1[ptr++] = 4.0;vertex_buffer_data1[ptr++] = 0.0;

    vertex_buffer_data1[ptr++] = -2.0;vertex_buffer_data1[ptr++] = -4.0;vertex_buffer_data1[ptr++] = 0.0;
    vertex_buffer_data1[ptr++] = 2.0;vertex_buffer_data1[ptr++] = -4.0;vertex_buffer_data1[ptr++] = 0.0;
    vertex_buffer_data1[ptr++] = -2.0;vertex_buffer_data1[ptr++] = 4.0;vertex_buffer_data1[ptr++] = 0.0;

    ptr = 0;
    vertex_buffer_data2[ptr++] = 2.0;vertex_buffer_data2[ptr++] = 2.0;vertex_buffer_data2[ptr++] = 0.0;
    vertex_buffer_data2[ptr++] = 2.0;vertex_buffer_data2[ptr++] = -4.0;vertex_buffer_data2[ptr++] = 0.0;
    vertex_buffer_data2[ptr++] = -2.0;vertex_buffer_data2[ptr++] = 2.0;vertex_buffer_data2[ptr++] = 0.0;

    vertex_buffer_data2[ptr++] = -2.0;vertex_buffer_data2[ptr++] = -4.0;vertex_buffer_data2[ptr++] = 0.0;
    vertex_buffer_data2[ptr++] = 2.0;vertex_buffer_data2[ptr++] = -4.0;vertex_buffer_data2[ptr++] = 0.0;
    vertex_buffer_data2[ptr++] = -2.0;vertex_buffer_data2[ptr++] = 2.0;vertex_buffer_data2[ptr++] = 0.0;

    ptr = 0;
    vertex_buffer_data3[ptr++] = 2.0;vertex_buffer_data3[ptr++] = 0.0;vertex_buffer_data3[ptr++] = 0.0;
    vertex_buffer_data3[ptr++] = 2.0;vertex_buffer_data3[ptr++] = -4.0;vertex_buffer_data3[ptr++] = 0.0;
    vertex_buffer_data3[ptr++] = -2.0;vertex_buffer_data3[ptr++] = 0.0;vertex_buffer_data3[ptr++] = 0.0;

    vertex_buffer_data3[ptr++] = -2.0;vertex_buffer_data3[ptr++] = -4.0;vertex_buffer_data3[ptr++] = 0.0;
    vertex_buffer_data3[ptr++] = 2.0;vertex_buffer_data3[ptr++] = -4.0;vertex_buffer_data3[ptr++] = 0.0;
    vertex_buffer_data3[ptr++] = -2.0;vertex_buffer_data3[ptr++] = 0.0;vertex_buffer_data3[ptr++] = 0.0;

    ptr = 0;
    vertex_buffer_data4[ptr++] = 2.0;vertex_buffer_data4[ptr++] = -2.0;vertex_buffer_data4[ptr++] = 0.0;
    vertex_buffer_data4[ptr++] = 2.0;vertex_buffer_data4[ptr++] = -4.0;vertex_buffer_data4[ptr++] = 0.0;
    vertex_buffer_data4[ptr++] = -2.0;vertex_buffer_data4[ptr++] = -2.0;vertex_buffer_data4[ptr++] = 0.0;

    vertex_buffer_data4[ptr++] = -2.0;vertex_buffer_data4[ptr++] = -4.0;vertex_buffer_data4[ptr++] = 0.0;
    vertex_buffer_data4[ptr++] = 2.0;vertex_buffer_data4[ptr++] = -4.0;vertex_buffer_data4[ptr++] = 0.0;
    vertex_buffer_data4[ptr++] = -2.0;vertex_buffer_data4[ptr++] = -2.0;vertex_buffer_data4[ptr++] = 0.0;

    this->object = create3DObject(GL_TRIANGLES, 10*3, vertex_buffer_data, color, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data1, COLOR_DARKGREEN, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data2, COLOR_GREEN, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data3, COLOR_YELLOW, GL_FILL);
    this->object4 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data4, COLOR_RED, GL_FILL);
}

void Fuelbar::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // this->rotation *= rotate_z*rotate_x*rotate_y;
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    this->timer += 0.1;
    draw3DObject(this->object);
    if(this->val > 6.0)draw3DObject(this->object1);
    else if(this->val < 6.0 && this->val > 4.0)draw3DObject(this->object2);
    if(this->val < 4.0 && this->val > 2.0)draw3DObject(this->object3);
    if(this->val < 2.0 && this->val > 0.0 && (int(this->timer))%2 == 0)draw3DObject(this->object4);
}

void Fuelbar::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Fuelbar::tick() {
    this->val -= 0.003;
    // this->rotation -= 0.5;
}

