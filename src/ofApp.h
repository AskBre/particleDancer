#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"
#include "World.h"
#include "ForceFields.h"

#define DEBUG

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

		float circRadius;
		float circDrawRadius;

		void drawDebug();

		World world;
		ForceFields fields;

		unsigned numCircles;
		vector<shared_ptr <ofxBox2dCircle> > circles;
		vector<ofVec2f> speakers;
};
