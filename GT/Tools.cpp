#include "Stdafx.h"
#include "Tools.h"


CTools::CTools()
{

}

CTools::~CTools()
{

}



double CTools::htond(double d)

{

  unsigned char *p, p0, p1, p2, p3;

  if(htons(1) ==1) return d;

  p =(unsigned char *)&d;

  p0 =p[0];

  p1 =p[1];

  p2 =p[2];

  p3 =p[3];

  p[0] =p[7];

  p[7] =p0;

  p[1] =p[6];

  p[6] =p1;

  p[2] =p[5];

  p[5] =p2;

  p[3] =p[4];

  p[4] =p3;

  return d;

}

double CTools::ntohd(double d)

{

  unsigned char *p, p0, p1, p2, p3;

  if(ntohs(1) ==1) return d;

  p =(unsigned char *)&d;

  p0 =p[0];

  p1 =p[1];

  p2 =p[2];

  p3 =p[3];

  p[0] =p[7];

  p[7] =p0;

  p[1] =p[6];

  p[6] =p1;

  p[2] =p[5];

  p[5] =p2;

  p[3] =p[4];

  p[4] =p3;

  return d;

}



float CTools::htonf(float f)

{

  unsigned char *p, p0, p1;

  if(htons(1) ==1) return f;

  p =(unsigned char *)&f;

  p0 =p[0];

  p1 =p[1];

  p[0] =p[3];

  p[3] =p0;

  p[1] =p[2];

  p[2] =p1;

  return f;

}

float CTools::ntohf(float f)

{

  unsigned char *p, p0, p1;

  if(ntohs(1) ==1) return f;

  p =(unsigned char *)&f;

  p0 =p[0];

  p1 =p[1];

  p[0] =p[3];

  p[3] =p0;

  p[1] =p[2];

  p[2] =p1;

  return f;

}

