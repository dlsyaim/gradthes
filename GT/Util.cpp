#include "stdafx.h"
#include <windows.h>
#include <GL/glut.h>
#include <vector>
#include <sstream>
#include "Util.h"

bool descend(Layer* la1, Layer* la2)
{
	if (la1->getW() > la2->getW()) {
		return true;
	}
	return false;
}

bool ascend(Layer* la1, Layer* la2)
{
	if (la1->getW() < la2->getW()) {
		return true;
	}
	return false;
}

double HexToDem(std::string hexString, BOOL isSigned)
{
	// First swap 0 and 2, 1 and 3
	char tmp = hexString[0];
	hexString[0] = hexString[2];
	hexString[2] = tmp;
	tmp = hexString[1];
	hexString[1] = hexString[3];
	hexString[3] = tmp;
	
	int HexNum = 0, DemNum = 0;
	
	std::string prefix = "0x";
	prefix.append(hexString);

	sscanf(prefix.c_str(), "%x", &HexNum);
	// If an signed 16-bit number's value is larger than 32768, then it must be a negative.
	if (isSigned) {
		if (HexNum >= 32768) {
			HexNum -= 65536;
		} 	
	}
	return HexNum / 100.0;
}

double FormatDouble(double angle)
{

	int nAngle = (int)angle;

	return nAngle % 360 + (angle - nAngle);
}

//
void glPrint(GLuint base, const char *fmt, ...)
{
	// The formatted string stored.
	char		text[256];											
	// Pointer to the parameter list.
	va_list		ap;													

	if (fmt == NULL)												
		return;														
	// Iterate the string to find a variable.
	va_start(ap, fmt);											
		// Converted the variable to the showing digits
	    vsprintf(text, fmt, ap);									
	// The result is saved in the text.
	va_end(ap);														

	// Show list state pushing in.
	glPushAttrib(GL_LIST_BIT);										
	// The offset
	glListBase(base);											
	// Render string
	glCallLists((int)strlen(text), GL_UNSIGNED_BYTE, text);			
	// Show list state poping up
	glPopAttrib();													
}

// Get the 9 flight state variable value
BOOL getFlyStatistics(CString aLine, double *stat, int size)
{
	if (!stat || size <= 0 || aLine.IsEmpty())  {
		return FALSE;
	}

	int i = 0;
	// Split the string by ' ' character
	std::istringstream ss(aLine.GetBuffer(0));
	std::string sub;
	double value;
	do {
		ss >> sub;
		switch(i) {
			case 0:
				value = HexToDem(sub);
				break;
			default:
				value = HexToDem(sub, TRUE);
				break;
		}		
		if (i >= 6) {
			value /= 100.0;
		}
		stat[i++] = value;
	} while (ss && i < size);
	
	return TRUE;	
}