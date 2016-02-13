#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);

	ofBackground(0);
	world.setup();
	world.world.setIterations(8, 1);

	for(int i=0; i<2000; i++) {
		unsigned xPos = ofRandom(ofGetWidth());
		unsigned yPos = ofRandom(50)+50;
		unsigned radius = 5;
		ofVec2f v(ofRandom(-1, 1), ofRandom(-1, 1));
		shared_ptr <ofxBox2dCircle> c(new ofxBox2dCircle);
		c.get()->setFixedRotation(true);
		c.get()->setPhysics(3, 0.53, 0.1);
		c.get()->setVelocity(v);
		c.get()->setup(world.world.getWorld(), xPos, yPos, radius);
		circles.push_back(c);
	}
}

void ofApp::update(){
	world.update();

	if(world.getMode() == PLAY) {
		updateCircles();
	}
}

void ofApp::draw(){
	drawFR();

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
		float strength = 0;
		float damping = 0.9;
		float dist = m.distance(c.get()->getPosition());
		float radius = 200;

		if(dist < radius) {
			strength = (radius-dist)/2;
		}

		c.get()->addRepulsionForce(m, strength);
		//		c.get()->setDamping(damping, damping);
	}
}

void ofApp::drawCircles() {
	for(auto c : circles) {
		ofVec2f pos = c.get()->getPosition();
		unsigned r = c.get()->getRadius();
		glPushMatrix();
		glTranslatef(pos.x, pos.y, 0);
		ofDrawCircle(0, 0, r);
		glPopMatrix();
	}
}

//--------------------------------------------------------------
void ofApp::drawFR() {
	ofDrawBitmapString(ofToString(ofGetFrameRate()), 10, 50);
}
