#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class GuiApp : public ofBaseApp {
	public:
		void setup();
		void update();
		void draw();

		void setVolsPtr(vector<float> *_volsPtr);

		unsigned circleCount;

	private:
		vector<float> *volsPtr;

		ofxPanel panel;
		ofxToggle isDraw;
};
