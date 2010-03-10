#pragma once
#include "Texture.h"
#include "Transformation.h"

class Layer
{	
public:

	enum LAYER_TYPE {
		SWITCH,
		TEXT,
		SPECIAL,
		BUILT_IN
	};

	Layer(void);
	Layer(int w, int h);
	~Layer(void);
	inline void setName(std::string name) {this->name = name;}
	inline std::string getName(void){return name;}
	inline void setW(int w){this->w = w;}
	inline int getW(void){return w;}
	inline void setH(int h){this->h = h;}
	inline int getH(void){return h;}
	inline void setTex(Texture* tex){this->tex = tex;}
	inline Texture* getTex(void){return tex;}
	inline void setTl(transformationList *tl) {this->tl = tl;}
	inline transformationList* getTl(void){return tl;}
	inline void setType(LAYER_TYPE type) {this->type = type;}
	inline LAYER_TYPE getType(void){return type;}
	inline void setSwitchLayers(std::vector<Layer*>* switchLayers) {this->switchLayers = switchLayers;}
	inline std::vector<Layer*>* getSwitchLayers(void){return switchLayers;}

private:
	// name
	std::string name;
	// size
	int w, h;
	// Texture
	Texture *tex;
	// Transformation list
	transformationList * tl;
	// Layer type
	LAYER_TYPE type;
	// switch Layer list
	std::vector<Layer*>* switchLayers;
};

typedef std::vector<Layer*> layerList;
