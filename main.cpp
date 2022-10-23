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

unsigned int ID,ID1;

double Txval=0,Tyval=0,Tzval=0;
double windowHeight=1200, windowWidth=1400;
GLfloat alpha = 0.0, theta = 0.0, gamma = 0.0, axis_x=0.0, axis_y=0.0, sandAngle=90;
bool fan4=false;
double lpan=0,rpan=0,bpan=0,tpan=0;

GLdouble eyex=20, eyey=50,eyez=150,centerx=14,centery=50,centerz=0, upx=0,upy=1,upz=0, zNear=4, zFar=250;
GLdouble dx,dy,dz;
// original -> 20,6,-20, 2,0,0, 0,1,0
double scale_x = 2;
double scale_y = 2;
double scale_z = 2;

GLboolean bRotate = false, uRotate = false, light0 = false,light1=false,light2=false, sandbagMov=false;

#define PI 3.1415927

static GLfloat v_cube[8][3] =
{
    {0, 0, 0}, //0
    {0, 0, 1}, //1
    {1, 0, 1}, //2
    {1, 0, 0}, //3
    {0, 1, 0}, //4
    {0, 1, 1}, //5
    {1, 1, 1}, //6
    {1, 1, 0}  //7
};

static GLubyte cubeIndices[6][4] =
{
    {0, 1, 2, 3}, //bottom
    {4, 5, 6, 7}, //top
    {5, 1, 2, 6}, //front
    {0, 4, 7, 3}, // back is clockwise
    {2, 3, 7, 6}, //right
    {1, 5, 4, 0}  //left is clockwise
};




static GLfloat v_floor[8][3] =
{
    {-14,15,25}, //0
    {-14,15,0}, //1
    {-14,0,0}, //2
    {-14,0,25}, //3

    {25,15,0}, //4
    {25,0,0}, //5
    {25,15,25}, //6
    {25,0,25}, //7


};



static GLubyte florindices[3][4] =
{
    //{0,1,2,3},
    {1,4,5,2},
    {4,6,7,5},
    {5,7,3,2}
};



//static GLfloat colors[10][3] =
//{
//    //polygon colors
//    {1.0, 1.0, 1.0},
//    {0.5, 0.5, 0.5},
//    //quad er shuru ekhan theke
//    {0.5f, 0.0f, 1.0f}, //purple
//    {1.0f, 0.0f, 0.0f}, //red
//    {0.0f, 1.0f, 0.0f}, //green
//    {1.0f, 1.0f, 0.0f}, //yellow
//    {0.0, 0.0, 1.0}, //blue
//    {1.0, 0.5, 0.0}, //idk what color
//    {0.002, 0.6, 0.98}, // bluish hue
//    {0.4, 0.2, 0.0} //brown
//};
//


void drawWall(GLfloat r=1,GLfloat g=1,GLfloat b=1,GLboolean emission=false)
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

    if(emission) glMaterialfv( GL_FRONT, GL_EMISSION, mat_em);
    else glMaterialfv( GL_FRONT, GL_EMISSION, no_mat);

    for (GLint i = 0; i <3; i++)
    {
        glBegin(GL_QUADS);

        //if(i!=3 && i!=1) glColor3f(colors[8][0],colors[8][1],colors[8][2]);
        //else if(i==3) glColor3f(colors[1][0],colors[1][1],colors[1][2]);
        //else glColor3f(colors[2][0],colors[2][1],colors[2][2]);

        glVertex3fv(&v_floor[florindices[i][0]][0]);glTexCoord2f(1,1);
        glVertex3fv(&v_floor[florindices[i][1]][0]);glTexCoord2f(1,0);
        glVertex3fv(&v_floor[florindices[i][2]][0]);glTexCoord2f(0,0);
        glVertex3fv(&v_floor[florindices[i][3]][0]);glTexCoord2f(0,1);

        glEnd();
    }
}



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












void drawCube(GLfloat r=1,GLfloat g=1,GLfloat b=1,GLboolean emission=false)
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

    if(emission) glMaterialfv( GL_FRONT, GL_EMISSION, mat_em);
    else glMaterialfv( GL_FRONT, GL_EMISSION, no_mat);

    for (GLint i = 0; i <6; i++)
    {
        glBegin(GL_QUADS);
        glVertex3fv(&v_cube[cubeIndices[i][0]][0]);glTexCoord2f(1,1);
        glVertex3fv(&v_cube[cubeIndices[i][1]][0]);glTexCoord2f(1,0);
        glVertex3fv(&v_cube[cubeIndices[i][2]][0]);glTexCoord2f(0,0);
        glVertex3fv(&v_cube[cubeIndices[i][3]][0]);glTexCoord2f(0,1);
        glEnd();
    }
}



static GLfloat v_pyramid[12][3] =
{
    {0.0, 1.0, 0.0}, //0
    {-1.0, 0.5, 0.0}, //1
    {-1.0, -0.5, 0.0}, //2
    {0.0, -1.0, 0.0}, //3
    {1.0, -0.5, 0.0}, //4
    {1.0, 0.5, 0.0}, //5

    {0.0, 1.0, -1}, //6
    {-1.0, 0.5, -1}, //7
    {-1.0, -0.5, -1}, //8
    {0.0, -1.0, -1}, //9
    {1.0, -0.5, -1}, //10
    {1.0, 0.5, -1} //11
};

static GLubyte poly_Indices[2][6] =
{
    {0,1,2,3,4,5},
    {6,7,8,9,10,11}
};

static GLubyte quadIndices[6][4] =
{
    {0,6,7,1},
    {0,5,11,6},
    {1,7,8,2},

    {5,4,10,11},
    {2,3,9,8},
    {4,3,9,10}
};



void drawpyramid()
{
    //glColor3f(1,0,0);

    for (GLint i = 0; i <2; i++)
    {
        glBegin(GL_POLYGON);
        glColor3f(0,0,0);
        glVertex3fv(&v_pyramid[poly_Indices[i][0]][0]);
        glVertex3fv(&v_pyramid[poly_Indices[i][1]][0]);
        glVertex3fv(&v_pyramid[poly_Indices[i][2]][0]);
        glVertex3fv(&v_pyramid[poly_Indices[i][3]][0]);
        glVertex3fv(&v_pyramid[poly_Indices[i][4]][0]);
        glVertex3fv(&v_pyramid[poly_Indices[i][5]][0]);
    }
    glEnd();


    for (GLint i = 0; i <6; i++)
    {
        glBegin(GL_QUADS);
        glColor3f(0,0,0);
        glVertex3fv(&v_pyramid[quadIndices[i][0]][0]);
        glVertex3fv(&v_pyramid[quadIndices[i][1]][0]);
        glVertex3fv(&v_pyramid[quadIndices[i][2]][0]);
        glVertex3fv(&v_pyramid[quadIndices[i][3]][0]);

    }
    glEnd();


}










void dumbbell(double weight = 5.0)
{
    double factor;
    if (weight==5.0) factor = 1;
    else factor = weight*0.5;

    glPushMatrix();
    glColor3b(1,1,1);
    glTranslatef(0,0,0);
    glScalef(0.1,0.02,0.8);
    drawCube(1,1,1);
    glPopMatrix();

    glPushMatrix();

    glTranslatef(0,0,0);
    glScalef(0.5,0.4,0.3*factor);
    //glScalef(factor,factor,factor);
    //drawCube(1,1,1);
//    glScalef(0.2,0.4,0.2);
    //glutSolidSphere( 0.4, 10.0, 15.0);
    drawpyramid();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0,0.8);
    glScalef(0.5,0.4,0.3*factor);
    //glScalef(factor,factor,factor);
    //drawCube(1,1,1);
//    glScalef(0.2,0.4,0.2);
    //glutSolidSphere( 0.4, 10.0, 15.0);
    drawpyramid();
    glPopMatrix();

}



void rack() {

    // left leg
    glPushMatrix();
    glColor3b(1,1,1);
    glTranslatef(-5,0,0);
    glScalef(0.5,5,2);
    drawCube(1,1,1);
    glPopMatrix();


    // right leg
    glPushMatrix();
    glColor3b(1,1,1);
    glTranslatef(4.5,0,0);
    glScalef(0.5,5,2);
    drawCube(1,1,1);
    glPopMatrix();

    // bottom rack
    glPushMatrix();
    glColor3b(1,1,1);
    glTranslatef(-4.5,0.8,0);
    glScalef(9,0.5,3);
    drawCube(0,0,0);
    glPopMatrix();

    // middle rack
    glPushMatrix();
    glColor3b(1,1,1);
    glTranslatef(-4.5,2.8,0);
    glScalef(9,0.5,3);
    drawCube(0,0,0);
    glPopMatrix();

    // top rack
    glPushMatrix();
    glColor3b(1,1,1);
    glTranslatef(-4.5,4.8,0);
    glScalef(9,0.5,3);
    drawCube(0,0,0);
    glPopMatrix();


}




void drawFan(GLfloat r=0,GLfloat g=0,GLfloat b=0,GLboolean emission=false) {

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

    if(emission) glMaterialfv( GL_FRONT, GL_EMISSION, mat_em);
    else glMaterialfv( GL_FRONT, GL_EMISSION, no_mat);


    glPushMatrix();

    glTranslatef(0,0,0);
    glScalef(0.1,0.1,1);
    drawCube();


    glPopMatrix();



}




void drawFanJack(GLfloat r=0,GLfloat g=0,GLfloat b=0,GLboolean emission=false) {

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

    if(emission) glMaterialfv( GL_FRONT, GL_EMISSION, mat_em);
    else glMaterialfv( GL_FRONT, GL_EMISSION, no_mat);


    glPushMatrix();

    glTranslatef(0,0,0);
    glScalef(0.1,0.1,2);
    drawCube();
    glutSolidSphere(2,6,6);


    glPopMatrix();



}







void ceiling_light_holder(GLfloat r,GLfloat g,GLfloat b,GLboolean emission=false)
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

    if(emission) glMaterialfv( GL_FRONT, GL_EMISSION, mat_em);
    else glMaterialfv( GL_FRONT, GL_EMISSION, no_mat);

    glPushMatrix();
    glTranslatef(3.48,8,4.48);
    //glRotatef(-90,1,0,0);
    glScalef(0.1,1,0.1);
    drawCube(1,1,1);
    glPopMatrix();
}





void ceiling_light(GLfloat r,GLfloat g,GLfloat b,GLfloat x=3.5,GLfloat y=8,GLfloat z=4.5,GLboolean emission=false)
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

    if(emission) glMaterialfv( GL_FRONT, GL_EMISSION, mat_em);
    else glMaterialfv( GL_FRONT, GL_EMISSION, no_mat);



    glPushMatrix();
    glTranslatef(x,y,z);
    glutSolidSphere(0.5,16,20);
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
    glTranslatef(10,8.5,4.5);
    glutSolidCube(1);
    glPopMatrix();*/


    if(spot)
    {
        GLfloat spot_direction[] = { 0, -1, 0 };
        glLightfv(Lights, GL_SPOT_DIRECTION, spot_direction);
        glLightf(Lights, GL_SPOT_CUTOFF, 55.0);
    }


}

void chair(int r=0) {
    //legs left top
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    //(1,1,1);
    glTranslatef(-1.45,0,-1.2);
    glScaled(0.2,1.5,0.2);

    glBindTexture(GL_TEXTURE_2D, 7);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //legs left bottom
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    //(1,1,1);
    glTranslatef(-1.45,0,1.3);
    glScaled(0.2,1.5,0.2);

    glBindTexture(GL_TEXTURE_2D, 7);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // right top legs
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();

    //(1,1,1);
    glTranslatef(1.55,0,-1.2);
    glScaled(0.2,1.5,0.2);

    glBindTexture(GL_TEXTURE_2D, 7);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // right bottom legs
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();

    //(1,1,1);
    glTranslatef(1.55,0,1.3);
    glScaled(0.2,1.5,0.2);

    glBindTexture(GL_TEXTURE_2D, 7);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // seat
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();

    glTranslatef(-1.45,1.5,-1.2);
    glScaled(3.2,0.2,2.7);

    glBindTexture(GL_TEXTURE_2D, 7);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // backrest
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    //(1,1,1);
    glTranslatef(-1.45,1.5,-1.2);
    glScaled(0.2,2.5,2.7);

    glBindTexture(GL_TEXTURE_2D, 7);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}



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


void draw_cylinder(GLfloat radius,
                   GLfloat height,
                   GLubyte R,
                   GLubyte G,
                   GLubyte B)
{
    GLfloat x              = 0.0;
    GLfloat y              = 0.0;
    GLfloat angle          = 0.0;
    GLfloat angle_stepsize = 0.1;

    /** Draw the tube */
    glColor3ub(R-40,G-40,B-40);
    glBegin(GL_QUAD_STRIP);
    angle = 0.0;
        while( angle < 2*PI ) {
            x = radius * cos(angle);
            y = radius * sin(angle);
            glVertex3f(x, y , height);
            glVertex3f(x, y , 0.0);
            angle = angle + angle_stepsize;
        }
        glVertex3f(radius, 0.0, height);
        glVertex3f(radius, 0.0, 0.0);
    glEnd();

    /** Draw the circle on top of cylinder */
    glColor3ub(R,G,B);
    glBegin(GL_POLYGON);
    angle = 0.0;
        while( angle < 2*PI ) {
            x = radius * cos(angle);
            y = radius * sin(angle);
            glVertex3f(x, y , height);
            angle = angle + angle_stepsize;
        }
        glVertex3f(radius, 0.0, height);
    glEnd();
}



void cyl(GLfloat r=0.3,
          GLfloat g=0.4,
          GLfloat b=0.5,
          GLboolean emission = false ) {

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

    if(emission) glMaterialfv( GL_FRONT, GL_EMISSION, mat_em);
    else glMaterialfv( GL_FRONT, GL_EMISSION, no_mat);

    GLUquadric* qobj;
    qobj = gluNewQuadric();
    gluCylinder(qobj,0.5,0.5,3,20,10);
}


void secondFloor();


void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glFrustum(-5+lpan, 5+rpan, -5+bpan, 5+tpan, zNear, zFar);
     //gluPerspective(60,1,5,100);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt(eyex,eyey,eyez,centerx+dx,centery+dy,centerz+dz,upx,upy,upz);
    glViewport(0, 0, windowHeight, windowWidth);

    //glRotatef(45, 0, 0, 1 );
    // triangle();

    //glRotatef(120,0,1,0);
//     glScalef(1,5,1);
    //glTranslatef(0,-10,0);


    glScalef(scale_x,scale_y,scale_z);

    glRotatef( alpha,axis_x, axis_y, 0.0 );
    glRotatef( theta, axis_x, axis_y, 0.0 );

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, 4);
    drawWall();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    { /// TILES
        /*
    // tiles outline
    //(.8,.7,.2);
    glPushMatrix();
    glTranslatef(-14,0,0);
    //glRotatef(22, 0,0,1);
    glScalef(23, 0.002, 20);
    drawCube(.8,.7,.2);
    glPopMatrix();
    //tiles
    int start_point=-1;
    for(int k=9;k<20;k++){

        start_point = (start_point+1)%2;

        for (int i=0;i<10;i+=2){
            //(.8,.7,.2);
            glPushMatrix();

            glTranslatef(k,0,i+start_point);
            //glRotatef(22, 0,0,1);
            glScalef(1, 0.002, 1);
            drawCube(.8,.7,.2);
            glPopMatrix();
        }

    }
    */}

    /// DUMBBELLS========================================

    {


    glPushMatrix();
    glTranslated(-4,1.7,1);
    dumbbell();
    glPopMatrix();

    glPushMatrix();
    glTranslated(0,1.7,1);
    dumbbell();
    glPopMatrix();

    glPushMatrix();
    glTranslated(0,1.7,1);
    dumbbell();
    glPopMatrix();

    glPushMatrix();
    glTranslated(3,1.7,1);
    dumbbell();
    glPopMatrix();

    glPushMatrix();
    glTranslated(1,1.7,1);
    dumbbell();
    glPopMatrix();





    glPushMatrix();
    glTranslated(0,3.7,1);
    dumbbell();
    glPopMatrix();

    glPushMatrix();
    glTranslated(3,3.7,1);
    dumbbell();
    glPopMatrix();

    glPushMatrix();
    glTranslated(1,3.7,1);
    dumbbell();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-3,3.7,1);
    dumbbell();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-1,3.7,1);
    dumbbell();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-3,5.7,1);
    dumbbell();
    glPopMatrix();


    glPushMatrix();
    glTranslated(0,5.7,1);
    dumbbell();
    glPopMatrix();

    glPushMatrix();
    glTranslated(3,5.7,1);
    dumbbell();
    glPopMatrix();

    glPushMatrix();
    glTranslated(1,5.7,1);
    dumbbell();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-3,5.7,1);
    dumbbell();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-1,5.7,1);
    dumbbell();
    glPopMatrix();

    }
    /// DUMBBELLS========================================




    glPushMatrix();

    rack();
    glPopMatrix();

    /// RACK ========================================


    /// COUNTER ====================================
    {
    // cupboards
    //(1.0, 0.5, 0.0);


    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-13,0,11);
    //glRotatef(22, 0,0,1);
    glScalef(4,4,2);
    glBindTexture(GL_TEXTURE_2D, 3);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // cupboards
    //(1.0, 0.5, 0.0);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-9,0,11);
    //glRotatef(22, 0,0,1);
    glScalef(2,4,7);
    glBindTexture(GL_TEXTURE_2D, 3);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    /// COUNTER


    /// chair
    glPushMatrix();
    glTranslatef(-12,0,15);
    //glRotatef(180,0,1,0);
    chair();
    glPopMatrix();
    }
    /// COUNTER ====================================


    {/// cyl=====================================
    glPushMatrix();

        glTranslatef(10, 8, 10);
        glRotatef(sandAngle, 1, 0, 0 );
        //glRotatef(sandAngle, 0, 0, 1 );
        glScalef(2, 2, 2);
        cyl( .5,.3,.4);
    glPopMatrix();

        // Base cyl
    glPushMatrix();

        glTranslatef(10, 8, 10);
        glRotatef(sandAngle, 1, 0, 0 );
        //glRotatef(sandAngle, 0, 0, 1 );
        glScalef(2, 2, 2);
        cyl( .5,.3,.4);
    glPopMatrix();
    }

    // cyl circle=====================================





    secondFloor();


    { ///LIGHT
    // ========================================

    //light(17.75,8.83,4.5,light0,GL_LIGHT0,false,false);
    light(3.5,8,4.5,light1,GL_LIGHT1,true,false);
    light(18,12,15,light2,GL_LIGHT2,false,true);

    }

    glFlush();
    glutSwapBuffers();
}





void secondFloor() {
    /// FLOOR
    {


    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-14,15,0);
    //glRotatef(22, 0,0,1);
    glScalef(39,0.1,25);
    glBindTexture(GL_TEXTURE_2D, 3);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    }
    double base = 15.1;


    ///Boxing Ring
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-4,base,4);
    //glRotatef(22, 0,0,1);
    glScalef(12,2,12);
    glBindTexture(GL_TEXTURE_2D, 1);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    /*
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-14,15,0);
    //glRotatef(22, 0,0,1);
    glScalef(39,0.5,25);
    glBindTexture(GL_TEXTURE_2D, 3);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    */


}






double limit = 360;
double roll_value = 0.2;
//GLfloat angleYaw = 90.0, anglePitch = 270.0, angleRoll = 90.0;
//GLfloat angleYawLimit1 = 180.0, anglePitchLimit1 = 360.0, angleRollLimit1 = 270.0;
//GLfloat angleYawLimit2 = 0.0, anglePitchLimit2 = 180.0, angleRollLimit2 = -90.0;
int f=0;
double yaw=0,pitch=0,roll=0;
int bv = 0;



void b_swap()
{
    if(bv==1)
    {
        int tmp = eyey;
        eyey = eyez;
        eyez = tmp;

        tmp = upy;
        upy = upz;
        upz = tmp;

    }
}


//
//void setCameraEye_Yaw() // y axis , y u
//{
//    //init(1);
//    f=1;
//    //centery = 200.0*(cos(angleYaw*3.1416/180.0));
//}
//
//void setCameraEye_Roll() // z axis ,i o
//{
//    //init(2);
//    f=2;
//    //upx = 200.0*(cos(angleRoll*3.1416/180.0));//-sin(angleYaw*3.1416/180.0));
//    //upy = 200.0*(sin(angleRoll*3.1416/180.0));//+cos(angleYaw*3.1416/180.0));
//}
//
//void setCameraEye_Pitch() // x axis , r t
//{
//    //init(3);
//    f=3;
//
//    //centerx = 400.0*(cos(anglePitch*3.1416/180.0));
//}
//



void bird_view()
{
//     init(6);
//     f=6;
     bv = 1;
     b_swap();

}


void normal_view()
{
//     init(6);
//     f=6;
     bv = 0;
     eyex=20, eyey=10,eyez=70,centerx=12,centery=10,centerz=0, upx=0,upy=1,upz=0;

}







void myKeyboardFunc( unsigned char key, int x, int y )
{
    switch ( key )
    {



    ///yaw
    case 'y':

        yaw+=1;

        if( yaw==90 || yaw ==0)
        {
            yaw=0;
            dx=0;
            break;
        }
        dx =  abs(eyez-centerz)*tan(yaw*3.1415/180);

        centery=centery;
        break;

    case 'u':

        yaw-=1;

        if(yaw==-90 || yaw==0)
        {
            yaw = 0;
            dx=0;
            break;
        }

        dx = abs(eyez-centerz)*tan(yaw*3.1415/180);

        centery=centery;

        break;

    ///pitch
    case 'r':

        pitch+=1;

        if( pitch==90 || pitch ==0)
        {
            pitch=0;
            dy=0;
            break;
        }
        dy =  abs(eyez-centerz)*tan(pitch*3.1415/180);

        centerx=centerx;
        break;

    case 't':
        pitch-=1;
        if(pitch==-90 || pitch==0)
        {
            pitch = 0;
            dy=0;
            break;
        }
        dy = abs(eyez-centerz)*tan(pitch*3.1415/180);

        centerx=centerx;
        break;


    ///    roll
    case 'i':
        roll+=0.5;
        upx = cos(roll);
        upy= sin(roll);

        break;
    case 'o':
        roll-=0.5;

        upx = cos(roll);
        upy= sin(roll);
        break;



    case '@':
       bRotate = !bRotate;
              // uRotate = false;
        axis_x=0.0;
        axis_y=1.0;

        break;


   case '#':
        uRotate = !uRotate;/**<  */
        bRotate = false;
       axis_x=1.0;
        axis_y=0.0;

       break;

    case 'z':
        //eyez-=2;
        //init(4);
        f=4;
        scale_x+=0.05;
        scale_y+=0.05;
        scale_z+=0.05;
        glutPostRedisplay();
        break;
    case 'c':
        //eyez-=2;
        //init(4);
        f=4;
        if(scale_x==0.05)break;
        scale_x-=0.05;
        scale_y-=0.05;
        scale_z-=0.05;
        glutPostRedisplay();
        break;

    //switch for light0
    case '0':
        light0 = !light0;
        glutPostRedisplay();
        break;
    case '1':
        light1 = !light1;
        glutPostRedisplay();
        break;
    case '2':
        light2 = !light2;
        glutPostRedisplay();
        break;

    case '4':
        fan4 = !fan4;
        glutPostRedisplay();
        break;

     case '5':
        sandbagMov = !sandbagMov;
        glutPostRedisplay();
        break;

    // bird's eye view
    case 'b':
        bv=1;
        bird_view();
        break;
    case 'n':
        normal_view();
        break;

    ///panning
    case 'k':
        lpan-=1;
        rpan-=1;
        glutPostRedisplay();
        break;

    case 'l':
        lpan+=1;
        rpan +=1;
        glutPostRedisplay();
        break;

    case ';':
        tpan-=1;
        bpan-=1;
        glutPostRedisplay();
        break;

    case ':':
        tpan+=1;
        bpan +=1;
        glutPostRedisplay();
        break;

    // zoom 2;
    case '|':
        eyez++;
        glutPostRedisplay();
        break;
    case '\\':
        eyez--;
        glutPostRedisplay();
        break;



    case 27:	// Escape key
        exit(1);
    }
}

/*
r, t => pitch
y, u => Yaw
i, o => roll
c, z => scaling

*/



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
        alpha += 0.2;
        if(alpha > 360.0)
            alpha -= 360.0*floor(alpha/360.0);
    }

    if (fan4 == true )
    {
        gamma += 1;
        if(gamma > 360.0)
            gamma -= 360.0 * floor(gamma/360.0);
    }

    if ( sandbagMov == true) {
        bool swingBehind=true, swingAhead=false;
        sandAngle += 0.02;
        if(sandAngle < 100.0 && swingBehind)
        {
            sandAngle -= 0.2;
        }
        if(sandAngle < 80.0)
            sandAngle += 1;
    }

    glutPostRedisplay();

}


int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(100,100);
    glutInitWindowSize(windowHeight, windowWidth);
    glutCreateWindow("Drawing Dining room");
    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_NORMALIZE );
    glEnable( GL_LIGHTING );



    LoadTexture1("C:\\Users\\ASUS\\Downloads\\test.bmp"); //1
    LoadTexture1("C:\\Users\\ASUS\\Downloads\\floor.bmp"); //2
    LoadTexture1("C:\\Users\\ASUS\\Downloads\\wood.bmp"); //3
    LoadTexture1("C:\\Users\\ASUS\\Downloads\\tiles.bmp"); //4
    LoadTexture1("C:\\Users\\ASUS\\Downloads\\table.bmp"); //5
    LoadTexture1("C:\\Users\\ASUS\\Downloads\\ground.bmp"); //6
    LoadTexture1("C:\\Users\\ASUS\\Downloads\\darkwood.bmp"); //7





    glutKeyboardFunc(myKeyboardFunc);
    glutDisplayFunc(display);
    glutIdleFunc(animate);
    glutMainLoop();

    return 0;
}
