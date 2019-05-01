#pragma once

#include "ofMain.h"
#include "MyShape.h"

class ToggleThread : public ofThread {
    // the thread function
    void threadedFunction();
};

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void exit();
    
    //  ofxPanel gui;
    
    ofParameter<float> radius;
    
    ofParameter<int> shapes_num;
    int old_num;
    
    ofParameter<ofVec3f> pos;
    ofParameter<ofVec3f> rot;
    ofParameter<float> speed;
    ofParameter<int> after_img;
    ofParameter<bool> color_mode;
    //ofxToggle color_mode;
    
    vector<MyShape> shapes;
    
    ofFbo image;
    bool guidraw;
    ofImage img;
    int imgcount;
    //    ofSoundPlayer beat;
    void audioIn(ofSoundBuffer & input);
    
    vector <float> left;
    vector <float> right;
    vector <float> volHistory;
    
    int     bufferCounter;
    int     drawCounter;
    
    float smoothedVol;
    float scaledVol;
    
    ofSoundStream soundStream;
    ToggleThread thread;
    
};
