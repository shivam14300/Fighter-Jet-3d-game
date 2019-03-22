#include "compass.h"
#include "main.h"

Compass::Compass(float x, float y, float z,color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0.0;
    // speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[1000];
    GLfloat vertex_buffer_data1[10];
    GLfloat vertex_buffer_data2[10];

    for(int i=0;i<36;i++)
    {
        vertex_buffer_data[9*i+0] = 5.0f*cos((10.0*M_PI*(float)i)/(float)180);
        vertex_buffer_data[9*i+1] = 5.0f*sin((10.0*M_PI*(float)i)/(float)180);
        vertex_buffer_data[9*i+2] = 0.0f;
        vertex_buffer_data[9*i+3] = 5.0f*cos((10.0*M_PI*(float)(i+1))/(float)180);
        vertex_buffer_data[9*i+4] = 5.0f*sin((10.0*M_PI*(float)(i+1))/(float)180);
        vertex_buffer_data[9*i+5] = 0.0f;
        vertex_buffer_data[9*i+6] = 4.0f*cos((10.0*M_PI*(float)(i))/(float)180);
        vertex_buffer_data[9*i+7] = 4.0f*sin((10.0*M_PI*(float)(i))/(float)180);
        vertex_buffer_data[9*i+8] = 0.0f;
    }
    for(int i=36;i<72;i++)
    {
        vertex_buffer_data[9*i+0] = 4.0f*cos((10.0*M_PI*(float)i)/(float)180);
        vertex_buffer_data[9*i+1] = 4.0f*sin((10.0*M_PI*(float)i)/(float)180);
        vertex_buffer_data[9*i+2] = 0.0f;
        vertex_buffer_data[9*i+3] = 4.0f*cos((10.0*M_PI*(float)(i+1))/(float)180);
        vertex_buffer_data[9*i+4] = 4.0f*sin((10.0*M_PI*(float)(i+1))/(float)180);
        vertex_buffer_data[9*i+5] = 0.0f;
        vertex_buffer_data[9*i+6] = 5.0f*cos((10.0*M_PI*(float)(i+1))/(float)180);
        vertex_buffer_data[9*i+7] = 5.0f*sin((10.0*M_PI*(float)(i+1))/(float)180);
        vertex_buffer_data[9*i+8] = 0.0f;
    }
    vertex_buffer_data2[0] = 1.0f;vertex_buffer_data2[1] = 0.0f;vertex_buffer_data2[2] = 0.0f;
    vertex_buffer_data2[3] = 0.0f;vertex_buffer_data2[4] = -4.0f;vertex_buffer_data2[5] = 0.0f;
    vertex_buffer_data2[6] =-1.0f;vertex_buffer_data2[7] = 0.0f;vertex_buffer_data2[8] = 0.0f;

    vertex_buffer_data1[0] = 1.0f;vertex_buffer_data1[1] = 0.0f;vertex_buffer_data1[2] = 0.0f;
    vertex_buffer_data1[3] = 0.0f;vertex_buffer_data1[4] = 4.0f;vertex_buffer_data1[5] = 0.0f;
    vertex_buffer_data1[6] =-1.0f;vertex_buffer_data1[7] = 0.0f;vertex_buffer_data1[8] = 0.0f;

    this->object = create3DObject(GL_TRIANGLES, 73*3, vertex_buffer_data, color, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data1, COLOR_RED, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data2, COLOR_BLUE, GL_FILL);
}

void Compass::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // this->rotation *= rotate_z*rotate_x*rotate_y;
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * this->rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
}

void Compass::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Compass::tick(glm::vec3 v) {
    this->rotate = glm::rotate((float) (atan2((double)v.z,(double)v.x) - M_PI/2.0), glm::vec3(0, 0, 1));
}

