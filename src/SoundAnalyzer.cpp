#include "SoundAnalyzer.h"

void SoundAnalyzer::setup(unsigned nChannels) {
	unsigned sampleRate = 44100;
	unsigned buffNum = 256;
	unsigned nBuffers = nChannels;
	
	soundStream.setup(this, 0, nChannels, sampleRate, buffNum, nBuffers);

	vols.resize(nChannels);
}

void SoundAnalyzer::audioIn(float *inBuff, int bufferSize, int nChannels) {
	for(unsigned i=0; i<vols.size(); i++) {
		float curVol = 0;
		unsigned counted = 0;

//		for(unsigned b=0; b<bufferSize; b+=nChannels) {
		for(unsigned b=0; b<bufferSize; b++) {
			float someVol = inBuff[b+i]*0.5;

			curVol += someVol * someVol;
			counted+=nChannels;
		}

		curVol /= (float)counted;
		curVol = sqrt(curVol);

		// Smoothed with the last value
		vols[i] *= 0.93;
		vols[i] += 0.7 * curVol;
	}
}
