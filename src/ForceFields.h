#pragma once

#include "ofMain.h"
#include "SoundAnalyzer.h"
#include "ofxBox2d.h"

class ForceFields : public ofBaseApp {
	public:
		void setup(unsigned numForceFields, unsigned r, 
				float soundThresLo, float soundInThresHi,
				float forceMax);
		void update();
		void draw();

		void mouseDragged(int &x, int &y, int &button);
		void mousePressed(int &x, int &y, int &button);
		void mouseReleased(int &x, int &y, int &button);

		void affectCircle(shared_ptr<ofxBox2dCircle> c);

	private:
		struct Field {
			ofVec2f pos;
			float strength;
			float radius;
			float distance(ofVec2f p) {
				return pos.distance(p);
			}
			bool isDragged;
		};

		SoundAnalyzer sound;

		vector<Field> fields;

		float soundInThresLow;
		float soundInThresHigh;
		unsigned numForceFields;
		float forceMax;
};
