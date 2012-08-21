/*
 *  ofxBezierWarp.cpp
 *
 *  Created by Patrick Saint-Denis on 12-03-05.
 *  
 *
 */

#include "ofxBezierWarp.h"

void ofxBezierWarp::setup(int grid , string _filename) {
    nscreens = 1;
	gridRes = grid;
	mouseON = 0;
	spritesON = 1;
	anchorControl = 0;
	rad = 15;
	width = ofGetWidth();;
	height = ofGetHeight();
	
    filename = _filename;
    isActive = false;
    bezSurfPoints = new ofPoint*[gridRes+1];
    gridPoint = new ofPoint*[gridRes+1];
    for(int i = 0 ; i <=gridRes ; i++)
    {
        bezSurfPoints[i] = new ofPoint[gridRes+1];
        gridPoint[i] = new ofPoint[gridRes+1];
        for(int j = 0 ; j <=gridRes ; j++)
        {
            bezSurfPoints[i][j].set(0,0);
            gridPoint[i][j].set(0,0);
        }
    }
    ratio = float(height/width);
    defaults();
}
void ofxBezierWarp::setup(int grid ,int _nscreen ,int _width ,int _height , string _filename) {
    nscreens = _nscreen;
	gridRes = grid;
	mouseON = 0;
	spritesON = 1;
	anchorControl = 0;
	rad = 15;
	width = _width;
	height = _height;
	
    filename = _filename;
    isActive = false;
    
    bezSurfPoints = new ofPoint*[gridRes+1];
    gridPoint = new ofPoint*[gridRes+1];
    for(int i = 0 ; i <=gridRes ; i++)
    {
        bezSurfPoints[i] = new ofPoint[gridRes+1];
        gridPoint[i] = new ofPoint[gridRes+1];
        for(int j = 0 ; j <=gridRes ; j++)
        {
            bezSurfPoints[i][j].set(0,0);
            gridPoint[i][j].set(0,0);
            
        }
    }
    ratio = height/width;
    ofLog(OF_LOG_VERBOSE,"ofxBezierWarp: Ratio = %f",ratio);
    defaults();
}

// resets control points to default position
void ofxBezierWarp::defaults(){
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
    
    for(int y = 0; y < gridRes; y++) {
        for(int x = 0; x < gridRes; x++) {
            gridPoint[x][y].x= 0;
            gridPoint[x][y].y= 0;
        }
    }
}
void ofxBezierWarp::defaults(int nscreen) {
	for(int i = 0; i < 4; i++) {
		selectedSprite[i] = 0;
	}
	for(int i = 0; i < 8; i++) {
		selectedControlPoint[i] = 0;
	}
	// top left first then clockwise
    float __width = float(width/nscreens);
    float w = __width*nscreen;
    float w1 = __width*(nscreen+1);
	corners[0] = ofPoint(w, 0);
	corners[1] = ofPoint(w1, 0);
	corners[2] = ofPoint(w1 , height);
	corners[3] = ofPoint(w, height);
	
	// top left first then clockwise
	anchors[0] = ofPoint(w+__width * 0, height *0.4);
	anchors[1] = ofPoint(w+__width * 0.4, height * 0);
	anchors[2] = ofPoint(w+__width * 0.6, height * 0);
	anchors[3] = ofPoint(w+__width * 1, height * 0.4);
	anchors[4] = ofPoint(w+__width * 1, height * 0.6);
	anchors[5] = ofPoint(w+__width * 0.6, height * 1);
	anchors[6] = ofPoint(w+__width * 0.4, height * 1);
	anchors[7] = ofPoint(w+__width * 0, height * 0.6);
    for(int y = 0; y < gridRes; y++) {
        for(int x = 0; x < gridRes; x++) {
            gridPoint[x][y].x= 0;
            gridPoint[x][y].y= 0;
        }
    }
}

void ofxBezierWarp::draw(ofTexture tex) {
	
	
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
    if(spritesON == 1)
    {
        
        
        for(int i = 0; i < gridRes; i++) {
            for(int j = 0; j < gridRes; j++) {
                
                
                glBegin(GL_LINE_LOOP);  
                glVertex2f(bezSurfPoints[i][j].x, bezSurfPoints[i][j].y); 
                
                
                
                glVertex2f(bezSurfPoints[i+1][j].x, bezSurfPoints[i+1][j].y);  
                
                
                glVertex2f(bezSurfPoints[i+1][j+1].x, bezSurfPoints[i+1][j+1].y);  
                
                
                glVertex2f(bezSurfPoints[i][j+1].x, bezSurfPoints[i][j+1].y);
                glEnd();  
                ostringstream os;
                os << i << "-" << j ;
                ofDrawBitmapString(os.str(), gridPoint[i][j]+bezSurfPoints[i][j]);
                
            }
        }
        
    }
	sprites();
}

void ofxBezierWarp::draw(ofTexture tex , ofPoint offset[4] , int n_screen) {
	//ofPoint bezSurfPoints[gridRes+1][gridRes+1];
	
	for(int i = 0; i <= gridRes; i++) {
		for(int j = 0; j <= gridRes; j++) {
			float start_x = bezierPoint(corners[0].x, anchors[0].x, anchors[7].x, corners[3].x, (float)j/gridRes);
			float end_x = bezierPoint(corners[1].x, anchors[3].x, anchors[4].x, corners[2].x, (float)j/gridRes);
			float start_y = bezierPoint(corners[0].y, anchors[0].y, anchors[7].y, corners[3].y, (float)j/gridRes);
			float end_y = bezierPoint(corners[1].y, anchors[3].y, anchors[4].y, corners[2].y, (float)j/gridRes);
			
			float x = bezierPoint(start_x, ((anchors[1].x - anchors[6].x) * (1.0f - (float)j/gridRes)) + anchors[6].x, ((anchors[2].x - anchors[5].x) * (1.0f - (float)j/gridRes)) + anchors[5].x, end_x, (float)i/gridRes);
			float y = bezierPoint(start_y, ((anchors[1].y - anchors[6].y) * (1.0f - (float)j/gridRes)) + anchors[6].y, ((anchors[2].y - anchors[5].y) * (1.0f - (float)j/gridRes)) + anchors[5].y, end_y, (float)i/gridRes);
			
			bezSurfPoints[i][j].set(x, y);
		} 
	} 
	for(int i = 0; i < gridRes; i++) {
		for(int j = 0; j < gridRes; j++) {
            float n_screen_width = (tex.getWidth()/n_screen);
            float gridWidth = n_screen_width/gridRes;
			tex.bind();
			glBegin(GL_QUADS);  
			
			glTexCoord2f( ((i) * gridWidth)+(n_screen_width)*offset[0].x, (j) * (tex.getHeight()/gridRes));
			glVertex2f(gridPoint[i][j].x+bezSurfPoints[i][j].x,
                       gridPoint[i][j].y+bezSurfPoints[i][j].y);  
			
			glTexCoord2f( ((i+1) * gridWidth)+(n_screen_width)*offset[0].x, (j) * (tex.getHeight()/gridRes));  
			glVertex2f(gridPoint[i+1][j].x+bezSurfPoints[i+1][j].x,
                       gridPoint[i+1][j].y+bezSurfPoints[i+1][j].y);  
			
			glTexCoord2f( ((i+1) * gridWidth)+(n_screen_width)*offset[0].x, (j+1) * (tex.getHeight()/gridRes)); 
			glVertex2f(gridPoint[i+1][j+1].x+bezSurfPoints[i+1][j+1].x,
                       gridPoint[i+1][j+1].y+bezSurfPoints[i+1][j+1].y);  
			
			glTexCoord2f( ((i) * gridWidth)+(n_screen_width)*offset[0].x, (j+1) * (tex.getHeight()/gridRes)); 
			glVertex2f(gridPoint[i][j+1].x+bezSurfPoints[i][j+1].x,
                       gridPoint[i][j+1].y+bezSurfPoints[i][j+1].y);
			glEnd();  
			tex.unbind(); 		
		}
	}
    if(spritesON == 1)
    {
        
        
        for(int i = 0; i < gridRes; i++) {
            for(int j = 0; j < gridRes; j++) {
                
                
                glBegin(GL_LINE_LOOP);  
                glVertex2f(gridPoint[i][j].x+bezSurfPoints[i][j].x,
                           gridPoint[i][j].y+bezSurfPoints[i][j].y); 
                
                
                glVertex2f(gridPoint[i+1][j].x+bezSurfPoints[i+1][j].x,
                           gridPoint[i+1][j].y+bezSurfPoints[i+1][j].y); 
                
                
                glVertex2f(gridPoint[i+1][j+1].x+bezSurfPoints[i+1][j+1].x,
                           gridPoint[i+1][j+1].y+bezSurfPoints[i+1][j+1].y);
                
                
                glVertex2f(gridPoint[i][j+1].x+bezSurfPoints[i][j+1].x,
                           gridPoint[i][j+1].y+bezSurfPoints[i][j+1].y);
                glEnd(); 
                
                
                
            }
        }
        for(int i = 0; i <= gridRes; i++) {
            for(int j = 0; j <= gridRes; j++) {
                ostringstream os;
                os << i << "-" << j ;
                glPushMatrix();
                glTranslatef(-10, 10, 0);
                ofDrawBitmapString(os.str(), gridPoint[i][j]+bezSurfPoints[i][j]);
                glPopMatrix();
            }
        }
        
    }
	sprites();
}


void ofxBezierWarp::sprites() {
	if(spritesON == 1) {
		ofEnableSmoothing();
        
		for(int i = 0; i < 4; i++) {
            ostringstream os;
            os << i ;
            ofDrawBitmapString(os.str(), corners[i]);
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
            ostringstream os;
            os << i ;
            ofDrawBitmapString(os.str(), anchors[i]);

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
	ofxXmlSettings XML;
	XML.clear();
	XML.addTag("corners");
	XML.pushTag("corners");
	
	for(int i = 0; i < 4; i++) {
        int t = XML.addTag("corner");
		XML.setValue("corner:x",corners[i].x,t);
		XML.setValue("corner:y",corners[i].y,t);
	}
    XML.popTag();
    XML.popTag();
    XML.addTag("anchors");
	XML.pushTag("anchors");

    for(int i = 0; i < 8; i++) {
        int t = XML.addTag("anchor");
		XML.setValue("anchor:x",anchors[i].x,t);
		XML.setValue("anchor:y",anchors[i].y,t);
	}
    XML.popTag();
    XML.popTag();
    XML.addTag("points");
	XML.pushTag("points");
    
    for(int y = 0; y < gridRes; y++) {
        for(int x = 0; x < gridRes; x++) {
            int t = XML.addTag("point");
            XML.setValue("point:x",gridPoint[x][y].x,t);
            XML.setValue("point:y",gridPoint[x][y].y,t);
        }
    }

	XML.saveFile(filename);
	// open and write data to the file
//	std::fstream ofs( ofToDataPath(filename).data(), std::ios::out | std::ios::binary );
//	for(int i = 0; i < 4; i++) {
//		ofs.write( (const char*) &corners[i].x, sizeof(corners[i].x) );
//		ofs.write( (const char*) &corners[i].y, sizeof(corners[i].y) );
//	}
//	for(int i = 0; i < 8; i++) {
//		ofs.write( (const char*) &anchors[i].x, sizeof(anchors[i].x) );
//		ofs.write( (const char*) &anchors[i].y, sizeof(anchors[i].y) );
//	}
//	ofs.close();	
}

//reloads last saved sprites positions
void ofxBezierWarp::recall() {
    ofxXmlSettings XML;
	if( !XML.loadFile(filename) ){
		ofLog(OF_LOG_ERROR, "ofxBezierWarp : xml file not loaded. Check file path.");
	}
	
	if(!XML.tagExists("corners")){
		ofLog(OF_LOG_ERROR, "ofxBezierWarp : incorrrect xml formating. No \"corners\" tag found");
		return;
	}
	XML.pushTag("corners");
	if (XML.getNumTags("corner")<4 ) {
		ofLog(OF_LOG_ERROR, "ofxBezierWarp : incorrrect xml formating. less than 4 \"corner\" tags found");
		return;	
	}
	for(int i =0; i<4; i++){
		int t = XML.addTag("corner");
		XML.pushTag("corner", i);
		if (XML.tagExists("x") && XML.tagExists("y")){
			corners[i].x = XML.getValue("x", double(1.0));
			corners[i].y = XML.getValue("y", double(1.0));
		}
		XML.popTag();
	}
    XML.popTag();
    XML.popTag();
    
    if(!XML.tagExists("anchors")){
		ofLog(OF_LOG_ERROR, "ofxBezierWarp : incorrrect xml formating. No \"anchors\" tag found");
		return;
	}
	XML.pushTag("anchors");
	if (XML.getNumTags("anchor")<8 ) {
		ofLog(OF_LOG_ERROR, "ofxBezierWarp : incorrrect xml formating. less than 8 \"anchor\" tags found");
		return;	
	}
	for(int i =0; i<8; i++){
		int t = XML.addTag("anchor");
		XML.pushTag("anchor", i);
		if (XML.tagExists("x") && XML.tagExists("y")){
			anchors[i].x = XML.getValue("x", double(1.0));
			anchors[i].y = XML.getValue("y", double(1.0));
		}
		XML.popTag();
	}
    XML.popTag();
    
    if(!XML.tagExists("points")){
		ofLog(OF_LOG_ERROR, "ofxBezierWarp : incorrrect xml formating. No \"points\" tag found");
		return;
	}
	XML.pushTag("points");
	if (XML.getNumTags("point")<gridRes*gridRes ) {
		ofLog(OF_LOG_ERROR, "ofxBezierWarp : incorrrect xml formating. less than "+ofToString(gridRes*gridRes)+" \"point\" tags found");
		return;	
	}
    for(int y = 0; y < gridRes; y++) {
        for(int x = 0; x < gridRes; x++) {
            
            int t = XML.addTag("point");
            
            XML.pushTag("point", x+(y*gridRes));
            if (XML.tagExists("x") && XML.tagExists("y")){
                gridPoint[x][y].x= XML.getValue("x", double(1.0));
                gridPoint[x][y].y= XML.getValue("y", double(1.0));
            }
            XML.popTag();
        }
        
    }
    XML.popTag();
    XML.popTag();

	// re-open the file, but this time to read from it
//	std::fstream ifs( ofToDataPath(filename).data(), std::ios::in | std::ios::binary );
//	for(int i = 0; i < 4; i++) {
//		ifs.read( (char*) &corners[i].x, sizeof(corners[i].x) );
//		ifs.read( (char*) &corners[i].y, sizeof(corners[i].y) );
//	}
//	for(int i = 0; i < 8; i++) {
//		ifs.read( (char*) &anchors[i].x, sizeof(anchors[i].x) );
//		ifs.read( (char*) &anchors[i].y, sizeof(anchors[i].y) );
//	}
//	ifs.close();
};

//handles mouse events 1
void ofxBezierWarp::mousePressed(int x, int y) {
    if(!isActive)return;
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
    if(!isActive)return;
	mousePosX = x;
	mousePosY = y;
}

//handles keyboard events
void ofxBezierWarp::keyPressed(int key) {
    if(!isActive)return;
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
			//defaults();
			break;
		case 'p':
			recall();
			break;
		case 'a':
			switch(anchorControl) {
				case 1:
					anchorControl = 0;
                    ofLog(OF_LOG_VERBOSE,"Start Control Corner");
					break;
				case 0:
					anchorControl = 1;
                    ofLog(OF_LOG_VERBOSE,"Start Control Anchor");
					break;
			}
			break;
		case 's':
			save();
			break;
	}
}

void ofxBezierWarp::toggleActive(){
    isActive = !isActive;
    spritesON = isActive;
}
