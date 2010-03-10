#include "stdafx.h"
#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include "Texture.h"


Texture::Texture(void)
{
}

Texture::~Texture(void)
{
}


/* Load the picture and convert it into a Texture  */
BOOL Texture::loadTexture(GLuint &texId)
{
	// DC is used to save bitmap
	HDC			hdcTemp;												
	// Save the temporary bitmap
	HBITMAP		hbmpTemp;			
	// Define IPicture Interface
	IPicture	*pPicture;												
	// The complete path of the picture
	OLECHAR		wszPath[MAX_PATH + 1];									
	// The complete path of the picture
	char		szPath[MAX_PATH + 1];										
	long		lWidth;													
	long		lHeight;												
	long		lWidthPixels;											
	long		lHeightPixels;			

	GLint		glMaxTexDim ;											

	// Get the current directory path
	GetCurrentDirectory(MAX_PATH, (LPTSTR)szPath);			
	// Add '\\'
	strcat(szPath, "\\..");											
	// Add the relative path 
	strcat(szPath, path.append("bmp").c_str());			
	// Convert to the wide char
	MultiByteToWideChar(CP_ACP, 0, szPath, -1, wszPath, MAX_PATH);		

	HRESULT hr = OleLoadPicturePath(wszPath, 0, 0, 0, IID_IPicture, (void**)&pPicture);
	// If failed
	if(FAILED(hr))
	{
		MessageBox (HWND_DESKTOP, _T("Ole loading function failed"), _T("Error"), MB_OK | MB_ICONEXCLAMATION);
		return FALSE;													
	}

    // Creates a memory device context (DC) compatible with the specified device
	hdcTemp = CreateCompatibleDC(GetDC(0));		
	// If failed
	if(!hdcTemp)														
	{
		pPicture->Release();										
		MessageBox (HWND_DESKTOP, _T("Memory DC creating failed"), _T("Error"), MB_OK | MB_ICONEXCLAMATION);
		return FALSE;													
	}

	// Get the maximal supported Texture size
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &glMaxTexDim);					
	
	pPicture->get_Width(&lWidth);										
	lWidthPixels = MulDiv(lWidth, GetDeviceCaps(hdcTemp, LOGPIXELSX), 2540);
	pPicture->get_Height(&lHeight);										
	lHeightPixels = MulDiv(lHeight, GetDeviceCaps(hdcTemp, LOGPIXELSY), 2540);

	// Adjust the picture to a better condition
	if (lWidthPixels <= glMaxTexDim) {									
		lWidthPixels = 1 << (int) floor(log((double)lWidthPixels) / log(2.0f) + 0.5f ); 
	} else {																
		lWidthPixels = glMaxTexDim;
	}
 
	if (lHeightPixels <= glMaxTexDim) {								
		lHeightPixels = 1 << (int)floor(log((double)lHeightPixels) / log(2.0f) + 0.5f);
	} else	 {														
		lHeightPixels = glMaxTexDim;
	}

	// Build a temporary bitmap
	BITMAPINFO	bi = {0};											
	// Pointer to the bitmap
	DWORD *pBits = 0;												

	// Some initialization
	bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);				
	bi.bmiHeader.biBitCount	 = 32;									
	bi.bmiHeader.biWidth	 = lWidthPixels;							
	bi.bmiHeader.biHeight = lHeightPixels;						
	// RGB 
	bi.bmiHeader.biCompression	= BI_RGB;
	// One bit plane
	bi.bmiHeader.biPlanes = 1;

	// After build a bitmap, we can specify the color and depth, and access the value of each bit
	hbmpTemp = CreateDIBSection(hdcTemp, &bi, DIB_RGB_COLORS, (void**)&pBits, 0, 0);
	
	// If failed
	if(!hbmpTemp)													
	{
		DeleteDC(hdcTemp);												
		pPicture->Release();	
		MessageBox (HWND_DESKTOP, _T("Create DIB failed"), _T("Error"), MB_OK | MB_ICONEXCLAMATION);
		return FALSE;												
	}

	// Selects hbmpTemp into the specified device context (DC) hdcTemp. 
	SelectObject(hdcTemp, hbmpTemp);

	// Draw IPicture on the bitmap
	pPicture->Render(hdcTemp, 0, 0, lWidthPixels, lHeightPixels, 0, lHeight, lWidth, -lHeight, 0);
	
	// Transform the BGR to RGB and set ALPHA to 255
	for(long i = 0; i < lWidthPixels * lHeightPixels; i++)				// 循环遍历所有的像素
	{
		// Get the current pixel
		BYTE* pPixel	= (BYTE*)(&pBits[i]);							
		// Because the first is blue
		BYTE  temp		= pPixel[0];									
		pPixel[0]		= pPixel[2];									
		pPixel[2]		= temp;										
		pPixel[3]		= 255;										
	}

	// Start to create Texture
	glGenTextures(1, &texId);											

	glBindTexture(GL_TEXTURE_2D, texId);				

	setTexId(texId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	// Generate Texture
	glTexImage2D(GL_TEXTURE_2D, 0, 3, lWidthPixels, lHeightPixels, 0, GL_RGBA, GL_UNSIGNED_BYTE, pBits);

	DeleteObject(hbmpTemp);												
	DeleteDC(hdcTemp);													

	pPicture->Release();												

	return TRUE;
}


// Load a tga file into the memory.
BOOL Texture::loadTexture(void)					
{    
	TextureTGA *textureTga = new TextureTGA();
	// A uncompressed TGA Header
	GLubyte		TGAheader[12] = {0,0,2,0,0,0,0,0,0,0,0,0};				
	// TGA Header to be used to compare
	GLubyte		TGAcompare[12];											
	// The first 6 usefull bytes in Header
	GLubyte		header[6];												
	// bytes per pixel
	GLuint		bytesPerPixel;											

	// Used to store the size of the image generated randomly
	GLuint imageSize;																								
	// GL mode
	GLuint type = GL_RGBA;											

	// The complete path of the picture
	char		szPath[MAX_PATH + 1];	
	// Get the current directory path
	GetCurrentDirectory(MAX_PATH, (LPTSTR)szPath);			
	// Add '\\'
	strcat(szPath, "\\..");											
	// Add the relative path 
	strcat(szPath, path.append("tga").c_str());	
	// Open tga file
	FILE *file = fopen(szPath, "rb");									

	if (file == NULL)													
	{
		MessageBox (HWND_DESKTOP, _T("fopen failed!\n(TextureLoad Failed!)"), _T("Error"), MB_OK | MB_ICONEXCLAMATION);
		return FALSE;													
	}

	// Is there 12 bytes to read and header is the one we want and read the following 6 bytes
	// Just check if the third byte is 2
	if (fread(TGAcompare, 1, sizeof(TGAcompare), file) != sizeof(TGAcompare)
		//|| memcmp(TGAheader, TGAcompare, sizeof(TGAheader)) != 0			
		|| TGAcompare[2] != 2
		|| fread(header, 1, sizeof(header), file) != sizeof(header))		
	{
		if (ferror(file)) {
			MessageBox (HWND_DESKTOP, _T("ferror file!\n(TextureLoad Failed!)"), _T("Error"), MB_OK | MB_ICONEXCLAMATION);
		}
		fclose(file);													
		MessageBox (HWND_DESKTOP, _T("fread failed!\n(TextureLoad Failed!)"), _T("Error"), MB_OK | MB_ICONEXCLAMATION);
		return FALSE;													
	}

	// Because the tga format specification says that the integer is stored with
	// the low order byte followed by the high order byte, ie. little endian.
	// Retrieves the image's width 
	textureTga->width  = header[1] * 256 + header[0];						
	// Retrieves the image's height
	textureTga->height = header[3] * 256 + header[2];						

 	if (textureTga->width	<= 0											
		|| textureTga->height	<= 0										
		|| (header[4] != 24 && header[4] != 32))							
	{
		fclose(file);													
		MessageBox (HWND_DESKTOP, _T("header[6] is not correct!\n(TextureLoad Failed!)"), _T("Error"), MB_OK | MB_ICONEXCLAMATION);
		return FALSE;													
	}

	textureTga->bpp	= header[4];										

	bytesPerPixel	= textureTga->bpp / 8;									

	imageSize	= textureTga->width * textureTga->height * bytesPerPixel;		
	// Allocate memory
	textureTga->imageData = (GLubyte *)malloc(imageSize);			
	GLubyte* _imageData = (GLubyte *)malloc(textureTga->width * textureTga->height * 4);

	// Check the value of the first byte of the header.
	if (TGAcompare[0] != 0) {
		GLubyte* identificationField = (GLubyte*)malloc(TGAcompare[0]);
		fread(identificationField, 1, TGAcompare[0], file);
		if (identificationField) {
			free(identificationField);
		}
	}
	
	if (textureTga->imageData == NULL 										
		|| fread(textureTga->imageData, 1, imageSize, file) != imageSize)
	{
		if (textureTga->imageData != NULL)									
		{
			free(textureTga->imageData);									
		}
		fclose(file);													
		MessageBox (HWND_DESKTOP, _T("fread image data failed!\n(TextureLoad Failed!)"), _T("Error"), MB_OK | MB_ICONEXCLAMATION);
		return FALSE;													
	}

	// Origin in upper left-hand corner
	if ((header[5] & 0x20) != 0 ) {
		GLubyte* tmp, *tmp1;
		for (GLuint i = 0; i < int(textureTga->height); i++) {
			for (GLuint j = 0; j < int(textureTga->width); j++) {
				tmp = &((GLubyte*)(_imageData + (textureTga->height - 1 - i) * textureTga->height * 4))[j * 4];
				tmp1= &((GLubyte*)(textureTga->imageData + i * textureTga->height * bytesPerPixel))[j * bytesPerPixel];
				tmp[0] = tmp1[2];
				tmp[1] = tmp1[1];
				tmp[2] = tmp1[0];
				if (tmp[0] == 0 && tmp[1] == 0 && tmp[2] == 0) {
					tmp[3] = 0;
				} else {
					tmp[3] = 255;
				}
			}
		}
	} else {	// Origin in lower left-hand corner.
		GLubyte* tmp, *tmp1;
		for (GLuint i = 0; i < int(textureTga->height); i++) {
			for (GLuint j = 0; j < int(textureTga->width); j++) {
				tmp = &((GLubyte*)(_imageData + i * textureTga->height * 4))[j * 4];
				tmp1= &((GLubyte*)(textureTga->imageData + i * textureTga->height * bytesPerPixel))[j * bytesPerPixel];
				tmp[0] = tmp1[2];
				tmp[1] = tmp1[1];
				tmp[2] = tmp1[0];
				if (tmp[0] == 0 && tmp[1] == 0 && tmp[2] == 0) {
					tmp[3] = 0;
				} else {
					tmp[3] = 255;
				}
			}
		}
	}	

	fclose (file);
	
	glGenTextures(1, &textureTga->texID);									

	glBindTexture(GL_TEXTURE_2D, textureTga->texID);		
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	
	
	setTexId(textureTga->texID);
	//if (Texture->bpp == 24)												
	//{
	//	type = GL_RGB;													
	//}

	glTexImage2D(GL_TEXTURE_2D, 0, type, textureTga->width, textureTga->height, 0, type, GL_UNSIGNED_BYTE, _imageData);

	// Free memory
	if (textureTga) {
		if (textureTga->getImageData()) {
			free(textureTga->getImageData());
		}
		delete textureTga;
	}

	if (_imageData) {
		free(_imageData);
	}

	return TRUE;														
}

BOOL Texture::loadTexture(std::string path) 
{
	this->path = path.substr(2, path.size() - 3 - 2);
	return loadTexture();
}