#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetVerticalSync(true);
    field.setup(1024,600);
    bFullscreen = false;
}

//--------------------------------------------------------------
void testApp::update(){
    field.update();
}

//--------------------------------------------------------------
void testApp::draw(){
    field.draw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

    field.keyPressed(key);
    	if(key == 'f'){

		bFullscreen = !bFullscreen;

		if(!bFullscreen){
			ofSetWindowShape(1024,600);
			ofSetFullscreen(false);
			// figure out how to put the window in the center:
			int screenW = ofGetScreenWidth();
			int screenH = ofGetScreenHeight();
			ofSetWindowPosition(screenW/2-300/2, screenH/2-300/2);
		} else if(bFullscreen == 1){
			ofSetFullscreen(true);
		}
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    field.mouseDragged(x,y,button);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    field.mousePressed(x,y,button);
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}
