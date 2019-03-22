#include "score.h"
#include "main.h"
#include<math.h>
Score::Score(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0.0;
    this->timer = 0.0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[200];
    GLfloat vertex_buffer_data1[200];
    GLfloat vertex_buffer_data2[200];
    GLfloat vertex_buffer_data3[200];
    GLfloat vertex_buffer_data4[200];
    GLfloat vertex_buffer_data5[200];
    GLfloat vertex_buffer_data6[200];
    this->x = 0;
    //a
    vertex_buffer_data[this->x++] =  0.25f;vertex_buffer_data[this->x++] = 0.00f;vertex_buffer_data[this->x++] = 0.0f;
    vertex_buffer_data[this->x++] =  0.30f;vertex_buffer_data[this->x++] = 0.00f;vertex_buffer_data[this->x++] = 0.0f;
    vertex_buffer_data[this->x++] =  0.30f;vertex_buffer_data[this->x++] = 0.50f;vertex_buffer_data[this->x++] = 0.0f;
    
    vertex_buffer_data[this->x++] =  0.25f;vertex_buffer_data[this->x++] = 0.00f;vertex_buffer_data[this->x++] = 0.0f;
    vertex_buffer_data[this->x++] =  0.25f;vertex_buffer_data[this->x++] = 0.50f;vertex_buffer_data[this->x++] = 0.0f;
    vertex_buffer_data[this->x++] =  0.30f;vertex_buffer_data[this->x++] = 0.50f;vertex_buffer_data[this->x++] = 0.0f;
    this->x = 0;
    //b
    vertex_buffer_data1[this->x++] =  0.25f;vertex_buffer_data1[this->x++] = 0.50f;vertex_buffer_data1[this->x++] = 0.0f;
    vertex_buffer_data1[this->x++] =  0.25f;vertex_buffer_data1[this->x++] = 0.55f;vertex_buffer_data1[this->x++] = 0.0f;
    vertex_buffer_data1[this->x++] = -0.25f;vertex_buffer_data1[this->x++] = 0.50f;vertex_buffer_data1[this->x++] = 0.0f;
    
    vertex_buffer_data1[this->x++] = -0.25f;vertex_buffer_data1[this->x++] = 0.55f;vertex_buffer_data1[this->x++] = 0.0f;
    vertex_buffer_data1[this->x++] =  0.25f;vertex_buffer_data1[this->x++] = 0.55f;vertex_buffer_data1[this->x++] = 0.0f;
    vertex_buffer_data1[this->x++] = -0.25f;vertex_buffer_data1[this->x++] = 0.50f;vertex_buffer_data1[this->x++] = 0.0f;
    this->x = 0;
    //c
    vertex_buffer_data2[this->x++] = -0.25f;vertex_buffer_data2[this->x++] = 0.00f;vertex_buffer_data2[this->x++] = 0.0f;
    vertex_buffer_data2[this->x++] = -0.25f;vertex_buffer_data2[this->x++] = 0.50f;vertex_buffer_data2[this->x++] = 0.0f;
    vertex_buffer_data2[this->x++] = -0.30f;vertex_buffer_data2[this->x++] = 0.00f;vertex_buffer_data2[this->x++] = 0.0f;
    
    vertex_buffer_data2[this->x++] = -0.30f;vertex_buffer_data2[this->x++] = 0.50f;vertex_buffer_data2[this->x++] = 0.0f;
    vertex_buffer_data2[this->x++] = -0.25f;vertex_buffer_data2[this->x++] = 0.50f;vertex_buffer_data2[this->x++] = 0.0f;
    vertex_buffer_data2[this->x++] = -0.30f;vertex_buffer_data2[this->x++] = 0.00f;vertex_buffer_data2[this->x++] = 0.0f;
    this->x = 0;
    //d
    vertex_buffer_data3[this->x++] = -0.25f;vertex_buffer_data3[this->x++] =  0.00f;vertex_buffer_data3[this->x++] = 0.0f;
    vertex_buffer_data3[this->x++] = -0.30f;vertex_buffer_data3[this->x++] =  0.00f;vertex_buffer_data3[this->x++] = 0.0f;
    vertex_buffer_data3[this->x++] = -0.25f;vertex_buffer_data3[this->x++] = -0.50f;vertex_buffer_data3[this->x++] = 0.0f;
    
    vertex_buffer_data3[this->x++] = -0.30f;vertex_buffer_data3[this->x++] = -0.50f;vertex_buffer_data3[this->x++] = 0.0f;
    vertex_buffer_data3[this->x++] = -0.30f;vertex_buffer_data3[this->x++] =  0.00f;vertex_buffer_data3[this->x++] = 0.0f;
    vertex_buffer_data3[this->x++] = -0.25f;vertex_buffer_data3[this->x++] = -0.50f;vertex_buffer_data3[this->x++] = 0.0f;
    this->x = 0;
    //e
    vertex_buffer_data4[this->x++] = -0.25f;vertex_buffer_data4[this->x++] = -0.55f;vertex_buffer_data4[this->x++] = 0.0f;
    vertex_buffer_data4[this->x++] = -0.25f;vertex_buffer_data4[this->x++] = -0.50f;vertex_buffer_data4[this->x++] = 0.0f;
    vertex_buffer_data4[this->x++] =  0.25f;vertex_buffer_data4[this->x++] = -0.55f;vertex_buffer_data4[this->x++] = 0.0f;
    
    vertex_buffer_data4[this->x++] =  0.25f;vertex_buffer_data4[this->x++] = -0.50f;vertex_buffer_data4[this->x++] = 0.0f;
    vertex_buffer_data4[this->x++] = -0.25f;vertex_buffer_data4[this->x++] = -0.50f;vertex_buffer_data4[this->x++] = 0.0f;
    vertex_buffer_data4[this->x++] =  0.25f;vertex_buffer_data4[this->x++] = -0.55f;vertex_buffer_data4[this->x++] = 0.0f;
    this->x = 0;
    //f
    vertex_buffer_data5[this->x++] =  0.25f;vertex_buffer_data5[this->x++] =  0.00f;vertex_buffer_data5[this->x++] = 0.0f;
    vertex_buffer_data5[this->x++] =  0.30f;vertex_buffer_data5[this->x++] =  0.00f;vertex_buffer_data5[this->x++] = 0.0f;
    vertex_buffer_data5[this->x++] =  0.25f;vertex_buffer_data5[this->x++] = -0.50f;vertex_buffer_data5[this->x++] = 0.0f;
    
    vertex_buffer_data5[this->x++] =  0.30f;vertex_buffer_data5[this->x++] = -0.50f;vertex_buffer_data5[this->x++] = 0.0f;
    vertex_buffer_data5[this->x++] =  0.30f;vertex_buffer_data5[this->x++] =  0.00f;vertex_buffer_data5[this->x++] = 0.0f;
    vertex_buffer_data5[this->x++] =  0.25f;vertex_buffer_data5[this->x++] = -0.50f;vertex_buffer_data5[this->x++] = 0.0f;
    this->x = 0;
    //g
    vertex_buffer_data6[this->x++] =  0.25f;vertex_buffer_data6[this->x++] =  0.00f;vertex_buffer_data6[this->x++] = 0.0f;
    vertex_buffer_data6[this->x++] =  0.25f;vertex_buffer_data6[this->x++] =  0.05f;vertex_buffer_data6[this->x++] = 0.0f;
    vertex_buffer_data6[this->x++] = -0.25f;vertex_buffer_data6[this->x++] =  0.00f;vertex_buffer_data6[this->x++] = 0.0f;
    
    vertex_buffer_data6[this->x++] = -0.25f;vertex_buffer_data6[this->x++] =  0.05f;vertex_buffer_data6[this->x++] = 0.0f;
    vertex_buffer_data6[this->x++] =  0.25f;vertex_buffer_data6[this->x++] =  0.05f;vertex_buffer_data6[this->x++] = 0.0f;
    vertex_buffer_data6[this->x++] = -0.25f;vertex_buffer_data6[this->x++] =  0.00f;vertex_buffer_data6[this->x++] = 0.0f;
    
    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, color, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data1, color, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data2, color, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data3, color, GL_FILL);
    this->object4 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data4, color, GL_FILL);
    this->object5 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data5, color, GL_FILL);
    this->object6 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data6, color, GL_FILL);
}

void Score::draw(glm::mat4 VP,int n) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    translate[0][0] *= 8.0;
    translate[1][1] *= 6.0;
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    if(n == 0 || n == 1 || n == 2 || n == 3 || n == 4 || n == 7 || n == 8 || n == 9)draw3DObject(this->object);
    if(n == 0 || n == 2 || n == 3 || n == 5 || n == 6 || n == 7 || n == 8 || n == 9)draw3DObject(this->object1);
    if(n == 0 || n == 4 || n == 5 || n == 6 || n == 8 || n == 9)draw3DObject(this->object2);
    if(n == 0 || n == 2 || n == 6 || n == 8)draw3DObject(this->object3);
    if(n == 0 || n == 2 || n == 3 || n == 5 || n == 6 || n == 8 || n == 9)draw3DObject(this->object4);
    if(n == 0 || n == 1 || n == 3 || n == 4 || n == 5 || n == 6 || n == 7 || n == 8 || n == 9)draw3DObject(this->object5);
    if(n == 2 || n == 3 || n == 4 || n == 5 || n == 6 || n == 8 || n == 9)draw3DObject(this->object6);
    
}

void Score::set_position(float x, float y) 
{
    this->position = glm::vec3(x, y, 0);
}

void Score::tick() {

}

