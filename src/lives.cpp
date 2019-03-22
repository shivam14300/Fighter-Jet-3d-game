#include "lives.h"
#include "main.h"
#include<math.h>
Lives::Lives(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0.0;
    this->timer = 0.0;
    this->flag = 4;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[400];
    GLfloat vertex_buffer_data1[200];
    GLfloat vertex_buffer_data2[200];
    GLfloat vertex_buffer_data3[200];
    this->x = 0;
    for(int i=0;i<18;i++)
    {
        vertex_buffer_data[this->x++] = 0.25f;
        vertex_buffer_data[this->x++] = 0.9f;
        vertex_buffer_data[this->x++] = 0.0f;
        vertex_buffer_data[this->x++] = 0.25f+0.25f*cos((M_PI*10.0*(float)i)/(float)180);
        vertex_buffer_data[this->x++] = 0.9f+0.25f*sin((M_PI*10.0*(float)i)/(float)180);
        vertex_buffer_data[this->x++] = 0.0f;
        vertex_buffer_data[this->x++] = 0.25f+0.25f*cos((M_PI*10.0*(float)(i+1))/(float)180);
        vertex_buffer_data[this->x++] = 0.9f+0.25f*sin((M_PI*10.0*(float)(i+1))/(float)180);
        vertex_buffer_data[this->x++] = 0.0f;
    }
    for(int i=0;i<18;i++)
    {
        vertex_buffer_data[this->x++] = -0.25f;
        vertex_buffer_data[this->x++] = 0.9f;
        vertex_buffer_data[this->x++] = 0.0f;
        vertex_buffer_data[this->x++] = -0.25f+0.25f*cos((M_PI*10.0*(float)i)/(float)180);
        vertex_buffer_data[this->x++] = 0.9f+0.25f*sin((M_PI*10.0*(float)i)/(float)180);
        vertex_buffer_data[this->x++] = 0.0f;
        vertex_buffer_data[this->x++] = -0.25f+0.25f*cos((M_PI*10.0*(float)(i+1))/(float)180);
        vertex_buffer_data[this->x++] = 0.9f+0.25f*sin((M_PI*10.0*(float)(i+1))/(float)180);
        vertex_buffer_data[this->x++] = 0.0f;
    }
    this->x = 0;
    vertex_buffer_data1[this->x++] =  0.45f;vertex_buffer_data1[this->x++] = 0.7f;vertex_buffer_data1[this->x++] = 0.0f;
    vertex_buffer_data1[this->x++] =  0.5f;vertex_buffer_data1[this->x++] = 0.9f;vertex_buffer_data1[this->x++] = 0.0f;
    vertex_buffer_data1[this->x++] = -0.5f;vertex_buffer_data1[this->x++] = 0.7f;vertex_buffer_data1[this->x++] = 0.0f;
    
    vertex_buffer_data1[this->x++] = -0.5f;vertex_buffer_data1[this->x++] = 0.9f;vertex_buffer_data1[this->x++] = 0.0f;
    vertex_buffer_data1[this->x++] =  0.5f;vertex_buffer_data1[this->x++] = 0.9f;vertex_buffer_data1[this->x++] = 0.0f;
    vertex_buffer_data1[this->x++] = -0.45f;vertex_buffer_data1[this->x++] = 0.7f;vertex_buffer_data1[this->x++] = 0.0f;
    this->x = 0;
    vertex_buffer_data2[this->x++] =  0.35f;vertex_buffer_data2[this->x++] = 0.50f;vertex_buffer_data2[this->x++] = 0.0f;
    vertex_buffer_data2[this->x++] =  0.45f;vertex_buffer_data2[this->x++] = 0.70f;vertex_buffer_data2[this->x++] = 0.0f;
    vertex_buffer_data2[this->x++] = -0.35f;vertex_buffer_data2[this->x++] = 0.50f;vertex_buffer_data2[this->x++] = 0.0f;
    
    vertex_buffer_data2[this->x++] = -0.45f;vertex_buffer_data2[this->x++] = 0.70f;vertex_buffer_data2[this->x++] = 0.0f;
    vertex_buffer_data2[this->x++] =  0.45f;vertex_buffer_data2[this->x++] = 0.70f;vertex_buffer_data2[this->x++] = 0.0f;
    vertex_buffer_data2[this->x++] = -0.35f;vertex_buffer_data2[this->x++] = 0.50f;vertex_buffer_data2[this->x++] = 0.0f;
    this->x = 0;
    vertex_buffer_data3[this->x++] =  0.35f;vertex_buffer_data3[this->x++] =  0.5f;vertex_buffer_data3[this->x++] = 0.0f;
    vertex_buffer_data3[this->x++] = -0.35f;vertex_buffer_data3[this->x++] =  0.5f;vertex_buffer_data3[this->x++] = 0.0f;
    vertex_buffer_data3[this->x++] =  0.00f;vertex_buffer_data3[this->x++] = -0.2f;vertex_buffer_data3[this->x++] = 0.0f;
    
    this->object = create3DObject(GL_TRIANGLES, 36*3, vertex_buffer_data, color, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data1, color, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data2, color, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 1*3, vertex_buffer_data3, color, GL_FILL);
}

void Lives::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    translate[0][0] *= 2.0;
    translate[1][1] *= 2.0;
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    if(flag == 4){
        draw3DObject(this->object);
        draw3DObject(this->object1);
        draw3DObject(this->object2);
        draw3DObject(this->object3);
    }
    if(flag == 3){
        draw3DObject(this->object1);
        draw3DObject(this->object2);
        draw3DObject(this->object3);
    }
    if(flag == 2){
        draw3DObject(this->object2);
        draw3DObject(this->object3);
    }
    if(flag == 1){
        draw3DObject(this->object3);
    }
}

void Lives::set_position(float x, float y) 
{
    this->position = glm::vec3(x, y, 0);
}

void Lives::tick() 
{
    // if(this->position.y < 3.0f)
    //     this->position.x -= 0.10;
    // this->position.y -= 0.05;
    // this->timer += 0.01;
    // this->rotation += 20.0f;
}

