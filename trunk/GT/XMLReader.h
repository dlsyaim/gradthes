#pragma once
#include "Instrument.h"
#include "Panel.h"

class XMLReader
{
public:
	XMLReader(void);
	~XMLReader(void);
	BOOL initializeParser(void);
	void loadPanel(char* szPathName, Panel* pan);
	void loadInstruments(char* szQueryString, instrumentList *inLi);
	void loadInstrument(const char* szPathName, Instrument *instr);
	void loadLayers(char* szQueryString, Instrument* instr, float w_scale, float h_scale);
	void loadTransformations(IXMLDOMNode* spXMLNode, Layer* la, float w_scale, float h_scale);
	void loadSwitchLayer(Layer* la, float w_scale, float h_scale);

private:
	// IXMLDOMDocument represents the top level of the XML source. 
    // Includes members for retrieving and creating all other XML objects.
	CComPtr<IXMLDOMDocument> spXMLDOM;
	void TESTHR(HRESULT hr);
	
};
