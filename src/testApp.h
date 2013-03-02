#pragma once
#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "ofEvents.h"
#include <fstream>

#define SPACE_VAL 1.0
#define PERIOD_VAL 3.0

#define RED_LED 8
#define GREEN_LED 9
#define PAUSE_PIN 10
#define SPEED_PIN 0


class testApp : public ofBaseApp{

	public:
		void                setup();
		void                update();
		void                draw();
		void                keyPressed(int key);
		void                keyReleased(int key);

        ofTrueTypeFont		times;
    
        string              bookData[6];
        string              titles[6];
        int                 titlePins[6];
        int                 titleIndex;
    
		vector 	<string> 	word;
		vector 	<float>		delay;
    
		float               ctrlSpeed;
		float               timer;
		int                 index;

		bool                debug;
        float               currentDelay;
    
        bool                bStarted;
        bool                bFwd;
        bool                bPaused;
    
        int                 historyPos;
        int                 prevHistory;

        ofArduino           ard;
        bool                bSetupArduino;
    
    
        int buttonState;
        int lastButtonState;
        float lastDebounceTime;
        float debounceDelay;
    
    private:
        
        void                setupArduino(const int & version);
        void                digitalPinChanged(const int & pinNum);
        void                analogPinChanged(const int & pinNum);
        void                updateArduino();

};

#endif
