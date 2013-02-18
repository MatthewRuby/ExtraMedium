#pragma once

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
		ifstream 		book;
		float 			time;
		vector 	<string> 	word;
		vector 	<int>		delay;
		float			currentDelay;
		float 			ctrlSpeed;
		float			timer;
		int			index;
		int			total_words;
		int			total_delays;

		bool			debug;
};
