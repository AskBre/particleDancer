#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class GuiApp : public ofBaseApp {
	public:
		void setup();
		void update();
		void draw();

		void setVolsPtr(vector<float> *_volsPtr);

		ofParameter<string> space;

		ofParameter<float> frameRate;
		ofParameter<unsigned> circleCount;

		ofParameter<bool> isPlay;
		ofParameter<bool> isDrawable;
		ofParameter<bool> isFieldEditable;

		ofParameter<float> force;
		ofParameter<unsigned> maxCircles;
		ofParameter<bool> isRedCircle;

		ofxButton save;
		ofxButton clear;

	private:
		vector<float> *volsPtr;

		ofxPanel panel;

		void playPressed(bool &b);
		void drawablePressed(bool &b);
		void fieldEditablePressed(bool &b);
};
