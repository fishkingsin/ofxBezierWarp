/*
 *  ofxBezierWarp.h
 *
 *  Created by Patrick Saint-Denis on 12-03-05.
 *	A Bezier Warp made of multiple homographies
 *  
 *
 */

#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"
class ofxBezierWarp{
	
private:
	int mousePosX, mousePosY, rad;
	float width, height;
	int selectedSprite[4], selectedControlPoint[8], anchorControl, mouseON, spritesON;
    string filename;
    ofPoint **bezSurfPoints;
    float ratio;
public:
    int nscreens;
    bool isActive;
	ofPoint corners[4];
	ofPoint anchors[8];
    ofPoint **gridPoint;
	int gridRes;
    
		
	ofxBezierWarp(){}
	void setup(int grid , string _filename);
	void setup(int grid ,int _nscreen,int _width ,int _height , string _filename);
	void draw(ofTexture texture);
	void draw(ofTexture texture, ofPoint offset[4] , int n_screen=1);
	void sprites();
	float bezierPoint(float x0, float x1, float x2, float x3, float t);
	void defaults();
    void defaults(int nscreen);
	void save();
	void recall();
	void mousePressed(int x, int y);
	void mouseDragged(int x, int y);
	void keyPressed(int clef);
    void toggleActive();
    
    void active(){ spritesON = isActive = true;}
    void inactive(){ spritesON = isActive = false;}
    bool getActive(){return isActive;}
    ofPoint drawDrid(int x ,int y)
    {
        ofCircle(gridPoint[x][y]+bezSurfPoints[x][y] ,60);
//        ostringstream str ;
//        str <<  ofToString(gridPoint[x][y].x+bezSurfPoints[x][y].x) << endl <<ofToString(gridPoint[x][y].y+bezSurfPoints[x][y].y);
//        ofDrawBitmapString(str.str(), gridPoint[x][y]+bezSurfPoints[x][y] );
        
        return ofPoint(gridPoint[x][y]+bezSurfPoints[x][y]);
    }
};