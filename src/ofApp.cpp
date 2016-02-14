#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);

	ofBackground(0);
	world.setup();
//	world.world.setIterations(8, 1);
	unsigned count = 1000;

	for(int i=0; i<count; i++) {
		unsigned xPos = ofRandom(ofGetWidth());
		unsigned yPos = ofRandom(ofGetHeight());
//		unsigned yPos = ofRandom(100)+75;
		unsigned radius = 3;
		ofVec2f v(ofRandom(-5, 5), ofRandom(-5, 5));
		shared_ptr <ofxBox2dCircle> c(new ofxBox2dCircle);
		c.get()->setFixedRotation(true);
		c.get()->setPhysics(3, 0.53, 0.1);
		c.get()->setVelocity(v);
		c.get()->setup(world.world.getWorld(), xPos, yPos, radius);
		c.get()->enableGravity(true);
		circles.push_back(c);
	}

	// Sound-stuff
	unsigned nChannels = 8;
	sound.setup(nChannels);
	speakers.resize(8);

	for(ofVec2f &s : speakers) {
		s.set(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));
	}
}

void ofApp::update(){
	world.update();

	if(world.getMode() == PLAY) {
		updateCircles();
	}
}

void ofApp::draw(){
#ifdef DEBUG
	drawDebug();
#endif

	world.draw();
	world.drawLines();

	ofFill();
	ofSetHexColor(0xFFFFFF);

	if(world.getMode() == PLAY) {
		drawCircles();
	}
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
}

void ofApp::keyReleased(int key){
	switch(key) {
		case 'c':
			world.clear();
			break;
		case '1':
			world.setMode(PLAY);
			break;
		case '2':
			world.setMode(DRAW);
			world.setDrawStyle(FREE);
			break;
		case '3':
			world.setMode(DRAW);
			world.setDrawStyle(LINE);
			break;
		case 's':
			world.saveWorld();
			break;
		default:
			break;
	}
}

void ofApp::mouseMoved(int x, int y){
}

void ofApp::mouseDragged(int x, int y, int button){
	world.mouseDragged(x, y, button);
}

void ofApp::mousePressed(int x, int y, int button){
	world.mousePressed(x, y, button);
}

void ofApp::mouseReleased(int x, int y, int button){
	world.mouseReleased(x, y, button);
}

void ofApp::mouseEntered(int x, int y){
}

void ofApp::mouseExited(int x, int y){
}

void ofApp::windowResized(int w, int h){
}

void ofApp::gotMessage(ofMessage msg){
}

void ofApp::dragEvent(ofDragInfo dragInfo){
}

//--------------------------------------------------------------
void ofApp::updateCircles() {
	ofVec2f m(ofGetMouseX(), ofGetMouseY());
	for(auto c : circles) {
		int pos = 30;
		for(unsigned i=0; i<sound.vols.size(); i++) {
			float v = sound.vols[i];
			float strength = 0;
			float damping = 0.9;
			float dist = speakers[i].distance(c.get()->getPosition());
			float radius = ofMap(v, 0.07, 1, 0, 200, true);

			if(dist < radius) {
//				strength = (radius-dist)/100;
				strength = ofMap(v, 0, 1, 0, 0.005, true);
			}

			c.get()->addRepulsionForce(speakers[i], strength);
//			if(i==0) cout << c << " " <<  speakers[i] << " " << strength <<  endl;
//			if(i==0) cout << m << endl;
//			c.get()->addRepulsionForce(m, strength);
//			c.get()->setDamping(damping);
		}
	}
}

void ofApp::drawCircles() {
	for(auto c : circles) {
		ofVec2f pos = c.get()->getPosition();
		unsigned r = 3;
		glPushMatrix();
		glTranslatef(pos.x, pos.y, 0);
		ofDrawCircle(0, 0, r);
		glPopMatrix();
	}
}

//--------------------------------------------------------------
void ofApp::drawDebug() {
	ofDrawBitmapString(ofToString(ofGetFrameRate()), 10, 50);
	for(int i=0; i<sound.vols.size();i++) {
		ofSetHexColor(0xAAFFFF);
		float r = ofMap(sound.vols[i], 0.07, 1.7, 0, 200, true);
		ofDrawCircle(speakers[i].x, speakers[i].y, r);

		ofSetHexColor(0xFFFFFFFF);
		ofDrawBitmapString(ofToString(sound.vols[i]), 10, (10*i)+60);
	}
}
