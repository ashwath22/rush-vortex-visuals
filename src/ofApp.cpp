#include "ofApp.h"
int bufferSize = 256;
long int timer = 0;
int toggle = 1;
int posToggle = 1;
int i = 0;
int j = 0;
int difference = 0;
int limit = 0;
int limits[700] = {0};
//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofSetFrameRate(60);
    ofSetBackgroundAuto(false);
    ofSetCircleResolution(60);
    
    shapes_num = 700;
    radius = 1;
    //    pos = ofVec3f(ofGetWidth(), ofGetHeight(), 1000);
    rot = ofVec3f(720, 720, 720);
    speed = 0.0001;
    color_mode = 0;
    after_img = 50;
    
    soundStream.printDeviceList();
    
    left.assign(bufferSize, 0.0);
    right.assign(bufferSize, 0.0);
    volHistory.assign(400, 0.0);
    
    bufferCounter    = 0;
    drawCounter        = 0;
    smoothedVol     = 0.0;
    scaledVol        = 0.0;
    
    ofSoundStreamSettings settings;
    auto devices = soundStream.getDeviceList();
    settings.setInDevice(devices[2]);
    settings.setInListener(this);
    settings.sampleRate = 44100;
    settings.numOutputChannels = 0;
    settings.numInputChannels = 2;
    settings.bufferSize = bufferSize;
    soundStream.setup(settings);
    thread.startThread();
}

//--------------------------------------------------------------
void ofApp::update(){
    
    while (shapes.size() != shapes_num){
        if (shapes.size() < shapes_num) {
            MyShape s;
            shapes.push_back(s);
        } else if (shapes.size() > shapes_num) {
            shapes.pop_back();
        }
    }
    if (toggle == 1){
        //        limits[i] = {ofGetHeight()};
        thread.startThread();
    }else if(toggle == -1){
        //        limit = ofMap( ofGetHeight(), 0, 1000, 0, right[2]*5000);
        //        difference = ofGetHeight() - limit;
        //        ofLog(OF_LOG_NOTICE, "limit: " + ofToString(limit));
        //        ofLog(OF_LOG_NOTICE, "difference: " + ofToString(difference));
        //
        //        for(i=0; i < shapes.size(); i++){
        //            limits[i] = limit - i;
        //        }
        thread.startThread();
    }
    for (i=0; i < shapes.size(); i++) {
        shapes[i].update();
        shapes[i].setRadius(radius);
        if(toggle == -1 && j < ofGetHeight()){
            shapes[i].setPosAmp(ofVec3f( ofGetWidth(), j, 1000));
        } else if (toggle == 1){
            shapes[i].setPosAmp(ofVec3f( ofGetWidth(), ofGetHeight(), 1000));
            j=0;
        }
        shapes[i].setRotAmp(rot);
        shapes[i].setSpeedAmp(speed);
        shapes[i].setColorMode(color_mode);
    }
    j++;
}

void ToggleThread::threadedFunction() {
    //    posToggle = 0;
    timer = (int)ofGetElapsedTimef();
    while((int)ofGetElapsedTimef() - timer < 5 ){
    }
    toggle *= -1;
    timer = 0;
    //    posToggle = 1;
}

void ofApp::draw(){
    ofSetColor( 255, 255, 255 );
    ofDrawBitmapString("timer: " + ofToString((int)ofGetElapsedTimef() - timer < 5), 4, 30);
    ofDrawBitmapString("toggle: " + ofToString(toggle), 4, 40);
    //    if(right[10]>2){
    //        ofLog(OF_LOG_NOTICE, "right[10] " + ofToString(right[10]));
    //        ofDrawBitmapString("right[10]: " + ofToString(right[10]), 4, 60);
    //    }
    //    ofLog(OF_LOG_NOTICE, "right[10] " + ofToString(right[2]));
    
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    
    for (int i = 0; i < shapes.size(); i++) {
        shapes[i].draw();
    }
    
    ofPopMatrix();
    
    ofDrawRectangle(0, ofGetHeight()/2, 2000, right[10]*20);
    ofDrawRectangle(0, ofGetHeight()/2, 2000, -right[10]*20);
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofFill();
    ofSetColor(0, after_img);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 's'){
        img.grabScreen(0,0,ofGetWidth(),ofGetHeight());
        img.save("pic" + ofToString(imgcount) + ".png", OF_IMAGE_QUALITY_BEST);
        imgcount++;
    }
    
    if (key == 'g') {
        guidraw = false;
    }
}

void ofApp::audioIn(ofSoundBuffer & input){
    
    float curVol = 0.0;
    // samples are "interleaved"
    int numCounted = 0;
    //lets go through each sample and calculate the root mean square which is a rough way to calculate volume
    float hold[256];
    
    
    for (size_t i = 0; i < bufferSize; i++){
        hold[i] = input[i];
        hold[i] *= 0.97;    //Slow decreasing
        hold[i] = max( hold[i], input[i] );
        if (hold[i] < 0){
            hold[i] *= -1;
        }
    }
    
    for (size_t i = 0; i < bufferSize; i++){
        //        left[i]        = input[i*2]*0.5;
        left[i] = hold[i]*0.95;
        right[i] = hold[i+1]*0.95;
        
        curVol += left[i] * left[i];
        curVol += right[i] * right[i];
        numCounted+=2;
    }
    
    //this is how we get the mean of rms :)
    curVol /= (float)numCounted;
    
    // this is how we get the root of rms :)
    curVol = sqrt( curVol );
    
    smoothedVol *= 0.93;
    smoothedVol += 0.07 * curVol;
    
    bufferCounter++;
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
void ofApp::exit() {
    // stop the thread
    thread.stopThread();
}

