#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	// Setting of the variables
	mode = DRAW_FREE;
	gui->maxCircles = 10000;
	circRadius = 1;
	circDrawRadius = 1.5;

	numFields = 8;
	float soundInThresLow = 0.01;
	float soundInThresHigh = 0.7;
	radius = 250;
	float forceMax = 1;

	ofSetVerticalSync(true);
//	ofDisableAntiAliasing();
	ofBackground(0);

	world.setup();
//	world.world.setIterations(8, 1);

	// Force fields
	fields.setup(numFields, radius, soundInThresLow, soundInThresHigh, forceMax);
	fieldPosPtrs = fields.getPosPtrs();

	gui->setVolsPtr(fields.getVolsPtr());

	gui->save.addListener(this, &ofApp::save);
	gui->clear.addListener(this, &ofApp::clear);

	// Circles
	for(int i=0; i<gui->maxCircles; i++) {
//		newCircle();
	}

}

void ofApp::update(){
	world.update();
	fields.update();
	gui->circleCount = circles.size();

	if(gui->isPlay) {
		updateCircles();
	}

}

void ofApp::draw(){
	world.draw();

	if(gui->isDrawable) world.drawLines();

	if(gui->isFieldEditable) fields.draw();

	ofFill();
	ofSetHexColor(0xFFFFFF);
	if(gui->isPlay) {
		drawCircles();
	}
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
}

void ofApp::keyReleased(int key){
}

void ofApp::mouseMoved(int x, int y){
}

void ofApp::mouseDragged(int x, int y, int button){
	if(gui->isDrawable) world.mouseDragged(x, y, button);
	if(gui->isFieldEditable) fields.mouseDragged(x, y, button);
}

void ofApp::mousePressed(int x, int y, int button){
	if(gui->isDrawable) world.mousePressed(x, y, button);
	if(gui->isFieldEditable) fields.mousePressed(x, y, button);
}

void ofApp::mouseReleased(int x, int y, int button){
	if(gui->isDrawable) world.mouseReleased(x, y, button);
	if(gui->isFieldEditable) fields.mouseReleased(x, y, button);
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

	if(circles.size() < gui->maxCircles) {
		newCircle();
	} else if(circles.size() > gui->maxCircles) {
		circles.pop_back();
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

	if(gui->isRedCircle) {
		glPushMatrix();
			ofSetHexColor(0xFF0000);
			ofVec2f pos = circles[0].get()->getPosition();
			glTranslatef(pos.x, pos.y, 0);
			ofDrawCircle(0, 0, circDrawRadius);
			ofSetHexColor(0xFFFFFF);
		glPopMatrix();
	}
}

void ofApp::newCircle() {
	ofVec2f relPos(ofRandom(radius), ofRandom(radius));
	unsigned f = ofRandom(fieldPosPtrs.size());

	ofVec2f *fPosPtr = fieldPosPtrs.at(f);

	ofVec2f pos = (*fPosPtr + relPos) - (radius/2);
	shared_ptr <ofxBox2dCircle> c = make_shared<ofxBox2dCircle>();
	circles.push_back(c);
	circles.back().get()->setFixedRotation(true);
	circles.back().get()->setPhysics(3, 0.53, 0.1);
	circles.back().get()->setup(world.world.getWorld(), pos.x, pos.y, circRadius);
	circles.back().get()->enableGravity(true);
	circles.back().get()->setMassFromShape = true;
}

//--------------------------------------------------------------
void ofApp::save() {
	fields.savePositions();
	world.saveWorld();
}

void ofApp::clear() {
	world.clear();
}
