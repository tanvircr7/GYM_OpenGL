#include <windows.h>
#include <mmsystem.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include<math.h>
#include<bits/stdc++.h>
#include "BmpLoader.h"



using namespace std;

double Txval=0,Tyval=0,Tzval=0;
double windowHeight=1200, windowWidth=1400;
double gammaa = 0;
GLfloat alpha = 0.0, theta = 0.0, axis_x=0.0, axis_y=0.0;
GLfloat eye_x = 0.0, eye_y = 0.0, eye_z = 50.0;
GLfloat lookat_x = 0.0, lookat_y = 0.0, lookat_z = 0.0;
GLdouble up_x = 0.0;
GLdouble up_y = 1.0;
GLdouble up_z = 0.0;
GLdouble sx=1.0,sy=1.0,sz=1.0;
GLdouble tx,ty,tz=0;

double anglePitch=0,angleYaw=90,angleRoll = 0;
GLboolean bRotate = false, uRotate = false, light0 = false,light1=false,light2=false,zRotate = false;
int pilotPitch=0,pilotYaw=0,pilotRoll=0;
unsigned int ID,ID1;


//static GLfloat v_box[8][3] =
//{
//    {-2.0, 0.0, 0.0},
//    {2.0, 0.0, 0.0},
//    {-2.0, 0.0, 2.0},
//    {2.0, 0.0, 2.0},
//
//    {-2.0, 2.0, 0.0},
//    {2.0, 2.0, 0.0},
//    {-2.0, 2.0, 2.0},
//    {2.0, 2.0, 2.0}
//};
//
//static GLubyte quadIndices[6][4] =
//{
//    {0,2,3,1},
//    {0,2,6,4},
//    {2,3,7,6},
//    {1,3,7,5},
//    {1,5,4,0},
//    {6,7,5,4}
//};

static GLfloat v_pyramid[8][3] =
{
    {-1.0, -1.0, 1.0},
    {1.0, -1.0, 1.0},
    {1.0, 1.0, 1.0},
    {-1.0, 1.0, 1.0},


    {-1.0, -1.0, -1.0},
    {1.0, -1.0, -1.0},
    {1.0, 1.0, -1.0},
    {-1.0, 1.0, -1.0},


};


static GLubyte quadIndices[6][4] =
{
    //{4,5,6,7},
    {0,1,2,3},
    {7,6,5,4},
    {2,6,7,3},

    {0,4,5,1},
    {2,1,5,6},
    {7,4,0,3},
};


static GLfloat colors[8][3] =
{
    //polygon colors
    {1.0, 1.0, 1.0},
    {0.5, 0.5, 0.5},
    //quad er shuru ekhan theke
    {0.8,0.5,0.3}, //right surface
    {0.8,0.5,0.5}, //shamner tol
    {0.6,0.4,0.2}, //left surface
    {0.6,0.4,0.2}, //pisertol
    {0.8,0.5,0.3}, //upper surface
    {1.0, 0.5, 0.0} //bottom surface
};

static void getNormal3p
(GLfloat x1, GLfloat y1,GLfloat z1, GLfloat x2, GLfloat y2,GLfloat z2, GLfloat x3, GLfloat y3,GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2-x1;
    Uy = y2-y1;
    Uz = z2-z1;

    Vx = x3-x1;
    Vy = y3-y1;
    Vz = z3-z1;

    Nx = Uy*Vz - Uz*Vy;
    Ny = Uz*Vx - Ux*Vz;
    Nz = Ux*Vy - Uy*Vx;

    glNormal3f(Nx,Ny,Nz);
}

void drawcube(GLfloat r,GLfloat g,GLfloat b)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { r, g, b, 1.0 };
    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    GLfloat mat_em[] = {1.0,1.0,1.0,1.0};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);


    for (GLint i = 0; i <6; i++)
    {
        glBegin(GL_QUADS);
        glVertex3fv(&v_pyramid[quadIndices[i][0]][0]);
        glTexCoord2f(1,1);
        glVertex3fv(&v_pyramid[quadIndices[i][1]][0]);
        glTexCoord2f(1,0);
        glVertex3fv(&v_pyramid[quadIndices[i][2]][0]);
        glTexCoord2f(0,0);
        glVertex3fv(&v_pyramid[quadIndices[i][3]][0]);
        glTexCoord2f(0,1);
        glEnd();

    }
}




void teapot(GLfloat r,GLfloat g,GLfloat b)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { r, g, b, 1.0 };
    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    GLfloat mat_em[] = {1.0,1.0,1.0,1.0};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    glTexCoord2f(1,1);
    glutSolidTeapot(1.4);

}

void knob(GLfloat r,GLfloat g,GLfloat b)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { r, g, b, 1.0 };
    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    GLfloat mat_em[] = {1.0,1.0,1.0,1.0};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);



    glutSolidCube(2);

}

void ceiling_light_holder(GLfloat r,GLfloat g,GLfloat b)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { r, g, b, 1.0 };
    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    GLfloat mat_em[] = {1.0,1.0,1.0,1.0};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    glPushMatrix();
    glTranslatef(12,12,8);
    glRotatef(-90,1,0,0);
    glutSolidCone(2.0,3.0,16,20);
    glPopMatrix();
}

void ceiling_light(GLfloat r,GLfloat g,GLfloat b)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { r, g, b, 1.0 };
    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    GLfloat mat_em[] = {1.0,1.0,1.0,1.0};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    glPushMatrix();
    glTranslatef(12,12,8);
    glutSolidSphere(1.0,16,20);
    glPopMatrix();
}

void venti_fan(GLfloat r,GLfloat g,GLfloat b)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { r, g, b, 1.0 };
    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    GLfloat mat_em[] = {1.0,1.0,1.0,1.0};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    glPushMatrix();
    glTranslatef(0,1,0);
    glScalef(0.3,1.3,0.2);
    glutSolidCube(2);
    glPopMatrix();
}


void chair()
{
    glPushMatrix();
    glTranslatef(-3,1.6,-7);
    glScalef(1.2,0.1,1.2);
    drawcube(1,1,1);

    //chair shamner left leg
    glTranslatef(-0.8,-6,0.8);
    glScalef(0.15,6.5,0.1);
    drawcube(0,0,0);

    //shamner right leg
    glTranslatef(10,0,0);
    drawcube(0,0,0);

    //piser right leg
    glTranslatef(0,0,-16.8);
    drawcube(0,0,0);

    //piser left leg
    glTranslatef(-10,0,0);
    drawcube(0,0,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.8,2.5,-7);
    glScalef(0.15,1, 1.2);
    drawcube(1,1,1);
    glPopMatrix();
}


void light(double x,double y,double z,bool lighton,GLenum Lights,bool spot,bool strip)
{
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {0.3, 0.3, 0.3, 1.0};
    GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat strip_light_diffuse[]  = { 1.0, 1.0, 0.8, 1.0 };
    GLfloat strip_light_specular[] = { 1.0, 1.0, 0.8, 1.0 };
    GLfloat light_position[] = { x, y, z, 1.0 };

    glEnable(Lights);
    if(lighton)
    {
        if(strip)
        {
            glLightfv( Lights, GL_AMBIENT, light_ambient);
            glLightfv( Lights, GL_DIFFUSE, strip_light_diffuse);
            glLightfv( Lights, GL_SPECULAR, strip_light_specular);
            glLightfv( Lights, GL_POSITION, light_position);
        }
        else
        {
            glLightfv( Lights, GL_AMBIENT, light_ambient);
            glLightfv( Lights, GL_DIFFUSE, light_diffuse);
            glLightfv( Lights, GL_SPECULAR, light_specular);
            glLightfv( Lights, GL_POSITION, light_position);
        }


    }
    else
    {
        glLightfv( Lights, GL_AMBIENT, no_light);
        glLightfv( Lights, GL_DIFFUSE, no_light);
        glLightfv( Lights, GL_SPECULAR, no_light);
        glLightfv( Lights, GL_POSITION, no_light);
    }



    //to know the position of strip light
    /*glPushMatrix();
    glTranslatef(-15,4,28);
    glutSolidCube(2);
    glPopMatrix();*/


    if(spot)
    {
        GLfloat spot_direction[] = { 0.0, -1.0, 0.0 };
        glLightfv(Lights, GL_SPOT_DIRECTION, spot_direction);
        glLightf(Lights, GL_SPOT_CUTOFF, 55.0);
    }


}

void cameraPitch()
{
    lookat_x = 30*(cos(anglePitch*3.1416/180.0))*(cos(angleYaw*3.1416/180.0));
    lookat_y = 30*(sin(anglePitch*3.1416/180.0));
    lookat_z = 30*(cos(anglePitch*3.1416/180.0))*(sin(angleYaw*3.1416/180.0));
}

void cameraYaw()
{
    lookat_x = 30*(cos(anglePitch*3.1416/180.0))*(cos(angleYaw*3.1416/180.0));
    lookat_z = 30*(cos(anglePitch*3.1416/180.0))*(sin(angleYaw*3.1416/180.0));
}

void cameraRoll()
{
    up_x = 1.0*(sin(angleRoll*3.1416/180.0));
    up_y = 1.0*(cos(angleRoll*3.1416/180.0));
}


//void light()
//{
//    //GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
//    GLfloat light_ambient[]  = {1.0, 1.0, 1.0, 1.0};
//    GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
//    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
//    GLfloat light_position[] = { 0.0, 10.0, 50.0, 1.0 };
//
//    glEnable( GL_LIGHT0);
//
//    glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient);
//    glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse);
//    glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular);
//    glLightfv( GL_LIGHT0, GL_POSITION, light_position);
//
//    /*GLfloat spot_direction[] = { 0.0, -1.0, 0.0 };
//    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
//    glLightf( GL_LIGHT0, GL_SPOT_CUTOFF, 10.0);*/
//}

void LoadTexture(const char*filename)
{
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    BmpLoader bl(filename);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bl.iWidth, bl.iHeight, GL_RGB, GL_UNSIGNED_BYTE, bl.textureData );
}

int i = 1;
GLuint ID_[100];

void LoadTexture1(const char*filename)
{
    glGenTextures(1, &ID_[i]);
    glBindTexture(GL_TEXTURE_2D, ID_[i]);
    glPixelStorei(GL_UNPACK_ALIGNMENT, ID_[i++]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    BmpLoader bl(filename);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bl.iWidth, bl.iHeight, GL_RGB, GL_UNSIGNED_BYTE, bl.textureData );
}


void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    //glFrustum(-5, 5, -5, 5, 4, 100);
    gluPerspective(60,1,4,200);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();




    gluLookAt(eye_x,eye_y,eye_z, lookat_x,lookat_y,lookat_z, up_x,up_y,up_z);
    glViewport(0, 0, windowHeight, windowWidth);

    glRotatef( alpha,axis_x, axis_y, 0.0 );
    glRotatef( theta, axis_x, axis_y, 0.0 );


    glScaled(sx,sy,sz);


    glTranslated(0,-7,0);
    glPushMatrix();
    drawcube(1,1,1);
    glPopMatrix();

    //floor
    glPushMatrix();
    glScalef(17,0.1,15);
    drawcube(0.5,0.5,0.5);
    glPopMatrix();

    //table
    glPushMatrix();
    glTranslatef(-6,2,8);
    glScalef(1.5,0.1,3);
    drawcube(1,1,1);

    // shamner left leg
    glTranslatef(-0.8,-9,0.8);
    glScalef(0.15,10,0.1);
    drawcube(0,0,0);

    // shamner right leg
    glTranslatef(10,0,0);
    drawcube(0,0,0);

    // back right leg
    glTranslatef(0,0,-16);
    drawcube(0,0,0);

    // back left leg
    glTranslatef(-10,0,0);
    drawcube(0,0,0);
    glPopMatrix();

    //GM wall partition
    glPushMatrix();
    glTranslatef(0,4.9,10.8);
    glScalef(0.15,4.8,4);
    drawcube(0.7,0.7,0.7);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,4.9,1.4);
    glScalef(0.15,4.8,1.5);
    drawcube(0.7,0.7,0.7);
    glPopMatrix();


    //dorja
    glPushMatrix();
    glTranslatef(0, 4.9, 4.8);
    glScalef(0.15,4.8,1.8);
    drawcube(1,1,1);
    glPopMatrix();

    //chair
    glPushMatrix();
    glTranslatef(-7.5,1.4,8);
    glScalef(1.2,0.1,1.2);
    drawcube(1,1,1);

    //chair shamner left leg
    glTranslatef(-0.8,-6,0.8);
    glScalef(0.15,6.5,0.1);
    drawcube(0,0,0);

    //shamner right leg
    glTranslatef(10,0,0);
    drawcube(0,0,0);

    //piser right leg
    glTranslatef(0,0,-16.8);
    drawcube(0,0,0);

    //piser left leg
    glTranslatef(-10,0,0);
    drawcube(0,0,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-8.55,2.5,8);
    glScalef(0.15,1, 1.2);
    drawcube(1,1,1);
    glPopMatrix();

    //arekwall partition
    glPushMatrix();
    glTranslatef(-7.6,4,0);

    glScalef(7.4,4,0.15);
    drawcube(1,1,1);
    glPopMatrix();

    //shelf
    glPushMatrix();
    glTranslatef(-9,0.1,2);
    glRotatef(90,0,1,0);
    glScalef(1.5,0.2,5.5);
    drawcube(1,1,1);
    glPopMatrix();



    glPushMatrix();
    glTranslatef(-9,3.3,2);
    glRotatef(90,0,1,0);
    glScalef(1.2,3,5.5);
    drawcube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-9,6.3,2);
    glRotatef(90,0,1,0);
    glScalef(1.5,0.2,5.5);
    drawcube(1,1,1);
    glPopMatrix();


    //laptop

    glPushMatrix();
    glTranslatef(-6,2.15,8);
    glScalef(1,0.03,1.2);
    drawcube(1,0,0);


    glTranslatef(0,0.5,0);
    drawcube(1,1,1);

    glPopMatrix();


    glPushMatrix();
    glTranslatef(-4.8,3,8);
    glRotatef(-10,0,0,1);
    glScalef(0.05,0.85,1.2);
    drawcube(0,0,0);

    glTranslatef(-0.03,0,0);

    drawcube(1,1,1);
    glPopMatrix();


    //cash counter shelf
    glPushMatrix();
    glTranslatef(7.5,1.6,-7);
    glScalef(7.5,1.5,1);
    drawcube(1,0,1);


    glPopMatrix();


    glPushMatrix();
    glTranslatef(7.5,3,-6.6);
    glScalef(7.5,0.2,1.4);
    drawcube(1,0,0);


    glPopMatrix();


    //counter er aynar frame

    glPushMatrix();
    glTranslatef(7.5,4.2,-6.6);
    glScalef(0.2,1.2,1.4);
    drawcube(1,1,0);

    glTranslatef(35,0,0);
    drawcube(1,1,0);


    glTranslatef(-70,0,0);
    drawcube(1,1,0);
    glPopMatrix();


    //counter ayna
    glPushMatrix();
    glTranslatef(11.2,4.7,-5.3);
    glScalef(3.5,0.7,0.2);
    drawcube(1,1,1);

    glTranslatef(-2.1,0,0);
    drawcube(1,1,1);
    glPopMatrix();

    //sofa
    glPushMatrix();
    glTranslatef(10,1,13);
    glScalef(3.5,1,1.3);
    drawcube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(10,2.5,14);
    glScalef(3.5,2,0.3);
    drawcube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(6.5,1.3,12.5);
    glScalef(0.8,1.4,1.3);
    drawcube(1,1,1);



    glTranslatef(9,0,0);
    drawcube(1,1,1);
    glPopMatrix();



    //lobbyroom table
    glPushMatrix();
    glTranslatef(10,2,8);
    glRotatef(90,0,1,0);
    glScalef(1.5,0.1,3);
    drawcube(1,1,1);


    glTranslatef(-0.8,-9,0.8);
    glScalef(0.15,10,0.1);
    drawcube(0,0,0);

    glTranslatef(0,0,-16);
    drawcube(0,0,0);

    glTranslatef(10,0,0);
    drawcube(0,0,0);

    glTranslatef(0,0,16);
    drawcube(0,0,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(10,2.05,8);
    glRotatef(25,0,1,0);
    glScalef(0.8,0.1,1);
    drawcube(0,0,1);


    glTranslatef(0,0.7,0);
    glRotatef(10,0,1,0);
    drawcube(0,1,1);
    glPopMatrix();


    //employee table
    glPushMatrix();
    glTranslatef(-9,1.6,-4.5);
    glScalef(1,1.3,4);
    drawcube(1,1,1);

    glTranslatef(0,1,0);
    glScalef(1.5,0.2,1);
    drawcube(1,1,1);


    glPopMatrix();

    glPushMatrix();
    glTranslatef(-9,1.6,-13.2);
    glScalef(1,1.3,1.7);
    drawcube(1,1,1);

    glTranslatef(0,1,0);
    glScalef(1.5,0.2,1);
    drawcube(1,1,1);


    glPopMatrix();

    glPushMatrix();
    glTranslatef(-9, 2.9, -10);
    glScalef(1.6,0.2,1.4);
    drawcube(0,0,0);
    glPopMatrix();

    //chair
    glPushMatrix();
    glTranslatef(-2,0,4);
    chair();

    glTranslatef(0,0,-3.8);
    chair();

    glTranslatef(0,0,-6.2);
    chair();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-16,0,-10);
    glRotatef(180,0,1,0);
    chair();

    glTranslatef(0,0,3.8);
    chair();

    glTranslatef(0,0,6);
    chair();
    glPopMatrix();


    //employee laptop
    glPushMatrix();

    glTranslatef(-3,1.1,-1);
    glPushMatrix();
    glTranslatef(-6,2.15,-2);
    glScalef(1,0.03,1.2);
    drawcube(1,0,0);
    glTranslatef(0,0.5,0);
    drawcube(1,1,1);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-4.8,3,-2);
    glRotatef(-10,0,0,1);
    glScalef(0.05,0.85,1.2);
    drawcube(0,0,0);
    glTranslatef(-0.03,0,0);
    drawcube(1,1,1);
    glPopMatrix();

    glPopMatrix();


    //laptop2

    glPushMatrix();

    glTranslatef(-3,1.1,-5);
    glPushMatrix();
    glTranslatef(-6,2.15,-2);
    glScalef(1,0.03,1.2);
    drawcube(1,0,0);
    glTranslatef(0,0.5,0);
    drawcube(1,1,1);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-4.8,3,-2);
    glRotatef(-10,0,0,1);
    glScalef(0.05,0.85,1.2);
    drawcube(0,0,0);
    glTranslatef(-0.03,0,0);
    drawcube(1,1,1);
    glPopMatrix();

    glPopMatrix();



    //laptop
    glPushMatrix();

    glTranslatef(-3,1.1,-11);
    glPushMatrix();
    glTranslatef(-6,2.15,-2);
    glScalef(1,0.03,1.2);
    drawcube(1,0,0);
    glTranslatef(0,0.5,0);
    drawcube(1,1,1);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-4.8,3,-2);
    glRotatef(-10,0,0,1);
    glScalef(0.05,0.85,1.2);
    drawcube(0,0,0);
    glTranslatef(-0.03,0,0);
    drawcube(1,1,1);
    glPopMatrix();

    glPopMatrix();


    glPushMatrix();
    glTranslatef(21,0,0);
    glScalef(4,0.3,4);
    drawcube(1,1,1);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(20.8 ,-0.4 ,4.8);
    glScalef(4,0.6,1);
    drawcube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(tx,ty,tz);
    glScalef(4,0.6,1);
    drawcube(1,1,1);
    glPopMatrix();










    light(-5.0,15.0,-7,light0,GL_LIGHT0,false,false);
    light(-5,13.85,0,light1,GL_LIGHT1,true,false);
    light(-55,4,28,light2,GL_LIGHT2,false,true);
    glFlush();
    glutSwapBuffers();
}

void myKeyboardFunc( unsigned char key, int x, int y )
{
    switch ( key )
    {
    case 't':
    case 'T':
        bRotate = !bRotate;
        uRotate = false;
        axis_x=0.0;
        axis_y=1.0;
        break;

    case 'r':
    case 'R':
        uRotate = !uRotate;
        bRotate = false;
        axis_x=1.0;
        axis_y=0.0;
        break;
    case 'w':
        eye_y++;
        lookat_y++;
        glutPostRedisplay();
        break;
    case 's':
        eye_y--;
        lookat_y--;
        glutPostRedisplay();
        break;
    case 'd':
        eye_x++;
        lookat_x++;
        glutPostRedisplay();
        break;
    case 'a':
        eye_x--;
        lookat_x--;
        glutPostRedisplay();
        break;

    case '+':
        eye_z--;
        if(pilotRoll)
        {
            angleRoll++;
        }
        else
        {
            lookat_z--;
        }
        glutPostRedisplay();
        break;
    case '-':
        eye_z++;
        if(pilotRoll)
        {
            angleRoll--;
        }
        else
        {
            lookat_z;
        }
        glutPostRedisplay();
        break;
    case '*':
        sx+=0.1;
        sy+=0.1;
        sz+=0.1;
        glutPostRedisplay();
        break;
    case '/':
        sx-=0.1;
        sy-=0.1;
        sz-=0.1;
        glutPostRedisplay();
        break;
    //for pitch-yaw-roll
    case 'i':
        if(angleRoll<=180)
        {
            angleRoll++;
            cameraRoll();
        }
        glutPostRedisplay();
        break;
    case 'j':
        if(angleRoll>=-180)
        {
            angleRoll--;
            cameraRoll();
        }
        glutPostRedisplay();
        break;
    case 'o':
        if(angleYaw<180)
        {
            angleYaw++;
            cameraYaw();

        }
        glutPostRedisplay();
        break;
    case 'p':
        if(angleYaw>0)
        {
            angleYaw--;
            cameraYaw();
        }
        glutPostRedisplay();
        break;
    case 'k':
        if(anglePitch<90)
        {
            anglePitch++;
            cameraPitch();

        }
        glutPostRedisplay();
        break;
    case 'l':
        if(anglePitch>-90)
        {
            anglePitch--;
            cameraPitch();
        }
        glutPostRedisplay();
        break;

    //switch for light0
    case '1':
        light0 = !light0;
        glutPostRedisplay();
        break;
    case '2':
        light1 = !light1;
        glutPostRedisplay();
        break;
    case '3':
        light2 = !light2;
        glutPostRedisplay();
        break;

    //for fan
    case '4':
        gammaa += 0.5;
        glutPostRedisplay();
        break;

    //for pilotview
    case '7':
        pilotPitch = !pilotPitch;
        glutPostRedisplay();
        break;
    case '8':
        pilotYaw = !pilotYaw;
        glutPostRedisplay();
        break;
    case '9':
        pilotRoll = !pilotRoll;
        glutPostRedisplay();
        break;
    case '5':
        ty -= 0.2;
        break;
    case '6':
        ty += 0.2;
        break;



    case 27:  // Escape key
        exit(1);
    }


}


void SpecialInput(int key, int x, int y)
{
    switch(key)
    {
    case GLUT_KEY_UP:
        tz -= 0.2;
        break;
    case GLUT_KEY_DOWN:
//do something here
        tz += 0.2;
        break;
    case GLUT_KEY_LEFT:
//do something here
        tx -= 0.2;
        break;
    case GLUT_KEY_RIGHT:
//do something here
        tx += 0.2;
        break;
    }
    cout<<"Starting Point "<<tx<<" "<<ty<<" "<<tz<<" \n";

    glutPostRedisplay();
}


void animate()
{
    if (bRotate == true)
    {
        theta += 0.1;
        if(theta > 360.0)
            theta -= 360.0*floor(theta/360.0);
    }

    if (uRotate == true)
    {
        alpha += 0.1;
        if(alpha > 360.0)
            alpha -= 360.0*floor(alpha/360.0);
    }
    if (zRotate == true)
    {
        gammaa += 0.5;
        if(gammaa > 90.0)
            gammaa -= 90.0*floor(gammaa/90.0);
    }


    glutPostRedisplay();

}



int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(windowHeight, windowWidth);
    glutCreateWindow("Janata Bank, Kuet");
    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);

    LoadTexture("C:\\Users\\nafir\\OneDrive\\Desktop\\letsgo\\wood.bmp"); //1
    LoadTexture("C:\\Users\\nafir\\OneDrive\\Desktop\\letsgo\\floor.bmp"); //2
    LoadTexture("C:\\Users\\nafir\\OneDrive\\Desktop\\letsgo\\teaaa.bmp"); //3
    LoadTexture("C:\\Users\\nafir\\OneDrive\\Desktop\\letsgo\\woodd.bmp"); //4

    glutKeyboardFunc(myKeyboardFunc);
    glutSpecialFunc(SpecialInput);
    //sndPlaySound("woo.wav",SND_ASYNC);
    glutDisplayFunc(display);
    glutIdleFunc(animate);
    //PlaySound(TEXT("woo.wav"),NULL, SND_SYNC);
    glutMainLoop();


    return 0;
}

