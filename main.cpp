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

unsigned int ID,ID1;

double Txval=0,Tyval=0,Tzval=0;
double windowHeight=960, windowWidth=540;
GLfloat alpha = 0.0, theta = 0.0, gamma = 0.0, axis_x=0.0, axis_y=0.0, sandAngle=90, kappa=20.0, kappapress=8.0, carTop=0.0, carBottom=0.0, wheels=0.0;
GLfloat doorAngle=0.0;
GLfloat BathdoorAngle=0.0;
bool openDoor=false, BathopenDoor=false, block=true;
bool fan4=false;
bool shoulderLeft = false;
bool squeeze=true, release=false;
bool swingBehind=true, swingAhead=true;
double lpan=0,rpan=0,bpan=0,tpan=0;
double changeX=.2,changeY=1.5;
double guy1Head=23.7, guy1Body=22.7, guy1Legs=20, carX=0,carY=0,carZ=0;
double bnchpressLx=40, bnchpressLy=18.5, bnchpressRx=44, bnchpressRy=18.5, barbellup=20, leftW=20, rightW=20;
double OHPpressLx=51, OHPpressLy=22, OHPpressRx=55, OHPpressRy=22, OHPbarbellup=23.5, OHPleftW=23.5, OHPrightW=23.5;

//GLdouble eyex=20, eyey=50,eyez=150,centerx=14,centery=50,centerz=0, upx=0,upy=1,upz=0, zNear=4, zFar=250;
GLdouble eyex=-9, eyey=28,eyez=96,centerx=-7.13907,centery=28,centerz=-54, upx=0,upy=1,upz=0, zNear=4, zFar=250;
//-9 28 96 -7.13907 28 -54 0 1 0
GLdouble dx,dy,dz;
// original -> 20,6,-20, 2,0,0, 0,1,0
double scale_x = 3;
double scale_y = 4;
double scale_z = 3;

GLboolean bRotate = false, uRotate = false, light0 = false,light1=false,light2=false, sandbagMov=false;

#define PI 3.1415927



/// 1920x1080
int ini_x, ini_y ;

static void resize(int width, int height)
{
    const float ar = (float) height / (float) width;
    cout<<" ar "<<ar<<endl;
    ini_x = width/2;
    ini_y = height/2;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -ar, ar, zNear, zFar);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;

}










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


static GLfloat v_cubeDOOR[8][3] =
{
    {0, 0, 0}, //0
    {0, 0, 5}, //1
    {0.2, 0, 5}, //2
    {0.2, 0, 0}, //3
    {0, 10, 0}, //4
    {0, 10, 5}, //5
    {0.2, 10, 5}, //6
    {0.2, 10, 0}  //7
};

static GLubyte cubeIndicesDOOR[6][4] =
{
    {0, 1, 2, 3}, //bottom
    {4, 5, 6, 7}, //top
    {5, 1, 2, 6}, //front
    {0, 4, 7, 3}, // back is clockwise
    {2, 3, 7, 6}, //right
    {1, 5, 4, 0}  //left is clockwise
};




static GLfloat v_cube0[8][3] =
{
    {-.5, -.5, -.5}, //0
    {-.5, -.5, .5}, //1
    {.5, -.5, .5}, //2
    {.5, -.5, -.5}, //3
    {-.5, .5, -.5}, //4
    {-.5, .5, .5}, //5
    {.5, .5, .5}, //6
    {.5, .5, -.5}  //7
};

static GLubyte cubeIndices0[6][4] =
{
    {0, 1, 2, 3}, //bottom
    {4, 5, 6, 7}, //top
    {5, 1, 2, 6}, //front
    {0, 4, 7, 3}, // back is clockwise
    {2, 3, 7, 6}, //right
    {1, 5, 4, 0}  //left is clockwise
};



static GLfloat v_cubePULL[8][3] =
{
    {0,-1,0}, //0
    {0,-1,1}, //1
    {1,-1,1}, //2
    {1,-1,0}, //3
    {0,0,0}, //4
    {0,0,1}, //5
    {1,0,1}, //6
    {1,0,0}  //7
};

static GLubyte cubeIndicesPULL[6][4] =
{
    {0, 1, 2, 3}, //bottom
    {4, 5, 6, 7}, //top
    {5, 1, 2, 6}, //front
    {0, 4, 7, 3}, // back is clockwise
    {2, 3, 7, 6}, //right
    {1, 5, 4, 0}  //left is clockwise
};


static GLfloat v_cubeNEW_PULL[8][3] =
{
    {0,-1.5,0}, //0
    {0,-1.5,.2}, //1
    {.2,-1.5,.2}, //2
    {.2,-1.5,0}, //3
    {0,0,0}, //4
    {0,0,.2}, //5
    {.2,0,.2}, //6
    {.2,0,0}  //7
};

static GLubyte cubeIndicesNEW_PULL[6][4] =
{
    {0, 1, 2, 3}, //bottom
    {4, 5, 6, 7}, //top
    {5, 1, 2, 6}, //front
    {0, 4, 7, 3}, // back is clockwise
    {2, 3, 7, 6}, //right
    {1, 5, 4, 0}  //left is clockwise
};




static GLfloat v_cubeNEW_PUSH_R[8][3] =
{
    {0,0,0}, //0
    {0,0,0.2}, //1
    {1.5,0,0.2}, //2
    {1.5,0,0}, //3
    {0,0.2,0}, //4
    {0,0.2,0.2}, //5
    {1.5,0.2,0.2}, //6
    {1.5,0.2,0}  //7
};

static GLubyte cubeIndicesNEW_PUSH_R[6][4] =
{
    {0, 1, 2, 3}, //bottom
    {4, 5, 6, 7}, //top
    {5, 1, 2, 6}, //front
    {0, 4, 7, 3}, // back is clockwise
    {2, 3, 7, 6}, //right
    {1, 5, 4, 0}  //left is clockwise
};



static GLfloat v_cubeNEW_PUSH_L[8][3] =
{
    {-1.5,0,0}, //0
    {-1.5,0,0.2}, //1
    {0,0,0.2}, //2
    {0,0,0}, //3
    {-1.5,0.2,0}, //4
    {-1.5,0.2,0.2}, //5
    {0,0.2,0.2}, //6
    {0,0.2,0}  //7
};

static GLubyte cubeIndicesNEW_PUSH_L[6][4] =
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



static GLubyte florindices[2][4] =
{
    //{0,1,2,3},
    {1,4,5,2},
    //{4,6,7,5},
    {5,7,3,2}
};



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

    for (GLint i = 0; i <2; i++)
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



void drawCubeDOOR(GLfloat r=1,GLfloat g=1,GLfloat b=1,GLboolean emission=false)
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
        glVertex3fv(&v_cubeDOOR[cubeIndicesDOOR[i][0]][0]);glTexCoord2f(1,1);
        glVertex3fv(&v_cubeDOOR[cubeIndicesDOOR[i][1]][0]);glTexCoord2f(1,0);
        glVertex3fv(&v_cubeDOOR[cubeIndicesDOOR[i][2]][0]);glTexCoord2f(0,0);
        glVertex3fv(&v_cubeDOOR[cubeIndicesDOOR[i][3]][0]);glTexCoord2f(0,1);
        glEnd();
    }
}




void drawCube0(GLfloat r=1,GLfloat g=1,GLfloat b=1,GLboolean emission=false)
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
        glVertex3fv(&v_cube0[cubeIndices0[i][0]][0]);glTexCoord2f(0,0);
        glVertex3fv(&v_cube0[cubeIndices0[i][1]][0]);glTexCoord2f(0,1);
        glVertex3fv(&v_cube0[cubeIndices0[i][2]][0]);glTexCoord2f(1,1);
        glVertex3fv(&v_cube0[cubeIndices0[i][3]][0]);glTexCoord2f(1,0);
        glEnd();
    }
}


double colors[10][3] = {
    {0,0,0},
    {1,1,1},
    {0,0,1},
    {0,1,0},
    {1,0,0},
    {1,0.5,0},
    {0.5,0.5,0.5},
    {1,0,1},
    {1,1,0},
    {0,1,1}

};

void drawCubePULL(GLfloat r=1,GLfloat g=1,GLfloat b=1,GLboolean emission=false)
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
        //glColor3f(colors[i+2][0],colors[i+2][1],colors[i+2][2]);
        glVertex3fv(&v_cubePULL[cubeIndicesPULL[i][0]][0]);glTexCoord2f(1,1);
        glVertex3fv(&v_cubePULL[cubeIndicesPULL[i][1]][0]);glTexCoord2f(1,0);
        glVertex3fv(&v_cubePULL[cubeIndicesPULL[i][2]][0]);glTexCoord2f(0,0);
        glVertex3fv(&v_cubePULL[cubeIndicesPULL[i][3]][0]);glTexCoord2f(0,1);
        glEnd();
    }
}



void drawCubeNEW_PULL(GLfloat r=1,GLfloat g=1,GLfloat b=1,GLboolean emission=false)
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
        //glColor3f(colors[i+2][0],colors[i+2][1],colors[i+2][2]);
        glVertex3fv(&v_cubeNEW_PULL[cubeIndicesNEW_PULL[i][0]][0]);glTexCoord2f(1,1);
        glVertex3fv(&v_cubeNEW_PULL[cubeIndicesNEW_PULL[i][1]][0]);glTexCoord2f(1,0);
        glVertex3fv(&v_cubeNEW_PULL[cubeIndicesNEW_PULL[i][2]][0]);glTexCoord2f(0,0);
        glVertex3fv(&v_cubeNEW_PULL[cubeIndicesNEW_PULL[i][3]][0]);glTexCoord2f(0,1);
        glEnd();
    }
}



void drawCubeNEW_PUSH_R(GLfloat r=1,GLfloat g=1,GLfloat b=1,GLboolean emission=false)
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
        //glColor3f(colors[i+2][0],colors[i+2][1],colors[i+2][2]);
        glVertex3fv(&v_cubeNEW_PUSH_R[cubeIndicesNEW_PUSH_R[i][0]][0]);glTexCoord2f(1,1);
        glVertex3fv(&v_cubeNEW_PUSH_R[cubeIndicesNEW_PUSH_R[i][1]][0]);glTexCoord2f(1,0);
        glVertex3fv(&v_cubeNEW_PUSH_R[cubeIndicesNEW_PUSH_R[i][2]][0]);glTexCoord2f(0,0);
        glVertex3fv(&v_cubeNEW_PUSH_R[cubeIndicesNEW_PUSH_R[i][3]][0]);glTexCoord2f(0,1);
        glEnd();
    }
}

void drawCubeNEW_PUSH_L(GLfloat r=1,GLfloat g=1,GLfloat b=1,GLboolean emission=false)
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
        //glColor3f(colors[i+2][0],colors[i+2][1],colors[i+2][2]);
        glVertex3fv(&v_cubeNEW_PUSH_L[cubeIndicesNEW_PUSH_L[i][0]][0]);glTexCoord2f(1,1);
        glVertex3fv(&v_cubeNEW_PUSH_L[cubeIndicesNEW_PUSH_L[i][1]][0]);glTexCoord2f(1,0);
        glVertex3fv(&v_cubeNEW_PUSH_L[cubeIndicesNEW_PUSH_L[i][2]][0]);glTexCoord2f(0,0);
        glVertex3fv(&v_cubeNEW_PUSH_L[cubeIndicesNEW_PUSH_L[i][3]][0]);glTexCoord2f(0,1);
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
        glVertex3fv(&v_pyramid[poly_Indices[i][0]][0]); glTexCoord3f(1,1,1);
        glVertex3fv(&v_pyramid[poly_Indices[i][1]][0]); glTexCoord3f(1,0,1);
        glVertex3fv(&v_pyramid[poly_Indices[i][2]][0]); glTexCoord3f(0,1,1);
        glVertex3fv(&v_pyramid[poly_Indices[i][3]][0]); glTexCoord3f(1,0,1);
        glVertex3fv(&v_pyramid[poly_Indices[i][4]][0]); glTexCoord3f(1,1,0);
        glVertex3fv(&v_pyramid[poly_Indices[i][5]][0]); glTexCoord3f(0,0,1);
    }
    glEnd();


    for (GLint i = 0; i <6; i++)
    {
        glBegin(GL_QUADS);
        glColor3f(0,0,0);
        glVertex3fv(&v_pyramid[quadIndices[i][0]][0]);glTexCoord2f(1,1);
        glVertex3fv(&v_pyramid[quadIndices[i][1]][0]);glTexCoord2f(1,0);
        glVertex3fv(&v_pyramid[quadIndices[i][2]][0]);glTexCoord2f(0,0);
        glVertex3fv(&v_pyramid[quadIndices[i][3]][0]);glTexCoord2f(0,1);

    }
    glEnd();


}










void dumbbell(double weight = 5.0)
{
    double factor;
    if (weight==5.0) factor = 1;
    else factor = weight*0.5;

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glColor3b(1,1,1);
    glTranslatef(0,0,0);
    glScalef(0.1,0.02,0.8);
    glBindTexture(GL_TEXTURE_2D, 9);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,0,0);
    glScalef(0.5,0.4,0.3*factor);
    //glScalef(factor,factor,factor);
    //drawCube(1,1,1);
//    glScalef(0.2,0.4,0.2);
    //glutSolidSphere( 0.4, 10.0, 15.0);
    glBindTexture(GL_TEXTURE_2D, 29);
    drawpyramid();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,0,0.8);
    glScalef(0.5,0.4,0.3*factor);
    //glScalef(factor,factor,factor);
    //drawCube(1,1,1);
//    glScalef(0.2,0.4,0.2);
    //glutSolidSphere( 0.4, 10.0, 15.0);
    glBindTexture(GL_TEXTURE_2D, 29);
    drawpyramid();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

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

void Garage();

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glFrustum(-5,5, -5, 5, zNear, zFar);
    //glFrustum(-5+lpan, 5+rpan, -5+bpan, 5+tpan, zNear, zFar);
     //gluPerspective(60,1,5,100);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt(eyex,eyey,eyez,centerx+dx,centery+dy,centerz+dz,upx,upy,upz);
    //glViewport(0, 0, windowHeight, windowWidth);

    //glRotatef(45, 0, 0, 1 );
    // triangle();

    //glRotatef(120,0,1,0);
//     glScalef(1,5,1);
    //glTranslatef(0,-10,0);


    glScalef(scale_x,scale_y,scale_z);

    glRotatef( alpha,axis_x, axis_y, 0.0 );
    glRotatef( theta, axis_x, axis_y, 0.0 );


    cout<<eyex<<" "<<eyey<<" "<<eyez<<" "<<centerx+dx<<" "<<centery+dy<<" "<<centerz+dz<<" "<<upx<<" "<<upy<<" "<<upz<<endl;

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, 30);
    drawWall();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    { /// Floor right


    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(25,0,0);
    //glRotatef(22, 0,0,1);
    glScalef(55,0.1,25);
    glBindTexture(GL_TEXTURE_2D, 3);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    }

    {/// Wall right back

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(25,0,0);
    //glRotatef(22, 0,0,1);
    glScalef(55,15,0.1);
    glBindTexture(GL_TEXTURE_2D, 2);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    }


    {/// Locker room wall
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(25,0,0);
    //glRotatef(22, 0,0,1);
    glScalef(.1,15,18);
    glBindTexture(GL_TEXTURE_2D, 1);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-14,10,0);
    //glRotatef(22, 0,0,1);
    glScalef(.1,5,5);
    glBindTexture(GL_TEXTURE_2D, 8);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    }


    /// BLOCK WALL
    if(block){
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-14,0,25);
    //glRotatef(22, 0,0,1);
    glScalef(14+80,15,.1);
    glBindTexture(GL_TEXTURE_2D, 1);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-45,15,25);
    //glRotatef(22, 0,0,1);
    glScalef(45+80,20,.1);
    glBindTexture(GL_TEXTURE_2D, 1);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    }



    {/// Wall right side

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(80,0,0);
    //glRotatef(22, 0,0,1);
    glScalef(0.1,15,25);
    glBindTexture(GL_TEXTURE_2D, 1);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    }




    {/// staircase

    int st=14,nxt=0;
    while(st>0){
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(21,0,nxt);
    //glRotatef(22, 0,0,1);
    glScalef(4,st,1);
    glBindTexture(GL_TEXTURE_2D, 15);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    st-=1;
    nxt++;
    }


    }


    {/// Wall left
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-14,0,5);
    //glRotatef(22, 0,0,1);
    glScalef(.1,15,20);
    glBindTexture(GL_TEXTURE_2D, 15);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-14,10,0);
    //glRotatef(22, 0,0,1);
    glScalef(.1,5,5);
    glBindTexture(GL_TEXTURE_2D, 8);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    }


    {/// Door
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-14,0,0);
    glRotatef(doorAngle, 0,1,0);
    //glScalef(.1,15,20);
    glBindTexture(GL_TEXTURE_2D, 7);
    drawCubeDOOR(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    }



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



    /// RACK
    {
    glPushMatrix();

    rack();
    glPopMatrix();
    }
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



    {// sandbag handle


    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(10, 8, 10);
    //glRotatef(22, 0,0,1);
    glScalef(0.1,7,0.1);
    glBindTexture(GL_TEXTURE_2D, 10);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



    }

    {/// cyl=====================================

    glPushMatrix();

        glTranslatef(10, 8, 10);
        glRotatef(sandAngle, 1, 0, 0 );
        //glRotatef(sandAngle, 0, 0, 1 );
        glScalef(2, 2, 2);
        cyl( .5,.3,.4);
    glPopMatrix();

    }

    // cyl circle=====================================


    /// bathroom
    /// toilet 1
    {

    //glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(75,0,5);
    //glRotatef(22, 0,0,1);
    glScalef(.4,2,.4);
    //glBindTexture(GL_TEXTURE_2D, 25);
    drawCube(1,1,1);
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);


    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(74.5,2,4.9);
    //glRotatef(22, 0,0,1);
    glScalef(1,1,1.5);
    glBindTexture(GL_TEXTURE_2D, 23);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(74.4,2,4.9);
    //glRotatef(22, 0,0,1);
    glScalef(.1,1,1.5);
    //glBindTexture(GL_TEXTURE_2D, 23);
    drawCube(1,1,1);
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);

    //glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(75.5,2,4.9);
    //glRotatef(22, 0,0,1);
    glScalef(.1,1,1.5);
    //glBindTexture(GL_TEXTURE_2D, 23);
    drawCube(1,1,1);
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);

    //glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(74.4,2,4.8);
    //glRotatef(22, 0,0,1);
    glScalef(1.1,1,.1);
    //glBindTexture(GL_TEXTURE_2D, 23);
    drawCube(1,1,1);
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);

    //glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(74.4,2,6.4);
    //glRotatef(22, 0,0,1);
    glScalef(1.1,1,.1);
    //glBindTexture(GL_TEXTURE_2D, 23);
    drawCube(1,1,1);
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);






    //glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(74.5,3,4.9);
    //glRotatef(22, 0,0,1);
    glScalef(1,1.4,.1);
    //glBindTexture(GL_TEXTURE_2D, 26);
    drawCube(1,1,1);
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);



    }


    /// toilet 2
    glPushMatrix();

    glTranslatef(0,0,10);
    {

    //glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(75,0,5);
    //glRotatef(22, 0,0,1);
    glScalef(.4,2,.4);
    //glBindTexture(GL_TEXTURE_2D, 25);
    drawCube(1,1,1);
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);


    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(74.5,2,4.9);
    //glRotatef(22, 0,0,1);
    glScalef(1,1,1.5);
    glBindTexture(GL_TEXTURE_2D, 23);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(74.4,2,4.9);
    //glRotatef(22, 0,0,1);
    glScalef(.1,1,1.5);
    //glBindTexture(GL_TEXTURE_2D, 23);
    drawCube(1,1,1);
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);

    //glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(75.5,2,4.9);
    //glRotatef(22, 0,0,1);
    glScalef(.1,1,1.5);
    //glBindTexture(GL_TEXTURE_2D, 23);
    drawCube(1,1,1);
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);

    //glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(74.4,2,4.8);
    //glRotatef(22, 0,0,1);
    glScalef(1.1,1,.1);
    //glBindTexture(GL_TEXTURE_2D, 23);
    drawCube(1,1,1);
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);

    //glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(74.4,2,6.4);
    //glRotatef(22, 0,0,1);
    glScalef(1.1,1,.1);
    //glBindTexture(GL_TEXTURE_2D, 23);
    drawCube(1,1,1);
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);






    //glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(74.5,3,4.9);
    //glRotatef(22, 0,0,1);
    glScalef(1,1.4,.1);
    //glBindTexture(GL_TEXTURE_2D, 26);
    drawCube(1,1,1);
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);



    }
    glPopMatrix();


    {/// Door 1
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(68,0,3);
    glRotatef(BathdoorAngle, 0,1,0);
    glScalef(1,.78,1);
    glBindTexture(GL_TEXTURE_2D, 24);
    drawCubeDOOR(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    }

    {/// Wall middle
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(68,0,8);
    //glRotatef(22, 0,0,1);
    glScalef(.1,8,5);
    glBindTexture(GL_TEXTURE_2D, 15);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(68,0,12.8);
    //glRotatef(22, 0,0,1);
    glScalef(12,8,.1);
    glBindTexture(GL_TEXTURE_2D, 15);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    }





    {/// Door 2
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(68,0,13);
    glRotatef(BathdoorAngle, 0,1,0);
    glScalef(1,.78,1);
    glBindTexture(GL_TEXTURE_2D, 24);
    drawCubeDOOR(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    }


    {/// Wall middle
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(68,0,18);
    //glRotatef(22, 0,0,1);
    glScalef(.1,8,7);
    glBindTexture(GL_TEXTURE_2D, 15);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    }


    /// locker seats
    for(int cnt=0;cnt<20;cnt++)
    {
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(35+cnt,0,2);
    //glRotatef(22, 0,0,1);
    glScalef(.1,2,.1);
    glBindTexture(GL_TEXTURE_2D, 7);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(34.5+cnt,2,1.9);
    //glRotatef(22, 0,0,1);
    glScalef(1,.2,1.5);
    glBindTexture(GL_TEXTURE_2D, 25);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    }

    /// locker seats
    for(int cnt=0;cnt<25;cnt++)
    {
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(30+cnt,0,2+4);
    //glRotatef(22, 0,0,1);
    glScalef(.1,2,.1);
    glBindTexture(GL_TEXTURE_2D, 7);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(29.5+cnt,2,1.9+4);
    //glRotatef(22, 0,0,1);
    glScalef(1,.2,1.5);
    glBindTexture(GL_TEXTURE_2D, 25);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    }


    /// locker seats
    for(int cnt=0;cnt<25;cnt++)
    {
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(30+cnt,0,2+8);
    //glRotatef(22, 0,0,1);
    glScalef(.1,2,.1);
    glBindTexture(GL_TEXTURE_2D, 7);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(29.5+cnt,2,1.9+8);
    //glRotatef(22, 0,0,1);
    glScalef(1,.2,1.5);
    glBindTexture(GL_TEXTURE_2D, 25);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    }


    /// sink




    /// bathroom guard walls

    {///
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(59,0,0);
    //glRotatef(22, 0,0,1);
    glScalef(.1,14,20);
    glBindTexture(GL_TEXTURE_2D, 1);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    }












    /// swimming pool



    secondFloor();

    Garage();





    /// Lockers

    {
        for(int y=5;y<=8;y++){
            for(int x=27;x<55;x++){
            glEnable(GL_TEXTURE_2D);
            glPushMatrix();
                glTranslatef(x, y, 1);
                glScalef(1,1,1);
                glBindTexture(GL_TEXTURE_2D, 7);
                drawCube(1,1,1);
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);
            }
        }
    }

    {
        for(int y=17;y<=24;y++){
            for(int x=27;x<34;x++){
            glEnable(GL_TEXTURE_2D);
            glPushMatrix();
                glTranslatef(x, y, 1);
                glScalef(1,1,1);
                glBindTexture(GL_TEXTURE_2D, 8);
                drawCube(1,1,1);
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);
            }
        }
    }




    if(block) {// ceiling
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-45,35,0);
    //glRotatef(22, 0,0,1);
    glScalef(45+80,1,25);
    glBindTexture(GL_TEXTURE_2D, 2);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    }

    {// ceiling bar |


    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-20,34,0);
    //glRotatef(22, 0,0,1);
    glScalef(.5,0.5,25);
    glBindTexture(GL_TEXTURE_2D, 3);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    // ceiling bar --
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-45,34,10);
    //glRotatef(22, 0,0,1);
    glScalef(80+45,0.5,.5);
    glBindTexture(GL_TEXTURE_2D, 3);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
     // =========================================
    }





    { ///LIGHT
    // ========================================

    light(26,8.83,4.5,light0,GL_LIGHT0,false,false);
    light(-10,13,10,light1,GL_LIGHT1,true,false);
    light(18,12,15,light2,GL_LIGHT2,false,true);
    light(-10,35,10,light1,GL_LIGHT3,true,false);
    light(-10,45,10,light1,GL_LIGHT4,false,true);


    }

    glFlush();
    glutSwapBuffers();

}


void Garage() {

    /// Garage
    {
        /// pillars 1 & 2
        glEnable(GL_TEXTURE_2D);
        glPushMatrix();
        glTranslatef(-45,0,1);
        //glRotatef(22, 0,0,1);
        glScalef(1,15,1);
        glBindTexture(GL_TEXTURE_2D, 5);
        drawCube(1,1,1);
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);

        glEnable(GL_TEXTURE_2D);
        glPushMatrix();
        glTranslatef(-45,0,20);
        //glRotatef(22, 0,0,1);
        glScalef(1,15,1);
        glBindTexture(GL_TEXTURE_2D, 5);
        drawCube(1,1,1);
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);

        /// boxes
        glEnable(GL_TEXTURE_2D);
        glPushMatrix();
        glTranslatef(-85,0,0);
        //glRotatef(22, 0,0,1);
        glScalef(+85-14,15,.2);
        glBindTexture(GL_TEXTURE_2D, 3);
        drawCube(1,1,1);
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);


        /// floor
        glEnable(GL_TEXTURE_2D);
        glPushMatrix();
        glTranslatef(-85,0,0);
        //glRotatef(22, 0,0,1);
        glScalef(+85-14,.2,25);
        glBindTexture(GL_TEXTURE_2D, 18);
        drawCube(1,1,1);
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);


        /// fence
        for(double pos=-85;pos<-45;pos++){
        glEnable(GL_TEXTURE_2D);
        glPushMatrix();
        glTranslatef(pos,15.5,0);
        //glRotatef(22, 0,0,1);
        glScalef(1,1,1);
        glBindTexture(GL_TEXTURE_2D, 16);
        //glutSolidTorus(0.2,0.3,15,20);
        glutWireTetrahedron();
        glutWireOctahedron();
        if( ((int)pos)%3==0) {
            glBindTexture(GL_TEXTURE_2D, 17);
            if(((int)pos)%4==0) glutWireDodecahedron();
            else      glutWireSphere(1.5,12,16);
        }
        if( ((int)pos)%5==0) {
            glBindTexture(GL_TEXTURE_2D, 17);
            glutWireTorus(.1,.3,15,20);
        }

        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
        }


        /// moving car


        /// driveway


        /// trees
        /// fence
        for(double pos=-55;pos<-15;pos++){
        glEnable(GL_TEXTURE_2D);
        glPushMatrix();
        glTranslatef(pos,0.2,23);
        //glRotatef(22, 0,0,1);
        glScalef(1,1,1);
        glBindTexture(GL_TEXTURE_2D, 33);
        //glutSolidTorus(0.2,0.3,15,20);
        glutWireTetrahedron();
        glutWireOctahedron();
        if( (rand())%3==0 && openDoor) {
            glBindTexture(GL_TEXTURE_2D, 33);
//            if((rand())%4==0) glutWireDodecahedron();
//            else
            glutWireSphere(.4,1,4);
        }
        else {
            glBindTexture(GL_TEXTURE_2D, 33);
            glutWireTorus(.1,.3,15,20);
        }

        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
        }





    }



}



void secondFloor() {
    double ext=4.4;

    /// COUNTER ====================================
    glPushMatrix();
    glTranslatef(16,15,-5);
    {
    // cupboards
    //(1.0, 0.5, 0.0);


    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-13,0,11);
    //glRotatef(22, 0,0,1);
    glScalef(4,4,2);
    glBindTexture(GL_TEXTURE_2D, 7);
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
    glBindTexture(GL_TEXTURE_2D, 7);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    /// COUNTER


//    /// chair
//    glPushMatrix();
//    glTranslatef(-12,0,15);
//    //glRotatef(180,0,1,0);
//    chair();
//    glPopMatrix();
//    }
    }
    glPopMatrix();
    /// COUNTER ====================================



    /// FLOOR
    {


    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-14,15,0);
    //glRotatef(22, 0,0,1);
    glScalef(35,0.1,25);
    glBindTexture(GL_TEXTURE_2D, 3);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    }

    /// FLOOR left
    {


    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-45,15,0);
    //glRotatef(22, 0,0,1);
    glScalef(34,0.1,25);
    glBindTexture(GL_TEXTURE_2D, 3);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    }

    /// Floor right
    {


    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(25,15,0);
    //glRotatef(22, 0,0,1);
    glScalef(55,0.1,25);
    glBindTexture(GL_TEXTURE_2D, 3);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    }
    /// Floor connector
    {


    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(21,15,8);
    //glRotatef(22, 0,0,1);
    glScalef(4,0.02,17);
    glBindTexture(GL_TEXTURE_2D, 12);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    }
    /// Floor hider
    {


    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(21,15.1,8);
    //glRotatef(22, 0,0,1);
    glScalef(4,0.1,17);
    glBindTexture(GL_TEXTURE_2D, 1);
    //glRotated(180,0,0,1);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    }

    /// partition wall
    {


    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(25,15,0);
    //glRotatef(22, 0,0,1);
    glScalef(.2,15+ext,8);
    glBindTexture(GL_TEXTURE_2D, 3);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    }
    /// walls back 2nd floor
    {

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-45,15,0);
    //glRotatef(22, 0,0,1);
    glScalef(125,15+ext,0.1);
    glBindTexture(GL_TEXTURE_2D, 16);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    }
    /// walls side 2nd floor

    {

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(80,15,0);
    //glRotatef(22, 0,0,1);
    glScalef(0.1,15+ext,25);
    glBindTexture(GL_TEXTURE_2D, 1);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    }


    /// walls side left 2nd floor

    {

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-45,15,0);
    //glRotatef(22, 0,0,1);
    glScalef(0.1,15+ext,25);
    glBindTexture(GL_TEXTURE_2D, 1);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    }

    double base = 15.1;




    /// ALI
    {

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-44.8,22.5,5);
    //glRotatef(22, 0,0,1);
    glScalef(.1,14,10);
    glBindTexture(GL_TEXTURE_2D, 11);
    drawCube0(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    }







    ///Boxing Ring
    {

    // base
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-12,base,5);
    //glRotatef(22, 0,0,1);
    glScalef(14,2,10);
    glBindTexture(GL_TEXTURE_2D, 8);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // pillars
    // left top
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-12,base+2,5);
    //glRotatef(22, 0,0,1);
    glScalef(0.5,5,0.5);
    glBindTexture(GL_TEXTURE_2D, 9);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    // left bottom
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-12,base+2,14.5);
    //glRotatef(22, 0,0,1);
    glScalef(0.5,5,0.5);
    glBindTexture(GL_TEXTURE_2D, 9);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    // right top
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(1.5,base+2,5);
    //glRotatef(22, 0,0,1);
    glScalef(0.5,5,0.5);
    glBindTexture(GL_TEXTURE_2D, 9);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    // right bottom
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(1.5,base+2,14.5);
    //glRotatef(22, 0,0,1);
    glScalef(0.5,5,0.5);
    glBindTexture(GL_TEXTURE_2D, 9);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    // ropes
    // top 1
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-12,base+2+1,5);
    //glRotatef(22, 0,0,1);
    glScalef(14,0.2,0.2);
    glBindTexture(GL_TEXTURE_2D, 10);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    // top 2
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-12,base+2+2.5,5);
    //glRotatef(22, 0,0,1);
    glScalef(14,0.2,0.2);
    glBindTexture(GL_TEXTURE_2D, 10);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    // top 3
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-12,base+2+4,5);
    //glRotatef(22, 0,0,1);
    glScalef(14,0.2,0.2);
    glBindTexture(GL_TEXTURE_2D, 10);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // bottom
    // bottom 1
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-12,base+2+1,14.5);
    //glRotatef(22, 0,0,1);
    glScalef(14,0.2,0.2);
    glBindTexture(GL_TEXTURE_2D, 10);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    // bottom 2
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-12,base+2+2.5,14.5);
    //glRotatef(22, 0,0,1);
    glScalef(14,0.2,0.2);
    glBindTexture(GL_TEXTURE_2D, 10);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    // bottom 3
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-12,base+2+4,14.5);
    //glRotatef(22, 0,0,1);
    glScalef(14,0.2,0.2);
    glBindTexture(GL_TEXTURE_2D, 10);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // left
    // left 1
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-12,base+2+1,5);
    //glRotatef(22, 0,0,1);
    glScalef(0.2,0.2,10);
    glBindTexture(GL_TEXTURE_2D, 10);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    // left 2
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-12,base+2+2.5,5);
    //glRotatef(22, 0,0,1);
    glScalef(0.2,0.2,10);
    glBindTexture(GL_TEXTURE_2D, 10);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    // left 3
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-12,base+2+4,5);
    //glRotatef(22, 0,0,1);
    glScalef(0.2,0.2,10);
    glBindTexture(GL_TEXTURE_2D, 10);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    // right
    // right 1
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(1.6,base+2+1,5);
    //glRotatef(22, 0,0,1);
    glScalef(0.2,0.2,10);
    glBindTexture(GL_TEXTURE_2D, 10);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    // right 2
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(1.6,base+2+2.5,5);
    //glRotatef(22, 0,0,1);
    glScalef(0.2,0.2,10);
    glBindTexture(GL_TEXTURE_2D, 10);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    // right 3
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(1.6,base+2+4,5);
    //glRotatef(22, 0,0,1);
    glScalef(0.2,0.2,10);
    glBindTexture(GL_TEXTURE_2D, 10);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    }
    /// Boxing ring end =============


    /// spectator seats=====
    {
    for(int i=0;i<4;i++){
        glPushMatrix();
        if(i!=1) glTranslated(-16,base,5+i*i);
        else glTranslated(-20,base,5+i);
        if(i%2==1){
            glRotated(20,0,1,0);
        }
        chair();
        glPopMatrix();
    }
    }




    /// more sandbags
    {// sandbag handle


    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-24, 23, 10);
    //glRotatef(22, 0,0,1);
    glScalef(0.1,11,0.1);
    glBindTexture(GL_TEXTURE_2D, 10);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



    }

    {/// cyl=====================================

    glPushMatrix();

        glTranslatef(-24, 23, 10);
        glRotatef(sandAngle, 1, 0, 0 );
        //glRotatef(sandAngle, 0, 0, 1 );
        glScalef(2, 2, 2);
        cyl( .5,.3,.4);
    glPopMatrix();

    }

    {// sandbag handle


    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-34, 23, 10);
    //glRotatef(22, 0,0,1);
    glScalef(0.1,11,0.1);
    glBindTexture(GL_TEXTURE_2D, 10);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



    }

    {/// cyl=====================================

    glPushMatrix();

        glTranslatef(-34, 23, 10);
        glRotatef(sandAngle, 1, 0, 0 );
        //glRotatef(sandAngle, 0, 0, 1 );
        glScalef(2, 2, 2);
        cyl( .5,.3,.4);
    glPopMatrix();

    }

    // cyl circle=====================================



    /// PULL UP BAR
    {


    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-45,26,15);
    //glRotatef(22, 0,0,1);
    glScalef(8,0.2,0.2);
    glBindTexture(GL_TEXTURE_2D, 15);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-37,15,15);
    //glRotatef(22, 0,0,1);
    glScalef(0.2,11,0.2);
    glBindTexture(GL_TEXTURE_2D, 15);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-45,26,20);
    //glRotatef(22, 0,0,1);
    glScalef(8,0.2,0.2);
    glBindTexture(GL_TEXTURE_2D, 15);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-37,15,20);
    //glRotatef(22, 0,0,1);
    glScalef(0.2,11,0.2);
    glBindTexture(GL_TEXTURE_2D, 15);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    }


    /// PULL UP MANequin
    {
    //right arm
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-40,24.5,20);
    //glRotatef(22, 0,0,1);
    glScalef(0.2,1.5,0.2);
    glBindTexture(GL_TEXTURE_2D, 26);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //left arm
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-43,24.5,20);
    //glRotatef(22, 0,0,1);
    glScalef(0.2,1.5,0.2);
    glBindTexture(GL_TEXTURE_2D, 26);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //right shoulder2
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-40,24.5,20);
    //glRotatef(22, 0,0,1);
    //glScalef(change,1.5,.2);
    glRotatef(-kappa,0,0,1);
    glBindTexture(GL_TEXTURE_2D, 9);
    //glRotatef(30,0,1,0);
    ///drawCubePULL(1,1,1);
    drawCubeNEW_PULL(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //left shoulder1
    // dynamic scaling going on
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-43,24.5,20);
    //glRotatef(22, 0,1,0);
    //glScalef(changeX,changeY,.2);
    glRotatef(kappa,0,0,1);
    glBindTexture(GL_TEXTURE_2D, 9);
    //glRotatef(-30,0,1,0);
    drawCubeNEW_PULL(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //head
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-41.5,guy1Head,20);
    //glRotatef(22, 0,1,0);
    //glScalef(2,1.5,.2);

    glBindTexture(GL_TEXTURE_2D, 27);
    glutSolidSphere(0.4,16,20);

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //upper body
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-41.7,guy1Body,20);
    //glRotatef(22, 0,1,0);
    glScalef(.5,2,.5);
    glBindTexture(GL_TEXTURE_2D, 10);
    //glRotatef(-30,0,1,0);
    drawCubePULL(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    // left leg
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-42.1,guy1Legs,20);
    //glRotatef(22, 0,1,0);
    glScalef(.4,3,.3);
    glBindTexture(GL_TEXTURE_2D, 27);
    //glRotatef(-30,0,1,0);
    drawCubePULL(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // right leg
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-41.3,guy1Legs,20);
    //glRotatef(22, 0,1,0);
    glScalef(.4,3,.3);
    glBindTexture(GL_TEXTURE_2D, 27);
    //glRotatef(-30,0,1,0);
    drawCubePULL(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);





    }




    /// Bench Pressing
    {


    // barbell
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    // intial translate (39.5,20,20))
    glTranslatef(39.5,barbellup,20);
    //glRotatef(22, 0,0,1);
    glScalef(5,.1,0.1);
    glBindTexture(GL_TEXTURE_2D, 9);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    /// wheels
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(39,leftW,20);
    //glRotatef(w1, 0,0,1);
    glScalef(.4,1,1);
    glBindTexture(GL_TEXTURE_2D, 28);
    glutSolidSphere(1,15,5);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    /// wheels
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(44.80,rightW,20);
    //glRotatef(w1, 0,0,1);
    glScalef(.4,1,1);
    glBindTexture(GL_TEXTURE_2D, 28);
    glutSolidSphere(1,15,5);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);







    //left arm
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(bnchpressLx,bnchpressLy,20);
    //glRotatef(22, 0,0,1);
    glScalef(0.2,1.5,0.2);
    glBindTexture(GL_TEXTURE_2D, 26);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //right arm
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(bnchpressRx,bnchpressRy,20);
    //glRotatef(22, 0,0,1);
    glScalef(0.2,1.5,0.2);
    glBindTexture(GL_TEXTURE_2D, 26);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //LEFT shoulder2
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(41.5,18,20);
    //glRotatef(22, 0,0,1);
    //glScalef(change,1.5,.2);
    glRotatef(-kappapress,0,0,1);
    glBindTexture(GL_TEXTURE_2D, 26);
    //glRotatef(30,0,1,0);
    ///drawCubePULL(1,1,1);
    drawCubeNEW_PUSH_L(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //RIGHT shoulder1
    // dynamic scaling going on
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(42.5,18,20);
    //glRotatef(22, 0,1,0);
    //glScalef(changeX,changeY,.2);
    glRotatef(kappapress,0,0,1);
    glBindTexture(GL_TEXTURE_2D, 26);
    //glRotatef(-30,0,1,0);
    drawCubeNEW_PUSH_R(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



    //head
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(42,18,20.8);
    //glRotatef(22, 0,1,0);
    //glScalef(2,1.5,.2);

    glBindTexture(GL_TEXTURE_2D, 27);
    glutSolidSphere(0.4,16,20);

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //upper body
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(41.35,17.7,18);
    //glRotatef(22, 0,1,0);
    glScalef(1.25,.5,2);
    glBindTexture(GL_TEXTURE_2D, 9);
    //glRotatef(-30,0,1,0);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    // left thigh
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(41.25,18,16);
    //glRotatef(22, 0,1,0);
    glScalef(.4,.3,3);
    glBindTexture(GL_TEXTURE_2D, 9);
    //glRotatef(-30,0,1,0);
    drawCubePULL(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // right thigh
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(42.25,18,16);
    //glRotatef(22, 0,1,0);
    glScalef(.4,.3,3);
    glBindTexture(GL_TEXTURE_2D, 9);
    //glRotatef(-30,0,1,0);
    drawCubePULL(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // left shin
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(41.25,18,15.5);
    //glRotatef(22, 0,1,0);
    glScalef(.2,2,.3);
    glBindTexture(GL_TEXTURE_2D, 26);
    //glRotatef(-30,0,1,0);
    drawCubePULL(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // right shin
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(42.25,18,15.5);
    //glRotatef(22, 0,1,0);
    glScalef(.2,2,.3);
    glBindTexture(GL_TEXTURE_2D, 26);
    //glRotatef(-30,0,1,0);
    drawCubePULL(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // seat
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(41.65,17,16);
    //glRotatef(22, 0,1,0);
    glScalef(.6,.5,4);
    glBindTexture(GL_TEXTURE_2D, 25);
    //glRotatef(-30,0,1,0);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    // seat leg1
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(41.75,17,19);
    //glRotatef(22, 0,1,0);
    glScalef(.5,2,.3);
    glBindTexture(GL_TEXTURE_2D, 10);
    //glRotatef(-30,0,1,0);
    drawCubePULL(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // seat leg2
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(41.75,17,16.5);
    //glRotatef(22, 0,1,0);
    glScalef(.5,2,.3);
    glBindTexture(GL_TEXTURE_2D, 10);
    //glRotatef(-30,0,1,0);
    drawCubePULL(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    }



    /// overhead press

    {


    // barbell
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    // intial translate (39.5,20,20))
    glTranslatef(50.5,OHPbarbellup,20);
    //glRotatef(22, 0,0,1);
    glScalef(5,.1,0.1);
    glBindTexture(GL_TEXTURE_2D, 9);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    /// wheels
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(50,OHPleftW,20);
    //glRotatef(w1, 0,0,1);
    glScalef(.4,1,1);
    glBindTexture(GL_TEXTURE_2D, 28);
    glutSolidSphere(1,15,5);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    /// wheels
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(55.80,OHPrightW,20);
    //glRotatef(w1, 0,0,1);
    glScalef(.4,1,1);
    glBindTexture(GL_TEXTURE_2D, 28);
    glutSolidSphere(1,15,5);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);







    //left arm
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(OHPpressLx,OHPpressLy,20);
    //glRotatef(22, 0,0,1);
    glScalef(0.2,1.5,0.2);
    glBindTexture(GL_TEXTURE_2D, 26);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //right arm
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(OHPpressRx,OHPpressRy,20);
    //glRotatef(22, 0,0,1);
    glScalef(0.2,1.5,0.2);
    glBindTexture(GL_TEXTURE_2D, 26);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //LEFT shoulder2
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(52.5,21.5,20);
    //glRotatef(22, 0,0,1);
    //glScalef(change,1.5,.2);
    glRotatef(-kappapress,0,0,1);
    glBindTexture(GL_TEXTURE_2D, 26);
    //glRotatef(30,0,1,0);
    ///drawCubePULL(1,1,1);
    drawCubeNEW_PUSH_L(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //RIGHT shoulder1
    // dynamic scaling going on
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(53.5,21.5,20);
    //glRotatef(22, 0,1,0);
    //glScalef(changeX,changeY,.2);
    glRotatef(kappapress,0,0,1);
    glBindTexture(GL_TEXTURE_2D, 26);
    //glRotatef(-30,0,1,0);
    drawCubeNEW_PUSH_R(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



    //head
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(53,22,20);
    //glRotatef(22, 0,1,0);
    //glScalef(2,1.5,.2);

    glBindTexture(GL_TEXTURE_2D, 27);
    glutSolidSphere(0.4,16,20);

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //upper body
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(52.7,21,20);
    //glRotatef(22, 0,1,0);
    glScalef(.6,3,.2);
    glBindTexture(GL_TEXTURE_2D, 22);
    //glRotatef(-30,0,1,0);
    drawCubePULL(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    // left leg
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(52.5,18,20);
    //glRotatef(22, 0,1,0);
    glScalef(.4,3,.3);
    glBindTexture(GL_TEXTURE_2D, 15);
    //glRotatef(-30,0,1,0);
    drawCubePULL(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // right leg
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(53.1,18,20);
    //glRotatef(22, 0,1,0);
    glScalef(.4,3,.3);
    glBindTexture(GL_TEXTURE_2D, 15);
    //glRotatef(-30,0,1,0);
    drawCubePULL(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);





    }




    /// RACK 1
    {
    glPushMatrix();
    glTranslatef(50,15,0);
    rack();
    glPopMatrix();
    }


    /// RACK 2
    {
    glPushMatrix();
    glTranslatef(60,15,0);
    rack();
    glPopMatrix();
    }

    /// DUMBBELLS========================================
    // RACK1
    glPushMatrix();
    glTranslatef(50,15,0);
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
    glPopMatrix();
    /// DUMBBELLS========================================


    /// DUMBBELLS========================================
    // RACK2
    glPushMatrix();
    glTranslatef(60,15,0);
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
    glPopMatrix();
    /// DUMBBELLS========================================


    /// RACK 3
    {
    glPushMatrix();
    glTranslatef(50,15,10);
    rack();
    glPopMatrix();
    }


    /// aRNY
    {

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(80,22.5,8);
    //glRotatef(22, 0,0,1);
    glScalef(.1,14,10);
    glBindTexture(GL_TEXTURE_2D, 19);
    drawCube0(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    }


    /// May
    {

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-15,18.15,0.1);
    //glRotatef(22, 0,0,1);
    glScalef(17,11.5,0.1);
    glBindTexture(GL_TEXTURE_2D, 21);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    }

    /// KHabib
    {

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(80,22.5,19);
    //glRotatef(22, 0,0,1);
    glScalef(.1,14,10);
    glBindTexture(GL_TEXTURE_2D, 20);
    drawCube0(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    }

    /// Ron
    {

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(40,18.15,0.1);
    //glRotatef(22, 0,0,1);
    glScalef(17,11.5,0.1);
    glBindTexture(GL_TEXTURE_2D, 14);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    }



    // lights =================================
    glPushMatrix();
    glTranslatef(-10,25,5.7);
    {


    ceiling_light_holder(0.3,.3,.4);
    ceiling_light(0.85,0.85,0.85);


    glPushMatrix();
    glTranslatef(16,8.75,4.25);
    //glRotatef(22, 0,0,1);
    glScalef(3,0.25,.25);
    drawCube(1,1,1);
    glPopMatrix();

    // ========================================




    ceiling_light(9,5.5,5);
    }
    //=======================================

    glPopMatrix();




    //light(-10,35,10,light1,GL_LIGHT4,true,false);
    //light(18,12,15,light2,GL_LIGHT5,false,true);




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
        //151 91 87 163.35 91 -63 0 1 0
       eyex=151; eyey=91;eyez=87;centerx=163.35;centery=91;centerz=-63;
       break;

   case '%':
        //-107 87 85 -142.537 87 -65
        eyex=-107; eyey=87; eyez=85; centerx=-142.537; centery=87; centerz=-65;
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
    case '6':
        shoulderLeft = !shoulderLeft;
        glutPostRedisplay();
        break;

    case '7':
        openDoor = !openDoor;
        glutPostRedisplay();
        break;

    case '8':
        BathopenDoor = !BathopenDoor;
        glutPostRedisplay();
        break;


    // bird's eye view
    case '&':
        bv=1;
        bird_view();
        break;
    case '$':
        normal_view();
        break;

    ///panning
    case 'g':
        lpan-=1;
        rpan-=1;
        glutPostRedisplay();
        break;

    case 'h':
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

    case 'w': // move eye point upwards along Y axis
        eyey+=1.0;
        centery+=1.0;
        break;
    case 's': // move eye point downwards along Y axis
        eyey-=1.0;
        centery-=1.0;
        break;
    case 'a': // move eye point left along X axis
        eyex-=1.0;
        centerx-=1.0;
        break;
    case 'd': // move eye point right along X axis
        eyex+=1.0;
        centerx+=1.0;
        break;

    case 'e': // move eye point left along X axis
        eyez-=1.0;
        centerz-=1.0;
        break;
    case 'x': // move eye point right along X axis
        eyez+=1.0;
        centerz+=1.0;
        break;




    case 'j': // move ref point upwards along Y axis
        centery+=1.0;
        break;
    case 'n': // move ref point downwards along Y axis
        centery-=1.0;
        break;
    case 'b': // move ref point left along X axis
        centerx-=1.0;
        break;
    case 'm': // move eye point right along X axis
        centerx+=1.0;
        break;
    case 'k':  //move ref point away from screen/ along z axis
        centerz+=1;
        break;

    case '*':
        changeX+=.2;
        if(changeX>1.5) changeX-=.2;
        break;

    case 'p':
        block = !block;
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


move eye point
w
s
a
d

move look at point
jnbm



*/

static void idle(void)
{
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

    if (shoulderLeft == true )
    {
        cout<<"Kappa "<<kappa<<endl;
        cout<<"KappaPress "<<kappapress<<endl;
//        kappa += 1;
//        if(kappa > 40.0){
//            kappa -= 360.0 * floor(kappa/360.0);
//        }


        if(squeeze==true && release==false)
        {
            //cout<<"squeeze ++"<<endl;
            kappa += .2;
            guy1Head += 0.002;
            guy1Body += 0.002;
            guy1Legs += 0.002;
            //cout<<"guyHead "<<guy1Head<<endl;
        }
        else if(squeeze==false && release==true){
            //cout<<"sadnAngle --"<<endl;
            kappa -= .2;
            guy1Head -= 0.002;
            guy1Body -= 0.002;
            guy1Legs -= 0.002;
            //cout<<"guyHead "<<guy1Head<<endl;

        }

        if(kappa > 40.0){
            //cout<<"Ecentric"<<endl;
            squeeze = false;
            release = true;
        }

        if(kappa <20.0){
            //cout<<"Concentric"<<endl;
            squeeze = true;
            release = false;
        }


        /// benchpress
        if(squeeze==true && release==false)
        {
            cout<<"Going down"<<endl;
            cout<<"ECCENTTRIC"<<endl;
            kappapress += .2;
            bnchpressLx += 0.002;
            bnchpressLy += 0.002;
            bnchpressRx -= 0.002;
            bnchpressRy += 0.002;

            OHPpressLx += 0.002;
            OHPpressLy += 0.002;
            OHPpressRx -= 0.002;
            OHPpressRy += 0.002;

            barbellup += 0.0022;
            leftW += 0.0022;
            rightW += 0.0022;

            OHPbarbellup += 0.0022;
            OHPleftW += 0.0022;
            OHPrightW += 0.0022;

            cout<<"guyHead "<<guy1Head<<endl;
        }
        else if(squeeze==false && release==true){
            cout<<"going UP"<<endl;
            cout<<"CONCENTRIC"<<endl;
            kappapress -= .2;
            bnchpressLx -= 0.002;
            bnchpressLy -= 0.002;
            bnchpressRx += 0.002;
            bnchpressRy -= 0.002;

            OHPpressLx -= 0.002;
            OHPpressLy -= 0.002;
            OHPpressRx += 0.002;
            OHPpressRy -= 0.002;

            barbellup -= 0.0022;
            leftW -= 0.0022;
            rightW -= 0.0022;

            OHPbarbellup -= 0.0022;
            OHPleftW -= 0.0022;
            OHPrightW -= 0.0022;

        }

        if(kappapress > 90.0){
            cout<<"Ecentric"<<endl;
            squeeze = false;
            release = true;
        }

        if(kappapress <10.0){
            cout<<"Concentric"<<endl;
            squeeze = true;
            release = false;
        }


    }

    if (openDoor == true && doorAngle<88) {
        doorAngle+= 0.5;
    }
    if (openDoor == false && doorAngle>0){
        doorAngle-= 0.5;
    }



    if (BathopenDoor == true && BathdoorAngle<88) {
        BathdoorAngle+= 0.5;
    }
    if (BathopenDoor == false && BathdoorAngle>0){
        BathdoorAngle-= 0.5;
    }


    if ( sandbagMov == true) {

        //cout<<" Swing Behind " <<swingBehind<<endl;
        //cout<<"SandlAngle "<<sandAngle<<endl;

        if(swingBehind==true)
        {
            //cout<<"sandAngle ++"<<endl;
            //cout<<"sandAngle ++"<<endl;
            sandAngle += .02;
        } else{
            //cout<<"sadnAngle --"<<endl;
            sandAngle -= .02;

        }

        if(sandAngle > 95.0){
            swingBehind=false;
            //cout<<"ANgle Behind FALSE"<<endl;
        }

        if(sandAngle <85.0){
                //cout<<"Angle gehind True"<<endl;
            swingBehind=true;
        }

    }

    glutPostRedisplay();

}


int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(100,100);
    glutInitWindowSize(windowHeight, windowWidth);
    glutCreateWindow("GYM room");
    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_NORMALIZE );
    glEnable( GL_LIGHTING );



    LoadTexture1("Textures\\test.bmp"); //1
    LoadTexture1("Textures\\floor.bmp"); //2
    LoadTexture1("Textures\\wood.bmp"); //3
    LoadTexture1("Textures\\tiles.bmp"); //4
    LoadTexture1("Textures\\table.bmp"); //5
    LoadTexture1("Textures\\ground.bmp"); //6
    LoadTexture1("Textures\\darkwood.bmp"); //7
    LoadTexture1("Textures\\box.bmp"); //8
    LoadTexture1("Textures\\NIKE.bmp"); //9
    LoadTexture1("Textures\\funkyred.bmp"); //10
    LoadTexture1("Textures\\ali.bmp"); //11
    LoadTexture1("Textures\\adidas.bmp"); //12
    LoadTexture1("Textures\\redbull.bmp"); //13
    LoadTexture1("Textures\\ron.bmp"); //14
    LoadTexture1("Textures\\black.bmp"); //15
    LoadTexture1("Textures\\barbwire.bmp"); //16
    LoadTexture1("Textures\\barbwire2.bmp"); //17
    LoadTexture1("Textures\\road1.bmp"); //18
    LoadTexture1("Textures\\arny.bmp"); //19
    LoadTexture1("Textures\\khabib.bmp"); //20
    LoadTexture1("Textures\\may.bmp"); //21
    LoadTexture1("Textures\\raku.bmp"); //22
    LoadTexture1("Textures\\toilet.bmp"); //23
    LoadTexture1("Textures\\toiletdoor.bmp"); //24
    LoadTexture1("Textures\\blackleather.bmp"); //25
    LoadTexture1("Textures\\paleskin.bmp"); //26
    LoadTexture1("Textures\\head.bmp"); //27
    LoadTexture1("Textures\\barbellW.bmp"); //28
    LoadTexture1("Textures\\dumbellBlue.bmp"); //29
    LoadTexture1("Textures\\tiles5.bmp"); //30
    LoadTexture1("Textures\\bricks.bmp"); //31
    LoadTexture1("Textures\\rocky.bmp"); //32
    LoadTexture1("Textures\\grass.bmp"); //33






//    glutKeyboardFunc(myKeyboardFunc);
//     glutReshapeFunc(resize);
//    glutDisplayFunc(display);
//    glutIdleFunc(animate);
//    glutMainLoop();

    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    //light0();
    //light1();
    glEnable( GL_DEPTH_TEST );
    glutKeyboardFunc(myKeyboardFunc);
    glutReshapeFunc(resize);
    glutDisplayFunc(display);

    glutIdleFunc(idle);
    glutIdleFunc(animate);
    glutMainLoop();

    return EXIT_SUCCESS;
}
