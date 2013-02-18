#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "ofEvents.h"
#include <fstream>

#define SPACE_VAL 1

class testApp : public ofBaseApp{

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

		ifstream fin;
		vector <string> data;
		vector <int> time;
	
		int word;
		float controlSpeed;
        double timer;

        bool debug;
    
        bool bFwd;
        bool bPaused;
    
    
        ofArduino	ard;
        bool		bSetupArduino;
        
    private:
        
        void setupArduino(const int & version);
        void digitalPinChanged(const int & pinNum);
        void analogPinChanged(const int & pinNum);
        void updateArduino();
        
    
};

#endif
