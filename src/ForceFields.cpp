#include "ForceFields.h"
//--------------------------------------------------------------

void ForceFields::setup(unsigned nFF) {
	numForceFields = nFF;
	soundInThresLow = 0.01;
	soundInThresHigh = 0.7;

	sound.setup(numForceFields);
	fields.resize(numForceFields);

	for(Field &f : fields) {
		f.pos.set(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));
		f.radius = 250;
	}
}

void ForceFields::update() {
	for(unsigned i=0; i<numForceFields; i++) {
		fields[i].strength = sound.vols[i];
	}
}

void ForceFields::draw() {
	for(unsigned i=0; i<numForceFields; i++) {
		Field *f = &fields[i];
		float r = ofMap(f->strength, soundInThresLow, soundInThresHigh, 0, 200, true);
		ofSetHexColor(0xAAFFFF);
		ofDrawCircle(f->pos, r);

		ofSetHexColor(0xFFFFFFFF);
		ofDrawBitmapString(ofToString(f->strength), 10, (10*i)+80);
	}
}

void ForceFields::affectCircle(shared_ptr<ofxBox2dCircle> c) {
	for(auto &f : fields) {
		float v = f.strength;
		float strength = 0;
		float dist = f.distance(c.get()->getPosition());
//		float radius = ofMap(v, soundInThresLow, soundInThresHigh, 0, 500, true);

		if(dist < f.radius) {
			strength = ofMap(v, soundInThresLow, soundInThresHigh, 0, 0.05, true);
		}

		c.get()->addRepulsionForce(f.pos, strength);
	}
}
