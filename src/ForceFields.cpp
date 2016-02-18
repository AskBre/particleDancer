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

	radiusMax = r;
}

//--------------------------------------------------------------
void ForceFields::update() {
	for(unsigned i=0; i<numForceFields; i++) {
		float v = ofNormalize(sound.vols[i], soundInThresLow, soundInThresHigh);
		float mv = ofMap(v, 0, soundInThresHigh, 0, forceMax);
		fields[i].strength = mv;
		fields[i].radius = v * radiusMax * 4;
	}
}

void ForceFields::draw() {
	for(unsigned i=0; i<numForceFields; i++) {
		Field *f = &fields[i];
		ofSetHexColor(0xFF0000);
		ofNoFill();
		ofDrawCircle(f->pos, f->radius);
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
vector<float> *ForceFields::getVolsPtr() {
	return &sound.vols;
}

void ForceFields::affectCircle(const shared_ptr<ofxBox2dCircle> &c) {
	for(auto &f : fields) {
		if(f.strength) {
			float dist = f.distance(c.get()->getPosition());
			if(dist < f.radius) {
				float iDist = f.radius - dist;
				float nDist = ofNormalize(iDist, 0, f.radius);

				float st = (f.strength * nDist)/10;

				c.get()->addRepulsionForce(f.pos, st);
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
