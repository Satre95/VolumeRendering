#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    ~ofApp();

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
		
    //-----------------------------------------
    //Volume Rendering.
    std::vector<ofImage*> images;
    ofDirectory imagesDir;
    
    //The 3D texture that will hold all the images.
    GLuint volTexture;
    
    void loadImages();
    void prepareTexture();
    
    ofEasyCam camera;
    ofShader volShader;
    
private:
    void preparePixelData(std::vector<char> & pixelData);
};
