#include "cannon.h"
#include "main.h"
#include<math.h>
Cannon::Cannon(float x, float y, float z,color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation.x = 0.0;
    this->rotation.y = 0.0;
    this->rotation.z = 0.0;
    this->a = a;
    this->b = b;
    this->c = c;
    this->flag = 0;
    this->timer = 0.5;
    this->rotate = glm::mat4(1.0f);
    speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[15200];
    int ptr = 0;
    for(int i=0;i<36;i++)
    {
        vertex_buffer_data[ptr++] = 2.0f*cos((10.0*M_PI*(float)i)/(float)180);
        vertex_buffer_data[ptr++] = 2.0f*sin((10.0*M_PI*(float)i)/(float)180);
        vertex_buffer_data[ptr++] = 0.0f;
        vertex_buffer_data[ptr++] = 2.0f*cos((10.0*M_PI*(float)(i+1))/(float)180);
        vertex_buffer_data[ptr++] = 2.0f*sin((10.0*M_PI*(float)(i+1))/(float)180);
        vertex_buffer_data[ptr++] = 0.0f;
        vertex_buffer_data[ptr++] = 1.0f*cos((10.0*M_PI*(float)(i))/(float)180);
        vertex_buffer_data[ptr++] = 1.0f*sin((10.0*M_PI*(float)(i))/(float)180);
        vertex_buffer_data[ptr++] = 8.0f;
    }
    for(int i=36;i<72;i++)
    {
        vertex_buffer_data[ptr++] = 1.0f*cos((10.0*M_PI*(float)i)/(float)180);
        vertex_buffer_data[ptr++] = 1.0f*sin((10.0*M_PI*(float)i)/(float)180);
        vertex_buffer_data[ptr++] = 8.0f;
        vertex_buffer_data[ptr++] = 1.0f*cos((10.0*M_PI*(float)(i+1))/(float)180);
        vertex_buffer_data[ptr++] = 1.0f*sin((10.0*M_PI*(float)(i+1))/(float)180);
        vertex_buffer_data[ptr++] = 8.0f;
        vertex_buffer_data[ptr++] = 2.0f*cos((10.0*M_PI*(float)(i+1))/(float)180);
        vertex_buffer_data[ptr++] = 2.0f*sin((10.0*M_PI*(float)(i+1))/(float)180);
        vertex_buffer_data[ptr++] = 0.0f;
    }
    int r = 2.0;
    for(int j=0;j<9;j++)
    {
        for(int i=0;i<36;i++)
        {
            vertex_buffer_data[ptr++] = r*sin(10.0*(float)j*M_PI/180.0)*cos((10.0*M_PI*(float)i)/(float)180);
            vertex_buffer_data[ptr++] = r*sin(10.0*(float)j*M_PI/180.0)*sin((10.0*M_PI*(float)i)/(float)180);
            vertex_buffer_data[ptr++] = -r*cos(10.0*(float)j*M_PI/180.0);
            vertex_buffer_data[ptr++] = r*sin(10.0*(float)j*M_PI/180.0)*cos((10.0*M_PI*(float)(i+1))/(float)180);
            vertex_buffer_data[ptr++] = r*sin(10.0*(float)j*M_PI/180.0)*sin((10.0*M_PI*(float)(i+1))/(float)180);
            vertex_buffer_data[ptr++] = -r*cos(10.0*(float)j*M_PI/180.0);
            vertex_buffer_data[ptr++] = r*sin(10.0*(float)(j+1.0)*M_PI/180.0)*cos((10.0*M_PI*(float)(i))/(float)180);
            vertex_buffer_data[ptr++] = r*sin(10.0*(float)(j+1.0)*M_PI/180.0)*sin((10.0*M_PI*(float)(i))/(float)180);
            vertex_buffer_data[ptr++] = -r*cos(10.0*(float)(j+1.0)*M_PI/180.0);
        }
        for(int i=36;i<72;i++)
        {
            vertex_buffer_data[ptr++] = r*sin(10.0*(float)(j+1.0)*M_PI/180.0)*cos((10.0*M_PI*(float)i)/(float)180);
            vertex_buffer_data[ptr++] = r*sin(10.0*(float)(j+1.0)*M_PI/180.0)*sin((10.0*M_PI*(float)i)/(float)180);
            vertex_buffer_data[ptr++] = -r*cos(10.0*(float)(j+1.0)*M_PI/180.0);
            vertex_buffer_data[ptr++] = r*sin(10.0*(float)(j+1.0)*M_PI/180.0)*cos((10.0*M_PI*(float)(i+1))/(float)180);
            vertex_buffer_data[ptr++] = r*sin(10.0*(float)(j+1.0)*M_PI/180.0)*sin((10.0*M_PI*(float)(i+1))/(float)180);
            vertex_buffer_data[ptr++] = -r*cos(10.0*(float)(j+1.0)*M_PI/180.0);
            vertex_buffer_data[ptr++] = r*sin(10.0*(float)j*M_PI/180.0)*cos((10.0*M_PI*(float)(i+1))/(float)180);
            vertex_buffer_data[ptr++] = r*sin(10.0*(float)j*M_PI/180.0)*sin((10.0*M_PI*(float)(i+1))/(float)180);
            vertex_buffer_data[ptr++] = -r*cos(10.0*(float)j*M_PI/180.0);
        }
    }
    this->object = create3DObject(GL_TRIANGLES, 72*9*3+72*3, vertex_buffer_data, color, GL_FILL);
}

void Cannon::draw(glm::mat4 VP,float a,float b,float c) {
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
    this->rotate[2][0] = a;
    this->rotate[2][1] = b;
    this->rotate[2][2] = c;
    glm:: vec3 v1 = glm::normalize(glm::vec3(-1.0*b,a,0.0));
    this->rotate[0][0] = v1.x;
    this->rotate[0][1] = v1.y;
    this->rotate[0][2] = v1.z;
    glm::vec3 v2 = glm::normalize(glm::cross(glm::vec3(a,b,c),glm::vec3(-1.0*b,a,0.0)));
    this->rotate[1][0] = v2.x;
    this->rotate[1][1] = v2.y;
    this->rotate[1][2] = v2.z;
    
    Matrices.model *= (translate * this->rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Cannon::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Cannon::tick() {
    if(this->flag == 1)
    {
        this->timer -= 0.01;
        if(this->timer < 0.0)
        {
            this->flag = 0;
            float x = ((float)(rand()%10)/10.0);
            this->timer = x;
        }
    }
}

