#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);
	ofBackground(0);
	world.setup();

	for(int i=0; i<1000; i++) {
		unsigned xPos = ofRandom(ofGetWidth());
		unsigned yPos = 0;
		circles.push_back(shared_ptr <ofxBox2dCircle> (new ofxBox2dCircle));
		circles.back().get()->setFixedRotation(true);
		circles.back().get()->setPhysics(3, 0.53, 0.1);
		circles.back().get()->setup(world.world.getWorld(), xPos, yPos, 5);
	}
}

//--------------------------------------------------------------
void ofApp::update(){
	world.update();

	ofVec2f m(ofGetMouseX(), ofGetMouseY());
	for(auto c : circles) {
		float strength = 0;
		float damping = 0.9;
		float dist = m.distance(c.get()->getPosition());

		if(dist < 100) {
			strength = (100-dist)/2;
		}

		c.get()->addRepulsionForce(m, strength);
		c.get()->setDamping(damping, damping);
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	drawFR();

	world.draw();
	world.drawLines();

	ofFill();
	ofSetHexColor(0xFFFFFF);

	for(auto c : circles) {
		c.get()->draw();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
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

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	world.mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	world.mousePressed(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	world.mouseReleased(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}

//--------------------------------------------------------------
void ofApp::drawFR() {
	ofDrawBitmapString(ofToString(ofGetFrameRate()), 10, 50);
}
