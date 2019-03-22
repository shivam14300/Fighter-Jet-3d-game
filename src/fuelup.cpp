#include "fuelup.h"
#include "main.h"

Fuelup::Fuelup(float x, float y, float z,color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation.x = 0.0;
    this->rotation.y = 0.0;
    this->rotation.z = 0.0;
    this->rotate = glm::mat4(1.0f);
    speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    int ptr1 = 0;
    GLfloat vertex_buffer_data1[1500];
    static const GLfloat vertex_buffer_data[] = {
        -1.0f,-2.0f,-0.5f, // triangle 1 : begin
        -1.0f,-2.0f, 0.5f,
        -1.0f, 2.0f, 0.5f, // triangle 1 : end
         1.0f, 2.0f,-0.5f, // triangle 2 : begin
        -1.0f,-2.0f,-0.5f,
        -1.0f, 2.0f,-0.5f, // triangle 2 : end
         
        -1.0f,-2.0f,-0.5f,
        -1.0f, 2.0f, 0.5f,
        -1.0f, 2.0f,-0.5f,
         1.0f,-2.0f, 0.5f,
        -1.0f,-2.0f, 0.5f,
        -1.0f,-2.0f,-0.5f,

         1.0f,-2.0f,-0.5f,
         1.0f, 2.0f, 0.5f,
         1.0f,-2.0f, 0.5f,
         1.0f, 2.0f, 0.5f,
         1.0f, 2.0f,-0.5f,
        -1.0f, 2.0f,-0.5f,
        
         1.0f,-2.0f, 0.5f,
        -1.0f,-2.0f,-0.5f,
         1.0f,-2.0f,-0.5f,
         1.0f, 2.0f,-0.5f,
         1.0f,-2.0f,-0.5f,
        -1.0f,-2.0f,-0.5f,
        
        -1.0f, 2.0f, 0.5f,
        -1.0f,-2.0f, 0.5f,
         1.0f,-2.0f, 0.5f,
         1.0f, 2.0f, 0.5f,
         1.0f,-2.0f,-0.5f,
         1.0f, 2.0f,-0.5f,
        
         
         1.0f, 2.0f, 0.5f,
        -1.0f, 2.0f,-0.5f,
        -1.0f, 2.0f, 0.5f,
         1.0f, 2.0f, 0.5f,
        -1.0f, 2.0f, 0.5f,
         1.0f,-2.0f, 0.5f
   
    };
        
    static const GLfloat vertex_buffer_data2[] = {

    };

    for(int i=0;i<36;i++)
    {
        vertex_buffer_data1[ptr1++] = 1.0f+1.0f*cos((10.0*M_PI*(float)i)/(float)180);
        vertex_buffer_data1[ptr1++] = 1.0f*sin((10.0*M_PI*(float)i)/(float)180);
        vertex_buffer_data1[ptr1++] = 0.0f;
        vertex_buffer_data1[ptr1++] = 1.0f+1.0f*cos((10.0*M_PI*(float)(i+1))/(float)180);
        vertex_buffer_data1[ptr1++] = 1.0f*sin((10.0*M_PI*(float)(i+1))/(float)180);
        vertex_buffer_data1[ptr1++] = 0.0f;
        vertex_buffer_data1[ptr1++] = 1.0f+1.0f*cos((10.0*M_PI*(float)(i))/(float)180);
        vertex_buffer_data1[ptr1++] = 1.0f*sin((10.0*M_PI*(float)(i))/(float)180);
        vertex_buffer_data1[ptr1++] = 0.5f;
    }
    for(int i=36;i<72;i++)
    {
        vertex_buffer_data1[ptr1++] = 1.0f+1.0f*cos((10.0*M_PI*(float)i)/(float)180);
        vertex_buffer_data1[ptr1++] = 1.0f*sin((10.0*M_PI*(float)i)/(float)180);
        vertex_buffer_data1[ptr1++] = 0.5f;
        vertex_buffer_data1[ptr1++] = 1.0f+1.0f*cos((10.0*M_PI*(float)(i+1))/(float)180);
        vertex_buffer_data1[ptr1++] = 1.0f*sin((10.0*M_PI*(float)(i+1))/(float)180);
        vertex_buffer_data1[ptr1++] = 0.5f;
        vertex_buffer_data1[ptr1++] = 1.0f+1.0f*cos((10.0*M_PI*(float)(i+1))/(float)180);
        vertex_buffer_data1[ptr1++] = 1.0f*sin((10.0*M_PI*(float)(i+1))/(float)180);
        vertex_buffer_data1[ptr1++] = 0.0f;
    }
    for(int i=0;i<36;i++)
    {
        vertex_buffer_data1[ptr1++] = -1.0f+1.0f*cos((10.0*M_PI*(float)i)/(float)180);
        vertex_buffer_data1[ptr1++] = 1.0f*sin((10.0*M_PI*(float)i)/(float)180);
        vertex_buffer_data1[ptr1++] = 0.0f;
        vertex_buffer_data1[ptr1++] = -1.0f+1.0f*cos((10.0*M_PI*(float)(i+1))/(float)180);
        vertex_buffer_data1[ptr1++] = 1.0f*sin((10.0*M_PI*(float)(i+1))/(float)180);
        vertex_buffer_data1[ptr1++] = 0.0f;
        vertex_buffer_data1[ptr1++] = -1.0f+1.0f*cos((10.0*M_PI*(float)(i))/(float)180);
        vertex_buffer_data1[ptr1++] = 1.0f*sin((10.0*M_PI*(float)(i))/(float)180);
        vertex_buffer_data1[ptr1++] = 0.5f;
    }
    for(int i=36;i<72;i++)
    {
        vertex_buffer_data1[ptr1++] = -1.0f+1.0f*cos((10.0*M_PI*(float)i)/(float)180);
        vertex_buffer_data1[ptr1++] = 1.0f*sin((10.0*M_PI*(float)i)/(float)180);
        vertex_buffer_data1[ptr1++] = 0.5f;
        vertex_buffer_data1[ptr1++] = -1.0f+1.0f*cos((10.0*M_PI*(float)(i+1))/(float)180);
        vertex_buffer_data1[ptr1++] = 1.0f*sin((10.0*M_PI*(float)(i+1))/(float)180);
        vertex_buffer_data1[ptr1++] = 0.5f;
        vertex_buffer_data1[ptr1++] = -1.0f+1.0f*cos((10.0*M_PI*(float)(i+1))/(float)180);
        vertex_buffer_data1[ptr1++] = 1.0f*sin((10.0*M_PI*(float)(i+1))/(float)180);
        vertex_buffer_data1[ptr1++] = 0.0f;
    }

    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, COLOR_YELLOW, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, 144*3, vertex_buffer_data1, COLOR_RED, GL_FILL);
}

void Fuelup::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object1);
    // draw3DObject(this->object2);
}

void Fuelup::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Fuelup::tick() {
}

