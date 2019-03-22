#include "surface.h"
#include "main.h"
#include<math.h>
Surface::Surface(float x, float y, float z,color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation.x = 0.0;
    this->rotation.y = 0.0;
    this->rotation.z = 0.0;
    // speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[200000];
    GLfloat vertex_buffer_data1[200000];
    GLfloat vertex_buffer_data2[200000];
    int ptr = 0,t = 0;
    int ptr1 = 0,t1 = 0;
    int ptr2 = 0,t2 = 0;
    for(int i=0;i<100;i++)
    {
        for(int j=0;j<100;j++)
        {
            int x = rand()%1000;
            if(x%3 == 0)
            {
                vertex_buffer_data[ptr++] = (float)i;vertex_buffer_data[ptr++] = 0.0;vertex_buffer_data[ptr++] = (float)j;
                vertex_buffer_data[ptr++] = (float)(i+1);vertex_buffer_data[ptr++] = 0.0;vertex_buffer_data[ptr++] =(float)j;
                vertex_buffer_data[ptr++] = (float)i;vertex_buffer_data[ptr++] = 0.0;vertex_buffer_data[ptr++] =(float)(j+1);

                vertex_buffer_data[ptr++] = (float)(i+1);vertex_buffer_data[ptr++] = 0.0;vertex_buffer_data[ptr++] = (float)(j+1);
                vertex_buffer_data[ptr++] = (float)(i+1);vertex_buffer_data[ptr++] = 0.0;vertex_buffer_data[ptr++] =(float)j;
                vertex_buffer_data[ptr++] = (float)i;vertex_buffer_data[ptr++] = 0.0;vertex_buffer_data[ptr++] =(float)(j+1);
                t += 18;
            }
            else if(x%3 == 1)
            {
                vertex_buffer_data1[ptr1++] = (float)i;vertex_buffer_data1[ptr1++] = 0.0;vertex_buffer_data1[ptr1++] = (float)j;
                vertex_buffer_data1[ptr1++] = (float)(i+1);vertex_buffer_data1[ptr1++] = 0.0;vertex_buffer_data1[ptr1++] =(float)j;
                vertex_buffer_data1[ptr1++] = (float)i;vertex_buffer_data1[ptr1++] = 0.0;vertex_buffer_data1[ptr1++] =(float)(j+1);

                vertex_buffer_data1[ptr1++] = (float)(i+1);vertex_buffer_data1[ptr1++] = 0.0;vertex_buffer_data1[ptr1++] = (float)(j+1);
                vertex_buffer_data1[ptr1++] = (float)(i+1);vertex_buffer_data1[ptr1++] = 0.0;vertex_buffer_data1[ptr1++] =(float)j;
                vertex_buffer_data1[ptr1++] = (float)i;vertex_buffer_data1[ptr1++] = 0.0;vertex_buffer_data1[ptr1++] =(float)(j+1);
                t1 += 18;
            }
            else
            {
                vertex_buffer_data2[ptr2++] = (float)i;vertex_buffer_data2[ptr2++] = 0.0;vertex_buffer_data2[ptr2++] = (float)j;
                vertex_buffer_data2[ptr2++] = (float)(i+1);vertex_buffer_data2[ptr2++] = 0.0;vertex_buffer_data2[ptr2++] =(float)j;
                vertex_buffer_data2[ptr2++] = (float)i;vertex_buffer_data2[ptr2++] = 0.0;vertex_buffer_data2[ptr2++] =(float)(j+1);

                vertex_buffer_data2[ptr2++] = (float)(i+1);vertex_buffer_data2[ptr2++] = 0.0;vertex_buffer_data2[ptr2++] = (float)(j+1);
                vertex_buffer_data2[ptr2++] = (float)(i+1);vertex_buffer_data2[ptr2++] = 0.0;vertex_buffer_data2[ptr2++] =(float)j;
                vertex_buffer_data2[ptr2++] = (float)i;vertex_buffer_data2[ptr2++] = 0.0;vertex_buffer_data2[ptr2++] =(float)(j+1);
                t2 += 18;
            }
            
            
        }
    }

    this->object = create3DObject(GL_TRIANGLES, t, vertex_buffer_data, COLOR_SURFACE1, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, t1, vertex_buffer_data1, COLOR_SURFACE, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, t2, vertex_buffer_data2, COLOR_SURFACE2, GL_FILL);
}

void Surface::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate_x    = glm::rotate((float) (this->rotation.x * M_PI / 180.0f), glm::vec3(1, 0, 0));
    glm::mat4 rotate_y    = glm::rotate((float) (this->rotation.y * M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 rotate_z    = glm::rotate((float) (this->rotation.z * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // this->rotation *= rotate_z*rotate_x*rotate_y;
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    translate[0][0] = 50.0;
    translate[1][1] = 50.0;
    translate[2][2] = 50.0;
    Matrices.model *= (translate * rotate_x * rotate_y * rotate_z);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
}

void Surface::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Surface::tick() {
    // this->rotation.x += speed;
    // this->rotation.y += speed;
    // this->rotation.z += speed;
    // this->position.z -= 0.1;
    // this->position.y -= speed;
}

