#include "main.h"
#include "timer.h"
#include "ball.h"
#include "plane.h"
#include "surface.h"
#include "speedometer.h"
#include "fuelbar.h"
#include "score.h"
#include "altitude.h"
#include "lives.h"
#include "volcano.h"
#include "ring.h"
#include "checkpoint.h"
#include "arrow.h"
#include "missile.h"
#include "bomb.h"
#include "cannon.h"
#include "cannonball.h"
#include "parachute.h"
#include "fuelup.h"
#include "compass.h"
#include "point.h"
#include "tree.h"
#include "mountain.h"
using namespace std;

GLMatrices Matrices;
GLMatrices Matrices1;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

//dashboard
Surface surface;
Speedo speedo;
Compass compass;
Fuelbar fuelbar;
Score score[4];
vector<Lives> lives;
Altitude altitude;
Arrow arrow;
Point point;
Plane plane; bounding_box_t plane_bbt;
vector<Parachute> parachute;vector<bounding_box_t> parachute_bbt;
vector<Fuelup> fuelup;vector<bounding_box_t> fuelup_bbt;
vector<Volcano> volcano;vector<bounding_box_t> volcano_bbt;
vector<Cannon> cannon;vector<bounding_box_t> cannon_bbt;
vector<Cannonball> cannonball;vector<bounding_box_t> cannonball_bbt;
vector<Missile> missile;vector<bounding_box_t> missile_bbt;
vector<Bomb> bomb;vector<bounding_box_t> bomb_bbt;
vector<Checkpoint> checkpoint;vector<bounding_box_t> checkpoint_bbt;
vector<Ring> ring;vector<bounding_box_t> ring_bbt;
vector<Tree> tree;
vector<Mountain> mountain;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float shoot_missile,shoot_bomb;
float camera_rotation_angle = 0;
float camx,camy,camz;
float tarx,tary,tarz;
float upx,upy,upz;
float y_speed,z_speed,x_speed;
int flag = 0;
int loop;
int barrel_roll;
int fullscore;
float max_speed,min_speed,cur_speed;
double xcur,ycur;
float zcur;
int pause;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    // glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    glm::vec3 eye ( camx, camy, camz);
    
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (tarx, tary, tarz);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (upx, upy, upz);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    Matrices1.view = glm::lookAt( glm::vec3(0,0,1), glm::vec3(0,0,0), glm::vec3(0,1,0) ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;
    glm::mat4 VP1 = Matrices1.projection * Matrices1.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model
    glm::mat4 MVP1;  // MVP = Projection * View * Model

    // Scene render
    plane.draw(VP);
    surface.draw(VP);
    speedo.draw(VP1);
    compass.draw(VP1);
    fuelbar.draw(VP1);
    altitude.draw(VP1);
    for(int i=0;i<lives.size();i++)lives[i].draw(VP1);
    for(int i=0;i<volcano.size();i++)volcano[i].draw(VP);
    for(int i=0;i<checkpoint.size();i++)checkpoint[i].draw(VP);
    for(int i=0;i<parachute.size();i++)
    {
        parachute[i].draw(VP);
        if(parachute[i].position.y < -5.0)
        {
            parachute.erase(parachute.begin()+i);
            parachute_bbt.erase(parachute_bbt.begin()+i);
        }
    }
    for(int i=0;i<fuelup.size();i++)fuelup[i].draw(VP);
    for(int i=0;i<ring.size();i++)ring[i].draw(VP);

    int temp = fullscore;
    for(int i=0;i<4;i++)
    {
        score[3-i].draw(VP1,temp%10);
        temp /= 10;
    }
    if(!checkpoint.empty()){
        float dirx = checkpoint[0].position.x - plane.position.x;
        float diry = checkpoint[0].position.y - plane.position.y;
        float dirz = checkpoint[0].position.z - plane.position.z;
        float mod = sqrt(dirx*dirx+diry*diry+dirz*dirz);
        arrow.draw(VP,dirx/mod,diry/mod,dirz/mod);
    }
    for(int i=0;i<cannon.size();i++){
        float dirx = plane.position.x - cannon[i].position.x;
        float diry = plane.position.y - cannon[i].position.y;
        float dirz = plane.position.z - cannon[i].position.z;
        float mod = sqrt(dirx*dirx+diry*diry+dirz*dirz);
        cannon[i].draw(VP,dirx/mod,diry/mod,dirz/mod);
    }
    for(int i=0;i<missile.size();i++)
    {
        missile[i].draw(VP);
        if(missile[i].timer <= 0.0)
        {
            missile.erase(missile.begin()+i);
            missile_bbt.erase(missile_bbt.begin()+i);
        }
    }
    for(int i=0;i<bomb.size();i++)
    {
        bomb[i].draw(VP);
        if(bomb[i].timer <= 0.0)
        {
            bomb.erase(bomb.begin()+i);
            bomb_bbt.erase(bomb_bbt.begin()+i);
        }
    }
    for(int i=0;i<cannonball.size();i++)
    {
        cannonball[i].draw(VP);
        if(cannonball[i].timer <= 0.0)
        {
            cannonball.erase(cannonball.begin()+i);
            cannonball_bbt.erase(cannonball_bbt.begin()+i);
        }
    }
    for(int i=0;i<tree.size();i++)
    {
        tree[i].draw(VP);
    }
    for(int i=0;i<mountain.size();i++)
    {
        mountain[i].draw(VP);
    }
    float x1 = (xcur - 400)/10;
    float y1 = (ycur - 400)/10;
    float x = plane.position.x + (cur_speed+x1)*plane.rotate[0][0] - (y1)*plane.rotate[1][0] - (-x_speed+zcur)*plane.rotate[2][0] ;
    float y = plane.position.y + (cur_speed+x1)*plane.rotate[0][1] - (y1)*plane.rotate[1][1] - (-y_speed+zcur)*plane.rotate[2][1] ;
    float z = plane.position.z + (cur_speed+x1)*plane.rotate[0][2] - (y1)*plane.rotate[1][2] - (-z_speed+zcur)*plane.rotate[2][2] ;
    point.position.x = x;        
    point.position.y = y;        
    point.position.z = z;
    glm::vec3 v = normalize(glm::vec3(plane.rotate[2][0],plane.rotate[2][1],plane.rotate[2][2]));
    point.draw(VP,v);        

}

void tick_input(GLFWwindow *window) {
    int fwd = glfwGetKey(window, GLFW_KEY_W);
    int bwd = glfwGetKey(window, GLFW_KEY_S);
    int space = glfwGetKey(window, GLFW_KEY_SPACE);
    int below = glfwGetKey(window, GLFW_KEY_V);
    int left_rotate = glfwGetKey(window, GLFW_KEY_Q);
    int right_rotate = glfwGetKey(window, GLFW_KEY_E);
    int left_tilt = glfwGetKey(window, GLFW_KEY_A);
    int right_tilt = glfwGetKey(window, GLFW_KEY_D);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int one = glfwGetKey(window, GLFW_KEY_1);
    int two = glfwGetKey(window, GLFW_KEY_2);
    int three = glfwGetKey(window, GLFW_KEY_3);
    int four = glfwGetKey(window, GLFW_KEY_4);
    int five = glfwGetKey(window, GLFW_KEY_5);
    int m = glfwGetKey(window, GLFW_KEY_M);
    int b = glfwGetKey(window, GLFW_KEY_B);
    int p = glfwGetKey(window, GLFW_KEY_P);
    int looping = glfwGetKey(window, GLFW_KEY_L);
    int barrel = glfwGetKey(window, GLFW_KEY_R);
    
    if(one)flag=1;
    if(two)flag=2;
    if(three)flag=3;
    if(four)flag=4;
    if(five)flag=5;
    if(p)pause = 1;
    if(looping)loop++;
    if(barrel)barrel_roll++;
    if(fuelbar.val < 0.0)plane.position.y -= 1.5;
    if(fuelbar.val > 0.0)
    {
        z_speed = cur_speed*plane.rotate[2][2];
        x_speed = cur_speed*plane.rotate[2][0];
        y_speed = cur_speed*plane.rotate[2][1];
        plane.position.z -= z_speed; 
        plane.position.x -= x_speed; 
        plane.position.y -= y_speed; 
        
        if(loop%2 == 1)
        {
            plane.rotation.x += 1.0;
            cur_speed = 2.0;
            speedo.rotation = -200.0;
        }
        else if(barrel_roll%2 == 1)
        {
            cur_speed = 2.0;
            plane.rotation.z += 1.0;
            speedo.rotation = -200.0;
        }
        else
        {
        
            if(space)
            {
                plane.position.y += 0.1;
            }
            if(below)
            {
                plane.position.y -= 0.1;
            }
            if(fwd)
            {
                cur_speed += 0.01;
                if(cur_speed > max_speed) cur_speed = max_speed;
                else speedo.rotation -= 1.0;
            }
            else
            {
                cur_speed -= 0.001;
                if(cur_speed < min_speed) cur_speed = min_speed;
                else speedo.rotation += 0.1;
            }
            if(bwd)
            {
                cur_speed -= 0.01;
                if(cur_speed < min_speed) cur_speed = min_speed;
                else speedo.rotation += 1.0;
            }
            if(up) 
            {
                plane.rotation.x += 1.0;
            }
            if(down) 
            {
                plane.rotation.x -= 1.0;
            }
            if(left_rotate)
            {
                plane.rotation.y += 1.0;
            }
            if(right_rotate)
            {
                plane.rotation.y -= 1.0;
            }
            if(left_tilt)
            {
                plane.rotation.z += 1.0;
            }
            if(right_tilt)
            {
                plane.rotation.z -= 1.0;
            }
            
        }
        if(m || shoot_missile == 1)
        {
            if(plane.missile_flag == 0 || shoot_missile == 1)
            {
                system("aplay -c 1 -t wav -q ./../sound/Missile+1.wav&");
                float x1 = (xcur - 400)/40;
                float y1 = -(ycur - 400)/40;
                // y1 = abs(y1);
                float x = point.position.x - plane.position.x;
                float y = point.position.y - plane.position.y;
                float z = point.position.z - plane.position.z;
                // cout<<x1<<" "<<y1<<endl;
                glm::vec3 v = normalize(glm::vec3(x,y,z));
                missile.push_back(Missile(plane.position.x,plane.position.y,plane.position.z,v.x,v.y,v.z,cur_speed,COLOR_BLACK));
                
                bounding_box_t temp;
                temp.x = plane.position.x;temp.y = plane.position.y;temp.y = plane.position.z;
                temp.height = temp.width = temp.depth = 2.0;
                missile_bbt.push_back(temp);
                plane.missile_flag = 1;
                shoot_missile = 0;
            }
        }
        if(b || shoot_bomb == 1)
        {
            if(plane.bomb_flag == 0 || shoot_bomb == 1)
            {
                system("aplay -c 1 -t wav -q ./../sound/Bomb+3.wav&");
                bomb.push_back(Bomb(plane.position.x,plane.position.y,plane.position.z,COLOR_BLACK));
                bounding_box_t temp;
                temp.x = plane.position.x;temp.y = plane.position.y;temp.y = plane.position.z;
                temp.height = temp.width = temp.depth = 2.0;
                bomb_bbt.push_back(temp);
                plane.bomb_flag = 1;
                shoot_bomb = 0;
            }
        }    
    }  
    
    if(flag==1)
    {
        //follow cam
        camx = plane.position.x + 30.0*plane.rotate[2][0] + 10.0*plane.rotate[1][0];
        camy = plane.position.y + 30.0*plane.rotate[2][1] + 10.0*plane.rotate[1][1];
        camz = plane.position.z + 30.0*plane.rotate[2][2] + 10.0*plane.rotate[1][2];
        tarx = plane.position.x;
        tary = plane.position.y;
        tarz = plane.position.z;
        upx = plane.rotate[1][0];
        upy = plane.rotate[1][1];
        upz = plane.rotate[1][2];
        arrow.position.x = plane.position.x - 5.0*plane.rotate[1][0] ;
        arrow.position.y = plane.position.y - 5.0*plane.rotate[1][1] ;
        arrow.position.z = plane.position.z - 5.0*plane.rotate[1][2] ;
    }
    else if(flag==2)
    {
        //tower
        camx = plane.position.x + 50.0;
        camy = plane.position.y + 50.0;
        camz = plane.position.z - 50.0;
        tarx = plane.position.x;
        tary = plane.position.y;
        tarz = plane.position.z;
        upx = 0;
        upy = 1;
        upz = 0;
    }
    else if(flag==3)
    {
        //plane view
        camx = plane.position.x - 12.0*plane.rotate[2][0];
        camy = plane.position.y - 12.0*plane.rotate[2][1];
        camz = plane.position.z - 12.0*plane.rotate[2][2];
        tarx = plane.position.x - 20.0*plane.rotate[2][0];
        tary = plane.position.y - 20.0*plane.rotate[2][1];
        tarz = plane.position.z - 20.0*plane.rotate[2][2];
        upx = plane.rotate[1][0];
        upy = plane.rotate[1][1];
        upz = plane.rotate[1][2]; 
        arrow.position.x = plane.position.x - 20.0*plane.rotate[2][0] + 3.0*plane.rotate[1][0];
        arrow.position.y = plane.position.y - 20.0*plane.rotate[2][1] + 3.0*plane.rotate[1][1];
        arrow.position.z = plane.position.z - 20.0*plane.rotate[2][2] + 3.0*plane.rotate[1][2]; 
    
    }
    else if(flag==4)
    {
        camx = plane.position.x; 
        camy = plane.position.y + 100.0; 
        camz = plane.position.z + 20.0; 
        tarx = plane.position.x; 
        tary = plane.position.y; 
        tarz = plane.position.z; 
        upx = 0;
        upy = 1;
        upz = 0;
        
    }
    else if(flag==5)
    {
        float x = (xcur - 400)/40;
        float y = (ycur - 400)/40;
        if(x > 10)x = 10.0;
        if(x < -10)x = -10.0;
        if(y > 10)y = 10.0;
        if(y < -10)y = -10.0;
        float z = sqrt(400 - x*x - y*y);
        camx = plane.position.x + x/screen_zoom; 
        camy = plane.position.y + y/screen_zoom; 
        camz = plane.position.z + z/screen_zoom; 
        tarx = plane.position.x; 
        tary = plane.position.y; 
        tarz = plane.position.z; 
        upx = 0;
        upy = 1;
        upz = 0;
        
    }
    
}

void tick_elements() {
    
    plane.tick();
    plane_bbt.x = plane.position.x;
    plane_bbt.y = plane.position.y;
    plane_bbt.z = plane.position.z - 5.5;
    // if(plane.position.y < -10.0)plane.position.y = -10.0;
    if(plane.position.y > 8000.0) plane.position.y = 8000.0;
    altitude.position.y = plane.position.y/1000.0;
    altitude.position.x = 0.0;
    
    fuelbar.tick();
    
    compass.tick(glm::vec3(plane.rotate[2][0],plane.rotate[2][1],plane.rotate[2][2]));
    
    
    
    for(int i=0;i<parachute.size();i++)
    {
        parachute[i].tick();
        parachute_bbt[i].x = parachute[i].position.x;
        parachute_bbt[i].y = parachute[i].position.y;
        parachute_bbt[i].z = parachute[i].position.z;
    }
    for(int i=0;i<missile.size();i++)
    {
        missile[i].tick();
        missile_bbt[i].x = missile[i].position.x;
        missile_bbt[i].y = missile[i].position.y;
        missile_bbt[i].z = missile[i].position.z;
    }
    for(int i=0;i<bomb.size();i++)
    {
        bomb[i].tick();
        bomb_bbt[i].x = bomb[i].position.x;
        bomb_bbt[i].y = bomb[i].position.y;
        bomb_bbt[i].z = bomb[i].position.z;
    }
    for(int i=0;i<cannonball.size();i++)
    {
        cannonball[i].tick();
        cannonball_bbt[i].x = cannonball[i].position.x;
        cannonball_bbt[i].y = cannonball[i].position.y;
        cannonball_bbt[i].z = cannonball[i].position.z;
    }
    if(!cannon.empty())
    {
        cannon[0].tick();
        if(cannon[0].flag == 0)
        {
            cannonball.push_back(Cannonball( cannon[0].position.x, cannon[0].position.y, cannon[0].position.z, cannon[0].rotate[2][0], cannon[0].rotate[2][1], cannon[0].rotate[2][2], COLOR_BLACK));
            bounding_box_t temp;
            temp.x = cannon[0].position.x;temp.y = cannon[0].position.y;temp.y = cannon[0].position.z;
            temp.height = temp.width = temp.depth = 2.0;
            cannonball_bbt.push_back(temp);
            cannon[0].flag = 1;
        }
    }
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    plane = Plane(0.0, 60.0, 0.0, COLOR_RED);

    plane_bbt.x = plane.position.x;
    plane_bbt.y = plane.position.y;
    plane_bbt.x = plane.position.z - 5.5;
    plane_bbt.height = plane_bbt.width = plane_bbt.depth = 12.0;

    point = Point(0.0,0.0,0.0,COLOR_BLACK);

    surface = Surface(-2500.0, -10.0, -2500.0, COLOR_GREEN);
    speedo = Speedo(-33.0, -33.0, 0.0, COLOR_BLACK);
    compass = Compass(33.0, -33.0, 0.0, COLOR_BLACK);
    fuelbar = Fuelbar(-1.0, -33.0, 0.0, COLOR_BLACK);
    altitude = Altitude(7.0, -33.0, 0.0, COLOR_BLACK);
    arrow = Arrow(plane.position.x, plane.position.y - 4.0, plane.position.z, COLOR_BLACK);
    for(int i=0;i<4;i++)score[i] = Score((float)i*5.2-35.0,34.0,COLOR_BLACK);
    for(int i=0;i<5;i++)lives.push_back(Lives((float)i*2.5+28.0,35.0,COLOR_RED));

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");
    Matrices1.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


void generateObjects()
{
    parachute.clear();
    parachute_bbt.clear();
    volcano.clear();
    volcano_bbt.clear();
    fuelup.clear();
    fuelup_bbt.clear();
    checkpoint.clear();
    checkpoint_bbt.clear();
    cannon.clear();
    cannon_bbt.clear();
    ring.clear();
    ring_bbt.clear();
    missile.clear();
    missile_bbt.clear();
    bomb.clear();
    bomb_bbt.clear();
    cannonball.clear();
    cannonball_bbt.clear();
    tree.clear();
    fuelbar.val = 8.0;

    float planex = plane.position.x;
    float planey = plane.position.y;
    float planez = plane.position.z;
    int cnt = rand()%45;
    cnt = max(cnt,40);
    for(int i=0;i<cnt;i++)
    {
        float x = (float)(rand()%1000);
        float z = (float)(rand()%1000);
        if((int)z%2)z*=-1.0;
        if(!(int)x%2)x*=-1.0;
        parachute.push_back(Parachute(planex + x, 100.0, planez + z, COLOR_BLACK));
        bounding_box_t temp;
        temp.x = planex+x;temp.y = 100.0;temp.z = planez+z;
        temp.width = 10.0;temp.height = 10.0;temp.depth = 10.0;
        parachute_bbt.push_back(temp);
    }
    cnt = rand()%100;
    cnt = max(cnt,80);
    for(int i=0;i<cnt;i++)
    {
        float x = (float)(rand()%1500);
        float y = (float)(rand()%150);
        float z = (float)(rand()%1500);
        if(!(int)z%2)z*=-1.0;
        if(!(int)x%2)x*=-1.0;
        ring.push_back(Ring(planex+x,y,planez+z,COLOR_RED));
        bounding_box_t temp;
        temp.x = planex+x;temp.y = y;temp.z = planez+z;
        temp.width = 0.5;temp.height = 0.5;temp.depth = 0.5;
        ring_bbt.push_back(temp);
    
    }
    cnt = rand()%25;
    cnt = max(cnt,20);
    for(int i=0;i<cnt;i++)
    {
        float x = (float)(rand()%1500);
        float z = (float)(rand()%1500);
        if(!(int)z%2)z*=-1.0;
        if(!(int)x%2)x*=-1.0;
        volcano.push_back(Volcano(planex+x, -10.2, planez+z, COLOR_BLACK));
        bounding_box_t temp;
        temp.x = planex+x;temp.y = -2.5;temp.z = planez+z;
        temp.width = 15.0;temp.height = 150000.0;temp.depth = 15.0;
        volcano_bbt.push_back(temp);
    }
    for(int i=0;i<1;i++)
    {
        float x = (float)(rand()%1500);
        float z = (float)(rand()%1500);
        x = max((int)x,850);
        z = max((int)z,850);
        if(!((int)z%2))z*=-1.0;
        if((int)x%2)x*=-1.0;
        checkpoint.push_back(Checkpoint(x, -10.0, z, COLOR_WHITE));
        cannon.push_back(Cannon(x, 0.0, z, COLOR_BLACK));
        bounding_box_t temp;
        temp.x = x;temp.y = -6.5;temp.z = z;
        temp.width = 16.0;temp.height = 12.0;temp.depth = 16.0;
        checkpoint_bbt.push_back(temp);
    }
    cnt = rand()%1000;
    cnt = max(cnt,950);
    for(int i=0;i<cnt;i++)
    {
        float x = (float)(rand()%2500);
        float z = (float)(rand()%2500);
        if((int)z%2)z*=-1.0;
        if((int)x%2)x*=-1.0;
        tree.push_back(Tree(x,-15.5,z,COLOR_GREEN));
    }
    cnt = rand()%30;
    cnt = max(cnt,25);
    for(int i=0;i<cnt;i++)
    {
        float x = (float)(rand()%1500);
        float z = (float)(rand()%1500);
        if((int)z%2)z*=-1.0;
        if(!((int)x%2))x*=-1.0;
        mountain.push_back(Mountain(planex+x,-10.0,planez+z,COLOR_WHITE));
    }   
}


void reduce_lives(int x)
{
    for(int i=0;i<lives.size();i++)
    {
        if(lives[i].flag > x)
        {
            lives[i].flag -= x;
            x -= x;
        }
        else
        {
            x -= lives[i].flag;
            lives[i].flag = 0;
        }
    }
}
void collisions()
{
    for(int i=0;i<ring.size();i++)
    {
        if(detect_collision(ring_bbt[i],plane_bbt))
        {
            ring.erase(ring.begin()+i);
            ring_bbt.erase(ring_bbt.begin()+i);
            for(int i=0;i<lives.size();i++)lives[i].flag = 4;
        }
    }
    for(int i=0;i<parachute.size();i++)
    {
        if(detect_collision(parachute_bbt[i],plane_bbt))
        {
            parachute.erase(parachute.begin()+i);
            parachute_bbt.erase(parachute_bbt.begin()+i);
            reduce_lives(3);
        }
    }
    for(int i=0;i<fuelup.size();i++)
    {
        if(detect_collision(fuelup_bbt[i],plane_bbt))
        {
            fuelup.erase(fuelup.begin()+i);
            fuelup_bbt.erase(fuelup_bbt.begin()+i);
            fuelbar.val = 8.0;
        }
    }
    for(int i=0;i<volcano.size();i++)
    {
        if(detect_collision(volcano_bbt[i],plane_bbt))
        {
            reduce_lives(16);
        }
    }
    for(int i=0;i<cannonball_bbt.size();i++)
    {
        if(detect_collision(cannonball_bbt[i],plane_bbt))
        {
            system("aplay -c 1 -t wav -q ./../sound/Explosion+1.wav&");
            cannonball.erase(cannonball.begin()+i);
            cannonball_bbt.erase(cannonball_bbt.begin()+i);
            reduce_lives(1);

        }
    }

    for(int i=0;i<parachute_bbt.size();i++)
    {
        for(int j=0;j<missile_bbt.size();j++)
        {
            if(detect_collision(parachute_bbt[i],missile_bbt[j]))
            {
                missile.erase(missile.begin()+j);
                missile_bbt.erase(missile_bbt.begin()+j);
                fullscore++;
                parachute[i].val--;
                if(parachute[i].val <= 0)
                {
                    system("aplay -c 1 -t wav -q ./../sound/Explosion+1.wav&");
                    fuelup.push_back(Fuelup(parachute[i].position.x,parachute[i].position.y,parachute[i].position.z,COLOR_GREEN));
                    bounding_box_t temp;
                    temp.x = parachute[i].position.x;temp.y = parachute[i].position.y;temp.z = parachute[i].position.z;
                    temp.width = temp.height = temp.depth = 2.0;
                    fuelup_bbt.push_back(temp);
                    parachute.erase(parachute.begin()+i);
                    parachute_bbt.erase(parachute_bbt.begin()+i);
                }
            }
        }
    }
    for(int i=0;i<parachute_bbt.size();i++)
    {
        for(int j=0;j<bomb_bbt.size();j++)
        {
            if(detect_collision(parachute_bbt[i],bomb_bbt[j]))
            {
                bomb.erase(bomb.begin()+j);
                bomb_bbt.erase(bomb_bbt.begin()+j);
                fullscore+=2;
                parachute[i].val-=2;
                if(parachute[i].val <= 0)
                {
                    system("aplay -c 1 -t wav -q ./../sound/Explosion+1.wav&");
                    fuelup.push_back(Fuelup(parachute[i].position.x,parachute[i].position.y,parachute[i].position.z,COLOR_GREEN));
                    bounding_box_t temp;
                    temp.x = parachute[i].position.x;temp.y = parachute[i].position.y;temp.z = parachute[i].position.z;
                    temp.width = temp.height = temp.depth = 2.0;
                    fuelup_bbt.push_back(temp);
                    parachute.erase(parachute.begin()+i);
                    parachute_bbt.erase(parachute_bbt.begin()+i);
                }
            }
        }
    }

    for(int i=0;i<cannonball_bbt.size();i++)
    {
        for(int j=0;j<missile_bbt.size();j++)
        {
            if(detect_collision(cannonball_bbt[i],missile_bbt[j]))
            {
                system("aplay -c 1 -t wav -q ./../sound/Explosion+1.wav&");
                missile.erase(missile.begin()+j);
                missile_bbt.erase(missile_bbt.begin()+j);
                cannonball.erase(cannonball.begin()+i);
                cannonball_bbt.erase(cannonball_bbt.begin()+i);
                fullscore++;
            }
        }
    }
    for(int i=0;i<cannonball_bbt.size();i++)
    {
        for(int j=0;j<bomb_bbt.size();j++)
        {
            if(detect_collision(cannonball_bbt[i],bomb_bbt[j]))
            {
                system("aplay -c 1 -t wav -q ./../sound/Explosion+1.wav&");
                bomb.erase(bomb.begin()+j);
                bomb_bbt.erase(bomb_bbt.begin()+j);
                cannonball.erase(cannonball.begin()+i);
                cannonball_bbt.erase(cannonball_bbt.begin()+i);
                fullscore++;
            }
        }
    }

    for(int i=0;i<checkpoint_bbt.size();i++)
    {
        for(int j=0;j<missile_bbt.size();j++)
        {
            if(detect_collision(checkpoint_bbt[i], missile_bbt[j]))
            {
                missile.erase(missile.begin()+j);
                missile_bbt.erase(missile_bbt.begin()+j);
                fullscore+=5;
                checkpoint[i].val--;
                if(checkpoint[i].val <= 0)
                {
                    fullscore += 60;
                    cannon.erase(cannon.begin()+i);
                    checkpoint.erase(checkpoint.begin()+i);
                    checkpoint_bbt.erase(checkpoint_bbt.begin()+i);
                    system("aplay -c 1 -t wav -q ./../sound/Explosion+1.wav&");
                }
            }
        }
    }
    for(int i=0;i<checkpoint_bbt.size();i++)
    {
        for(int j=0;j<bomb_bbt.size();j++)
        {
            if(detect_collision(checkpoint_bbt[i], bomb_bbt[j]))
            {
                bomb.erase(bomb.begin()+j);
                bomb_bbt.erase(bomb_bbt.begin()+j);
                fullscore+=10;
                checkpoint[i].val-=2;
                if(checkpoint[i].val <= 0)
                {
                    fullscore += 60;
                    cannon.erase(cannon.begin()+i);
                    checkpoint.erase(checkpoint.begin()+i);
                    checkpoint_bbt.erase(checkpoint_bbt.begin()+i);
                    system("aplay -c 1 -t wav -q ./../sound/Explosion+1.wav&");
                }
            }
        }
    }
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 800;
    int height = 800;
    camx = 0.0;camy = 30.0;camz = 30.0;
    tarx = 0.0;tary = 0.0;tarz = 0.0;
    upx = 0.0;upy = 1.0;upz = 0.0;
    y_speed = 0.3;z_speed = 0.1;x_speed = 0.0;
    max_speed = 3.0;min_speed = 0.0;cur_speed = min_speed;
    fullscore = 0;
    zcur = 50.0;
    flag = 1;
    window = initGLFW(width, height);

    initGL (window, width, height);
    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers
        if (t60.processTick()) 
        {
            if(pause == 1)
            {
                if(glfwGetKey(window, GLFW_KEY_O))
                {
                    pause = 0;
                }
            }
            else
            {
                int sum = 0;
                for(int i=0;i<lives.size();i++)
                {
                    sum += lives[i].flag;
                }
                if(sum == 0 || plane.position.y < surface.position.y + 1.5)exit(0);
                glfwGetCursorPos(window, &xcur, &ycur);
                float x = (xcur - 400)/10;
                float y = (400 - ycur)/10;
                float z = sqrt(200 - x*x - y*y);
                // 60 fps
                // OpenGL Draw commands
                if(checkpoint.empty())
                {
                    generateObjects();
                }
                collisions(); 
                draw();
                // Swap Frame Buffer in double buffering
                glfwSwapBuffers(window);

                tick_elements();
                tick_input(window);
            }
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height)) &&
           (abs(a.z - b.z) * 2 < (a.depth + b.depth));
}

void reset_screen() {
    float top    = screen_center_y + 40;
    float bottom = screen_center_y - 40;
    float left   = screen_center_x - 40;
    float right  = screen_center_x + 40;
    Matrices.projection = glm::perspective(45.0,1.0,0.1,1000.0);
    Matrices1.projection = glm::ortho(left,right,bottom,top,0.1f,1000.0f);
}
