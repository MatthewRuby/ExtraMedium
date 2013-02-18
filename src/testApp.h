#pragma once
#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include <fstream>

#define SPACE_VAL 1.0
#define PERIOD_VAL 1.5

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);

        ofTrueTypeFont		times;
    
        string              bookData[4];
        string              titles[4];
        int                 titleIndex;
    
		ifstream            book;
		float               time;
		vector 	<string> 	word;
		vector 	<float>		delay;
		float               currentDelay;
		float               ctrlSpeed;
		float               timer;
		int                 index;
		int                 total_words;
		int                 total_delays;

		bool                debug;
};

#endif
