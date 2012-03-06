/*
 *  ofxBezierWarp.cpp
 *
 *  Created by Patrick Saint-Denis on 12-03-05.
 *  
 *
 */

#include "ofxBezierWarp.h"

void ofxBezierWarp::setup(int grid) {
	gridRes = grid;
	mouseON = 0;
	spritesON = 1;
	anchorControl = 0;
	rad = 15;
	width = ofGetWidth();
	height = ofGetHeight();
	defaults();
}

// resets control points to default position
void ofxBezierWarp::defaults() {
	for(int i = 0; i < 4; i++) {
		selectedSprite[i] = 0;
	}
	for(int i = 0; i < 8; i++) {
		selectedControlPoint[i] = 0;
	}
	// top left first then clockwise
	corners[0] = ofPoint(width * 0.2, height * 0.2);
	corners[1] = ofPoint(width * 0.8, height * 0.2);
	corners[2] = ofPoint(width * 0.8, height * 0.8);
	corners[3] = ofPoint(width * 0.2, height * 0.8);
	
	// top left first then clockwise
	anchors[0] = ofPoint(width * 0.2, height * 0.4);
	anchors[1] = ofPoint(width * 0.4, height * 0.2);
	anchors[2] = ofPoint(width * 0.6, height * 0.2);
	anchors[3] = ofPoint(width * 0.8, height * 0.4);
	anchors[4] = ofPoint(width * 0.8, height * 0.6);
	anchors[5] = ofPoint(width * 0.6, height * 0.8);
	anchors[6] = ofPoint(width * 0.4, height * 0.8);
	anchors[7] = ofPoint(width * 0.2, height * 0.6);
}

void ofxBezierWarp::draw(ofTexture tex) {
	ofPoint bezSurfPoints[gridRes+1][gridRes+1];
	
	for(int i = 0; i <= gridRes; i++) {
		for(int j = 0; j <= gridRes; j++) {
			float start_x = bezierPoint(corners[0].x, anchors[0].x, anchors[7].x, corners[3].x, (float)j/gridRes);
			float end_x = bezierPoint(corners[1].x, anchors[3].x, anchors[4].x, corners[2].x, (float)j/gridRes);
			float start_y = bezierPoint(corners[0].y, anchors[0].y, anchors[7].y, corners[3].y, (float)j/gridRes);
			float end_y = bezierPoint(corners[1].y, anchors[3].y, anchors[4].y, corners[2].y, (float)j/gridRes);
			
			float x = bezierPoint(start_x, ((anchors[1].x - anchors[6].x) * (1.0f - (float)j/gridRes)) + anchors[6].x, ((anchors[2].x - anchors[5].x) * (1.0f - (float)j/gridRes)) + anchors[5].x, end_x, (float)i/gridRes);
			float y = bezierPoint(start_y, ((anchors[1].y - anchors[6].y) * (1.0f - (float)j/gridRes)) + anchors[6].y, ((anchors[2].y - anchors[5].y) * (1.0f - (float)j/gridRes)) + anchors[5].y, end_y, (float)i/gridRes);
			
			bezSurfPoints[i][j] = ofPoint(x, y);
		} 
	} 
	for(int i = 0; i < gridRes; i++) {
		for(int j = 0; j < gridRes; j++) {
			tex.bind();
			glBegin(GL_QUADS);  
			
			glTexCoord2f((i) * (tex.getWidth()/gridRes), (j) * (tex.getHeight()/gridRes));
			glVertex2f(bezSurfPoints[i][j].x, bezSurfPoints[i][j].y);  
			
			glTexCoord2f((i+1) * (tex.getWidth()/gridRes), (j) * (tex.getHeight()/gridRes));  
			glVertex2f(bezSurfPoints[i+1][j].x, bezSurfPoints[i+1][j].y);  
			
			glTexCoord2f((i+1) * (tex.getWidth()/gridRes), (j+1) * (tex.getHeight()/gridRes)); 
			glVertex2f(bezSurfPoints[i+1][j+1].x, bezSurfPoints[i+1][j+1].y);  
			
			glTexCoord2f((i) * (tex.getWidth()/gridRes), (j+1) * (tex.getHeight()/gridRes)); 
			glVertex2f(bezSurfPoints[i][j+1].x, bezSurfPoints[i][j+1].y);
			glEnd();  
			tex.unbind(); 		
		}
	}
	sprites();
}


void ofxBezierWarp::sprites() {
	if(spritesON == 1) {
		ofEnableSmoothing();
		for(int i = 0; i < 4; i++) {
			if(selectedSprite[i] == 1) {
				corners[i] = ofPoint(mousePosX,mousePosY); 
				ofEnableAlphaBlending();
				ofPushStyle();
				ofSetColor(0, 255, 0, 100);
				ofFill();
				ofCircle(corners[i].x, corners[i].y, rad);
				ofDisableAlphaBlending();
				ofPopStyle();
				ofPushStyle();
				ofSetColor(255, 0, 0);
				ofNoFill();
				ofCircle(corners[i].x, corners[i].y, rad);
				ofLine(corners[i].x, corners[i].y - (rad) - 5, corners[i].x, corners[i].y + (rad) + 5);
				ofLine(corners[i].x - (rad) - 5, corners[i].y, corners[i].x + (rad) + 5, corners[i].y);
				ofPopStyle();
			} else {
				ofPushStyle();
				ofSetColor(255, 0, 0);
				ofNoFill();
				ofCircle(corners[i].x, corners[i].y, rad);
				ofLine(corners[i].x, corners[i].y - (rad) - 5, corners[i].x, corners[i].y + (rad) + 5);
				ofLine(corners[i].x - (rad) - 5, corners[i].y, corners[i].x + (rad) + 5, corners[i].y);
				ofPopStyle();
			}		      
		}
		for(int i = 0; i < 8; i++) {		    
		    if(selectedControlPoint[i] == 1) {
				anchors[i] = ofPoint(mousePosX,mousePosY);
				ofEnableAlphaBlending();
				ofPushStyle();
				ofSetColor(0, 255, 0, 100);
				ofFill();
				ofCircle(anchors[i].x, anchors[i].y, rad/2);
				ofPopStyle();
				ofDisableAlphaBlending();
				ofPushStyle();
				ofNoFill();
				ofSetColor(255, 255, 0);
				ofCircle(anchors[i].x, anchors[i].y, rad/2);
				if((i % 2) == 0) {
			    	ofBezier(corners[i/2].x, corners[i/2].y, anchors[(i+1) % 8].x, anchors[(i+1) % 8].y, anchors[(i+2) % 8].x, anchors[(i+2) % 8].y, corners[((i/2)+1) % 4].x, corners[((i/2)+1) % 4].y); 
				}
				ofLine(corners[i/2].x, corners[i/2].y, anchors[i].x, anchors[i].y);
				ofPopStyle();
		    } else {
				ofPushStyle();
				ofNoFill();
				ofSetColor(255, 255, 0);
				ofCircle(anchors[i].x, anchors[i].y, rad/2);
				if((i % 2) == 0) {
			    	ofBezier(corners[i/2].x, corners[i/2].y, anchors[(i+1) % 8].x, anchors[(i+1) % 8].y, anchors[(i+2) % 8].x, anchors[(i+2) % 8].y, corners[((i/2)+1) % 4].x, corners[((i/2)+1) % 4].y); 
				}
				ofLine(corners[i/2].x, corners[i/2].y, anchors[i].x, anchors[i].y);
				ofPopStyle();
			}
		}
		ofDisableSmoothing();
	}
}

float ofxBezierWarp::bezierPoint(float x0, float x1, float x2, float x3, float t) {
	float   ax, bx, cx;
	float   ay, by, cy;
	float   t2, t3;
	float   x;
	
	// polynomial coefficients
	cx = 3.0f * (x1 - x0);
	bx = 3.0f * (x2 - x1) - cx;
	ax = x3 - x0 - cx - bx;
	
	t2 = t * t;
	t3 = t2 * t;
	x = (ax * t3) + (bx * t2) + (cx * t) + x0;
	
	return x;
}

//saves sprites positions
void ofxBezierWarp::save() {
	
	// open and write data to the file
	std::fstream ofs( "presets.bin", std::ios::out | std::ios::binary );
	for(int i = 0; i < 4; i++) {
		ofs.write( (const char*) &corners[i].x, sizeof(corners[i].x) );
		ofs.write( (const char*) &corners[i].y, sizeof(corners[i].y) );
	}
	for(int i = 0; i < 8; i++) {
		ofs.write( (const char*) &anchors[i].x, sizeof(anchors[i].x) );
		ofs.write( (const char*) &anchors[i].y, sizeof(anchors[i].y) );
	}
	ofs.close();	
}

//reloads last saved sprites positions
void ofxBezierWarp::recall() {
	// re-open the file, but this time to read from it
	std::fstream ifs( "presets.bin", std::ios::in | std::ios::binary );
	for(int i = 0; i < 4; i++) {
		ifs.read( (char*) &corners[i].x, sizeof(corners[i].x) );
		ifs.read( (char*) &corners[i].y, sizeof(corners[i].y) );
	}
	for(int i = 0; i < 8; i++) {
		ifs.read( (char*) &anchors[i].x, sizeof(anchors[i].x) );
		ifs.read( (char*) &anchors[i].y, sizeof(anchors[i].y) );
	}
	ifs.close();
};

//handles mouse events 1
void ofxBezierWarp::mousePressed(int x, int y) {
	mousePosX = x;
	mousePosY = y;
	
	for(int i = 0; i < 4; i++) {
		selectedSprite[i] = 0;
	}
	for(int i = 0; i < 8; i++) {
		selectedControlPoint[i] = 0;
	}
	
	if(spritesON == 1) {
		for(int i = 0; i < 4; i++) {
			if(selectedSprite[i] == 0 && anchorControl == 0) {
				if((mousePosX > corners[i].x - (rad)) && (mousePosX < corners[i].x + (rad)) && (mousePosY >  corners[i].y - (rad)) && (mousePosY <  corners[i].y + (rad))) {
					selectedSprite[i] = 1;
				} else {
					selectedSprite[i] = 0;
				}
			}
		}
		for(int i = 0; i < 8; i++) {
			if(selectedControlPoint[i] == 0 && anchorControl == 1) {
				if((mousePosX > anchors[i].x - (rad/2)) && (mousePosX < anchors[i].x + (rad/2)) && (mousePosY >  anchors[i].y - (rad/2)) && (mousePosY <  anchors[i].y + (rad/2))) {
					selectedControlPoint[i] = 1;
				} else {
					selectedControlPoint[i] = 0;
				}
			}
			
		}
	}
}

//handles mouse events 3
void ofxBezierWarp::mouseDragged(int x, int y) {
	mousePosX = x;
	mousePosY = y;
}

//handles keyboard events
void ofxBezierWarp::keyPressed(int key) {
	switch(key) {
		case 'c':
			switch(spritesON) {
				case 1:
					spritesON = 0;
					break;
				case 0:
					spritesON = 1;
					break;
			}
			break;
		case 'd':
			defaults();
			break;
		case 'p':
			recall();
			break;
		case 'a':
			switch(anchorControl) {
				case 1:
					anchorControl = 0;
					break;
				case 0:
					anchorControl = 1;
					break;
			}
			break;
		case 's':
			save();
			break;
	}
}

