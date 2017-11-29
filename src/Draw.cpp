//
//  Draw.cpp
//  image_generator
//
//  Created by mb on 03/08/2016.
//
//

#include "Shape.h"

//ofColor fill_color = ofColor(0, 0, 0, 255);
//ofColor line_color = ofColor(0, 0, 0, 255);

void Circle::draw(int off_x, int off_y, int w, int h) {

    if (opaque) setFilled(true);

    float zoom = float(w);
    ofPoint offset(off_x, off_y);
    ofPushStyle();
    filled? ofFill() : ofNoFill();
    if (opaque) ofFill();
    ofSetLineWidth(line_width);
    ofSetColor(line_color);
    ofDrawCircle(offset+ofPoint(x, y)*zoom, d/2*zoom);

    ofPopStyle();
}

void Line::draw(int off_x, int off_y, int w, int h) {

    setFilled(false);

    float zoom = float(w);
    ofPoint offset(off_x, off_y);
    ofPushStyle();
    ofSetLineWidth(line_width);
    ofSetColor(line_color);
    ofDrawLine(offset+ofPoint(x1, y1)*zoom, offset+ofPoint(x2, y2)*zoom);
    ofPopStyle();
}


void Rectangle::draw(int off_x, int off_y, int w, int h) {
    float zoom = float(w);
    ofPoint offset(off_x, off_y);
    ofPushStyle();
    filled? ofFill() : ofNoFill();

    ofSetLineWidth(line_width);
    ofSetColor(line_color);
    ofDrawRectangle(offset+ofPoint(x, y)*zoom, this->w*zoom, this->h*zoom);

    ofPopStyle();
}

void Image::draw(int off_x, int off_y, int w, int h) {

    ofPushStyle();

    for (int i = 0; i < shapes.size(); i++) {
        float zoom = float(w);

        ofPushMatrix();
        ofTranslate(off_x+w*0.5f+w*shapes[i]->tx, off_y+h*0.5f+h*shapes[i]->ty);
        ofRotate(shapes[i]->angle);

        shapes[i]->draw(0, 0, w, h);
        ofPopMatrix();

        shapes[i]->makeLabel();

        ofPushMatrix();
        ofTranslate(off_x, off_y);
        ofDrawBitmapString(shapes[i]->label, 5, 13);
        ofPopMatrix();
       //
    //    ofPushMatrix();
    //    ofTranslate(off_x+w*0.5f+w*shapes[i]->tx, off_y+h*0.5f+h*shapes[i]->ty);
       //
    //    ofPath path;
    //    for (auto &p: shapes[i]->points) {
    //        path.lineTo(p * zoom);
    //    }
    //    path.close();
    //    path.setFilled(false);
    //    path.setStrokeWidth(1.0f);
    //    path.setStrokeColor(ofColor::red);
    //    path.draw();
       //
    //    ofPoint offset(0, 0);
    //    ofSetLineWidth(1.0f);
    //    ofNoFill();
    //    ofSetColor(ofColor::grey);
    //    ofDrawRectangle(ofPoint(shapes[i]->min.x,
    //                                   shapes[i]->min.y)*zoom,
    //                                   (shapes[i]->max.x-shapes[i]->min.x)*zoom,
    //                                   (shapes[i]->max.y-shapes[i]->min.y)*zoom);
    //    ofPopMatrix();

    }
    ofPopStyle();
}
