#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"


class World : public ofBaseApp {
	public:
		void setup();
		void update();
		void draw();

		void drawLines();

		void mouseDragged(int& x, int& y, int& button);
		void mousePressed(int& x, int& y, int& button);
		void mouseReleased(int& x, int& y, int& button);

		void saveWorld();
		void clear();

		ofxBox2d world;

	private:
		void saveLine(int& x, int& y);

		vector<ofPolyline> lines;
		vector<ofPtr<ofxBox2dEdge> > edges;
};
