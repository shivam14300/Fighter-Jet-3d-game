#include "plane.h"
#include "main.h"

Plane::Plane(float x, float y, float z,color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation.x = 0.0;
    this->rotation.y = 0.0;
    this->rotation.z = 0.0;
    this->rotate = glm::mat4(1.0f);
    this->missile_timer = 0.0;
    this->bomb_timer = 0.0;
    this->missile_flag = 0;
    this->bomb_flag = 0;
    speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[3200];
    GLfloat vertex_buffer_data1[3200];
    int ptr = 0;
    int ptr1 = 0;
    for(int i=0;i<36;i++)
    {
        vertex_buffer_data[ptr++] = 1.0f*cos((10.0*M_PI*(float)i)/(float)180);
        vertex_buffer_data[ptr++] = 1.0f*sin((10.0*M_PI*(float)i)/(float)180);
        vertex_buffer_data[ptr++] = 0.0f;
        vertex_buffer_data[ptr++] = 1.0f*cos((10.0*M_PI*(float)(i+1))/(float)180);
        vertex_buffer_data[ptr++] = 1.0f*sin((10.0*M_PI*(float)(i+1))/(float)180);
        vertex_buffer_data[ptr++] = 0.0f;
        vertex_buffer_data[ptr++] = 1.0f*cos((10.0*M_PI*(float)(i))/(float)180);
        vertex_buffer_data[ptr++] = 1.0f*sin((10.0*M_PI*(float)(i))/(float)180);
        vertex_buffer_data[ptr++] = -8.0f;
    }
    for(int i=0;i<36;i++)
    {
        vertex_buffer_data1[ptr1++] = 1.0f*cos((10.0*M_PI*(float)i)/(float)180);
        vertex_buffer_data1[ptr1++] = 1.0f*sin((10.0*M_PI*(float)i)/(float)180);
        vertex_buffer_data1[ptr1++] = -8.0f;
        vertex_buffer_data1[ptr1++] = 1.0f*cos((10.0*M_PI*(float)(i+1))/(float)180);
        vertex_buffer_data1[ptr1++] = 1.0f*sin((10.0*M_PI*(float)(i+1))/(float)180);
        vertex_buffer_data1[ptr1++] = -8.0f;
        vertex_buffer_data1[ptr1++] = 1.0f*cos((10.0*M_PI*(float)(i+1))/(float)180);
        vertex_buffer_data1[ptr1++] = 1.0f*sin((10.0*M_PI*(float)(i+1))/(float)180);
        vertex_buffer_data1[ptr1++] = 0.0f;
    }
    for(int i=0;i<36;i++)
    {
        vertex_buffer_data[ptr++] = 1.0f*cos((10.0*M_PI*(float)i)/(float)180);
        vertex_buffer_data[ptr++] = 1.0f*sin((10.0*M_PI*(float)i)/(float)180);
        vertex_buffer_data[ptr++] = 0.0f;
        vertex_buffer_data[ptr++] = 1.0f*cos((10.0*M_PI*(float)(i+1))/(float)180);
        vertex_buffer_data[ptr++] = 1.0f*sin((10.0*M_PI*(float)(i+1))/(float)180);
        vertex_buffer_data[ptr++] = 0.0f;
        vertex_buffer_data[ptr++] = 1.5f*cos((10.0*M_PI*(float)(i))/(float)180);
        vertex_buffer_data[ptr++] = 1.5f*sin((10.0*M_PI*(float)(i))/(float)180);
        vertex_buffer_data[ptr++] = 2.5f;
    }
    for(int i=0;i<36;i++)
    {
        vertex_buffer_data1[ptr1++] = 1.5f*cos((10.0*M_PI*(float)i)/(float)180);
        vertex_buffer_data1[ptr1++] = 1.5f*sin((10.0*M_PI*(float)i)/(float)180);
        vertex_buffer_data1[ptr1++] = 2.5f;
        vertex_buffer_data1[ptr1++] = 1.5f*cos((10.0*M_PI*(float)(i+1))/(float)180);
        vertex_buffer_data1[ptr1++] = 1.5f*sin((10.0*M_PI*(float)(i+1))/(float)180);
        vertex_buffer_data1[ptr1++] = 2.5f;
        vertex_buffer_data1[ptr1++] = 1.0f*cos((10.0*M_PI*(float)(i+1))/(float)180);
        vertex_buffer_data1[ptr1++] = 1.0f*sin((10.0*M_PI*(float)(i+1))/(float)180);
        vertex_buffer_data1[ptr1++] = 0.0f;
    }
    for(int i=0;i<36;i++)
    {
        vertex_buffer_data[ptr++] = 1.0f*cos((10.0*M_PI*(float)i)/(float)180);
        vertex_buffer_data[ptr++] = 1.0f*sin((10.0*M_PI*(float)i)/(float)180);
        vertex_buffer_data[ptr++] = -8.0f;
        vertex_buffer_data[ptr++] = 1.0f*cos((10.0*M_PI*(float)(i+1))/(float)180);
        vertex_buffer_data[ptr++] = 1.0f*sin((10.0*M_PI*(float)(i+1))/(float)180);
        vertex_buffer_data[ptr++] = -8.0f;
        vertex_buffer_data[ptr++] = 0.0;
        vertex_buffer_data[ptr++] = 0.0;
        vertex_buffer_data[ptr++] = -10.5f;
    }
    vertex_buffer_data[ptr++] = 1.0;vertex_buffer_data[ptr++] = 0.0;vertex_buffer_data[ptr++] = -3.0;
    vertex_buffer_data[ptr++] = 1.0;vertex_buffer_data[ptr++] = 0.0;vertex_buffer_data[ptr++] = -5.0;
    vertex_buffer_data[ptr++] = 6.0;vertex_buffer_data[ptr++] = 0.0;vertex_buffer_data[ptr++] = -4.0;

    vertex_buffer_data[ptr++] = -1.0;vertex_buffer_data[ptr++] = 0.0;vertex_buffer_data[ptr++] = -3.0;
    vertex_buffer_data[ptr++] = -1.0;vertex_buffer_data[ptr++] = 0.0;vertex_buffer_data[ptr++] = -5.0;
    vertex_buffer_data[ptr++] = -6.0;vertex_buffer_data[ptr++] = 0.0;vertex_buffer_data[ptr++] = -4.0;

    this->object = create3DObject(GL_TRIANGLES, 110*3, vertex_buffer_data, COLOR_BLACK, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, 72*3, vertex_buffer_data1, COLOR_GRANADE, GL_FILL);
}

void Plane::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate_x    = glm::rotate((float) (this->rotation.x * M_PI / 180.0f), glm::vec3(1, 0, 0));
    glm::mat4 rotate_y    = glm::rotate((float) (this->rotation.y * M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 rotate_z    = glm::rotate((float) (this->rotation.z * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // this->rotation *= rotate_z*rotate_x*rotate_y;
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    // rotate_x = this->rotate*rotate_x;
    // rotate_y = this->rotate*rotate_y;
    // rotate_z = this->rotate*rotate_z;
    this->rotate *= (rotate_y*rotate_x*rotate_z);
    
    Matrices.model *= (translate * this->rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object1);
    this->rotation.x = 0.0;
    this->rotation.y = 0.0;
    this->rotation.z = 0.0;
}

void Plane::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Plane::tick() 
{
    if(this->missile_flag == 1)
    {
        this->missile_timer += 1.0/60.0;
        if(missile_timer > 0.25)
        {
            this->missile_flag = 0;
            this->missile_timer = 0.0;
        }
    }
    if(this->bomb_flag == 1)
    {
        this->bomb_timer += 1.0/60.0;
        if(bomb_timer > 0.25)
        {
            this->bomb_flag = 0;
            this->bomb_timer = 0.0;
        }
    }
}

