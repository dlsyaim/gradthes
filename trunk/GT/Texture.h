#pragma once
#include "TextureTGA.h"

class Texture
{
public:
	Texture(void);
	Texture(std::string _path):path(_path), x1(0.0f), x2(1.0f), y1(0.0f), y2(1.0f){}
	~Texture(void);
	inline void setPath(std::string path){this->path = path.substr(8, path.size() - 3 - 8);}
	inline std::string getPath(void){return path;}
	inline void setX1(float x1) {this->x1 = x1;}
	inline float getX1(void){return x1;}
	inline void setX2(float x2) {this->x2 = x2;}
	inline float getX2(void){return x2;}
	inline void setY1(float y1) {this->y1 = y1;}
	inline float getY1(void){return y1;}
	inline void setY2(float y2) {this->y2 = y2;}
	inline float getY2(void){return y2;}
	inline void setTexId(GLuint texId){this->texId = texId;}
	inline GLuint getTexId(void){return texId;}
	
	// Load textures
	BOOL loadTexture(GLuint& texId);
	BOOL loadTexture(void);
	BOOL loadTexture(std::string path);
	BOOL loadTexture(CString fileName);

private:
	// path
	std::string path;
	// Texture coordinates
	float x1, y1, x2, y2;
	// Texture id
	GLuint texId;

};
