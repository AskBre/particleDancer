#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"

enum _mode {
	DRAW,
	PLAY,
};

enum _drawStyle {
	FREE,
	LINE,
};

class World : public ofBaseApp {
	public:
		void setup();
		void update();
		void draw();

		void drawLines();
		void setMode(_mode);
		void setDrawStyle(_drawStyle);

		void mouseDragged(int& x, int& y, int& button);
		void mousePressed(int& x, int& y, int& button);
		void mouseReleased(int& x, int& y, int& button);

		void saveWorld();
		void clear();

		ofxBox2d world;

	private:
		void saveLine(int& x, int& y);

		_mode mode;
		_drawStyle drawStyle;

		vector<ofPolyline> lines;
		vector<ofPtr<ofxBox2dEdge> > edges;
};
