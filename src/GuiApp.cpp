#include "GuiApp.h"

void GuiApp::setup() {
	ofBackground(0);
	ofSetVerticalSync(false);

	panel.setup();
	panel.add(isDraw.set("Draw", true));
}

void GuiApp::update() {
}

void GuiApp::draw() {
	panel.draw();
	if(isDraw) {
		ofSetHexColor(0xFF0000);
		ofDrawBitmapString(ofToString(ofGetFrameRate()), 10, 50);
		ofDrawBitmapString(ofToString(circleCount), 10, 60);
		ofSetHexColor(0xFFFFFF);

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
}

void GuiApp::setVolsPtr(vector<float> *_volsPtr) {
	volsPtr = _volsPtr;
}
