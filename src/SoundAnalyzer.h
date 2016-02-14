#pragma once

#include "ofMain.h"

class SoundAnalyzer : public ofBaseApp {
	public:
		void setup(unsigned nChannels);

		void audioIn(float *inBuff, int bufferSize, int nChannels);

		vector<float> vols;

		ofSoundStream soundStream;
};
