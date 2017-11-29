//
//  Shape.h
//  image_generator
//
//  Created by mb on 30/07/2016.
//
//

#pragma once

#include "ofMain.h"

#define IMAGE_SIZE 104

#define SHAPES_N 13

void getPolygon(vector<ofPoint> &points, int n, float min, float max,
                bool equal = false, bool sorted = true, bool check_area = true);
void getBoundingBox(vector<ofPoint> &points, ofPoint &min, ofPoint &max);

class Shape {
public:
    Shape() {};
    virtual ~Shape() {};

    float width = 1.0f;
    float height = 1.0f;
    float line_width = 2.0f;

    ofColor fill_color = ofColor(0, 0, 0, 255);
    ofColor line_color = ofColor(0, 0, 0, 255);

    // bounding box
    ofPoint min;
    ofPoint max;

    int type;
    string label;

    bool filled = false;
    bool opaque = false;

    float angle = 0.0f;
    float tx = 0.0f;
    float ty = 0.0f;
    vector<ofPoint> points;

    void makeLabel();
    virtual void makeRandom() = 0;
    virtual void draw(int off_x, int off_y, int w, int h) = 0;
    void setFilled(bool filled_in) {
        filled = filled_in;
    }
};

class Line: public Shape {
public:
    float x1;
    float y1;
    float x2;
    float y2;
    void makeRandom() {
        float l1 = (0.1 + ofRandom(1.0f) * 0.8);
        x1 = 0;
        y1 = -l1/2;
        x2 = 0;
        y2 = +l1/2;
        min.set(x1, y1);
        max.set(x2, y2);
    }
    void draw(int off_x, int off_y, int w, int h);
};

class PolygonShape: public Shape {
public:
    vector<ofPoint> points;
    virtual void makeRandom() = 0;
    void draw(int off_x, int off_y, int w, int h) {
        float zoom = float(w);
        ofPoint offset(off_x, off_y);
        ofPath path;
        for (auto &p: points) {
            path.lineTo(offset + p * zoom);
        }
        path.close();

        path.setFilled(filled);
        path.setStrokeWidth(2.0f);
        path.setStrokeColor(line_color);
        path.setFillColor(fill_color);
        path.draw();
    };
};

class Polyline: public PolygonShape {
public:
    void makeRandom() {
        int n = 3 + floor(ofRandom(1.0f)*3);
        for (int i = 0; i < n; i++) {
            float x = (ofRandom(-1.0f, 1.0f) * 0.4);
            float y = (ofRandom(-1.0f, 1.0f) * 0.4);
            points.push_back(ofPoint(x, y));
        }
        getBoundingBox(points, min, max);
    };
    void draw(int off_x, int off_y, int w, int h) {

        setFilled(false);

        float zoom = float(w);
        ofPoint offset(off_x, off_y);
        ofPath path;
        for (auto &p: points) {
            path.lineTo(offset + p * zoom);
        }
        path.setFilled(false);
        path.setStrokeWidth(2.0f);
        path.setStrokeColor(line_color);
        path.draw();
    };
};

class Triangle: public PolygonShape {
public:
    void makeRandom() {
        getPolygon(points, 3, 0.1, 0.4);
        getBoundingBox(points, min, max);
    }
//    void draw(int off_x, int off_y, int w, int h);
};

class Rectangle: public Shape {
public:
    float w;
    float h;
    float x;
    float y;
    void makeRandom() {
        w = (0.1 + ofRandom(1.0f) * 0.5);
        h = (0.1 + ofRandom(1.0f) * 0.5);
        x = -w/2;
        y = -h/2;
        min.set(x, y);
        max.set(x+w, y+h);
    };
    void draw(int off_x, int off_y, int w, int h);
};

class Circle: public Shape {
public:
    float x, y;
    float d;
    void makeRandom() {
        d = (0.1 + ofRandom(1.0f) * 0.5) * width;
        x = 0;
        y = 0;
        min.set(x-d/2, y-d/2);
        max.set(x+d/2, y+d/2);
    };
    void draw(int off_x, int off_y, int w, int h);
};

class Square: public Rectangle {
public:
    void makeRandom() {
        w = (0.1 + ofRandom(1.0f) * 0.5) * width;
        h = w;
        x = -w/2;
        y = -w/2;
        min.set(x, y);
        max.set(x+w, y+h);
    };
};

class Ellipse: public Shape {
public:
    float x, y, rx, ry;
    void makeRandom() {
        rx = (0.1 + ofRandom(1.0f) * 0.5);
        ry = rx * (0.2 + ofRandom(1.0f) * 0.7);
        x = 0;
        y = 0;
        min.set(x-rx/2, y-ry/2);
        max.set(x+rx/2, y+ry/2);
    };
    void draw(int off_x, int off_y, int w, int h) {
        float zoom = float(w);
        ofPoint offset(off_x, off_y);
        ofPushStyle();
        filled? ofFill() : ofNoFill();
        ofSetLineWidth(line_width);

        ofSetColor(fill_color);
        ofDrawEllipse(offset+ofPoint(x, y)*zoom, rx*zoom, ry*zoom);

        ofSetColor(line_color);
        ofDrawEllipse(offset+ofPoint(x, y)*zoom, rx*zoom, ry*zoom);

        ofPopStyle();
    };
};

class EqualTriangle: public Triangle {
public:
    void makeRandom() {
        getPolygon(points, 3, 0.1, 0.4, true);
        getBoundingBox(points, min, max);
    };
};

class Quad: public PolygonShape {
public:
    void makeRandom() {
        getPolygon(points, 4, 0.1, 0.4);
        getBoundingBox(points, min, max);
    };
};


class Pentagon: public PolygonShape {
public:
    void makeRandom() {
        getPolygon(points, 5, 0.1, 0.4);
        getBoundingBox(points, min, max);
    };
};

class Hexagon: public PolygonShape {
public:
    void makeRandom() {
        getPolygon(points, 6, 0.1, 0.4);
        getBoundingBox(points, min, max);
    };
};

class EqualPentagon: public Pentagon {
public:
    void makeRandom() {
        getPolygon(points, 5, 0.1, 0.3, true);
        getBoundingBox(points, min, max);
    };
};

class EqualHexagon: public Hexagon {
public:
    void makeRandom() {
        getPolygon(points, 6, 0.1, 0.3, true);
        getBoundingBox(points, min, max);
    };
};

class CrossedPentagon: public Pentagon {
public:
    void makeRandom() {
        getPolygon(points, 5, 0.1, 0.4, false, false, false);
        getBoundingBox(points, min, max);
    };
};

class CrossedHexagon: public Hexagon {
public:
    void makeRandom() {
        getPolygon(points, 6, 0.1, 0.4, false, false, false);
        getBoundingBox(points, min, max);
    };
};

class Dot: public Circle {
public:
    void makeRandom() {
        opaque = true;
        d = 0.05;
        x = 0;
        y = 0;
        min.set(x-d/2, y-d/2);
        max.set(x+d/2, y+d/2);
        opaque = true;
    };
};

class Image {
public:
    ~Image() {
        clear();
    }
    vector<Shape *> shapes;

    string label;

    void makeRandom(int i);
    void draw(int off_x, int off_y, int w, int h);

    void clear() {
        for (int i = 0; i < shapes.size(); i++) {
            delete shapes[i];
        }
        shapes.clear();
    }
};
