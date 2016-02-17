#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	// Setting of the variables
	mode = DRAW_FREE;
	numCircles = 10000;
	circRadius = 1;
	circDrawRadius = 1.5;

	unsigned numFields = 8;
	float soundInThresLow = 0.01;
	float soundInThresHigh = 0.7;
	float radius = 250;
	float forceMax = 1;

	ofSetVerticalSync(true);

	ofBackground(0);

	world.setup();
//	world.world.setIterations(8, 1);

	// Circles
	for(int i=0; i<numCircles; i++) {
		newCircle();
	}

	// Force fields
	fields.setup(numFields, radius, soundInThresLow, soundInThresHigh, forceMax);
}

void ofApp::update(){
	world.update();
	fields.update();

	if(mode == PLAY) {
		updateCircles();
	}
}

void ofApp::draw(){
#ifdef DEBUG
	drawDebug();
#endif

	world.draw();
	if(mode != PLAY) {
		world.drawLines();
		fields.draw();
		drawMode();
	}

	ofFill();
	ofSetHexColor(0xFFFFFF);

	if(mode == PLAY) {
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
			mode = PLAY;
			break;
		case '2':
			mode = DRAW_FREE;
			break;
		case '3':
			mode = DRAW_LINE;
			break;
		case '4':
			mode = EDIT_FIELDS;
			break;
		case 's':
			fields.savePositions();
			world.saveWorld();
			break;
		default:
			break;
	}
}

void ofApp::mouseMoved(int x, int y){
}

void ofApp::mouseDragged(int x, int y, int button){
	switch(mode) {
		case DRAW_FREE:
			world.mouseDragged(x, y, button);
			break;
		case EDIT_FIELDS:
			fields.mouseDragged(x, y, button);
			break;
		default:
			break;
	}
}

void ofApp::mousePressed(int x, int y, int button){
	if(mode == DRAW_LINE) world.mousePressed(x, y, button);
	if(mode == EDIT_FIELDS) fields.mousePressed(x, y, button);
}

void ofApp::mouseReleased(int x, int y, int button){
	if(mode == DRAW_LINE) world.mouseReleased(x, y, button);
	if(mode == EDIT_FIELDS) fields.mouseReleased(x, y, button);
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
	//		shared_ptr <ofxBox2dCircle> c(new ofxBox2dCircle);
	shared_ptr <ofxBox2dCircle> c = make_shared<ofxBox2dCircle>();
	circles.push_back(c);
	circles.back().get()->setFixedRotation(true);
	circles.back().get()->setPhysics(3, 0.53, 0.1);
	circles.back().get()->setup(world.world.getWorld(), xPos, yPos, circRadius);
	circles.back().get()->enableGravity(true);
	circles.back().get()->setMassFromShape = true;
}

//--------------------------------------------------------------
void ofApp::drawMode() {
	ofSetHexColor(0xFF0000);
	string m;
	switch(mode) {
		case DRAW_FREE:
			m = "Free";
			break;
		case DRAW_LINE:
			m = "Line";
			break;
		case EDIT_FIELDS:
			m = "Edit fields";
			break;
		default:
			break;
	}
	ofDrawBitmapString(m, 10, 15);
	ofSetHexColor(0xFFFFFF);
}

void ofApp::drawDebug() {
	ofSetHexColor(0xFF0000);
	ofDrawBitmapString(ofToString(ofGetFrameRate()), 10, 50);
	ofDrawBitmapString(ofToString(circles.size()), 10, 60);
	ofSetHexColor(0xFFFFFF);
}
