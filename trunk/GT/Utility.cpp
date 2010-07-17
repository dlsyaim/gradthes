#include "StdAfx.h"
#include "Utility.h"

float calculateDifferences(const RECT &rect)
{
	// Because this LPRECT represents the client area's size, so upper-left cornor is (0, 0)
	static LONG originRight = rect.right;
	static LONG originBottom = rect.bottom;

	// Calculate the differences
	float diff = (float)max(rect.right - originRight, rect.bottom - originBottom);
	if (diff >= 0.0f) {
		diff = (float)min(rect.right - originRight, rect.bottom - originBottom);
	}

	originRight = rect.right;
	originBottom = rect.bottom;
	
	return diff;
}