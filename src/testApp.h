#pragma once
#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "ofEvents.h"
#include <fstream>

#define SPACE_VAL 1.0
#define PERIOD_VAL 3.0

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

		bool                debug;

        bool bStarted;
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
