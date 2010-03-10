#pragma once
class Texture;

class TextureTGA
{
public:
	TextureTGA(void);
	~TextureTGA(void);

	inline void setImageData(GLubyte* imageData){this->imageData = imageData;}
	inline GLubyte* getImageData(void){return imageData;}
	inline void setBpp(GLuint bpp){this->bpp = bpp;}
	inline GLuint getBpp(void){return bpp;}
	inline void setWidth(GLuint width){this->width = width;}
	inline GLuint getWidth(void){return width;}
	inline void setHeight(GLuint height){this->height = height;}
	inline GLuint getHeight(void){return height;}
	inline void setTexID(GLuint texID){this->texID = texID;}
	inline GLuint getTexID(void){return texID;}

private:
	GLubyte* imageData;
	GLuint bpp;
	GLuint width;
	GLuint height;
	GLuint texID;

	friend class Texture;
};
