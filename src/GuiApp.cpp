#include "GuiApp.h"

void GuiApp::setup() {
	ofBackground(0);
	ofSetVerticalSync(false);
}

void GuiApp::update() {
}

void GuiApp::draw() {
	// Needs optimization
	for(unsigned i=0; i<vols.size(); i++) {
		ofSetHexColor(0xFFFFFF);
		int gap = 5;
		int w = (ofGetWidth()/vols.size()) - gap;
		int mh = ofGetHeight();
		int h = vols.at(i) * mh;
		ofVec2f p(i * (w+gap), mh);
		ofDrawRectangle(p, w, -h);
	}
}
