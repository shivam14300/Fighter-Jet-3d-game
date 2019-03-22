#include "arrow.h"
#include "main.h"

Arrow::Arrow(float x, float y, float z,color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation.x = 0.0;
    this->rotation.y = 0.0;
    this->rotation.z = 0.0;
    this->rotate = glm::mat4(1.0f);
    speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[3200];
    GLfloat vertex_buffer_data1[3200];
    int ptr = 0;
    int ptr1 = 0;
    for(int i=0;i<36;i++)
    {
        vertex_buffer_data[ptr++] = 0.0f;
        vertex_buffer_data[ptr++] = 0.3f*cos((10.0*M_PI*(float)i)/(float)180);
        vertex_buffer_data[ptr++] = 0.3f*sin((10.0*M_PI*(float)i)/(float)180);
        vertex_buffer_data[ptr++] = 0.0f;
        vertex_buffer_data[ptr++] = 0.3f*cos((10.0*M_PI*(float)(i+1))/(float)180);
        vertex_buffer_data[ptr++] = 0.3f*sin((10.0*M_PI*(float)(i+1))/(float)180);
        vertex_buffer_data[ptr++] = 2.0f;
        vertex_buffer_data[ptr++] = 0.3f*cos((10.0*M_PI*(float)(i))/(float)180);
        vertex_buffer_data[ptr++] = 0.3f*sin((10.0*M_PI*(float)(i))/(float)180);
    }
    for(int i=36;i<72;i++)
    {
        vertex_buffer_data[ptr++] = 2.0f;
        vertex_buffer_data[ptr++] = 0.3f*cos((10.0*M_PI*(float)i)/(float)180);
        vertex_buffer_data[ptr++] = 0.3f*sin((10.0*M_PI*(float)i)/(float)180);
        vertex_buffer_data[ptr++] = 2.0f;
        vertex_buffer_data[ptr++] = 0.3f*cos((10.0*M_PI*(float)(i+1))/(float)180);
        vertex_buffer_data[ptr++] = 0.3f*sin((10.0*M_PI*(float)(i+1))/(float)180);
        vertex_buffer_data[ptr++] = 0.0f;
        vertex_buffer_data[ptr++] = 0.3f*cos((10.0*M_PI*(float)(i+1))/(float)180);
        vertex_buffer_data[ptr++] = 0.3f*sin((10.0*M_PI*(float)(i+1))/(float)180);
    }
    for(int i=72;i<108;i++)
    {
        vertex_buffer_data1[ptr1++] = 2.0f;
        vertex_buffer_data1[ptr1++] = 0.3f*cos((10.0*M_PI*(float)i)/(float)180);
        vertex_buffer_data1[ptr1++] = 0.3f*sin((10.0*M_PI*(float)i)/(float)180);
        vertex_buffer_data1[ptr1++] = 2.0f;
        vertex_buffer_data1[ptr1++] = 0.3f*cos((10.0*M_PI*(float)(i+1))/(float)180);
        vertex_buffer_data1[ptr1++] = 0.3f*sin((10.0*M_PI*(float)(i+1))/(float)180);
        vertex_buffer_data1[ptr1++] = 3.0f;
        vertex_buffer_data1[ptr1++] = 0.0;
        vertex_buffer_data1[ptr1++] = 0.0;
    }

    this->object = create3DObject(GL_TRIANGLES, 72*3, vertex_buffer_data, COLOR_RED, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, 36*3, vertex_buffer_data1, COLOR_BLACK, GL_FILL);
}

void Arrow::draw(glm::mat4 VP,float rx,float ry,float rz) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // glm::mat4 rotate_x    = glm::rotate((float) (this->rotation.x * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // glm::mat4 rotate_y    = glm::rotate((float) (this->rotation.y * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // glm::mat4 rotate_z    = glm::rotate((float) (this->rotation.z * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // this->rotation *= rotate_z*rotate_x*rotate_y;
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    // rotate_x = this->rotate*rotate_x;
    // rotate_y = this->rotate*rotate_y;
    // rotate_z = this->rotate*rotate_z;
    this->rotate[0][0] = rx;
    this->rotate[0][1] = ry;
    this->rotate[0][2] = rz;
    glm:: vec3 v1 = glm::normalize(glm::vec3(-1.0*ry,rx,0.0));
    this->rotate[1][0] = v1.x;
    this->rotate[1][1] = v1.y;
    this->rotate[1][2] = v1.z;
    glm::vec3 v2 = glm::normalize(glm::cross(glm::vec3(rx,ry,rz),glm::vec3(-1.0*ry,rx,0.0)));
    this->rotate[2][0] = v2.x;
    this->rotate[2][1] = v2.y;
    this->rotate[2][2] = v2.z;
    
    Matrices.model *= (translate * this->rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object1);
}

void Arrow::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Arrow::tick() {
}

