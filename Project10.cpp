// Mason Hamilton
// CST-310-1:55
// 4/26/20
// Professor Citro
// Project 10 Advanded Shadders 2
// Collabrated with Dylan Nasser and Logan Hoots
//All the libaries included
#include <GL/glut.h>
#include <cmath>
#include <cstdlib>
#include <string>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <SOIL/SOIL.h>
#include <vector>
#include <stdio.h>
#include <GL/glu.h>
#define PI 3.1415927
//To use namespace
using namespace std;
//Definng all the colors
GLfloat WHITE[] = {1, 1, 1};
GLfloat RED[] = {1, 0, 0};
GLfloat BLACK[] = {0, 0, 0};
GLfloat GREEN[] = {0, 1, .5};
GLfloat MAGENTA[] = {1, 0, 1};
GLfloat STICK[] = {.8,.7, 1};
float camPitch = 0, yamCam = 0, CamRoll1 = 0, CamRoll2 = 1, angleRoll = 0; //variables for camera angles
float camHeight = 2, camPostition = 2.5, camDepth = -12; //variables to control the camera location
float camX = 0, camY = 0; //variables for camera angles
GLuint sphere_texture, cube_texture[6], cylinder_texture;
int width, height;

//checker board class
class Checkerboard {
  int displayListId;
  int width;
  int depth;
//Checkerclass public
public:
  Checkerboard(int width, int depth): width(width), depth(depth) {}
  double centerx() {return width / 2;}
  double centerz() {return depth / 2;}
  void create() {
    displayListId = glGenLists(1);
    glNewList(displayListId, GL_COMPILE);
    GLfloat lightPosition[] = {4, 3, 7, 1};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glBegin(GL_QUADS);
    glNormal3d(0, 1, 0);
    for (int x = 0; x < width - 1; x++) {
      for (int z = 0; z < depth - 1; z++) {
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE,
                     (x + z) % 2 == 0 ? BLACK : WHITE);
        glVertex3d(x, 0, z);
        glVertex3d(x+1, 0, z);
        glVertex3d(x+1, 0, z+1);
        glVertex3d(x, 0, z+1);
      }
    }
    glEnd();
    glEndList();
  }
  void draw() {
    glCallList(displayListId);
  }
};



//sphere calls to create 
class sphere{
       
    //private sphere class variables
    double radius; // sphere radius
    GLfloat* color; // sphere color
    double x; //sphere x position
    double z; //sphere z position

public:
    
    //sphere Constructor
    sphere(double r, GLfloat* c, double x, double z): radius(r), color(c), x(x), z(z) {}
    
    
    void draw() {
        glEnable(GL_TEXTURE_2D); //Enables 2D textures
        glBindTexture(GL_TEXTURE_2D, sphere_texture); //Binds the sphere texture to use
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //Sets up texture parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //Sets up texture parameters
        
        //pushes the matrix stack
        glPushMatrix();
            
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
            
            // quadric object
            GLUquadricObj * sphere;
            sphere = gluNewQuadric();
            //object texture-able
            gluQuadricTexture(sphere, GL_TRUE);
            

            glTranslated(x, 1, z);

            glRotatef(90, 1.0, 0.0, 0.0);
            
            //the sphere
            gluSphere(sphere, radius, 60, 60);
            
            //stops 2D textures
            glDisable(GL_TEXTURE_2D);
        //Pops off the matrix stack
        glPopMatrix();
    }


};

class cylinder
{
 //private cylinder class variables
    GLfloat* color; // cylinder color
    float height; // cylinder height
    float radius; // cylinder radius
    float x; // cylinder x position
    float z; // cylinder z position
    
public:
    
    //Cylinder Constructor
    cylinder(GLfloat* c, float h, float r, float x, float z): color(c), height(h), radius(r), x(x), z(z) {}
    

    void draw() {
        
        //Enables Textures
        glEnable(GL_TEXTURE_2D);
        //Cylinder texture to the drawing texture
        glBindTexture(GL_TEXTURE_2D, cylinder_texture);
        //Texture Parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        

        glPushMatrix();

            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
            //a quadratic object
            GLUquadricObj* cylinder;
            cylinder = gluNewQuadric();
            gluQuadricTexture(cylinder, GL_TRUE);
 
            //Creates the cylinder
            gluCylinder(cylinder, radius, radius, height, 32, 32);
            glDisable(GL_TEXTURE_2D);

        glPopMatrix();
    }
};
//cube class given to us 
class cube {

    //private cube class variables
    GLfloat* color; // cube color
    float length; // cube length
    float x; // cube x position
    float z; // cube z position
    
public:
    
    //cube Constructor
    cube(GLfloat* c, float l, float x, float z): color(c), length(l), x(x), z(z) {}
    
    //Creates the "draw" function to draw the cube
    void draw() {
        //Enables 2D Texturing
        glEnable(GL_TEXTURE_2D);

        glPushMatrix();
            // cube to the correct location
            glTranslated(x, 1, z);
            //Sets the texture to cube texture[0]
            glBindTexture(GL_TEXTURE_2D, cube_texture[0]);
            //Draws GL Quads for the top of the cube
            glBegin(GL_QUADS);
                // Texture Coordinates and drawing Coordinate
                glTexCoord2f(0, 0); glVertex3d(length / 2, length / 2, length / 2); //First Coord
                glTexCoord2f(1, 0); glVertex3d(-length / 2, length / 2, length / 2); //Second Coord
                glTexCoord2f(1, 1); glVertex3d(-length / 2, length / 2, -length / 2); //Third Coord
                glTexCoord2f(0, 1); glVertex3d(length / 2, length / 2, -length / 2); //Fourth Coord
            glEnd(); 

            glBindTexture(GL_TEXTURE_2D, cube_texture[1]);
            //Draws GL Quads for the left of the cube
            glBegin(GL_QUADS);
                //Sets the Texture Coordinates and drawing coordinate
                glTexCoord2f(0, 0); glVertex3d(length / 2, length / 2, length / 2); 
                glTexCoord2f(1, 0); glVertex3d(length / 2, length / 2, -length / 2);
                glTexCoord2f(1, 1); glVertex3d(length / 2, -length / 2, -length / 2);
                glTexCoord2f(0, 1); glVertex3d(length / 2, -length / 2, length / 2); 
            glEnd(); 

            glBindTexture(GL_TEXTURE_2D, cube_texture[2]);
            //Draws GL Quads for the right of the cube
            glBegin(GL_QUADS);
                //Sets the Texture Coordinates and drawing coordinate
                glTexCoord2f(1, 0); glVertex3d(-length / 2, length / 2, length / 2);  
                glTexCoord2f(0, 0); glVertex3d(-length / 2, length / 2, -length / 2); 
                glTexCoord2f(0, 1); glVertex3d(-length / 2, -length / 2, -length / 2);
                glTexCoord2f(1, 1); glVertex3d(-length / 2, -length / 2, length / 2); 
            glEnd(); 

            glBindTexture(GL_TEXTURE_2D, cube_texture[3]);
            //Draws GL Quads for the back of the cube
            glBegin(GL_QUADS);
                //Sets the Texture Coordinates and drawing coordinate
                glTexCoord2f(1, 0); glVertex3d(length / 2, length / 2, length / 2); 
                glTexCoord2f(0, 0); glVertex3d(-length / 2, length / 2, length / 2); 
                glTexCoord2f(0, 1); glVertex3d(-length / 2, -length / 2, length / 2);
                glTexCoord2f(1, 1); glVertex3d(length / 2, -length / 2, length / 2); 
            glEnd(); 

            glBindTexture(GL_TEXTURE_2D, cube_texture[4]);
            //Draws GL Quads for the front of the cube
            glBegin(GL_QUADS);
                //Sets the Texture Coordinates and drawing coordinate
                glTexCoord2f(0, 0); glVertex3d(length / 2, length / 2, -length / 2); 
                glTexCoord2f(1, 0); glVertex3d(-length / 2, length / 2, -length / 2);
                glTexCoord2f(1, 1); glVertex3d(-length / 2, -length / 2, -length / 2);
                glTexCoord2f(0, 1); glVertex3d(length / 2, -length / 2, -length / 2); 
            glEnd(); 
            
            glBindTexture(GL_TEXTURE_2D, cube_texture[5]);
            //Draws GL Quads for the bottom of the cube
            glBegin(GL_QUADS);
                //Sets the Texture Coordinates and drawing coordinate
                glTexCoord2f(0, 1); glVertex3d(length / 2, -length / 2, length / 2); 
                glTexCoord2f(1, 1); glVertex3d(-length / 2, -length / 2, length / 2);
                glTexCoord2f(1, 0); glVertex3d(-length / 2, -length / 2, -length / 2);
                glTexCoord2f(0, 0); glVertex3d(length / 2, -length / 2, -length / 2); 
            glEnd(); 
            //Binds no texture to the drawing texture
            glBindTexture(GL_TEXTURE_2D, 0);
            //Disables 2D Textures
            glDisable(GL_TEXTURE_2D);
        //Pops off the matrix stack
        glPopMatrix();
        //Sets up the light
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
    }
};

//Creates checkerboard
Checkerboard checkerboard(9, 9);

//Creates a sphere object
sphere sphere(1, WHITE, 1, 3.5);
//Creates a cube object
cube cube(WHITE, 2, 3.5, 3.5);
//Creates a cylinder object
cylinder cylinder(WHITE, 3, 1, 6, 3.5);

//fucntions start all of our gl libraires
//also starts all the lighting for out scene
void init() {
  glEnable(GL_DEPTH_TEST);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, WHITE);
  glLightfv(GL_LIGHT0, GL_SPECULAR, WHITE);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, WHITE);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 50);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  checkerboard.create();
  glEnable(GL_TEXTURE_2D);
}

GLuint load(const char * filename) {
    //Creates a GLuint based on the file that was input
    GLuint id = SOIL_load_OGL_texture(filename, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
    //Enables 2D Textures
    glEnable(GL_TEXTURE_2D);
    //Binds the id texture to the drawing texture
    glBindTexture(GL_TEXTURE_2D, id);
    //Sets up Parameters for the texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //Unbinds the texture to 0
    glBindTexture(GL_TEXTURE_2D, 0);
    //Returns the drawing texture
    return id;
}



//fucntion to display our scene
void display() {
  //cleares all the previous buffers
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //loads idenity matrix
  glLoadIdentity();
  glTranslatef(0, 0, -5);
  //calls our camera look funtion
  gluLookAt(camPostition, camHeight, camDepth, camPostition + camX, camHeight + camY, 3.5, CamRoll1, 1.0 + CamRoll2, 0.0);
  glTranslatef(0, -1, 0);
  //calls our bottom checker board
  checkerboard.draw();
  glTranslatef(1, 1, 3);
  //calls the sphere class
  sphere.draw();
  glTranslatef(2, 0,0);
  //calls cuber class
  cube.draw();
  glRotatef(90, 1, 0, 0);
  glTranslatef(1, 2, -2);
//draws our cylinder class
  cylinder.draw();
  glFlush();
  glutSwapBuffers();
  glutPostRedisplay();
}






void initTexture() {
    //Loads the sphere texture
    sphere_texture = load("Bump-Map.jpg");
    //Loads the texture for each side of the cube
    cube_texture[0] = load("lava2.jpg"); //Positive y face
    cube_texture[1] = load("lava.jpg"); //Negative x face
    cube_texture[2] = load("lava2.jpg"); //Positive x face
    cube_texture[3] = load("lava.jpg"); //Negative z face
    cube_texture[4] = load("lava2.jpg"); //Positive z face
    cube_texture[5] = load("lava.jpg"); //Negative y face
    //Loads the cylinder texture
    cylinder_texture = load("Bump-Picture.jpg"); 
}




//reshape function called to adjust the camera and view
void reshape(GLint w, GLint h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(40.0, GLfloat(w) / GLfloat(h), 1.0, 150.0);
  glMatrixMode(GL_MODELVIEW);
}

void special(int key, int, int) {
  //sets a variable to handle shift, alt, and ctrl keys
    int adjust;
    
   
    switch (key) {
        
        //checks if the input is the left key
        case GLUT_KEY_LEFT: {
            //sets adjust to additional key
            adjust= glutGetModifiers();
            //if input is 'ctrl'
            if (adjust== GLUT_ACTIVE_CTRL) {
                //decreases the yaw
                yamCam -= 2 * PI / 180;
                camX = tan(yamCam);
            }
     
            else {
                //increases the camera to the left
                camPostition += 1;
            }
            break;
        }
        
        
        case GLUT_KEY_RIGHT: {
            //Sets adjust to additional key
            adjust= glutGetModifiers();
            //Checks if adjustis ctrl
            if (adjust== GLUT_ACTIVE_CTRL) {
                //increases the yaw
                yamCam += 2 * PI / 180;
                camX = tan(yamCam);
            }
            
            else {
                //decreases the camera to the right
                camPostition -= 1; 
            }
            break;
        }
        
        //checks if the input is the up key
        case GLUT_KEY_UP: {
            //Sets adjust to additonal key
            adjust= glutGetModifiers();
            //if input is 'shift'
            if (adjust== GLUT_ACTIVE_SHIFT) {
                //Zooms in
                camDepth += 1;
            }
            //Checks if adjustis ctrl
            else if (adjust== GLUT_ACTIVE_CTRL) {
                //decreases pitch
                camPitch -= 2 * PI / 180;
                camY = tan(camPitch);
            }
            
            else {
                //increases the camera height
                camHeight += 1;
            }
            break;
        }
        
        //checks if the input is the down key
        case GLUT_KEY_DOWN: {
            //sets adjust to special button
            adjust= glutGetModifiers();
            //if the input has 'shift'
            if (adjust== GLUT_ACTIVE_SHIFT) {
                //decreaes camera depth
                camDepth -= 1;
            }
            //if the input has 'ctrl' clicked
            else if (adjust== GLUT_ACTIVE_CTRL) {
                //increases pitch
                camPitch += 2 * PI / 180;
                camY = tan(camPitch);
            }
            else {
                //decreases the camera height
                camHeight -= 1;
            }
            break;
        }
    }
    //calls this funciton to redisplay
    glutPostRedisplay();
}

void onKeyboard(unsigned char key, int, int) {
    
    //switch case 
    switch (key) {
        
        //case input '<'
        case '<': {
            //increases roll
            angleRoll += 2 * PI / 180;
            CamRoll1 = 2 * sin(angleRoll);
            CamRoll2 = 2 * cos(angleRoll);
            break;
        }
        
        //case input '<'
        case '>': {
            //decreases roll
            angleRoll -= 2 * PI / 180;
            CamRoll1 = 2 * sin(angleRoll);
            CamRoll2 = 2 * cos(angleRoll);
            break;
        }
        
        //case input esc
        case 27: {
            //exits program
            exit(0);
        }
        
        //case input 'r'
        case 'r': {
            //resest the camera to the starting positon
            camHeight = 2, camPostition = 2.5, camDepth = -12;
            camX = 0, camY = 0;
            camPitch = 0, yamCam = 0, CamRoll1 = 0, CamRoll2 = 1, angleRoll = 0;
        }
    }
    //calls the function to redisplay
    glutPostRedisplay();
}

//Main function that calls all above functions
//then loads into the termnial
int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(800, 800);
  glutCreateWindow("Project 10");
  init();
  initTexture();
  glutDisplayFunc(display); 
  glutReshapeFunc(reshape);
  glutSpecialFunc(special);
  glutKeyboardFunc(onKeyboard);
  glutMainLoop();
  return 1;
}
  
