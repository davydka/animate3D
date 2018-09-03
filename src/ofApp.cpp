#include "ofApp.h"

int val;
string translate;
string scale;
string rotx;
string roty;
string rotz;

ofVec3f camPos;


ofPlanePrimitive plane;
ofLight pointLight;
ofLight pointLight2;
ofLight pointLight3;
ofMaterial material;

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofBackground(50, 0);

    ofDisableArbTex(); // we need GL_TEXTURE_2D for our models coords.

    animationPosition = 0;

    model.loadModel("untitled.dae", false);
    // model.setPosition(ofGetWidth() * 0.5, (float)ofGetHeight() * 0.5 , 0);
    model.setLoopStateForAllAnimations(OF_LOOP_NORMAL);
    model.setScale(100,100,100);
    model.playAllAnimations();

    cout << ofToString(model.getAssimpScene()) << endl;

    if(xml.loadFile("untitled.dae")){
      cout << "xml file loaded" << endl;
    }
    else {
      cout << "can't load xml file" << endl;
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

    cout << "cam translate: " + translate << endl;
    cout << "cam scale: " + scale << endl;
    cout << "rotx :" + rotx << endl;
    cout << "roty :" + roty << endl;
    cout << "rotz :" + rotz << endl;

    vector<string> transPos = ofSplitString(translate, " ");
    // cam.setScale(100,100,100);
    /*
    camPos.set(
      ofToFloat(transPos[0]),
      ofToFloat(transPos[1]),
      ofToFloat(transPos[2])
    );
    */
    /*
    camPos.set(
        7.48*100,
        -6.5*100,
        5.34*100
    );
    */
    cam.setFov(35);
    cam.setTarget(ofVec3f(0,0,0));
    // cam.rotateDeg(63.6, 1, 0, 1);
    // cam.rotateDeg(0, 0, 1, 0);
    // cam.rotateDeg(46.7, 0, 0, 1);
    // cam.rotateDeg(77.4, 0.773, 0.334, 0.539);
    // cam.rotate(ofQuaternion(0.484, 0.209, 0.337, 0.780));

    /*
    camPos.set(
        7.48*100,
        -6.5*100,
        5.34*100
    );
    */
    // cam.setPosition(camPos);
    // cam.tiltDeg(63.6); // X
    // cam.panDeg(0); // Y
    // cam.rollDeg(46.7); // Z

    plane.set(640, 640);
    plane.setPosition(0, 0, 0);
    plane.tiltDeg(90);
    plane.setResolution(2, 2);

    ofSetSmoothLighting(true);
    pointLight.setDiffuseColor( ofFloatColor(.85, .85, .55) );
    pointLight.setSpecularColor( ofFloatColor(1.f, 1.f, 1.f));

    pointLight2.setDiffuseColor( ofFloatColor( 238.f/255.f, 57.f/255.f, 135.f/255.f ));
    pointLight2.setSpecularColor(ofFloatColor(.8f, .8f, .9f));

    pointLight3.setDiffuseColor( ofFloatColor(19.f/255.f,94.f/255.f,77.f/255.f) );
    pointLight3.setSpecularColor( ofFloatColor(18.f/255.f,150.f/255.f,135.f/255.f) );

    // shininess is a value between 0 - 128, 128 being the most shiny //
    material.setShininess( 120 );
    // the light highlight of the material //
    material.setSpecularColor(ofColor(255, 255, 255, 255));
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
    ofEnableSeparateSpecularLight();

    cam.begin();

    light.enable();
    pointLight.enable();
    pointLight2.enable();
    pointLight3.enable();




    // cam.setPosition(camPos);
    material.begin();
    ofNoFill();
    model.drawFaces();
    plane.drawFaces();
    material.end();

    light.disable();
    pointLight.disable();
    pointLight2.disable();
    pointLight3.disable();

    cam.end();

    ofDisableDepthTest();
    ofDisableLighting();
    ofDisableSeparateSpecularLight();

    // ofSetColor(255);
    stringstream ss;
    ss << "FPS: " << ofToString(ofGetFrameRate(),0) <<endl;
    ss << "animations: " + ofToString(model.getAnimationCount()) << endl;

    ss << "cam pos: " + ofToString(cam.getPosition()) << endl;

    ss << "cam pitch/X: " + ofToString(cam.getPitchDeg()) << endl;
    ss << "cam heading/Y: " + ofToString(cam.getHeadingDeg()) << endl;
    ss << "cam roll/Z: " + ofToString(cam.getRollDeg()) << endl;
    ss << "cam FOV: " + ofToString(cam.getFov()) << endl;
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

