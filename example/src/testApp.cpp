#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	myMovie.loadMovie("ski-nautique.mov");
	myMovie.play();
	
	// grid resolution of the warp (10x10 is good)
	bz.setup(10);
}

//--------------------------------------------------------------
void testApp::update(){
	myMovie.update();
}

//--------------------------------------------------------------
void testApp::draw(){
	//serie of homographies forming a bezier surface texture warp
	bz.draw(myMovie.getTextureReference());
	
	// infos about controls
	ofDrawBitmapString("c: show/hide controls", 10,10);
	ofDrawBitmapString("a: corner/anchor controls", 10,20);
	ofDrawBitmapString("s: save", 10,30);
	ofDrawBitmapString("d: default", 10,40);
	ofDrawBitmapString("p: preset (last saved)", 10,50);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	bz.keyPressed(key);
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	bz.mouseDragged(x, y);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	bz.mousePressed(x, y);
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