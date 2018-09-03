#include "ofApp.h"

int val;
string translate;
string scale;
string rotx;
string roty;
string rotz;

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

    cout << ofToString(model.getAssimpScene()) << endl;
    // cout << ofToString(model.getMeshCount()) << endl;

    if(xml.loadFile("untitled.dae")){
      cout << "file loaded" << endl;
    }
    else {
      cout << "can't load file" << endl;
    }
    
    xml.pushTag("COLLADA", 0);
    xml.pushTag("library_visual_scenes", 0);
    xml.pushTag("visual_scene", 0);
    /*
    vector<string> outNames;
    xml.getAttributeNames("node", outNames);
    cout << ofToString(outNames) << endl;
    */
    int num = xml.getNumTags("node");
    for( int i = 0; i < num; i++ ) {
      if(xml.getAttribute("node", "id", "", i) == "Camera") {
        xml.pushTag("node", i);
        translate = xml.getValue("translate", "", 0);
        scale = xml.getValue("scale", "", 0);

        int rots = xml.getNumTags("rotate");
        for( int ii = 0; ii < rots; ii++ ) {
          // cout << xml.getAttribute("rotate", "sid", "", ii) << endl;
          if(xml.getAttribute("rotate", "sid", "", ii) == "rotationX") {
            rotx = xml.getValue("rotate", "", ii);
          }
          if(xml.getAttribute("rotate", "sid", "", ii) == "rotationY") {
            roty = xml.getValue("rotate", "", ii);
          }
          if(xml.getAttribute("rotate", "sid", "", ii) == "rotationZ") {
            rotz = xml.getValue("rotate", "", ii);
          }
        }

        xml.popTag();
      }
    }
    xml.popTag();
    xml.popTag();
    xml.popTag();

    cout << translate << endl;
    cout << scale << endl;
    cout << rotx << endl;
    cout << roty << endl;
    cout << rotz << endl;
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

    ofDisableDepthTest();
    light.disable();
    ofDisableLighting();
    ofDisableSeparateSpecularLight();

    // ofSetColor(255);
    stringstream ss;
    ss << "FPS: " << ofToString(ofGetFrameRate(),0) <<endl;
    ss << "animations: " + ofToString(model.getAnimationCount());
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

