#include "GuiApp.h"

void GuiApp::setup() {
	ofBackground(0);
	ofSetVerticalSync(false);
}

void GuiApp::update() {
}

void GuiApp::draw() {
	for(unsigned i=0; i<volsPtr->size(); i++) {
		ofSetHexColor(0xFFFFFF);
		int gap = 5;
		int w = (ofGetWidth()/volsPtr->size()) - gap;
		int mh = ofGetHeight();
		int h = volsPtr->at(i) * mh;
		ofVec2f p((i *w+gap), mh);
		ofDrawRectangle(p, w, -h);
	}
}

void GuiApp::setVolsPtr(vector<float> *_volsPtr) {
	volsPtr = _volsPtr;
}
