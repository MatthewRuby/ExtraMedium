#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include <fstream>

#define SPACE_VAL 7

class testApp : public ofBaseApp{

	struct word {
		string term;
		string sound;
		int len;
	};
	
	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);

		ofTrueTypeFont 	times;
	
		ifstream dict;
		vector <word> terms;
	
		ifstream fin; //declare a file stream
		vector <string> data; //declare a vector of strings to store data
		vector <int> time;
	
		int word;
		float controlSpeed;
        double timer;

        bool debug;
};

#endif
