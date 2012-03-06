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

class ofxBezierWarp{
	
private:
	int mousePosX, mousePosY, rad;
	float width, height;
	int selectedSprite[4], selectedControlPoint[8], anchorControl, mouseON, spritesON;
			
public:
	ofPoint corners[4];
	ofPoint anchors[8];
	int gridRes;
		
	ofxBezierWarp(){}
	
	void setup(int grid);
	void draw(ofTexture texture);
	void sprites();
	float bezierPoint(float x0, float x1, float x2, float x3, float t);
	void defaults();
	void save();
	void recall();
	void mousePressed(int x, int y);
	void mouseDragged(int x, int y);
	void keyPressed(int clef);
};