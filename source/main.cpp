#include "main.h"
#include "timer.h"
#include "ball.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include<GL/freeglut.h>
#include<string>
#include <chrono>
#include<sys/time.h>
#include<set>
#include<queue>
using std::cout; using std::endl;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;
/**************************
* Customizable functions *
**************************/

Ball ball1;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;

Timer t60(1.0 / 60);

void RenderString(float x, float y, const unsigned char* msg, float r, float g, float b)
{  
    glColor3f(r, g, b); 
    glRasterPos2f(x, y);

    glutBitmapString(GLUT_BITMAP_HELVETICA_18, msg);
}


const double gridSize = 55;
int number=12;
int number2=15;
const int SCREEN_WIDTH = 15*gridSize;
const int SCREEN_HEIGHT = gridSize*12;
int length=0;
int width=30;
int height=30;
int *chosen;
int gameover=0;
int timesup=0;
int jhanda2=0;
int finalx;
int finaly;
int youwon=0;

class Blocks {
    public:
        int path[4];    
        int visit; 
        Blocks() {
            visit=0;
            for (int i=0;i< 4;i++) {
                path[i]=0;
            }
        }
}; 
double scaling=0.7;
Blocks *blocks;
int objectflag=0;
class Player {
   
   public:
    double posx;
    double posy;
    double oldposx;
    double oldposy;
    int id;
    double coorx;
    double coory;
    int status;

     Player(double a, double b,int c)
     {
        posx=a;
        posy=b;
        oldposx=a;
        oldposy=b;
        id=c;
        status=0;




     }
     void draw()
     {   if(status==1)
          {return;}
           if(id==1)
            {
                glColor3f( 0, 1,0 );
                glScalef(scaling,scaling,1);
            

            glBegin( GL_POLYGON );
            glEdgeFlag( GL_TRUE );
            for (float angle = 0; angle <  M_PI; angle = angle + 0.01) {
                //glTexCoord2f(0.5 * cos(angle) + 0.5, 0.5 * sin(angle) + 0.5);
                glVertex2f(20 * cos(angle) + posx, -20 * sin(angle) + posy);
            }
            
            glEnd();

            glColor3f( 0, 0,1 );
            glRectd(-5+posx,posy-5,5+posx,posy-10);
            glColor3f(0,1,0);
            glRectd(-20+posx,posy+20,20+posx,posy);
            glRectd(-20+posx,posy+30,-5+posx,posy+20);
            glRectd(20+posx,posy+30,5+posx,posy+20);
            glColor3f(0,0,1);
            glRectd(-30+posx,posy+20,-20+posx,posy);
            
            glEnd();
        }
        else if(id==2)
        {
            glColor3f( 1, 0,0 );
            
            
            glBegin( GL_POLYGON );
            glEdgeFlag( GL_TRUE );
            for (float angle = 0; angle <  M_PI; angle = angle + 0.01) {
                //glTexCoord2f(0.5 * cos(angle) + 0.5, 0.5 * sin(angle) + 0.5);
                glVertex2f(20 * cos(angle) + posx, -20 * sin(angle) + posy);
            }
            glEnd();
            glColor3f( 0, 0,1 );
            glRectd(-5+posx,posy-5,5+posx,posy-10);
            glColor3f(1,0,0);
            glRectd(-20+posx,posy+20,20+posx,posy);
            glRectd(-20+posx,posy+30,-5+posx,posy+20);
            glRectd(20+posx,posy+30,5+posx,posy+20);
            glColor3f(0,0,1);
            glRectd(-30+posx,posy+20,-20+posx,posy);
            //glScalef(1.66,1.66,1);
            glEnd();


        }
            




     }
     void changexy(double a, double b)
     {
        posx=oldposx+a;
        posy=oldposy+b;
        oldposx=posx;
        oldposy=posy;


     }
     void updatecoords()
     {
         posx=((coorx+1.5)*gridSize)*(1/scaling);
         posy=((coory+1.5)*gridSize)*(1/scaling);

     }
        



};

class Buttonsandp{
   
   public:
    double posx;
    double posy;
    double oldposx;
    double oldposy;
    int id;
    double coorx;
    double coory;
    int status;

     Buttonsandp()
     {
        
        status=0;




     }
     void draw()
     {
           if(id==1&&status==0)
            {
                glColor3f( 0, 1,0 );
                //glScalef(scaling,scaling,1);
            

            glBegin( GL_POLYGON );
            glEdgeFlag( GL_TRUE );
            for (float angle = 0; angle <  2*M_PI; angle = angle + 0.01) {
                //glTexCoord2f(0.5 * cos(angle) + 0.5, 0.5 * sin(angle) + 0.5);
                glVertex2f(20 * cos(angle) + posx, -20 * sin(angle) + posy);
            }
            
            glEnd();
        }
        else if(id==2&&status==0)
        {
            glColor3f( 1, 0,0 );
            
            
            glBegin( GL_POLYGON );
            glEdgeFlag( GL_TRUE );
            for (float angle = 0; angle < 2*M_PI; angle = angle + 0.01) {
                //glTexCoord2f(0.5 * cos(angle) + 0.5, 0.5 * sin(angle) + 0.5);
                glVertex2f(20 * cos(angle) + posx, -20 * sin(angle) + posy);
            }
            glEnd();


        }
            




     }
     void updatecoords()
     {
         posx=((coorx+1.5)*gridSize)*(1/scaling);
         posy=((coory+1.5)*gridSize)*(1/scaling);

     }
        



};

int m=0;
class Buttons{
   
   public:
    double posx;
    double posy;
    double oldposx;
    double oldposy;
    int id;
    double coorx;
    double coory;
    int status;

     Buttons(double a,double b)
     {
        
        status=0;
        coorx=a;
        coory=b;




     }
     void draw()
     {
           if(id==1&&status==0)
            {
                glColor3f( 0, 1,0 );
                //glScalef(scaling,scaling,1);
            

            glBegin( GL_POLYGON );
            glEdgeFlag( GL_TRUE );
            for (float angle = 0; angle <  2*M_PI; angle = angle + 0.01) {
                //glTexCoord2f(0.5 * cos(angle) + 0.5, 0.5 * sin(angle) + 0.5);
                glVertex2f(20 * cos(angle) + posx, -20 * sin(angle) + posy);
            }
            glColor3f( 1, 0,0 );
            for (float angle = 0; angle <  2*M_PI; angle = angle + 0.01) {
                //glTexCoord2f(0.5 * cos(angle) + 0.5, 0.5 * sin(angle) + 0.5);
                glVertex2f(10 * cos(angle) + posx, -10 * sin(angle) + posy);
            }
            glEnd();
        }
        else if(id==2&&m==0)
        {
            glColor3f( 1, 0,0 );
            
            
            glBegin( GL_POLYGON );
            glEdgeFlag( GL_TRUE );
            for (float angle = 0; angle < 2*M_PI; angle = angle + 0.01) {
                //glTexCoord2f(0.5 * cos(angle) + 0.5, 0.5 * sin(angle) + 0.5);
                glVertex2f(20 * cos(angle) + posx, -20 * sin(angle) + posy);
            }
            glColor3f( 1, 1,1 );
            for (float angle = 0; angle <  2*M_PI; angle = angle + 0.01) {
                //glTexCoord2f(0.5 * cos(angle) + 0.5, 0.5 * sin(angle) + 0.5);
                glVertex2f(10 * cos(angle) + posx, -10 * sin(angle) + posy);
            }
            glEnd();


        }
            




     }
     void updatecoords()
     {
         posx=((coorx+1.5)*gridSize)*(1/scaling);
         posy=((coory+1.5)*gridSize)*(1/scaling);

     }
        



};



Buttons *button;
Buttons *button2; 
Buttonsandp *objects;
Player *player;
Player *player2; 
int flag=0;
int total_tasks=2;
int tasks_done=0;
int lights=0;
int globcoorx;
int globcoory;
/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    ball1.draw(VP);
}






void tick_elements() {
    ball1.tick();
    camera_rotation_angle += 1;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    // ball1       = Ball(0, 0, COLOR_RED);

    // // Create and compile our GLSL program from the shaders
    // programID = LoadShaders("../source/shaders/shader.vert", "../source/shaders/shader.frag");
    // // Get a handle for our "MVP" uniform
    // Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


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






static void inputK(GLFWwindow* window, int key, int scancode, int action, int mods){
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(window, GL_TRUE);
}

static void error_callback2(int error, const char* description){
    fputs(description, stderr);
}


void change_maze(){
    int i;
    int x, y;

    for( i = 0 ; i < (number-2)*(number2-2) ; i++ ){
        x = i % (number2-2);
        y = i / (number2-2);

        if (blocks[i].path[2]==1) {

               glColor3f( 0, 0, 0);
                glBegin( GL_LINES );
            glVertex2f( (x+2)*gridSize, (y+2)*gridSize );
            glVertex2f( (x+2)*gridSize, (y+1)*gridSize );
            glEnd();
        }
        if (blocks[i].path[0] == 1) {
            glColor3f( 0, 0, 0 );
                glBegin( GL_LINES );
            glVertex2f( (x+1)*gridSize, (y+2)*gridSize );
            glVertex2f( (x+2)*gridSize, (y+2)*gridSize );
            glEnd();
        }
        if (blocks[i].path[1] ==1) {
            glColor3f( 0, 0, 0 );
                glBegin( GL_LINES );
            glVertex2f( (x+1)*gridSize, (y+1)*gridSize );
            glVertex2f( (x+2)*gridSize, (y+1)*gridSize );
            glEnd();
        }
        if (blocks[i].path[3] ==1) {
            glColor3f( 0, 0, 0 );
                glBegin( GL_LINES );
            glVertex2f( (x+1)*gridSize, (y+2)*gridSize );
            glVertex2f( (x+1)*gridSize, (y+1)*gridSize );
            glEnd();
        }
    }
}
int no_of_obs=0;
int jhandi=0;
void gen_maze(){

    int x, y;   // position of the current grid
    int dest;   // direction of to be connected grid
    int b,a;

    int check=0;
    if(length==0)
        {length=1;}
    else if(length==(number-2)*(number2-2))
    {   jhandi=1; return;     }
//cout<<"mmmm"<<endl;
//cout<<length<<endl;
    while (check==0) {
       b= chosen[rand()%length];  
        x = b%(number2-2);
        y = b/(number2-2);
        a= rand()%4;    
          if(a==0){
        
                if(y==(number-2)-1||blocks[x+(number2-2)*(y + 1)].visit ==1)
                    continue;
                blocks[x+(number2-2)*(y + 1)].visit =1;
                blocks[x+(number2-2)*(y + 1)].path[1] =1;
                blocks[x+(number2-2)*(y)].path[0] =1;
                check=1;
                chosen[length] = (number2-2)*( y + 1 ) + x;
                length++;
                
                break;
            }
            else if(a==1){
                if( y == 0 || blocks[x+(number2-2)*(y-1)].visit ==1)
                    continue;

                blocks[x+(number2-2)*(y -1)].visit =1;

                blocks[x+(number2-2)*(y-1)].path[0] =1;
                blocks[x+(number2-2)*(y)].path[1] =1;
                check=1;
                chosen[length] = (number2-2)*(y -1) + x;
                length++;
                break;
            }
            else if(a==3){
                if( x == 0 || blocks[x-1+(number2-2)*(y)].visit == 1)
                    continue;

                blocks[x-1+(number2-2)*(y )].visit=1;

                blocks[x-1+(number2-2)*(y)].path[2] =1;
                blocks[x+(number2-2)*(y)].path[3] =1;
                 check=1;
                chosen[length] = (number2-2)*y+x-1;
                length++;
                break;
            }
           else if(a==2)
            {
                if( x == (number2-2)-1 || blocks[x+1+(number2-2)*(y)].visit ==1 )
                    continue;

                blocks[x+1+(number2-2)*(y)].visit =1;

                blocks[x+1+(number2-2)*(y)].path[3] =1;
                blocks[x+(number2-2)*(y)].path[2] =1;
                 check=1;
                chosen[length] = (number2-2)*y+x+1;
                length++;
                break;
            }
            
        
    }
}

void start_point()
{
  int x, y;
    int a= rand()%2 + 1;
    if( a==1){

        x = rand()%(number2-2);
        y = number-3;
        globcoorx=x;
        globcoory=y;
        blocks[y*(number2-2)+x].path[0] = 1;

        x = rand()%(number2-2);
        finalx=x;
        y = 0;
        finaly=y-1;
        blocks[y*(number2-2)+x].path[1] = 1;
    } else {
        x = (number2-2) - 1;
        y = rand()%(number-2);
        finalx=x+1;
        finaly=y;

        blocks[y*(number2-2)+x].path[2] = 1;

        x = 0;
        y = rand()%(number-2);
        globcoorx=x;
        globcoory=y;
        blocks[y*(number2-2)+x].path[3] = 1;
    }
    chosen = new int [(number-2) * (number2-2)];

    x = rand()%(number2-2);
    y = rand()%(number-2);
    blocks[y*(number2-2)+x].visit =1;
    chosen[0] = (number2-2)*y+x;    

}

void change_grid()
{

   if(flag==0)
    {start_point();flag=1;}
    gen_maze();
   
   change_maze();

    

}
int points=0;
void tick_input(GLFWwindow *window, Player *player, Buttons *button,int a,Buttons buttoni,Player *player2) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up=glfwGetKey(window,GLFW_KEY_UP);
    int down=glfwGetKey(window,GLFW_KEY_DOWN);
    int k=glfwGetKey(window,GLFW_KEY_K);
    if (left) {
        // Do something
        if(blocks[int((player->coory)*(number2-2)+player->coorx)].path[3]==1)
          {player->coorx=player->coorx-1;}

    }
    if (right){
        if(blocks[int((player->coory)*(number2-2)+player->coorx)].path[2]==1)
          {player->coorx=player->coorx+1;}
    }
    if(down){
        if(blocks[int((player->coory)*(number2-2)+player->coorx)].path[0]==1)
          {player->coory=player->coory+1;}
    }
    if(up)
    {
        if(blocks[int((player->coory)*(number2-2)+player->coorx)].path[1]==1)
          {player->coory=player->coory-1;}
    }
    if(player->coorx==button->coorx&&player->coory==button->coory&&button->status==0)
    {
        objectflag=1;
        button->status=1;
        tasks_done++;


    }
    if(player->coorx==buttoni.coorx&&player->coory==buttoni.coory&&m==0)
    {
         m=1;
         buttoni.status=1;
        tasks_done++;
        player2->status=1;
        jhanda2=1;


    }
    if(player->coorx==finalx&&player->coory==finaly&&tasks_done==2)
    {youwon=1;}
    if(objectflag==1)
    {
        for(int i=0;i<no_of_obs;i++)
        {
            if(objects[i].coorx==player->coorx&&objects[i].coory==player->coory)
            {
                if(i<a&&objects[i].status==0)
                {
                    objects[i].status=1;
                    points+=1;
                }
                else if(i>=a&&objects[i].status==0)
                {
                    objects[i].status=1;
                    points-=1;
                }
            }

        }
    }
    player->updatecoords();
}

int main(int argc,char **argv){
    srand( ( unsigned )time( NULL ) );
    GLFWwindow* window;
    glfwSetErrorCallback(error_callback2);
    if (!glfwInit())
        exit(EXIT_FAILURE);
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Maze", NULL, NULL);
    if (!window){
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwSetKeyCallback(window, inputK);


//      unsigned int texture;
// glGenTextures(1, &texture);
// glBindTexture(GL_TEXTURE_2D, texture);
// // set the texture wrapping/filtering options (on the currently bound texture object)
// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   
// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// // load and generate the texture
// int width3,height3,nrChannels;
// stbi_set_flip_vertically_on_load(true);
// unsigned char *data = stbi_load("./container.jpg", &width3, &height3, &nrChannels, STBI_rgb);
// cout<<stbi_failure_reason()<<endl;
// if (data)
// {
//     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width3,height3, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//     glGenerateMipmap(GL_TEXTURE_2D);
//     cout<<"ya"<<endl;

// }
// else
// {
//     std::cout << "Failed to load texture" << std::endl;
// }
// stbi_image_free(data);
set<pair<int,int> >se;
set<pair<int,int> >se2;
for(int i=0;i<10;i++)
{
    int aa=rand()%(number2-2);
    int ba=rand()%(number-2);
    se.insert(make_pair(aa,ba));


}
for(int i=0;i<10;i++)
{
    int aa=rand()%(number2-2);
    int ba=rand()%(number-2);
    se2.insert(make_pair(aa,ba));


}
objects =new Buttonsandp[se.size()+se2.size()];
blocks = new Blocks[(number2-2) * (number-2)];
static Player yo(200, 660,1);
static Player yo2(200,500,2);
static Buttons yo3(rand()%(number2-2),rand()%(number-2));
static Buttons yo4(rand()%(number2-2),rand()%(number-2));
yo3.id=1;
yo4.id=2;
yo2.coorx=rand()%(number2-2);
yo2.coory=rand()%(number-2);
yo2.updatecoords();
no_of_obs=se.size()+se2.size();
glutInit(&argc,argv);
   time_t *ti;
    time_t a=time(ti);
    int c=1;
    int d=0;
    int oldc=100;
     int millisec_since_epoch = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
      int millisec_since_epoch2 = millisec_since_epoch;
      int millisec_since_epoch3 = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
      int millisec_since_epoch4=millisec_since_epoch3;
      
    while (!glfwWindowShouldClose(window)){
        
        int width1, height1;
        glfwGetFramebufferSize(window, &width1, &height1);
        
        glViewport(0, 0, width1, height1);
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        //draw_text();


        //glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        glOrtho(0.0f, width1, height1, 0.0f, 0.0f, 1.0f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

    //attempt to draw lines
       // glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D, texture);
    if(timesup)
    {      string str6="Time's Up";
         RenderString(300,200 , (const unsigned char *)str6.c_str(),1,0, 0);
          
     }
     else if(youwon==1)
     {
            string str6="CONGRATS ! YOU WON";
         RenderString(300,200 , (const unsigned char *)str6.c_str(),0,1, 0);
     }
     else if(gameover==1)
     {
         string str6="Game Over You Lost";
    
         RenderString(300,200 , (const unsigned char *)str6.c_str(),1,0, 0);
         glScalef(2,2,1);

     }
     else{
                        glColor3f( 1.0, 1.0, 1.0 ); 
                    glBegin(GL_LINES);
                    //horizontal
                    for (int i = gridSize; i < SCREEN_HEIGHT; i+=gridSize){
                        glVertex2f(gridSize, i);
                        glVertex2f(SCREEN_WIDTH-gridSize,i);
                    }
                    //vertical
                    for (int i = gridSize; i < SCREEN_WIDTH; i += gridSize){
                        glVertex2f(i,gridSize);
                        glVertex2f(i, SCREEN_HEIGHT-gridSize);
                    }
                    glEnd();
                    change_grid();
                    

                    if (player == NULL) {
                        player = &yo; 
                    }
                    
                    if(d==0)
                    {
                        d=1;
                        player->coorx=globcoorx;
                        player->coory=globcoory;
                        yo.updatecoords();
                    }
                    yo.draw();
                    //glScalef(10,10,1);
                    if (player2 == NULL) {
                        player2 = &yo2; 
                    }
                    yo2.draw();
                    if(button==NULL)
                    {
                        button=&yo3;
                    }
                    if(button2=NULL)
                    {
                        button2=&yo4;
                    }
                    yo3.updatecoords();
                    yo3.draw();
                    yo4.updatecoords();
                    yo4.draw();
                    if(objectflag==1)
                    {
                          int j=0;
                          set<pair<int,int> >::iterator itr;
                        for(itr=se.begin();itr!=se.end();itr++)
                        {
                            objects[j].coorx=itr->first;
                            objects[j].coory=itr->second;
                            objects[j].id=1;
                            objects[j].updatecoords();
                            objects[j].draw();
                            
                            j++;
                        }
                        for(itr=se2.begin();itr!=se2.end();itr++)
                        {
                            objects[j].coorx=itr->first;
                            objects[j].coory=itr->second;
                            objects[j].id=2;
                            objects[j].updatecoords();
                            objects[j].draw();
                            j++;
                        }
                    }

                    glScalef(2.4,2.4,1);
                    string str = "Points: "+to_string(points);
                    string str2= "Time: ";
                    RenderString(10,10 , (const unsigned char *)str.c_str(),0,1, 0);
                    time_t *tii;
                    time_t b=time(tii);
                    c=b-a;
                    c=100-c;
                    if(c==0)
                    {timesup=1;}
                     
                    millisec_since_epoch2 = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
                     millisec_since_epoch4 = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
                    if(millisec_since_epoch2-millisec_since_epoch>200)
                    {tick_input(window,player,button,se.size(),yo4,player2);millisec_since_epoch=millisec_since_epoch2;}
                    if(millisec_since_epoch4-millisec_since_epoch3>1000&&jhandi==1&&jhanda2==0)
                    {
                        int ye=yo2.coorx;
                        int ye2=yo2.coory;
                        int ye3=yo.coorx;
                        int ye4=yo.coory;
                        int vis[(number2-2)*(number-2)];
                        int par[(number2-2)*(number-2)];
                        //cout<<"hhh"<<endl;
                        for(int i=0;i<(number2-2)*(number-2);i++)
                        {
                            vis[i]=0;par[i]=i;
                        }
                        queue<int>q;
                        
                        q.push((number2-2)*ye2+ye);
                        vis[(number2-2)*ye2+ye]=1;
                        int hmm=0;
                        while(1)
                        {
                            int hm=q.front();
                            hmm=hm;
                            //cout<<hm<<endl;
                            if(hm==(ye4*(number2-2)+ye3))
                            {break;}
                            q.pop();
                            if(hm%(number2-2)!=0&&blocks[hm].path[3]==1&&vis[hm-1]==0)
                            {q.push(hm-1);vis[hm-1]=1;par[hm-1]=hm;}
                            if((hm-(number2-2)>=0)&&blocks[hm].path[1]==1&&vis[hm-number2+2]==0)
                            {q.push(hm-number2+2);vis[hm-number2+2]=1;par[hm-number2+2]=hm;}
                            if((hm+number2-2<(number2-2)*(number-2))&&blocks[hm].path[0]==1&&vis[hm+number2-2]==0)
                            {q.push(hm+number2-2);vis[hm+number2-2]=1;par[hm+number2-2]=hm;}
                            if(hm%(number2-2)!=(number2-3)&&blocks[hm].path[2]==1&&vis[hm+1]==0)
                            {q.push(hm+1);vis[hm+1]=1;par[hm+1]=hm;}
                            //cout<<"lll"<<endl;

                        }
                        //cout<<hmm<<endl;
                        while(par[hmm]!=((number2-2)*ye2+ye))
                        {
                            hmm=par[hmm];
                        }
                        ye=hmm%(number2-2);
                        ye2=hmm/(number2-2);
                        yo2.coorx=ye;
                        yo2.coory=ye2;
                        yo2.updatecoords();
                        if(yo2.coorx==yo.coorx&&yo2.coory==yo.coory)
                        {gameover=1;}
                        millisec_since_epoch3=millisec_since_epoch4;






                    }

                    string str3=to_string(c);
                    str2=str2+str3;
                    RenderString(10,20 , (const unsigned char *)str2.c_str(),0,1, 0);
                    string str4="Tasks: ";
                    str4+=to_string(tasks_done)+'/'+to_string(total_tasks);
                    RenderString(10,30 , (const unsigned char *)str4.c_str(),0,1, 0);
                    if(lights==0)
                    {   string str5="Lights: off";
                        RenderString(10,40 , (const unsigned char *)str5.c_str(),0,1, 0);
                    }
                    if(lights==1)
                    {   string str5="Lights: on";
                        RenderString(10,40 , (const unsigned char *)str5.c_str(),0,1, 0);
                    }
     }



    


    glfwSwapBuffers(window);
    glfwPollEvents();

    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}



bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + height)) &&
           (abs(a.y - b.y) * 2 < (a.width + b.height));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
