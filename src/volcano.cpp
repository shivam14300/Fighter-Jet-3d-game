#include "volcano.h"
#include "main.h"

Volcano::Volcano(float x, float y, float z,color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation.x = 0.0;
    this->rotation.y = 0.0;
    this->rotation.z = 0.0;
    this->rotate = glm::mat4(1.0f);
    speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[1000];
    GLfloat vertex_buffer_data1[1000];
    GLfloat vertex_buffer_data2[100];
    GLfloat vertex_buffer_data3[120000];
    int ptr = 0;
    int ptr1 = 0;
    for(int i=0;i<36;i++)
    {
        vertex_buffer_data[ptr++] = 8.0f*cos((10.0*M_PI*(float)i)/(float)180);
        vertex_buffer_data[ptr++] = 0.0f;
        vertex_buffer_data[ptr++] = 8.0f*sin((10.0*M_PI*(float)i)/(float)180);
        vertex_buffer_data[ptr++] = 8.0f*cos((10.0*M_PI*(float)(i+1))/(float)180);
        vertex_buffer_data[ptr++] = 0.0f;
        vertex_buffer_data[ptr++] = 8.0f*sin((10.0*M_PI*(float)(i+1))/(float)180);
        vertex_buffer_data[ptr++] = 4.0f*cos((10.0*M_PI*(float)(i))/(float)180);
        vertex_buffer_data[ptr++] = 8.0f;
        vertex_buffer_data[ptr++] = 4.0f*sin((10.0*M_PI*(float)(i))/(float)180);
    }
    for(int i=36;i<72;i++)
    {
        vertex_buffer_data[ptr++] = 4.0f*cos((10.0*M_PI*(float)i)/(float)180);
        vertex_buffer_data[ptr++] = 8.0f;
        vertex_buffer_data[ptr++] = 4.0f*sin((10.0*M_PI*(float)i)/(float)180);
        vertex_buffer_data[ptr++] = 4.0f*cos((10.0*M_PI*(float)(i+1))/(float)180);
        vertex_buffer_data[ptr++] = 8.0f;
        vertex_buffer_data[ptr++] = 4.0f*sin((10.0*M_PI*(float)(i+1))/(float)180);
        vertex_buffer_data[ptr++] = 8.0f*cos((10.0*M_PI*(float)(i+1))/(float)180);
        vertex_buffer_data[ptr++] = 0.0f;
        vertex_buffer_data[ptr++] = 8.0f*sin((10.0*M_PI*(float)(i+1))/(float)180);
    }
    for(int i=0;i<36;i++)
    {
        vertex_buffer_data1[ptr1++] = 4.0f*cos((10.0*M_PI*(float)i)/(float)180);
        vertex_buffer_data1[ptr1++] = 8.0f;
        vertex_buffer_data1[ptr1++] = 4.0f*sin((10.0*M_PI*(float)i)/(float)180);
        vertex_buffer_data1[ptr1++] = 4.0f*cos((10.0*M_PI*(float)(i+1))/(float)180);
        vertex_buffer_data1[ptr1++] = 8.0f;
        vertex_buffer_data1[ptr1++] = 4.0f*sin((10.0*M_PI*(float)(i+1))/(float)180);
        vertex_buffer_data1[ptr1++] = 2.0f*cos((10.0*M_PI*(float)(i))/(float)180);
        vertex_buffer_data1[ptr1++] = 15.0f;
        vertex_buffer_data1[ptr1++] = 2.0f*sin((10.0*M_PI*(float)(i))/(float)180);
    }
    for(int i=36;i<72;i++)
    {
        vertex_buffer_data1[ptr1++] = 2.0f*cos((10.0*M_PI*(float)i)/(float)180);
        vertex_buffer_data1[ptr1++] = 15.0f;
        vertex_buffer_data1[ptr1++] = 2.0f*sin((10.0*M_PI*(float)i)/(float)180);
        vertex_buffer_data1[ptr1++] = 2.0f*cos((10.0*M_PI*(float)(i+1))/(float)180);
        vertex_buffer_data1[ptr1++] = 15.0f;
        vertex_buffer_data1[ptr1++] = 2.0f*sin((10.0*M_PI*(float)(i+1))/(float)180);
        vertex_buffer_data1[ptr1++] = 4.0f*cos((10.0*M_PI*(float)(i+1))/(float)180);
        vertex_buffer_data1[ptr1++] = 8.0f;
        vertex_buffer_data1[ptr1++] = 4.0f*sin((10.0*M_PI*(float)(i+1))/(float)180);
    }
    vertex_buffer_data2[0] = 20.0;vertex_buffer_data2[1] = 0.1;vertex_buffer_data2[2] = 20.0;
    vertex_buffer_data2[3] = 20.0;vertex_buffer_data2[4] = 0.1;vertex_buffer_data2[5] = -20.0;
    vertex_buffer_data2[6] = -20.0;vertex_buffer_data2[7] = 0.1;vertex_buffer_data2[8] = 20.0;

    vertex_buffer_data2[9] = -20.0;vertex_buffer_data2[10] = 0.1;vertex_buffer_data2[11] = -20.0;
    vertex_buffer_data2[12] = 20.0;vertex_buffer_data2[13] = 0.1;vertex_buffer_data2[14] = -20.0;
    vertex_buffer_data2[15] = -20.0;vertex_buffer_data2[16] = 0.1;vertex_buffer_data2[17] = 20.0;


    this->object = create3DObject(GL_TRIANGLES, 72*3, vertex_buffer_data, COLOR_BLACK, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, 72*3, vertex_buffer_data1, COLOR_LAVARED, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data2, COLOR_GRAY, GL_FILL);
}

void Volcano::draw(glm::mat4 VP) {
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
    draw3DObject(this->object2);
    // draw3DObject(this->object3);
}

void Volcano::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Volcano::tick() {
}

