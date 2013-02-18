#include "testApp.h"

void loadBook(vector<string> *w, vector<float> *t, string path){
    if(w->size() > 0){
        w->empty();
    }
    if(t->size() > 0){
        t->empty();
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
}

//--------------------------------------------------------------
void testApp::setup(){
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofBackground(255,255,255);
	ofSetRectMode(OF_RECTMODE_CENTER);

    
    titleIndex = 0;
    bookData[0] = "SemplicaGirls.txt";
    bookData[1] = "HarrisonBerg.txt";
    bookData[2] = "DoAndroids.txt";
    bookData[3] = "ATaleOf.txt";
    
    titles[0] = "THE SEMPLICA-GIRL DIARIES\n by George Saunders";
    titles[1] = "HARRISON BERGERON\n by Kurt Vonnegut";
    titles[2] = "DO ANDROIDS DREAM OF ELECTRIC SHEEP\n by Philip K. Dick";
    titles[3] = "A TALE OF TWO CITIES\n by Charles Dickens";

    loadBook(&word, &delay, bookData[titleIndex]);
    
	total_words = word.size();
	total_delays = delay.size();
    
	index = 0;
	timer = 0;
	times.loadFont("times.ttf", 60);
	ctrlSpeed = 0.25;
	debug = true;
	currentDelay = log(1 + delay[index]) * ctrlSpeed;

}

//--------------------------------------------------------------
void testApp::update(){

	if(ofGetElapsedTimef() > 5.0){

		if(ofGetElapsedTimef() > timer){
			index++;
			currentDelay = log(1 + delay[index]) * ctrlSpeed;
			timer = ofGetElapsedTimef() + currentDelay;
		}

	}
}

//--------------------------------------------------------------
void testApp::draw(){

	ofSetColor(0,0,0);

	if(debug){
        
		ofDrawBitmapString("Program Time = " + ofToString(ofGetElapsedTimef(),2), 10, ofGetHeight() - 50);
		ofDrawBitmapString("Total Words = " + ofToString(total_words), 10, ofGetHeight() - 30);
		ofDrawBitmapString("Total Delays = " + ofToString(total_delays), 10, ofGetHeight() - 10);
        
		ofDrawBitmapString("Word Index = " + ofToString(index), 250, ofGetHeight() - 50);
		ofDrawBitmapString("Current = " + ofToString(word[index]), 250, ofGetHeight() - 30);
        
        ofDrawBitmapString("Control Speed = " + ofToString(ctrlSpeed), 500, ofGetHeight() - 50);
		ofDrawBitmapString("Word Delay = " + ofToString(delay[index]), 500, ofGetHeight() - 30);
		ofDrawBitmapString("This Delay = " + ofToString(currentDelay), 500, ofGetHeight() - 10);
        
	}

    
    
	ofRectangle rect = times.getStringBoundingBox(word[index], 0, 0);
	times.drawString(word[index], (ofGetWidth()/2) - (rect.width/2), (ofGetHeight()/2) + 30);

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

	if(key == ' '){
		debug = !debug;
	}
	if(key == OF_KEY_UP){
		ctrlSpeed += 0.01;
	}
	if(key == OF_KEY_DOWN){
		ctrlSpeed -= 0.01;
	}
    if(key == OF_KEY_LEFT){

	}
	if(key == OF_KEY_RIGHT){

	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}
