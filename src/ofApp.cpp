#include "ofApp.h"

ofVec3f camPos;
string translate;
string scale;
string rotx;
string roty;
string rotz;

ofPlanePrimitive plane;

//--------------------------------------------------------------
void ofApp::setup(){
  ofSetLogLevel(OF_LOG_VERBOSE);
  ofBackground(50, 0);

  ofDisableArbTex(); // we need GL_TEXTURE_2D for our models coords.

  animationPosition = 0;

  model.loadModel("untitled.dae", false);
  model.disableMaterials();
  // model.setPosition(ofGetWidth() * 0.5, (float)ofGetHeight() * 0.5 , 0);
  model.setLoopStateForAllAnimations(OF_LOOP_NORMAL);
  model.setScale(100,100,100);
  model.setRotation(0,180,0,0,1);
  model.playAllAnimations();

  cout << ofToString(model.getAssimpScene()) << endl;






  xml.loadFile("untitled.dae");
  xml.pushTag("COLLADA", 0);
  xml.pushTag("library_visual_scenes", 0);
  xml.pushTag("visual_scene", 0);

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

  vector<string> transPos = ofSplitString(translate, " ");
  vector<string> Xrot = ofSplitString(rotx, " ");
  vector<string> Yrot = ofSplitString(roty, " ");
  vector<string> Zrot = ofSplitString(rotz, " ");

  xml.popTag();
  xml.popTag();
  xml.popTag();





  cam.setAutoDistance(false);
  cam.setFov(35);
  cam.setPosition(
    0,
    ofToFloat(transPos[2])*100, // y value in blender is Z value in OF
    -(ofToFloat(transPos[1]))*100 // z value in blender is negative Y value in OF
  );
  cam.tiltDeg(ofToFloat(Xrot[3]) - 90); // X for OF, X - 90 from blender
  cam.panDeg(ofToFloat(Zrot[3])); // Y for OF, Z from blender
  cam.rollDeg(-(ofToFloat(Yrot[3]))); // Z for OF, negative Y from blender

  plane.set(640, 640);
  plane.setPosition(0, 0, 0);
  plane.tiltDeg(90);
  plane.setResolution(64, 64);
}

//--------------------------------------------------------------
void ofApp::update(){
  model.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
  ofSetColor(255);

  ofEnableDepthTest();
  ofEnableSeparateSpecularLight();

  cam.begin();


  // cam.setPosition(camPos);
  ofSetColor(0, 255, 0, 255);
  model.draw(OF_MESH_WIREFRAME);


  ofSetColor(0, 128, 255, 255);
  plane.draw(OF_MESH_WIREFRAME);


  cam.end();

  ofDisableDepthTest();
  ofDisableLighting();
  ofDisableSeparateSpecularLight();

  ofSetColor(255);
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

