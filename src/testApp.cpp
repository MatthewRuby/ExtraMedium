#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofSetRectMode(OF_RECTMODE_CENTER);
	
	ofBackground(255, 255, 255);


	
	fin.open(ofToDataPath("vonnegut.txt").c_str()); //open your text file
	size_t findNL;
	while(fin!=NULL){ //as long as theres still text to be read
		
		string str;
		getline(fin, str, ' ');
		
		findNL = str.find('\n');
        
		if (findNL != string::npos) {
			
			string str1 = "";
			string str2 = "";
			
			for (int i = 0; i < str.size(); i++) {

				if (i < findNL) {
					str1 += str[i];
				}
				
				if (i > findNL) {
					str2 += str[i];
				}
			}
			
			data.push_back(str1);
            time.push_back(str1.length());

            
			data.push_back(" ");
            time.push_back(SPACE_VAL);
            
            data.push_back(str2);
            time.push_back(str2.length());
            
            data.push_back(" ");
            time.push_back(SPACE_VAL);
			
		} else {
            
            data.push_back(str);
            time.push_back(str.length());
		}
	}
    
    cout << data.size() << endl;
    cout << time.size() << endl;

    
	times.loadFont("times.ttf", 120);
    
    word = 0;
	controlSpeed = 0.2;
    timer = 0;
    
    debug = true;
    
    bFwd = true;
    bPaused = false;
    
	ard.connect("/dev/tty.usbmodemfd121", 57600);

	ofAddListener(ard.EInitialized, this, &testApp::setupArduino);
	bSetupArduino	= false;
   
}

//--------------------------------------------------------------
void testApp::update(){

    updateArduino();
    
	if (ofGetFrameNum() > 120) {
		if (ofGetElapsedTimef() > timer) {
            
            if (bFwd) {
                if(word < data.size()){
                    word++;
                }
            } else {
                if(word < 1){
                     word--;
                }
            }
            
            timer = ofGetElapsedTimef() + (time[word] * controlSpeed);
		}
	}
    
    if (bPaused) {
        timer = ofGetElapsedTimef() + (time[word] * controlSpeed);
    }
    
}

//--------------------------------------------------------------
void testApp::setupArduino(const int & version) {
	ofRemoveListener(ard.EInitialized, this, &testApp::setupArduino);

    bSetupArduino = true;

    cout << ard.getFirmwareName() << endl;
    cout << "firmata v" << ard.getMajorFirmwareVersion() << "." << ard.getMinorFirmwareVersion() << endl;

    ard.sendDigitalPinMode(4, ARD_INPUT);

    ard.sendAnalogPinReporting(0, ARD_ANALOG);
    ard.sendAnalogPinReporting(1, ARD_ANALOG);

	ard.sendDigitalPinMode(6, ARD_OUTPUT);
    ard.sendDigitalPinMode(7, ARD_OUTPUT);

    ofAddListener(ard.EDigitalPinChanged, this, &testApp::digitalPinChanged);
    ofAddListener(ard.EAnalogPinChanged, this, &testApp::analogPinChanged);
}

//--------------------------------------------------------------
void testApp::updateArduino(){
    
    ard.update();
    
	if (bSetupArduino) {
        if(bPaused){
            ard.sendDigital(7, ARD_HIGH);
            ard.sendDigital(6, ARD_LOW);
        } else {
            ard.sendDigital(6, ARD_HIGH);
            ard.sendDigital(7, ARD_LOW);
        }
	}
    
}

//--------------------------------------------------------------
void testApp::digitalPinChanged(const int & pinNum) {
    if(ard.getDigital(4)){
        bPaused = !bPaused;
    }
}

//--------------------------------------------------------------
void testApp::analogPinChanged(const int & pinNum) {

    float speed = ofMap(ard.getAnalog(0), 0, 1024, 0.001, 1.0);
    controlSpeed = speed;

    if (ard.getAnalog(1) > 512) {
        bFwd = false;
    } else {
        bFwd = true;
    }
  
}

//--------------------------------------------------------------
void testApp::draw(){

	ofSetColor(0, 0, 0);
	
	ofRectangle rect = times.getStringBoundingBox(data[word], 0,0);

	times.drawString(data[word], (ofGetWidth()/2) - (rect.width/2), (ofGetHeight()/2)+60);
    
    if(debug){
        ofDrawBitmapString("word = " + ofToString(word), 10, 30);
        ofDrawBitmapString("control speed = " + ofToString(controlSpeed), 10, 50);
        ofDrawBitmapString("this word = " + ofToString(time[word] * controlSpeed), 10, 70);
        ofDrawBitmapString("next change = " + ofToString(timer), 10, 90);
        ofDrawBitmapString("current time = " + ofToString(ofGetElapsedTimef()), 10, 110);
        ofDrawBitmapString("paused = " + ofToString(bPaused), 10, 130);
        ofDrawBitmapString("forward = " + ofToString(bFwd), 10, 150);
    }
    
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

	if (key == OF_KEY_UP) {
		controlSpeed += 0.01;
	}
	if (key == OF_KEY_DOWN) {
		controlSpeed -= 0.01;
	}
    
    if (key == ' ') {
        debug = !debug;
    }

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}
