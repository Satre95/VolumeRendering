#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    loadImages();
    prepareTexture();
    ofLogNotice() << glGetString(GL_VERSION);
    
    volShader.load("Shaders/VolShader.vert", "Shaders/VolShader.frag");
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
    
    for (int i = 0; i < imagesDir.size(); i++) {
        ofImage * anImage = new ofImage(imagesDir.getPath(i));
        images.push_back(anImage);
    }
    
    
}

void ofApp::prepareTexture() {
    //make get all the pixel data of all images into a single array.
    std::vector<char> pixelData; //Images are all greyscale, so only need 1 color value per pixel to save memory.
    //Load the pixel data into 1 unified array.
    preparePixelData(pixelData);
    
    glEnable(GL_TEXTURE_3D);
    
    glGenTextures(1, &volTexture);
    glActiveTexture(GL_TEXTURE0);
    
    glBindTexture(GL_TEXTURE_3D, volTexture);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
        int width = images[0]->getWidth();
        int height = images[0]->getHeight();
        glTexImage3D(GL_TEXTURE_3D, 0, GL_RED, width, height, images.size(), 0, GL_RED, GL_BYTE, (GLvoid*)&pixelData[0]);
    
    glBindTexture(GL_TEXTURE_3D, 0);
    
    volShader.setUniformTexture("volTexture", GL_TEXTURE_3D, volTexture, 0);
    
}

void ofApp::preparePixelData(std::vector<char> & pixelData) {
    for(ofImage * anImage: images) {
        ofPixels & pixels = anImage->getPixels();
        
        for (int i = 0; i < pixels.size(); i++) {
            char val = pixels[i];
            pixelData.push_back(val);
        }
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