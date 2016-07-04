#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    loadImages();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
//MARK: - Image Loading

void ofApp::loadImages() {
    imagesDir = ofDirectory("Head-Images/");
    imagesDir.allowExt("png");
    imagesDir.listDir();
    
    ofLogNotice() << "Directory: " << imagesDir.getAbsolutePath();
    
    for (int i = 0; i < imagesDir.size(); i++) {
        ofImage * anImage = new ofImage(imagesDir.getPath(i));
        images.push_back(anImage);
    }
    
    
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

ofApp::~ofApp() {
    for(auto anImage: images) {
        delete anImage;
    }
}