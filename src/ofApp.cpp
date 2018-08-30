#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofBackground(50, 0);

    ofDisableArbTex(); // we need GL_TEXTURE_2D for our models coords.

    animationPosition = 0;

    model.loadModel("untitled.dae", false);
    model.setPosition(ofGetWidth() * 0.5, (float)ofGetHeight() * 0.5 , 0);
    model.setLoopStateForAllAnimations(OF_LOOP_NORMAL);
    model.setScale(100,100,100);
    model.playAllAnimations();
}

//--------------------------------------------------------------
void ofApp::update(){
    model.update();

    mesh = model.getCurrentAnimatedMesh(0);
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);

    ofEnableDepthTest();

    light.enable();
    ofEnableSeparateSpecularLight();

    model.drawFaces();

    ofSetColor(255, 255, 255 );
    stringstream ss;
    ss << "FPS: " << ofToString(ofGetFrameRate(),0) <<endl<<endl;
    ss << "num of animations in this model: " + ofToString(model.getAnimationCount());
    ofDrawBitmapString(ss.str().c_str(), 20, 20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
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

