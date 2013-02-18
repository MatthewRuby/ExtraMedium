#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofBackground(255,255,255);

	ofSetRectMode(OF_RECTMODE_CENTER);

	book.open(ofToDataPath("dick.txt").c_str());
	size_t findNL;
	while( book != NULL) {
		string str;
		getline(book, str, ' ');
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

			word.push_back(str1);
			delay.push_back(str.length());

			word.push_back(" ");
			if(str1[str1.length()-1] == '.' || 
str1[str.length()-1] == ','){
				delay.push_back(PERIOD_VAL);
			} else {
				delay.push_back(SPACE_VAL);
			}

			word.push_back(str2);
			delay.push_back(str2.length());

			word.push_back(" ");
			if(str2[str2.length()-1] == '.' || 
str2[str2.length()-1] == ','){
				delay.push_back(PERIOD_VAL);
			} else {
				delay.push_back(SPACE_VAL);
			}

		} else {

			word.push_back(str);
			delay.push_back(str.length());

			word.push_back(" ");
			if(str[str.length()-1] == '.' || 
str[str.length()-1] == ','){
				delay.push_back(PERIOD_VAL);
			} else {
				delay.push_back(SPACE_VAL);
			}

		}
	}

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
		ofDrawBitmapString(ofToString(ofGetElapsedTimef(),2), 100, 
75);
		ofDrawBitmapString("Total Words = " + 
ofToString(total_words), 100, 25);
		ofDrawBitmapString("Total Delays = " + 
ofToString(total_delays), 100, 50);
		ofDrawBitmapString("Word = " + ofToString(index), 100, 
100);
		ofDrawBitmapString("Current = " + ofToString(word[index]), 
100, 125);
		ofDrawBitmapString("Word Delay = " + 
ofToString(delay[index]), 100, 150);
		ofDrawBitmapString("Control Speed = " + 
ofToString(ctrlSpeed), 100, 175);
		ofDrawBitmapString("This Delay = " + 
ofToString(currentDelay), 100, 200);
	}
/*
	for(int i = 1; i < 20; i++){
		ofDrawBitmapString(ofToString(log(i)), 200, 10 + i * 20);
	}
*/
	ofRectangle rect = times.getStringBoundingBox(word[index], 0, 0);
	times.drawString(word[index], (ofGetWidth()/2) - (rect.width/2), 
(ofGetHeight()/2) + 30);
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

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

