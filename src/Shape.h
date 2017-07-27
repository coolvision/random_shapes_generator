//
//  Shape.h
//  image_generator
//
//  Created by mb on 30/07/2016.
//
//

#pragma once

#include "ofMain.h"
#include "Shape.h"

#define IMAGE_SIZE 104
#define IMAGE_PADDING 10
#define IMAGE_SIZE_SAVE 64

enum ShapeType {
    ANY = -1,
    LINE = 0,
    POLYLINE,
    TRIANGLE,
    RECTANGLE,
    CIRCLE,
    SQUARE,
    DOT,
    ELLIPSE,
    PENTAGON,
    HEXAGON,
    SHAPES_N
};

std::string shapeLabel(ShapeType t);

class Shape {
public:
    Shape(): angle(0), filled(false), area(0), length(0), opaque(false) {}
    virtual ~Shape() {};
    ofPoint center;
    ofPoint min;
    ofPoint max;
    float angle;
    float width;
    float height;
    float area;
    float length;
    string label;

    int vertices_n;
    int line_segments_n;

    bool filled;
    bool opaque;

    vector<ofPoint> v;

    // "symmetric", "filled", etc...
    vector<string> tags;

    virtual void makeRandom() = 0;
    virtual void draw(int off_x, int off_y, int w, int h) = 0;
    void setFilled(bool filled_in) {
        filled = filled_in;
    }
};
//
//class Polygon: public Shape {
//    
//    void init(ofPoint center, float r) {
//        label = shapeLabel(TRIANGLE);
//        min.set(MIN(p1.x, MIN(p2.x, p3.x)), MIN(p1.y, MIN(p2.y, p3.y)));
//        max.set(MAX(p1.x, MAX(p2.x, p3.x)), MAX(p1.y, MAX(p2.y, p3.y)));
//        v.resize(3);
//        v[0] = p1;
//        v[1] = p2;
//        v[2] = p3;
//        center = (p1 + p2 + p3) / 3;
//        line_segments_n = 3;
//        vertices_n = 3;
//        width = max.x - min.x;
//        height = max.y - min.y;
//        area = abs((p1.x*(p2.y-p3.y)+p2.x*(p3.y-p1.y)+p3.x*(p1.y-p2.y))/2);
//    }
//    
//    void makeRandom() {
//        area = 0.0f;
//        while (area < 0.04 || area > 0.25)
//            init(ofPoint(ofRandom(0.1f, 0.9f), ofRandom(0.1f, 0.9f)),
//                 ofPoint(ofRandom(0.1f, 0.9f), ofRandom(0.1f, 0.9f)),
//                 ofPoint(ofRandom(0.1f, 0.9f), ofRandom(0.1f, 0.9f)));
//    }
//    
//    void draw(int off_x, int off_y, int w, int h);
//};
//
//class Pentagon: public Polygon {
//
//};
//
//class Hexagon: public Polygon {
//    
//    
//    
//};
//
//class Polyline: public Shape {
//    
//    
//    
//};
//
//class Ellipse: public Shape {
//
//    
//    
//};

class Line: public Shape {
public:
    void init(ofPoint p1, ofPoint p2) {
        label = shapeLabel(LINE);
        v.resize(2);
        v[0] = p1;
        v[1] = p2;
        center = (p1 + p2) / 2;
        line_segments_n = 1;
        vertices_n = 0;
        min.set(MIN(p1.x, p2.x), MIN(p1.y, p2.y));
        max.set(MAX(p1.x, p2.x), MAX(p1.y, p2.y));
        width = max.x - min.x;
        height = max.y - min.y;
        length = ofDist(p1.x, p1.y, p2.x, p2.y);
        //cout << "length " << length << " " << p1.x << " " << p1.y << " " << p2.x << " " << p2.y << endl;
    }
    void makeRandom() {
        length = 0.0f;
        while (length < 0.25)
            init(ofPoint(ofRandom(1.0f), ofRandom(1.0f)),
                 ofPoint(ofRandom(1.0f), ofRandom(1.0f)));
        //cout << "final length " << length << endl;
    }
    void draw(int off_x, int off_y, int w, int h);
};

class Triangle: public Shape {
public:
    void init(ofPoint p1, ofPoint p2, ofPoint p3) {
        label = shapeLabel(TRIANGLE);
        min.set(MIN(p1.x, MIN(p2.x, p3.x)), MIN(p1.y, MIN(p2.y, p3.y)));
        max.set(MAX(p1.x, MAX(p2.x, p3.x)), MAX(p1.y, MAX(p2.y, p3.y)));
        v.resize(3);
        v[0] = p1;
        v[1] = p2;
        v[2] = p3;
        center = (p1 + p2 + p3) / 3;
        line_segments_n = 3;
        vertices_n = 3;
        width = max.x - min.x;
        height = max.y - min.y;
        area = abs((p1.x*(p2.y-p3.y)+p2.x*(p3.y-p1.y)+p3.x*(p1.y-p2.y))/2);
    }
    void makeRandom() {
        area = 0.0f;
        while (area < 0.04 || area > 0.25)
            init(ofPoint(ofRandom(0.1f, 0.9f), ofRandom(0.1f, 0.9f)),
                 ofPoint(ofRandom(0.1f, 0.9f), ofRandom(0.1f, 0.9f)),
                 ofPoint(ofRandom(0.1f, 0.9f), ofRandom(0.1f, 0.9f)));
    }
    void draw(int off_x, int off_y, int w, int h);
};

class Rectangle: public Shape {
public:
    void init(ofPoint center, float w, float h, float angle) {
        label = shapeLabel(RECTANGLE);
        this->center = center;
        width = w;
        height = h;
        area = width * height;
        this->angle = angle;
    }
    virtual void makeRandom() {
        area = 0.0f;
        width = 1.0f;
        height = 1.0f;
        while (area < 0.04 || area > 0.4 ||
            center.x - width/2 < 0 || center.x + width/2 > 1 ||
            center.y - height/2 < 0 || center.y + height/2 > 1 ||
            abs(1.0f-float(width)/float(height)) < 0.2) {
            init(ofPoint(ofRandom(0.1f, 0.9f), ofRandom(0.1f, 0.9f)),
                 ofRandom(0.1f, 0.9f),
                 ofRandom(0.1f, 0.9f),
                 ofRandom(0.0f, 180.0f));
        }
    };
    void draw(int off_x, int off_y, int w, int h);
};

class Circle: public Shape {
public:
    void init(ofPoint center, float r) {
        label = shapeLabel(CIRCLE);
        this->center = center;
        this->r = r;
        line_segments_n = 0;
        vertices_n = 0;
        min = center - ofPoint(r, r);
        max = center + ofPoint(r, r);
        width = max.x - min.x;
        height = max.y - min.y;
        area = M_PI * pow(r, 2);
    }
    float r;
    virtual void makeRandom() {
        area = 0.0f;
        ofPoint min = ofPoint(ofRandom(0.2f, 0.8f), ofRandom(0.2f, 0.8f));
        float d = ofRandom(0.2f, MIN(0.7, MIN(1.0f - min.x, 1.0f - min.y)));
        init(min+ofPoint(d/2, d/2), d/2);
    };
    void draw(int off_x, int off_y, int w, int h);
};

// optional
class Square: public Rectangle {
public:
    void init(ofPoint center, float side, float angle) {
        Rectangle::init(center, side, side, angle);
        label = shapeLabel(SQUARE);
    }
    void makeRandom() {
        while (area < 0.04 || area > 0.4 ||
               center.x - width/2 < 0 || center.x + width/2 > 1 ||
               center.y - height/2 < 0 || center.y + height/2 > 1) {
            init(ofPoint(ofRandom(0.1f, 0.9f), ofRandom(0.1f, 0.9f)),
                 ofRandom(0.1f, 0.9f),
                 ofRandom(0.0f, 180.0f));
        }
    };
};

class Dot: public Circle {
public:
    void init(ofPoint center) {
        Circle::init(center, 0.05);
        label = shapeLabel(DOT);
        setFilled(true);
        opaque = true;
    }
    virtual void makeRandom() {
        ofPoint center = ofPoint(ofRandom(0.05, 0.95f), ofRandom(0.05, 0.95f));
        init(center);
    };
};

class Image {
public:
    ~Image() {
        clear();
    }
    vector<Shape *> shapes;

    string label;

    void makeRandom();
    void draw(int off_x, int off_y, int w, int h);

    void clear() {
        for (int i = 0; i < shapes.size(); i++) {
            delete shapes[i];
        }
        shapes.clear();
    }
};
