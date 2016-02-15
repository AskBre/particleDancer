#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);

	ofBackground(0);

	world.setup();
//	world.world.setIterations(8, 1);

	// Circles
	circRadius = 1;
	circDrawRadius = 1.5;

	for(int i=0; i<numCircles; i++) {
		newCircle();
	}

	// Force fields
	unsigned numFields = 8;
	fields.setup(numFields);
}

void ofApp::update(){
	world.update();
	fields.update();

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
	for(auto &c : circles) {
		fields.affectCircle(c);
	}

	ofRemove(circles, ofxBox2dBaseShape::shouldRemoveOffScreen);

	if(circles.size() < numCircles) {
		newCircle();
	}
}

void ofApp::drawCircles() {
	for(auto c : circles) {
		ofVec2f pos = c.get()->getPosition();
		glPushMatrix();
		glTranslatef(pos.x, pos.y, 0);
		ofDrawCircle(0, 0, circDrawRadius);
		glPopMatrix();
	}
}

void ofApp::newCircle() {
		unsigned xPos = ofRandom(ofGetWidth());
		unsigned yPos = ofRandom(ofGetHeight());
//		unsigned yPos = ofRandom(100)+75;
		shared_ptr <ofxBox2dCircle> c(new ofxBox2dCircle);
		c.get()->setFixedRotation(true);
		c.get()->setPhysics(3, 0.53, 0.1);
		c.get()->setup(world.world.getWorld(), xPos, yPos, circRadius);
		c.get()->enableGravity(true);
		c.get()->setMassFromShape = true;
		circles.push_back(c);

}

//--------------------------------------------------------------
void ofApp::drawDebug() {
	ofDrawBitmapString(ofToString(ofGetFrameRate()), 10, 50);
	ofDrawBitmapString(ofToString(circles.size()), 10, 60);
	fields.draw();
	}
