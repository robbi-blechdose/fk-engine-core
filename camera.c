#include "camera.h"

#include "GL/gl.h"

vec3 cameraPos;

void setCameraPos(vec3 pos)
{
    cameraPos = pos;
}

void drawCameraPos()
{
    glTranslatef(-cameraPos.x, -cameraPos.y, -cameraPos.z);
}

//----- Camera rotation using 3 axes -----
//x = pitch, y = yaw, z = roll
vec3 cameraRot;

void drawCamera3AImm(vec3* pos, vec3* rot)
{
	glLoadIdentity();
    glRotatef(RAD_TO_DEG(rot->x), 1, 0, 0);
    glRotatef(RAD_TO_DEG(rot->y), 0, 1, 0);
    glRotatef(RAD_TO_DEG(rot->z), 0, 0, 1);
    glTranslatef(-pos->x, -pos->y, -pos->z);
}

void drawCamera3A()
{
    drawCamera3AImm(&cameraPos, &cameraRot);
}

void setCameraRot3A(vec3 rot)
{
    cameraRot = rot;
}

//----- Camera rotation using a matrix -----
float cameraRotMat[16];

void drawCameraMatRot()
{
	glLoadIdentity();
    glLoadMatrixf(cameraRotMat);
}

void drawCameraMat()
{
    drawCameraMatRot();
    drawCameraPos();
}

void setCameraRotMat(quat rot)
{
    quatToMatrix(cameraRotMat, rot);
}