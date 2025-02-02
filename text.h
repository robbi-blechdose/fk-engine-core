#ifndef FKEC_TEXT_H
#define FKEC_TEXT_H

#include <GL/gl.h>

/**
 * Calculates the X position for a string of the given length
 * Note: X * 8 / 2 = X * 4
 **/
#define CENTER_TEXT(X) (WINX / 2 - (X) * 4)

//Fixes warnings for string literals
#define glDrawText(text, x, y, pixel) glDrawText((const GLubyte*) (text), (x), (y), (pixel))

#define glDrawTextCentered(text, y, pixel) glDrawText((text), CENTER_TEXT(strlen(text)), (y), (pixel))

#endif