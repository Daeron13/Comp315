/*
 * Displays the a wired teapot using the GLUT wire frame objects
 */
#include <windows.h>  // for MS Windows
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <iostream>
#include<math.h>
#include <time.h>
#include <vector>
#include <list>
#include <cstdlib>
#include <fstream>
using namespace std;

//const float PI = 22.0/7.0;
const int FPS = 30;
boolean flag=false;
int wallcords[400][2];
// Global variables
float x_rotation=0;
float y_rotation=0;
int timet=0;
float turn_inc;
float z_dist_at;
float camera[3][3] = {
            {0,0, -z_dist_at},
            {0, 0, 0},
            {0, 1.0f, 0}
    };//100 > 0 for normal view
float lx, ly, lz;
float angle;

void resetCamera(){
		angle = 0;
		lx=0;
		lz=z_dist_at;
		camera[0][2] =  -z_dist_at;
}


/* Initialize OpenGL Graphics */
void init()
{
    //glShadeModel(GL_SMOOTH);
    // Set "clearing" or background color
    glClearColor(0, 0, 0, 1); // White and opaque

    glEnable(GL_DEPTH_TEST); // turns on hidden surface removal so that objects behind other objects do not get displayed





    turn_inc = 2.0; // in degrees

    z_dist_at = 95.0;

    resetCamera();



}

void setCamera(){

		//cout << angle << " lx: " << lx << " lz:" << lz << "\n";
    	// Set the camera

		gluLookAt(	camera[0][0], camera[0][1], camera[0][2],
    				camera[1][0], camera[1][1], camera[1][2],
    				camera[2][0], camera[2][1], camera[2][2]  );

}

void lookAround(){
    cout << "\n Looking around \n";
    // distance
    for(int i=360; i>=0; i-=0.0001){
        double a = M_PI*i/180.0;

        lx = z_dist_at * sin(a);
        lz = z_dist_at * cos(a);

		cout << angle << " lx: " << lx << " lz:" << lz << "\n";

        camera[1][0]=camera[1][0]+lx;
        camera[1][2]=camera[1][2]+lz;

        glutPostRedisplay();

        timet = glutGet(GLUT_ELAPSED_TIME); // get the elapsed time in milliseconds since glutInit() was executed

        glutPostRedisplay();

    }

    cout << "\n Completed looking around \n";
        //glutTimerFunc(1000/v, myTimer, v);  //could use a timer function to repeat instead of a loop

}

void myTimer(){


}
void drawFloor(){


glColor3ub((byte) 0, (byte) 64, (byte) 0); // green
//glBindTexture(GL_TEXTURE_2D, textureId)

glBegin(GL_POLYGON);
glVertex3f(-100.0f, -5.0f, -100.0f);
glVertex3f(-100.0f, -5.0f, 100.0f);
glVertex3f(100.0f, -5.0f, 100.0f);
glVertex3f(100.0f, -5.0f, -100.0f);
glEnd();
}
void drawCeiling() {

glColor3ub((byte) 0, (byte) 0, (byte) 100);
glBegin(GL_POLYGON);
glVertex3f(-100.0f, 15.0f, -100.0f);
glVertex3f(-100.0f, 15.0f, 100.0f);
glVertex3f(100.0f, 15.0f, 100.0f);
glVertex3f(100.0f, 15.0f, -100.0f);
glEnd();
}
void drawWall()
{
 float z=-95.0f;
 glPushMatrix();
 glColor3f(1.0f, 0.0f , 0.0f);
 glTranslatef(0,0,0);
 glutSolidCube(200);
 glPopMatrix();

  for (int i=0;i<400;i++)
   {

          // cout << " x  " << wallcords[i][0];

          // cout << " z " << wallcords[i][1] << " coords " ;

           if (wallcords[i][0]<100){

                           glPushMatrix();

                            /**/

                            glTranslatef(wallcords[i][0],0,wallcords[i][1]);

                            glColor3f(1.0f, 1.0f , 0.0f);
                            glutSolidCube(10);
                            glPopMatrix();}


           }
           float light_pos[]={-2.00,2.00,2.00,1.00};
                           float light_Ka[]={0.00,0.00,0.00,1.00};
                           float light_Kd[]={1.00,1.00,1.00,1.00};
                           float light_Ks[]={1.00,1.00,1.00,1.00};
                           glLightfv(GL_LIGHT0,GL_POSITION,light_pos);
                           glLightfv(GL_LIGHT0,GL_AMBIENT,light_Ka);
                           glLightfv(GL_LIGHT0,GL_DIFFUSE,light_Kd);
                           glLightfv(GL_LIGHT0,GL_SPECULAR,light_Ks);
                        float Imodel_Ka[]={0.22,0.20,0.20,1.00};
                        glLightModelfv(GL_LIGHT_MODEL_AMBIENT,Imodel_Ka);



   }








void mazeGenerator()
{

   srand(time(0));

   const int maze_size_x=20;
   const int maze_size_y=20;
   vector < vector < bool > > maze;
   list < pair < int, int> > drillers;

   maze.resize(maze_size_y);
   for (size_t y=0;y<maze_size_y;y++)
           maze[y].resize(maze_size_x);

   for (size_t x=0;x<maze_size_x;x++)
           for (size_t y=0;y<maze_size_y;y++)
                   maze[y][x]=false;

   drillers.push_back(make_pair(maze_size_x/2,maze_size_y/2));
   while(drillers.size()>0)
   {
           list < pair < int, int> >::iterator m,_m,temp;
           m=drillers.begin();
           _m=drillers.end();
           while (m!=_m)
           {
                   bool remove_driller=false;
                   switch(rand()%4)
                   {
                   case 0:
                           (*m).second-=2;
                           if ((*m).second<0 || maze[(*m).second][(*m).first])
                           {
                                   remove_driller=true;
                                   break;
                           }
                           maze[(*m).second+1][(*m).first]=true;
                           break;
                   case 1:
                           (*m).second+=2;
                           if ((*m).second>=maze_size_y || maze[(*m).second][(*m).first])
                           {
                                   remove_driller=true;
                                   break;
                           }
                           maze[(*m).second-1][(*m).first]=true;
                           break;
                   case 2:
                           (*m).first-=2;
                           if ((*m).first<0 || maze[(*m).second][(*m).first])
                           {
                                   remove_driller=true;
                                   break;
                           }
                           maze[(*m).second][(*m).first+1]=true;
                           break;
                   case 3:
                           (*m).first+=2;
                           if ((*m).first>=maze_size_x || maze[(*m).second][(*m).first])
                           {
                                   remove_driller=true;
                                   break;
                           }
                           maze[(*m).second][(*m).first-1]=true;
                           break;
                   }
                   if (remove_driller)
                           m = drillers.erase(m);
                   else
                   {
                           drillers.push_back(make_pair((*m).first,(*m).second));
                           // uncomment the line below to make the maze easier
                           // if (rand()%2)
                           drillers.push_back(make_pair((*m).first,(*m).second));

                           maze[(*m).second][(*m).first]=true;
                           ++m;
                   }
           }
   }

   // Done
   float xc=-95.0f;
   float zc=-95.0f;
   int i=0;
   for (size_t y=0;y<maze_size_y;y++)
   {


           for (size_t x=0;x<maze_size_x;x++)
           {
                   if (maze[y][x]==false){

                           wallcords[i][0]=xc;
                           wallcords[i][1]=zc;
                            zc+=10.0f;
                            i++;


           }
           else{
                           wallcords[i][0]=100;
                           wallcords[i][1]=zc;
                            zc+=10.0f;
                            i++;

           }

   }       zc=-95.0f;
           xc+=10.0f;



}
}

void render(){

    // GL_DEPTH_BUFFER_BIT - resets the depth test values for hidden surface removal
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reset transformations
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // Set the camera
    /*gluLookAt(0, 5, -50, // camera position
                  0, 0, 0, // look at position, line of sight
                  0, 1, 0); // up direction (vector) for camera tilt
*/
    setCamera();

    drawFloor();
    drawCeiling();
    if(flag==false)
    {
    mazeGenerator();
    flag=true;
    }
    drawWall();


    // Draw ground


    glFlush();   // ******** DO NOT FORGET THIS **********

}


void update()
{
    timet = glutGet(GLUT_ELAPSED_TIME); // get the elapsed time in milliseconds since glutInit() was executed
    // do nothing
}
/* Handler for window-repaint event. Call back when the window first appears and
   whenever the window needs to be re-painted. */
void display()
{
    update();

    render();
}

/* Handler for window re-size event. Called back when the window first appears and
   whenever the window is re-sized with its new width and height */

void reshape(int w, int h)
{

    // Prevent a divide by zero, when window is too short
    // (you cant make a window of zero width).
    if(h == 0)	h = 1;

    GLfloat ratio = 1.0f * (GLfloat)w / (GLfloat)h;

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Reset the coordinate system before modifying
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Set the clipping volume

    gluPerspective(45, ratio, 0.1, 300);//400=set distance away from screen
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();



}

void processNormalKeys(unsigned char key, int x, int y) {

	switch (key) {
		//case 'l' : lookAround(); break;
		case 27 :  exit(0); break;
	}
    glutPostRedisplay();
}


void inputKey(int key, int ix, int iy) {
    float a, x, z;
	switch (key) {
		case GLUT_KEY_LEFT :
        	angle += turn_inc;
			a = M_PI*angle/180.0;
			lx = z_dist_at *sin(a);
			lz = z_dist_at *cos(a);
			camera[1][0]=camera[0][0]+lx;
			camera[1][2]=camera[0][2]+lz;
            break;

		case GLUT_KEY_RIGHT :
           	angle -= turn_inc;
			a = M_PI*angle/180.0;
			lx = z_dist_at *sin(a);
			lz = z_dist_at *cos(a);
			camera[1][0]=camera[0][0]+lx;
			camera[1][2]=camera[0][2]+lz;
		    break;

		case GLUT_KEY_UP :
		    a = M_PI*angle/180.0;
			x =  sin(a);
			z = cos(a);
        	camera[0][0] += x; // move x by
            camera[0][2] += z;
        	camera[1][0] += x; // move x by
            camera[1][2] += z;
		    break;
		case GLUT_KEY_DOWN :
		    a = M_PI*angle/180.0;
			x =  sin(a);
			z = cos(a);
        	camera[0][0] -= x; // move x by
            camera[0][2] -= z;
        	camera[1][0] -= x; // move x by
            camera[1][2] -= z;
            break;
	}

    glutPostRedisplay();
}

/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv)
{
    glutInit(&argc, argv);          // Initialize GLUT

    glutInitWindowSize(640, 480);   // Set the window's initial width & height - non-square
    glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
    glutCreateWindow("Maze");  // Create window with the given title

    init();                       // Our own OpenGL initialization

    glutDisplayFunc(display);       // Register callback handler for window re-paint event
    glutReshapeFunc(reshape);       // Register callback handler for window re-size event

	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(inputKey);

    //glutTimerFunc(1000,myTimer,FPS);

    glutMainLoop();                 // Enter the infinite event-processing loop
    return 0;
}

