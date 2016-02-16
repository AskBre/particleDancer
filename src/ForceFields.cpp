#include "ForceFields.h"
//--------------------------------------------------------------

void ForceFields::setup(unsigned nFF, unsigned r, float sITL, float sITH, float fM) {
	numForceFields = nFF;
	soundInThresLow = sITL;
	soundInThresHigh = sITH;
	forceMax = fM;

	sound.setup(numForceFields);
	fields.resize(numForceFields);

	for(Field &f : fields) {
		f.pos.set(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));
		f.radius = r;
	}
}

//--------------------------------------------------------------
void ForceFields::update() {
	for(unsigned i=0; i<numForceFields; i++) {
		fields[i].strength = sound.vols[i];
	}
}

void ForceFields::draw() {
	for(unsigned i=0; i<numForceFields; i++) {
		Field *f = &fields[i];
		float r = ofMap(f->strength, soundInThresLow, soundInThresHigh,
				0, f->radius, true);
		ofSetHexColor(0xAAFFFF);
		ofDrawCircle(f->pos, r);

		ofSetHexColor(0xFFFFFFFF);
		ofDrawBitmapString(ofToString(f->strength), 10, (10*i)+80);
	}
}

//--------------------------------------------------------------
void ForceFields::affectCircle(shared_ptr<ofxBox2dCircle> c) {
	for(auto &f : fields) {
		float v = ofNormalize(f.strength, soundInThresLow, soundInThresHigh);
		float strength = 0;
		float dist = f.distance(c.get()->getPosition());
		float iDist = f.radius - dist;
		float nDist = ofNormalize(iDist, 0, f.radius);
//		float dist = ofDistSquared(f.pos.x, f.pos.y, cp.x, cp.y);
		float mv = ofMap(v, 0, soundInThresHigh, 0, forceMax);

		strength = mv * (nDist/10);

//		if(dist < f.radius && v > soundInThresLow) {
//		if(dist < f.radius) {
			c.get()->addRepulsionForce(f.pos, strength);
//		}
	}
}
