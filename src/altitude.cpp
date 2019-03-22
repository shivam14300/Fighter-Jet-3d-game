#include "altitude.h"
#include "main.h"

Altitude::Altitude(float x, float y, float z,color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0.0;
    this->val = 4.0;
    this->p.x = x;
    this->p.y = y;
    this->p.z = z;
    // speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[1000];
    GLfloat vertex_buffer_data1[100];
    int ptr = 0;
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
    
    ptr = 0;
    vertex_buffer_data1[ptr++] = -2.0;vertex_buffer_data1[ptr++] = -2.8;vertex_buffer_data1[ptr++] = 0.0;
    vertex_buffer_data1[ptr++] = 2.2;vertex_buffer_data1[ptr++] = -3.4;vertex_buffer_data1[ptr++] = 0.0;
    vertex_buffer_data1[ptr++] = -2.0;vertex_buffer_data1[ptr++] = -3.4;vertex_buffer_data1[ptr++] = 0.0;

    vertex_buffer_data1[ptr++] = -2.0;vertex_buffer_data1[ptr++] = -3.4;vertex_buffer_data1[ptr++] = 0.0;
    vertex_buffer_data1[ptr++] = 2.2;vertex_buffer_data1[ptr++] = -3.4;vertex_buffer_data1[ptr++] = 0.0;
    vertex_buffer_data1[ptr++] = -2.0;vertex_buffer_data1[ptr++] = -4.0;vertex_buffer_data1[ptr++] = 0.0;



    this->object = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data, COLOR_BLACK, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data1, COLOR_RED, GL_FILL);
}

void Altitude::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->p);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    
    translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate );
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
}

void Altitude::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Altitude::tick() {
}

