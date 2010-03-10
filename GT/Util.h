#ifndef _UTIL_H
#define _UTIL_H
#include "Layer.h"

bool descend(Layer*, Layer*);
bool ascend(Layer*, Layer*);

// Convert hex to dem
double HexToDem(std::string u_hexString, BOOL isSigned = FALSE);

// Format a double number into the rangle of -360 ~ 360
double FormatDouble(double angle);

// 
void glPrint(GLuint base, const char *fmt, ...);

// Get the 9 flight state variable value
BOOL getFlyStatistics(CString aLine, double *stat, int size);


#endif