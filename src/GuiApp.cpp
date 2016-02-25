#include "GuiApp.h"

void GuiApp::setup() {
	ofBackground(0);
	ofSetVerticalSync(false);

	isPlay.addListener(this,  &GuiApp::playPressed);
	isDrawable.addListener(this,  &GuiApp::drawablePressed);
	isFieldEditable.addListener(this,  &GuiApp::fieldEditablePressed);

	space.set(" ");

	panel.setup();
	panel.add(frameRate.set("Framerate", 0));
	panel.add(circleCount.set("CircleCount", 0));

	panel.add(space);
	panel.add(isPlay.set("Play", true));
	panel.add(isDrawable.set("Draw", true));
	panel.add(isFieldEditable.set("Edit fields", true));

	panel.add(space);
	panel.add(save.setup("Save"));
	panel.add(clear.setup("Clear"));
}

void GuiApp::update() {
	frameRate = ofGetFrameRate();
}

void GuiApp::draw() {
	panel.draw();

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

//--------------------------------------------------------------
void GuiApp::playPressed(bool &b) {
	if(b) {
		isDrawable = false;
		isFieldEditable = false;
	}
}

void GuiApp::drawablePressed(bool &b) {
	if(b) {
		isPlay = false;
		isFieldEditable = false;
	}
}

void GuiApp::fieldEditablePressed(bool &b) {
	if(b) {
		isDrawable = false;
		isPlay = false;
	}
}
