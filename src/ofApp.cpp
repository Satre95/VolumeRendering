#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
//    loadImages();
//    prepareTexture();
    ofLogNotice() << "Using OpenGL version: " << glGetString(GL_VERSION);
    
    ofSetFrameRate(60);
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    imageSequence.init("Head-Images/head-", 3, ".png", 0);
    volWidth = imageSequence.getWidth();
    volHeight = imageSequence.getHeight();
    volDepth = imageSequence.getSequenceLength();
    
    volData = std::vector<unsigned char>(volWidth * volHeight * volDepth * 4);
    
    for (int z = 0; z < volDepth; z++) {
        imageSequence.loadFrame(z);
        
        for (int x = 0; x < volWidth; x++) {
            for (int y = 0; y < volHeight; y++) {
                int pixelIndex = ( ( x + volWidth * y ) + z * volWidth * volHeight ) * 4;
                int sample = imageSequence.getPixels()[x+y*volWidth];
                ofColor c(sample);
                
                volData[pixelIndex] = c.r;
                volData[pixelIndex+1] = c.g;
                volData[pixelIndex+2] = c.b;
                volData[pixelIndex+3] = sample;
            }
        }
    }
    
    headVolume.setup(volWidth, volHeight, volDepth, ofVec3f(1,1,2),true);
    headVolume.updateVolumeData(&volData[0],volWidth,volHeight,volDepth,0,0,0);
    headVolume.setRenderSettings(1.0, 1.0, 0.75, 0.1);
    
    camera.setDistance(1000);
    camera.enableMouseInput();
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofClear(0, 0, 0);
//    ofColor centerColor = ofColor(85, 78, 68);
    ofColor centerColor(185, 131, 118);
    ofColor edgeColor(0);
    ofBackgroundGradient(centerColor, edgeColor, OF_GRADIENT_CIRCULAR);
    
    camera.begin();
    headVolume.drawVolume(0, 0, 0, ofGetHeight(), 0);
    camera.end();
     
    
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