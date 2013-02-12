#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofSetRectMode(OF_RECTMODE_CENTER);
	
	ofBackground(255, 255, 255);

	
	
	dict.open(ofToDataPath("phones.txt").c_str());
	while(dict != NULL){
		string w; //declare a string for storage
		getline(dict, w, '\n');
		
		int pos = w.find(" ");
        if (pos > 0) {
            string word = w.substr(0,pos);
            string phone = w.substr(pos,w.length());

            string sound = w.substr(pos);
            int length = sound.length();
         
            struct word t;
            t.term = word;
            t.sound = sound;
            t.len = length;
            terms.push_back(t);
            //cout << word << " = " << sound << " -> " << length << endl;
        }
	}
	
	
	
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
            cout << "add data str 1" << endl;
            bool foundTerm = false;
            for (int i = 0; i < terms.size(); i++) {
                if (terms[i].term == str1) {
                    foundTerm = true;
                    int l = terms[i].len;
                    time.push_back(l);
                    cout << "add time found phone" << endl;
                }
            }
            if (foundTerm == false) {
                int l = str1.length();
                time.push_back(l);
                cout << "add time phone not found " << endl;
            }
            
			data.push_back(" ");
            cout << "add data space" << endl;
            time.push_back(SPACE_VAL);
            
            foundTerm = false;
			data.push_back(str2);
            cout << "add data str 2" << endl;
            for (int i = 0; i < terms.size(); i++) {
                if (terms[i].term == str2) {
                    foundTerm = true;
                    int l = terms[i].len;
                    time.push_back(l);
                    cout << "add time found phone" << endl;
                }
            }
            if (foundTerm == false) {
                int l = str2.length();
                time.push_back(l);
                cout << "add time phone not found " << endl;
            }
			
		} else {
			
			data.push_back(str);
            cout << "add data str" << endl;
            bool foundTerm = false;
			data.push_back(str);
            for (int i = 0; i < terms.size(); i++) {
                if (terms[i].term == str) {
                    foundTerm = true;
                    int l = terms[i].len;
                    time.push_back(l);
                    cout << "add time found phone" << endl;
                }
            }
            if (foundTerm == false) {
                int l = str.length();
                time.push_back(l);
                cout << "add time phone not found " << endl;
            }
		}
	}
    
    cout << data.size() << endl;
    cout << time.size() << endl;
/*
	size_t findPageNum;
	
	for (int i = 0; i < data.size(); i++) {
		 if (isdigit(data[i][0]) != 0) {
			 if (data[i+1] == "of") {
				 if (isdigit(data[i+2][0]) != 0) {
					 if (data[i+7] == "Cities") {
						 data.erase(data.begin()+i, data.begin()+i + 8);
					 }
				 }
			 }
		 }
	}
*/
	times.loadFont("times.ttf", 120);
    
    word = 0;
	controlSpeed = 0.2;
    timer = 0;
    
    debug = false;
}

//--------------------------------------------------------------
void testApp::update(){

	if (ofGetFrameNum() > 120) {
		if (ofGetElapsedTimef() > timer) {
            cout << "change" << endl;
            word++;
            timer = ofGetElapsedTimef() + (time[word] * controlSpeed);
		}
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
