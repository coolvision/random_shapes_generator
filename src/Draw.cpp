//
//  Draw.cpp
//  image_generator
//
//  Created by mb on 03/08/2016.
//
//

#include "Shape.h"

ofColor fill_color = ofColor(0, 0, 0, 255);
ofColor line_color = ofColor(0, 0, 0, 255);
//ofColor fill_color = ofColor(255, 255, 255, 255);
//ofColor line_color = ofColor(255, 255, 255, 255);

void Circle::draw(int off_x, int off_y, int w, int h) {
    float zoom = float(w);
    ofPoint offset(off_x, off_y);
    ofPushStyle();
    filled? ofFill() : ofNoFill();
    //ofEnableAntiAliasing();
    ofSetLineWidth(2.0f);
    // if (!opaque) {
    //     ofSetColor(fill_color);
    //     ofDrawCircle(offset+center*zoom, r*zoom);
    //     ofSetColor(line_color);
    //     ofNoFill();
    //     ofDrawCircle(offset+center*zoom, r*zoom);
    // } else {
        //ofNoFill();
        ofSetColor(line_color);
        ofDrawCircle(offset+center*zoom, r*zoom);
    //}
    ofPopStyle();
}

void Line::draw(int off_x, int off_y, int w, int h) {
    float zoom = float(w);
    ofPoint offset(off_x, off_y);
    ofPushStyle();
    filled? ofFill() : ofNoFill();
    //ofEnableAntiAliasing();
    ofSetLineWidth(2.0f);
    ofSetColor(line_color);
    ofNoFill();
    ofDrawLine(offset+v[0]*zoom, offset+v[1]*zoom);
    //ofDrawBitmapString(ofToString(length), offset+v[0]*zoom);
    ofPopStyle();
}

void Triangle::draw(int off_x, int off_y, int w, int h) {
    float zoom = float(w);
    ofPoint offset(off_x, off_y);
    ofPushStyle();
    filled? ofFill() : ofNoFill();
    //ofEnableAntiAliasing();
    ofSetLineWidth(2.0f);
     ofSetColor(fill_color);
     ofDrawTriangle(offset+v[0]*zoom, offset+v[1]*zoom, offset+v[2]*zoom);

    ofSetColor(line_color);
    ofNoFill();
    ofDrawTriangle(offset+v[0]*zoom, offset+v[1]*zoom, offset+v[2]*zoom);

    //ofDrawBitmapString(ofToString(area), offset+v[0]*zoom);
    ofPopStyle();
}

void Rectangle::draw(int off_x, int off_y, int w, int h) {
    float zoom = float(w);
    ofPoint offset(off_x, off_y);
    ofPushStyle();
    filled? ofFill() : ofNoFill();
    //ofEnableAntiAliasing();
    ofSetLineWidth(2.0f);
    
    ofSetRectMode(OF_RECTMODE_CENTER);

    ofPushMatrix();
    
    
    ofTranslate(offset+center*zoom);
    ofRotate(angle);
    
    ofSetColor(fill_color);
    //ofDrawRectangle(offset+center*zoom, width*zoom, height*zoom);
    ofDrawRectangle(ofPoint(0, 0), width*zoom, height*zoom);
    
    //ofDrawRectangle(offset+min*zoom, width*zoom, height*zoom);

    ofSetColor(line_color);
    ofNoFill();
    ofDrawRectangle(ofPoint(0, 0), width*zoom, height*zoom);
    
    
    ofPopMatrix();
    
    ofSetRectMode(OF_RECTMODE_CORNER);
    
    ofPopStyle();
}

void Image::draw(int off_x, int off_y, int w, int h) {

    ofPushStyle();
    
    //cout << "draw " << shapes.size() << endl;

//    ofColor bg_color = ofColor(255, 255, 255, 255);
//
//    ofSetColor(bg_color);
//    ofFill();
//    ofDrawRectangle(off_x, off_y, w, h);
    
    
    for (int i = 0; i < shapes.size(); i++) {
        shapes[i]->draw(off_x, off_y, w, h);
    }
    ofPopStyle();
}
