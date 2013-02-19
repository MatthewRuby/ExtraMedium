#include "testApp.h"

static int total_words = 0;
static int total_delays = 0;

void loadBook(vector<string> *w, vector<float> *t, string path){
    if(w->size() > 0){
        w->clear();
    }
    if(t->size() > 0){
        t->clear();
    }

    ifstream data;
    data.open(ofToDataPath(path).c_str());
    
    size_t findNL;
	while( data != NULL) {
        string str;
		getline(data, str, ' ');
		findNL = str.find('\n');
        
		if(findNL != string::npos){
			string str1 = "";
			string str2 = "";
			for(int i = 0; i < str.size(); i++){
				if(i < findNL){
					str1 += str[i];
				}
				if(i > findNL){
					str2 += str[i];
				}
			}
            
			w->push_back(str1);
			t->push_back(str.length());
            
			w->push_back(" ");
			if(str1[str1.length()-1] == '.' || str1[str.length()-1] == ','){
				t->push_back(PERIOD_VAL);
			} else {
				t->push_back(SPACE_VAL);
			}
            
			w->push_back(str2);
			t->push_back(str2.length());
            
			w->push_back(" ");
			if(str2[str2.length()-1] == '.' || str2[str2.length()-1] == ','){
				t->push_back(PERIOD_VAL);
			} else {
				t->push_back(SPACE_VAL);
			}
		} else {
			w->push_back(str);
			t->push_back(str.length());
			w->push_back(" ");
			if(str[str.length()-1] == '.' || str[str.length()-1] == ','){
				t->push_back(PERIOD_VAL);
			} else {
				t->push_back(SPACE_VAL);
			}
        }
	}
    
    total_words = w->size();
	total_delays = t->size();
    
}

//--------------------------------------------------------------
void testApp::setup(){
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofBackground(0,0,0);
	ofSetRectMode(OF_RECTMODE_CENTER);
    ofEnableSmoothing();

    titleIndex = 0;
    bookData[0] = "SemplicaGirls.txt";
    bookData[1] = "HarrisonBerg.txt";
    bookData[2] = "DoAndroids.txt";
    bookData[3] = "ATaleOf.txt";
    
    titles[0] = "THE SEMPLICA-GIRL\nDIARIES by\nGeorge Saunders";
    titles[1] = "HARRISON BERGERON\nby Kurt Vonnegut";
    titles[2] = "DO ANDROIDS DREAM\nOF ELECTRIC SHEEP\nby Philip K. Dick";
    titles[3] = "A TALE OF TWO\nCITIES by\nCharles Dickens";

	index = 0;
	timer = 0;
	times.loadFont("times.ttf", 60);
	ctrlSpeed = 0.25;
	debug = true;
    currentDelay = 0;

    bFwd = true;
    bPaused = true;
    bStarted = false;
    
	ard.connect("/dev/tty.usbmodemfd121", 57600);

	ofAddListener(ard.EInitialized, this, &testApp::setupArduino);
	bSetupArduino	= false;

}

//--------------------------------------------------------------
void testApp::update(){

    updateArduino();
    

    if(word.size() > 0 && delay.size() > 0) {
        
        if (ofGetElapsedTimef() > timer) {
            
            if (bFwd) {
                if(index < word.size()){
                    index++;
                    currentDelay = log(1 + delay[index]) * ctrlSpeed;
                    timer = ofGetElapsedTimef() + currentDelay;
                }
            } else {
                if(index < 1){
                    index++;
                    currentDelay = log(1 + delay[index]) * ctrlSpeed;
                    timer = ofGetElapsedTimef() + currentDelay;
                }
            }

        }
        
                
        if (bPaused || !bStarted) {
            timer = ofGetElapsedTimef() + (delay[index] * ctrlSpeed);
        }
        
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
        if(!bStarted){
            bStarted = true;
            bPaused = false;
            loadBook(&word, &delay, bookData[titleIndex]);
        }
    }
}

//--------------------------------------------------------------
void testApp::analogPinChanged(const int & pinNum) {

    float speed = ofMap(ard.getAnalog(0), 0, 1024, 0.001, 1.0);
    ctrlSpeed = speed;

    
    int enumTitle = ofMap(ard.getAnalog(1), 0, 1024, 0, 4);
    if(titleIndex != enumTitle){
        bStarted = false;
        bPaused = true;
        titleIndex = enumTitle;
    }
    
    // Stub For Back
/*    historyPos = ard.getAnalog(1);
    if(bPaused && prevHistory != historyPos){
        cout << historyPos << endl;
//        index = ofMap(ard.getAnalog(1), 0, 1024, 0, word.size());
    }
    if (ard.getAnalog(1) > 512) {
        bFwd = false;
    } else {
        bFwd = true;
    }
    prevHistory = historyPos;
*/
}

//--------------------------------------------------------------
void testApp::draw(){

	ofSetColor(255,255,255);

	if(debug){
        
		ofDrawBitmapString("Program Time = " + ofToString(ofGetElapsedTimef(),2), 10, ofGetHeight() - 50);
		ofDrawBitmapString("Total Words = " + ofToString(total_words), 10, ofGetHeight() - 30);
		ofDrawBitmapString("Total Delays = " + ofToString(total_delays), 10, ofGetHeight() - 10);
        
        if(word.size() > 0 && delay.size() > 0) {
            ofDrawBitmapString("Word Index = " + ofToString(index), 250, ofGetHeight() - 50);
            ofDrawBitmapString("Current = " + ofToString(word[index]), 250, ofGetHeight() - 30);
            
            ofDrawBitmapString("Control Speed = " + ofToString(ctrlSpeed, 2), 500, ofGetHeight() - 50);
            ofDrawBitmapString("Word Delay = " + ofToString(delay[index]), 500, ofGetHeight() - 30);
            ofDrawBitmapString("This Delay = " + ofToString(currentDelay, 2), 500, ofGetHeight() - 10);
        }
        ofDrawBitmapString("Paused = " + ofToString(bPaused), 750, ofGetHeight() - 50);
		ofDrawBitmapString("Forward = " + ofToString(bFwd), 750, ofGetHeight() - 30);
        
        ofDrawBitmapString("History = " + ofToString(historyPos), 750, ofGetHeight() - 10);
        
	}
    
    if(bStarted && word.size() > 0 && delay.size() > 0){
        ofRectangle rect = times.getStringBoundingBox(word[index], 0, 0);
        times.drawString(word[index], (ofGetWidth()/2) - (rect.width/2), (ofGetHeight()/2) + 30);
    } else {
        
        ofRectangle rect = times.getStringBoundingBox(titles[titleIndex], 0, 0);
        times.drawString(titles[titleIndex], (ofGetWidth()/2) - (rect.width/2), (ofGetHeight()/2) + 30);
        
    }

	

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

	if(key == ' '){
		debug = !debug;
	}
    if(key == 's'){
		bStarted = !bStarted;
        
        if (bStarted) {
            loadBook(&word, &delay, bookData[titleIndex]);
        }
	}
	if(key == OF_KEY_UP){
		ctrlSpeed += 0.01;
	}
	if(key == OF_KEY_DOWN){
		ctrlSpeed -= 0.01;
	}
    if(key == OF_KEY_LEFT){
        bStarted = false;
        titleIndex--;
        if (titleIndex < 0) {
            titleIndex = 3;
        }
	}
	if(key == OF_KEY_RIGHT){
        bStarted = false;
        titleIndex++;
        if (titleIndex > 3) {
            titleIndex = 0;
        }
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}
