#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);
	ofBackground(0);
	world.setup();
}

//--------------------------------------------------------------
void ofApp::update(){
	world.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	world.draw();
	world.drawLines();
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
