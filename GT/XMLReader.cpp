#include "stdafx.h"
#include <stdio.h>	
#include <algorithm>
#include <atlbase.h>
#include <msxml2.h>
#include <iostream>
#include <GL\gl.h>
#include <vector>
#include <string>
#include <comutil.h>
#include "XMLReader.h"
#include "Layer.h"
#include "Transformation.h"
#include "TextureTGA.h"
#include "RPM.h"
#include "FuelKnob.h"
#include "MagneticCompass.h"
#include "VerticalVelocityIndicator.h"
#include "TurnCoordinator.h"
#include "AttitudeGyro.h"
#include "DirectionalGyro.h"
#include "BrakeIndicator.h"
#include "FlapsIndicator.h"
#include "Altimeter.h"
#include "ControlPositionIndicator.h"
#include "AirspeedIndicator.h"
#include "Util.h"

XMLReader::XMLReader(void)
{
	
}

XMLReader::~XMLReader(void)
{
	CoUninitialize();
}

BOOL XMLReader::initializeParser(void)
{	
	try {
		// Start COM. Must initialize the COM library before they can call COM library functions 
		HRESULT hr = CoInitialize(NULL);
		if (FAILED(hr)) {
			throw "Initialize failed";
		}
		// Create an instance of the parser
		hr = spXMLDOM.CoCreateInstance(__uuidof(DOMDocument));

		if (FAILED(hr)) {
			throw "Unable to create XML parser object";
		}
		if (spXMLDOM.p == NULL) {
			throw "Unable to create XML parser object";
		}
		return TRUE;
	} catch (char *lpstrError) {
		std::cout << lpstrError << std::endl;
		return FALSE;
	}
}

// Load the Panel into memory.
void XMLReader::loadPanel(char *szPathName, Panel* pl)
{
	try {
		// Load the XML document file...
		VARIANT_BOOL bSuccess = false;
		HRESULT hr = spXMLDOM->load(CComVariant(szPathName), &bSuccess);
		if (FAILED(hr)) {
			throw "Unable to load XML document into the parser";
		}
		if (!bSuccess) {
			throw "Unable to load XML document into the parser";
		}

		// Construct search string
		CComBSTR bstrSS(L"PropertyList");
		CComPtr<IXMLDOMNode> spXMLNode;
		CComPtr<IXMLDOMNodeList> spXMLNodeList;
		
		hr = spXMLDOM->selectSingleNode(bstrSS, &spXMLNode);
		if (FAILED(hr)) {
			throw "Unable to locate PropertyList node";
		}
		if (spXMLNode.p == NULL) {
			throw "Unable to locate PropertyList node";
		}

		hr = spXMLNode->get_childNodes(&spXMLNodeList);
		if (FAILED(hr)) {
			throw "Unable to get the child nodes";
		} 
		if (spXMLNodeList.p == NULL) {
			throw "Unable to get the child nodes";
		}

		long len;
		hr = spXMLNodeList->get_length(&len);
		if (FAILED(hr)) {
			throw "Unable to get the number of children";
		} 

		// The name of the element.
		CComBSTR nodeName;
		// The value of the element.
		CComVariant varValue(VT_EMPTY);

		// If assigned through & operator, then the smart pointer must be NULL.
		spXMLNode = NULL;
		while (!FAILED(spXMLNodeList->nextNode(&spXMLNode))) {
			if (spXMLNode.p == NULL) {
				break;
			}

			hr = spXMLNode->get_nodeName(&nodeName);
			if (FAILED(hr)) {
				throw "Unable to get the element name";
			}
			hr = spXMLNode->get_nodeTypedValue(&varValue);
			if (FAILED(hr)) {
				throw "Unable to get eh element value";
			}

			// W2T is the original text conversion macros.
			USES_CONVERSION;
			LPTSTR lpstrVal = W2T(varValue.bstrVal);
			if (nodeName == L"name") {
				pl->setName(lpstrVal);
			} else if (nodeName == L"background") {
				pl->setBg(lpstrVal);
			} else if (nodeName == L"w") {
				pl->setW(atoi((const char*)lpstrVal));
			} else if (nodeName == L"h") {
				pl->setH(atoi((const char*)lpstrVal));
			} else if (nodeName == L"y-offset") {
				pl->setYoffset(atoi((const char*)lpstrVal));
			} else if (nodeName == L"view-height") {
				pl->setViewHeight(atoi((const char*)lpstrVal));
			}
			// This line is very important. spXMLNode must be set to NULL.
			spXMLNode = NULL;
		}

		// Load instruments
		loadInstruments("PropertyList/instruments/instrument", pl->getInLi());		
	} catch (char *lpstrError){
		std::cout << lpstrError << std::endl;
	} catch (...) {
		std::cout << "Unknown error in loading Panel" << std::endl;
	}
}

// Load instruments belonging to one Panel.
void XMLReader::loadInstruments(char *szQueryString, instrumentList* inLi)
{
	try {
		// Construct search string
		CComBSTR bstrSS (szQueryString);
		
		// Declare some variables.
		CComPtr<IXMLDOMNode> spXMLNode;
		CComPtr<IXMLDOMNodeList> spXMLNodeList;

		HRESULT hr = spXMLDOM->selectNodes(bstrSS, &spXMLNodeList);
		if (FAILED(hr)) {
			throw "Unable to locate PropertyList/instruments/instrument nodes";
		}
		if (spXMLNodeList.p == NULL) {
			throw "Unable to locate PropertyList/instruments/instrument nodes";
		}

		long numOfInst;
		hr = spXMLNodeList->get_length(&numOfInst);
		if (FAILED(hr)) {
			throw "Unable to get the length of the node list";
		}		
		// The name of the attributes.
		CComBSTR attrName(L"include");
		CComBSTR nodeName;
		CComVariant varValue(VT_EMPTY);
		// Iterate the node list
		CComPtr<IXMLDOMNode> spXMLChildNode;
		CComPtr<IXMLDOMNodeList> spXMLChildNodeList;
		CComPtr<IXMLDOMElement> spXMLElement;
		spXMLNode = NULL;
		while (!FAILED(spXMLNodeList->nextNode(&spXMLNode))) {
			if (spXMLNode.p == NULL) {
				break;
			}			
			Instrument* intr;

			spXMLElement = spXMLNode;
			if (spXMLElement.p == NULL) {
				throw "Unable to convert node to element";
			}
			hr = spXMLElement->getAttribute(attrName, &varValue);
			if (FAILED(hr)) {
				throw "Unable to get the value of the attribute";
			}
			USES_CONVERSION;
			LPTSTR attrLVal = W2T(varValue.bstrVal);

			hr = spXMLNode->get_childNodes(&spXMLChildNodeList);
			if (FAILED(hr)) {
				throw "Unable to get the child node list";
			}

			spXMLChildNode = NULL;
			while (!FAILED(spXMLChildNodeList->nextNode(&spXMLChildNode))) {
				if (spXMLChildNode.p == NULL) {
					break;
				}
				hr = spXMLChildNode->get_nodeName(&nodeName);
				hr = spXMLChildNode->get_nodeTypedValue(&varValue);
				USES_CONVERSION;
				LPTSTR lpstrVal = W2T(varValue.bstrVal);
				if (nodeName == L"name") {
					if (!strcmp((const char*)lpstrVal, "RPM Gauge")) {
						intr = new RPM();
					} else if (!strcmp((const char*)lpstrVal, "Fuel Mixture Knob")) {
						intr = new FuelKnob();
					} else if (!strcmp((const char*)lpstrVal, "Flaps Control")) {
						intr = new FlapsIndicator();
					} else if (!strcmp((const char*)lpstrVal, "Brake Indicator Light")) {
						intr = new BrakeIndicator();
					} else if (!strcmp((const char*)lpstrVal, "Control Position Indicators")) {
						intr = new ControlPositionIndicator();
					} else if (!strcmp((const char*)lpstrVal, "Airspeed Indicator")) {
						intr = new AirspeedIndicator();
					} else if (!strcmp((const char*)lpstrVal, "Attitude Gyro")) {
						intr = new AttitudeGyro();
					} else if (!strcmp((const char*)lpstrVal, "Altimeter")) {
						intr = new Altimeter();
					} else if (!strcmp((const char*)lpstrVal, "Turn Coordinator")) {
						intr = new TurnCoordinator();
					} else if (!strcmp((const char*)lpstrVal, "Directional Gyro")) {
						intr = new DirectionalGyro();
					} else if (!strcmp((const char*)lpstrVal, "Vertical Velocity Indicator")) {
						intr = new VerticalVelocityIndicator();
					} else if (!strcmp((const char*)lpstrVal, "Magnetic Compass")) {
						intr = new MagneticCompass();
					}
				} else if (nodeName == L"x") {
					intr->setX(atoi((const char*)lpstrVal));
				} else if (nodeName == L"y") {
					intr->setY(atoi((const char*)lpstrVal));
				} else if (nodeName == L"w") {
					intr->setWidth(atoi((const char*)lpstrVal));
				} else if (nodeName == L"h") {
					intr->setHeight(atoi((const char*)lpstrVal));
				}		
				
				spXMLChildNode = NULL;
			}
			intr->setInPath(attrLVal);
			inLi->push_back(intr);
			spXMLChildNodeList = NULL;
			spXMLNode = NULL; 
		}	

		// Load each Instrument
		instrumentList::iterator inLiIt;
		for (inLiIt = inLi->begin(); inLiIt != inLi->end(); inLiIt++) {
			loadInstrument((*inLiIt)->getInPath().c_str(), (*inLiIt));
		}

	} catch (char *lpstrErr) {
		// Some error...
		std::cout << lpstrErr << std::endl;
	} catch (...) {
		std::cout << "Unknown error" << std::endl;
	}	
}

// Load each instruments.
void XMLReader::loadInstrument(const char *szPathName, Instrument *instr)
{
	try {
		// Load the XML document file...
		VARIANT_BOOL bSuccess = false;
		HRESULT hr = spXMLDOM->load(CComVariant(szPathName), &bSuccess);
		if (FAILED(hr)) {
			throw "Unable to load XML document into the parser ";
		}
		if (!bSuccess) {
			throw "Unable to load XML document into the parser ";
		}

		// Construct search string
		CComBSTR bstrSS(L"PropertyList");
		CComPtr<IXMLDOMNode> spXMLNode;
		CComPtr<IXMLDOMNodeList> spXMLNodeList;
		
		hr = spXMLDOM->selectSingleNode(bstrSS, &spXMLNode);
		if (FAILED(hr)) {
			throw "Unable to locate PropertyList";
		}
		if (spXMLNode.p == NULL) {
			throw "Unable to locate PropertyList";
		}

		hr = spXMLNode->get_childNodes(&spXMLNodeList);
		if (FAILED(hr)) {
			throw "Unable to get the node list";
		}

		CComBSTR nodeName;
		CComVariant nodeValue(VT_EMPTY);

		spXMLNode = NULL;
		while (!FAILED(spXMLNodeList->nextNode(&spXMLNode))) {
			if (spXMLNode.p == NULL) {
				break;
			}
			hr = spXMLNode->get_nodeName(&nodeName);
		    hr = spXMLNode->get_nodeTypedValue(&nodeValue);
			USES_CONVERSION;
			LPTSTR lpstrVal = W2T(nodeValue.bstrVal);

			// We just need name, w-base, h-base.
			if (nodeName == L"name") {
				instr->setFullName(lpstrVal);
			} else if (nodeName == L"w-base") {
				instr->setW_base(atoi((const char*)lpstrVal));
			} else if (nodeName == L"h-base") {
				instr->setH_base(atoi((const char*)lpstrVal));
			} else {
				break;
			}
			spXMLNode = NULL;
		}

		// load layers
		loadLayers("PropertyList/layers/layer", instr, instr->getW_scale(), instr->getH_scale());
	} catch (char* lpstrError) {
		std::cout << lpstrError << std::endl;
	} catch (...) {
		std::cout << "Unknown error" << std::endl;
	}
}

// Load all of layers.
void XMLReader::loadLayers(char *szQueryString, Instrument* instr, float w_scale, float h_scale)
{
	try {
		layerList *ll = instr->getLl();
		// Construct search string
		CComBSTR bstrSS(szQueryString);
		CComPtr<IXMLDOMNode> spXMLNode, spXMLChildNode, spXMLGChildNode;
		CComPtr<IXMLDOMNodeList> spXMLNodeList, spXMLChildNodeList, spXMLGChildNodeList;	
		
		HRESULT hr = spXMLDOM->selectNodes(bstrSS, &spXMLNodeList);
		if (FAILED(hr)) {
			throw "Unable to locate PropertyList/layers/layer";
		}
		if (spXMLNodeList.p == NULL) {
			throw "Unable to locate PropertyList/layers/layer";
		}

		CComBSTR nodeName;
		CComVariant nodeValue(VT_EMPTY);
		spXMLNode = NULL;
		while (!FAILED(spXMLNodeList->nextNode(&spXMLNode))) {
			if (spXMLNode.p == NULL) {
				break;
			}
			
			Layer *la = new Layer(instr->getWidth(), instr->getHeight());
			hr = spXMLNode->get_childNodes(&spXMLChildNodeList);
			
			spXMLChildNode = NULL;
			while (!FAILED(spXMLChildNodeList->nextNode(&spXMLChildNode))) {
				if (spXMLChildNode.p == NULL) {
					break;
				}

				hr = spXMLChildNode->get_nodeName(&nodeName);
				hr = spXMLChildNode->get_nodeTypedValue(&nodeValue);
				USES_CONVERSION;
				LPTSTR lpstrVal = W2T(nodeValue.bstrVal);

				if (nodeName == L"name") {
					la->setName(lpstrVal);
				} else if (nodeName == L"texture") {
					spXMLGChildNodeList = NULL;
					hr = spXMLChildNode->get_childNodes(&spXMLGChildNodeList);
					while (!FAILED(spXMLGChildNodeList->nextNode(&spXMLGChildNode))){
						if (spXMLGChildNode.p == NULL) {
							break;
						}
						hr = spXMLGChildNode->get_nodeTypedValue(&nodeValue);
						hr = spXMLGChildNode->get_nodeName(&nodeName);
						USES_CONVERSION;
						LPTSTR _lpstrVal = W2T(nodeValue.bstrVal);

						if (nodeName == L"path") {
							la->getTex()->setPath(_lpstrVal);
							la->getTex()->loadTexture();
							//la->getTex()->loadTexture(texId);
						} else if (nodeName == L"x1") {
							la->getTex()->setX1((float)atof((const char*)_lpstrVal));
						} else if (nodeName == L"y1") {
							la->getTex()->setY1((float)atof((const char*)_lpstrVal));
						} else if (nodeName == L"x2") {
							la->getTex()->setX2((float)atof((const char*)_lpstrVal));
						} else if (nodeName == L"y2") {
							la->getTex()->setY2((float)atof((const char*)_lpstrVal));
						} 
						spXMLGChildNode = NULL;
					}
				} else if (nodeName == L"w") {
					la->setW((int)(atoi((const char*)lpstrVal) * w_scale));
				} else if (nodeName == L"h") {
					la->setH((int)(atoi((const char*)lpstrVal) * h_scale));
				} else if (nodeName == L"transformations") {
					loadTransformations(spXMLChildNode, la, w_scale, h_scale);
				} else if (nodeName == L"type") {
					if (!strcmp((const char*)lpstrVal, "switch")) {
						la->setType(Layer::SWITCH);
						loadSwitchLayer(la, w_scale, h_scale);
					} else if (!strcmp((const char*)lpstrVal, "text")) {
						la->setType(Layer::TEXT);
						// Because the text type layer has no textures associating with it, so set the tex member to be NULL
						la->setTex(NULL);
					} else if (!strcmp((const char*)lpstrVal, "built-in")) {
						la->setType(Layer::BUILT_IN);
						// Because the built-in type layer has no textures associating with it, so set the tex member to be NULL
						la->setTex(NULL);
					}
				}
				spXMLChildNode = NULL;
			}

			ll->push_back(la);
			spXMLChildNodeList = NULL;
			spXMLNode = NULL;
		}

		// sort the Layer list
		sort(ll->begin(), ll->end(), descend);

	} catch (char *lpstrError) {
		std::cout << lpstrError << std::endl;
	} catch (...) {
		std::cout << "Unknown error" << std::endl;
	}
}

// Load switch Layer
void XMLReader::loadSwitchLayer(Layer* _la, float w_scale, float h_scale)
{
	try {
		// Construct the search string.
		CComBSTR bstrSS(L"PropertyList/layers/layer/layer");

		CComPtr<IXMLDOMNode> spXMLNode, spXMLChildNode, spXMLGChildNode;
		CComPtr<IXMLDOMNodeList> spXMLNodeList, spXMLChildNodeList, spXMLGChildNodeList;		
		
		HRESULT hr = spXMLDOM->selectNodes(bstrSS, &spXMLNodeList);
		if (FAILED(hr)) {
			throw "Unable to locate PropertyList/layers/layer/layer";
		}
		if (spXMLNodeList.p == NULL) {
			throw "Unable to locate PropertyList/layers/layer/layer";
		}

		layerList* ll = new layerList();
		_la->setSwitchLayers(ll);

		CComBSTR nodeName;
		CComVariant nodeValue(VT_EMPTY);
		spXMLNode = NULL;
		while (!FAILED(spXMLNodeList->nextNode(&spXMLNode))) {
			if (spXMLNode.p == NULL) {
				break;
			}
			
			Layer *la = new Layer(_la->getW(), _la->getH());
			hr = spXMLNode->get_childNodes(&spXMLChildNodeList);

			while (!FAILED(spXMLChildNodeList->nextNode(&spXMLChildNode))) {
				if (spXMLChildNode.p == NULL) {
					break;
				}

				spXMLChildNode->get_nodeName(&nodeName);
				spXMLChildNode->get_nodeTypedValue(&nodeValue);
				USES_CONVERSION;
				LPTSTR lpstrVal = W2T(nodeValue.bstrVal);

				if (nodeName == L"name") {
					la->setName(lpstrVal);
				} else if (nodeName == L"texture") {
					spXMLGChildNodeList = NULL;
					spXMLChildNode->get_childNodes(&spXMLGChildNodeList);
					while (!FAILED(spXMLGChildNodeList->nextNode(&spXMLGChildNode))){
						if (spXMLGChildNode.p == NULL) {
							break;
						}

						hr = spXMLGChildNode->get_nodeTypedValue(&nodeValue);
						hr = spXMLGChildNode->get_nodeName(&nodeName);
						USES_CONVERSION;
						LPTSTR _lpstrVal = W2T(nodeValue.bstrVal);

						if (nodeName == L"path") {
							la->getTex()->setPath(_lpstrVal);
							la->getTex()->loadTexture();
							//la->getTex()->loadTexture(texId);
						} else if (nodeName == L"x1") {
							la->getTex()->setX1((float)atof((const char*)_lpstrVal));
						} else if (nodeName == L"y1") {
							la->getTex()->setY1((float)atof((const char*)_lpstrVal));
						} else if (nodeName == L"x2") {
							la->getTex()->setX2((float)atof((const char*)_lpstrVal));
						} else if (nodeName == L"y2") {
							la->getTex()->setY2((float)atof((const char*)_lpstrVal));
						} 
						spXMLGChildNode = NULL;
					}
				} else if (nodeName == L"w") {
					la->setW((int)(atoi((const char*)lpstrVal) * w_scale));
				} else if (nodeName == L"h") {
					la->setH((int)(atoi((const char*)lpstrVal) * h_scale));
				} else if (nodeName == L"transformations") {
					loadTransformations(spXMLChildNode, la, w_scale, h_scale);
				} 
				spXMLChildNode = NULL;
			}

			ll->push_back(la);
			spXMLChildNodeList = NULL;
			spXMLNode = NULL;
		}

		// sort the Layer list
		sort(ll->begin(), ll->end(), descend);

	} catch (char *lpstrError) {
		std::cout << lpstrError << std::endl;
	} catch (...) {
		std::cout << "Unknown error" << std::endl;
	}
}

// Load transformations' parameters such as offset, min, max and scale.
void XMLReader::loadTransformations(IXMLDOMNode *spXMLDOMNode, Layer *la, float w_scale, float h_scale)
{
	try {
		CComPtr<IXMLDOMNode> spXMLNode = spXMLDOMNode;
		CComPtr<IXMLDOMNode> spXMLCNode;
		CComPtr<IXMLDOMNodeList> spXMLNodeList, spXMLCNodeList;

		CComBSTR nodeName;
		CComVariant nodeVal (VT_EMPTY);

		HRESULT hr = spXMLNode->get_childNodes(&spXMLNodeList);
		
		spXMLNode = NULL;
		while (!FAILED(spXMLNodeList->nextNode(&spXMLNode))) {
			if (spXMLNode.p == NULL) {
				break;
			}
			Transformation *tr = new Transformation(w_scale, h_scale);

			spXMLCNodeList = NULL;
			hr = spXMLNode->get_childNodes(&spXMLCNodeList);

			spXMLCNode = NULL;
			while (!FAILED(spXMLCNodeList->nextNode(&spXMLCNode))) {
				if (spXMLCNode.p == NULL) {
					break;
				}
				
				hr = spXMLCNode->get_nodeName(&nodeName);
				hr = spXMLCNode->get_nodeTypedValue(&nodeVal);
				USES_CONVERSION;
				LPTSTR lpstrVal = W2T(nodeVal.bstrVal);

				// Recently just need type, offset, min, max, scale.
				if (nodeName == L"type") {
					tr->setType(lpstrVal);
				} else if (nodeName == L"offset") {
					tr->setOffset(atoi((const char*)lpstrVal));
				} else if (nodeName == L"min") {
					tr->setMinR(atof((const char*)lpstrVal));
				} else if (nodeName == L"max") {
					tr->setMaxR(atof((const char*)lpstrVal));
				} else if (nodeName == L"scale") {
					tr->setScale(atof((const char*)lpstrVal));
				}
				spXMLCNode = NULL;
			}
			la->getTl()->push_back(tr);
			spXMLNode = NULL;
		}
	} catch (char *lpstrError) {
		std::cout << lpstrError << std::endl;
	} catch (...) {
		std::cout << "Unknown error" << std::endl;
	}
}


void XMLReader::TESTHR(HRESULT hr)
{
	if (FAILED(hr)) {
		throw hr;
	}
}