#include "camera.h"

#include "GL/gl.h"

vec3 cameraPos;
//x = pitch, y = yaw, z = roll
vec3 cameraRot;
//Camera rotation as matrix instead of 3 axes
float cameraRotMat[16];

void drawCamera(vec3* pos, vec3* rot)
{
	glLoadIdentity();
    glRotatef(RAD_TO_DEG(rot->x), 1, 0, 0);
    glRotatef(RAD_TO_DEG(rot->y), 0, 1, 0);
    glRotatef(RAD_TO_DEG(rot->z), 0, 0, 1);
    glTranslatef(-pos->x, -pos->y, -pos->z);
}

void drawCameraPrep()
{
    drawCamera(&cameraPos, &cameraRot);
}

void drawCameraPrepMat()
{
	glLoadIdentity();
    glLoadMatrixf(cameraRotMat);
    glTranslatef(-cameraPos.x, -cameraPos.y, -cameraPos.z);
}

void setCameraPos(vec3 pos)
{
    cameraPos = pos;
}

void setCameraRot(vec3 rot)
{
    cameraRot = rot;
}

void setCameraRotMat(quat rot)
{
    quatToMatrix(cameraRotMat, rot);
}