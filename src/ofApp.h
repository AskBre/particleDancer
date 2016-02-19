#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"
#include "World.h"
#include "ForceFields.h"
#include "GuiApp.h"

#define DEBUG

enum run_mode_t {
	PLAY,
	DRAW_FREE,
	DRAW_LINE,
	EDIT_FIELDS,
};

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		void updateCircles();
		void drawCircles();
		void newCircle();

		shared_ptr<GuiApp> gui;

		float circRadius;
		float circDrawRadius;

		void drawMode();
		void drawDebug();

		World world;
		ForceFields fields;
		run_mode_t mode;

		unsigned numCircles;
		float radius;
		unsigned numFields;

		vector<shared_ptr <ofxBox2dCircle> > circles;
		vector<ofVec2f *> fieldPosPtrs;
};
