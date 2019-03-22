#include "bomb.h"
#include "main.h"

Bomb::Bomb(float x, float y, float z,color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation.x = 0.0;
    this->rotation.y = 0.0;
    this->rotation.z = 0.0;
    this->rotate = glm::mat4(1.0f);
    this->timer = 5.0;
    speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[6000];
    GLfloat vertex_buffer_data1[6000];
    int ptr = 0;
    int ptr1 = 0;
    float r = 1.0;
    for(int j=0;j<18;j++)
    {
        for(int i=0;i<36;i++)
        {
            vertex_buffer_data[ptr++] = r*sin(10.0*(float)j*M_PI/180.0)*cos((10.0*M_PI*(float)i)/(float)180);
            vertex_buffer_data[ptr++] = r*sin(10.0*(float)j*M_PI/180.0)*sin((10.0*M_PI*(float)i)/(float)180);
            vertex_buffer_data[ptr++] = r*cos(10.0*(float)j*M_PI/180.0);
            vertex_buffer_data[ptr++] = r*sin(10.0*(float)j*M_PI/180.0)*cos((10.0*M_PI*(float)(i+1))/(float)180);
            vertex_buffer_data[ptr++] = r*sin(10.0*(float)j*M_PI/180.0)*sin((10.0*M_PI*(float)(i+1))/(float)180);
            vertex_buffer_data[ptr++] = r*cos(10.0*(float)j*M_PI/180.0);
            vertex_buffer_data[ptr++] = r*sin(10.0*(float)(j+1.0)*M_PI/180.0)*cos((10.0*M_PI*(float)(i))/(float)180);
            vertex_buffer_data[ptr++] = r*sin(10.0*(float)(j+1.0)*M_PI/180.0)*sin((10.0*M_PI*(float)(i))/(float)180);
            vertex_buffer_data[ptr++] = r*cos(10.0*(float)(j+1.0)*M_PI/180.0);
        }
        for(int i=36;i<72;i++)
        {
            vertex_buffer_data1[ptr1++] = r*sin(10.0*(float)(j+1.0)*M_PI/180.0)*cos((10.0*M_PI*(float)i)/(float)180);
            vertex_buffer_data1[ptr1++] = r*sin(10.0*(float)(j+1.0)*M_PI/180.0)*sin((10.0*M_PI*(float)i)/(float)180);
            vertex_buffer_data1[ptr1++] = r*cos(10.0*(float)(j+1.0)*M_PI/180.0);
            vertex_buffer_data1[ptr1++] = r*sin(10.0*(float)(j+1.0)*M_PI/180.0)*cos((10.0*M_PI*(float)(i+1))/(float)180);
            vertex_buffer_data1[ptr1++] = r*sin(10.0*(float)(j+1.0)*M_PI/180.0)*sin((10.0*M_PI*(float)(i+1))/(float)180);
            vertex_buffer_data1[ptr1++] = r*cos(10.0*(float)(j+1.0)*M_PI/180.0);
            vertex_buffer_data1[ptr1++] = r*sin(10.0*(float)j*M_PI/180.0)*cos((10.0*M_PI*(float)(i+1))/(float)180);
            vertex_buffer_data1[ptr1++] = r*sin(10.0*(float)j*M_PI/180.0)*sin((10.0*M_PI*(float)(i+1))/(float)180);
            vertex_buffer_data1[ptr1++] = r*cos(10.0*(float)j*M_PI/180.0);
        }
    }
    
    this->object = create3DObject(GL_TRIANGLES, 9*72*3, vertex_buffer_data, COLOR_GRANADE, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, 9*72*3, vertex_buffer_data1, COLOR_BLACK, GL_FILL);
}

void Bomb::draw(glm::mat4 VP) {
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
    // this->rotate *= (rotate_y*rotate_x*rotate_z);
    
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object1);
}

void Bomb::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Bomb::tick() {
    this->timer -= 0.01;
    this->position.y -= 0.8;
}

