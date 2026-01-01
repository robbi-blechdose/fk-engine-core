#ifndef FKEC_CAMERA_H
#define FKEC_CAMERA_H

#include "util.h"
#include "includes/3dMath.h"
#include "quaternion.h"

void setCameraPos(vec3 pos);
void drawCameraPos();

//----- Camera rotation using 3 axes -----
void drawCamera3AImm(vec3* pos, vec3* rot);
void drawCamera3A();
void setCameraRot3A(vec3 rot);

//----- Camera rotation using a matrix -----
void drawCameraMatRot();
void drawCameraMat();
void setCameraRotMat(quat rot);

#endif