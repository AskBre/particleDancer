#include "ForceFields.h"
//--------------------------------------------------------------

void ForceFields::setup(unsigned nFF, unsigned r, float sITL, float sITH, float fM) {
	numForceFields = nFF;
	soundInThresLow = sITL;
	soundInThresHigh = sITH;
	forceMax = fM;

	sound.setup(numForceFields);
	fields.resize(numForceFields);

	loadPositions();
	
	for(auto &f : fields) {
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
		ofSetHexColor(0xFF0000);
		ofNoFill();
		ofDrawCircle(f->pos, f->radius * f->strength);
		ofSetHexColor(0xFFFFFF);
		ofFill();
		ofDrawBitmapString(ofToString(i), f->pos.x-4, f->pos.y+4);

		ofDrawBitmapString(ofToString(f->strength), 10, (10*i)+80);
	}
}

//--------------------------------------------------------------
void ForceFields::mouseDragged(int& x, int& y, int& button) {
	ofVec2f m(x, y);
	for(auto &f: fields) {
		if(f.isDragged) {
			f.pos = m;
			break;
		}
	}
}

void ForceFields::mousePressed(int &x, int &y, int &button){
	ofVec2f m(x, y);
	for(auto &f: fields) {
		if(f.distance(m) < 20) {
			f.isDragged = true;
		}
	}
}

void ForceFields::mouseReleased(int &x, int &y, int &button){
	for(auto &f: fields) {
		f.isDragged = false;
	}
}

//--------------------------------------------------------------
void ForceFields::affectCircle(const shared_ptr<ofxBox2dCircle> &c) {
	for(auto &f : fields) {
		float v = ofNormalize(f.strength, soundInThresLow, soundInThresHigh);
		if(v > soundInThresLow) {
			float dist = f.distance(c.get()->getPosition());
			if(dist < f.radius) {
				float strength = 0;
				float iDist = f.radius - dist;
				float nDist = ofNormalize(iDist, 0, f.radius);
				float mv = ofMap(v, 0, soundInThresHigh, 0, forceMax);

				strength = mv * (nDist/10);

				c.get()->addRepulsionForce(f.pos, strength);
			}
		}
	}
}

//--------------------------------------------------------------
void ForceFields::savePositions() {
	ofxXmlSettings s;
	s.addTag("fieldPositions");
	s.pushTag("fieldPositions");
	for(int i=0; i<numForceFields; i++) {
		s.addTag("position");
		s.pushTag("position", i);
		s.addValue("x", fields[i].pos.x);
		s.addValue("y", fields[i].pos.y);
		s.popTag();
	}
	s.popTag();
	s.saveFile("fieldPositions.xml");

	cout << "Field positions saved" << endl;
}

void ForceFields::loadPositions() {
	ofxXmlSettings s;
	if(s.loadFile("fieldPositions.xml")) {
		s.pushTag("fieldPositions");
		for(unsigned i=0; i<numForceFields; i++) {
				ofVec2f p;
			if(s.tagExists("position", i)) {
				s.pushTag("position", i);
				p.x = s.getValue("x", 0);
				p.y = s.getValue("y", 0);
				s.popTag();
			} else {
				cout << "Not enough field positions loaded, ";
				cout << "setting to 100,100." << endl;
				p.set(100,100);
			}
				fields[i].pos = p;

		}
		s.popTag();
	} else {
		cerr << "No field position file found" << endl;
	}
}
