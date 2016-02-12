#include "World.h"

//--------------------------------------------------------------
void World::setup() {
	world.init();
	world.setGravity(0, 30);
//	world.createBounds();
	world.setFPS(60.0);
	world.enableEvents();

	vector <string> strLines;
	ifstream f;
	f.open(ofToDataPath("lines.txt").c_str());
	if(f.is_open()) {
		while(!f.eof()) {
			string ptStr;
			getline(f, ptStr);
			strLines.push_back(ptStr);
		}
		f.close();
	} else {
		cout << "Doesn't seem to be open" << endl;
	}

	for(int i=0; i<strLines.size(); i++) {
		vector <string> pts = ofSplitString(strLines[i], ",");
		if(pts.size() > 0) {
			ofPtr <ofxBox2dEdge> edge = ofPtr<ofxBox2dEdge> (new ofxBox2dEdge);
			ofPolyline l;
			for(int j=0; j<pts.size(); j+=2) {
				if(pts[j].size() > 0) {
					float x = ofToFloat(pts[j]);
					float y = ofToFloat(pts[j+1]);
					edge.get()->addVertex(x, y);
					l.addVertex(x, y);
			}
		}
		edge.get()->create(world.getWorld());
		edges.push_back(edge);
		lines.push_back(l);
		}
	}
}

void World::update() {
	world.update();
}

void World::draw() {
	world.drawGround();
}

//--------------------------------------------------------------
void World::drawLines() {
	if(mode==DRAW) {
		ofPushStyle();
		ofFill();
		ofSetHexColor(0xffffff);

		for(int i=0; i < lines.size(); i++) {
			lines[i].draw();
		}

		ofSetHexColor(0xff0000);
		ofDrawBitmapString("DRAW", 10, 10);


		switch(drawStyle) {
			case FREE:
				ofDrawBitmapString("FREEHAND", 10, 25);
				break;
			case LINE:
				ofDrawBitmapString("LINE", 10, 25);
				break;
			default:
				break;
		}

		ofPopStyle();
	}
}

void World::setDrawStyle(_drawStyle s) {
	drawStyle = s;
}

void World::setMode(_mode m) {
	mode = m;
}

//--------------------------------------------------------------
void World::mousePressed(int& x, int& y, int& button) {
	if(mode==DRAW) {
		switch(button) {
			case 0:
				lines.push_back(ofPolyline());
				lines.back().addVertex(x, y);
				break;
			default:
				break;
		}
	}
}

void World::mouseReleased(int& x, int& y, int& button) {
	if(mode==DRAW) {
		switch(button) {
			case 0:
				saveLine(x, y);
				break;
			case 2:
				if(lines.size() && edges.size()){
					lines.pop_back();
					edges.pop_back();
				}

				break;
			default:
				break;
		}
	}
}

void World::mouseDragged(int& x, int& y, int& button) {
	if(mode==DRAW) {
		switch(drawStyle) {
			case FREE:
				lines.back().addVertex(x, y);
				break;
			default:
				break;
		}
	}
}

//--------------------------------------------------------------
void World::clear() {
	lines.clear();
	edges.clear();
}

void World::saveLine(int& x, int& y) {
	lines.back().addVertex(x, y);
	ofPtr <ofxBox2dEdge> edge = ofPtr<ofxBox2dEdge>(new ofxBox2dEdge);
	lines.back().simplify();

	for(int i=0; i < lines.back().size(); i++) {
		edge.get()->addVertex(lines.back()[i]);
	}

	edge.get()->create(world.getWorld());
	edges.push_back(edge);
}

void World::saveWorld() {
	ofstream f;
	f.clear();
	f.open(ofToDataPath("lines.txt").c_str());
	for(int i=0; i<lines.size(); i++) {
		for(int j=0; j < lines.at(i).size();j++) {
			float x = lines[i][j].x;
			float y = lines[i][j].y;

			f << x << "," << y << ",";
		}
		f << "\n";
	}
	f.close();

	cout << "World saved" << endl;
}
