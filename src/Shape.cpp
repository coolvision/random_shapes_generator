//
//  Shape.cpp
//  image_generator
//
//  Created by mb on 30/07/2016.
//
//

#include "Shape.h"

ofPoint rotate(float cx, float cy, float x, float y, float angle) {
    float radians = (M_PI / 180) * angle;
    float c = cos(radians);
    float s = sin(radians);
    ofPoint p;
    p.x = (c * (x - cx)) + (s * (y - cy)) + cx,
    p.y = (c * (y - cy)) - (s * (x - cx)) + cy;
    return p;
}

void getPolygon(vector<ofPoint> &points, int n, float min, float max,
                bool equal, bool sorted, bool check_area) {

    float area = 0;

    while (area < 0.03) {
        float r = 0;

        vector<ofPoint> points_array;
        vector<float> angles;
        ofPolyline polyline;

        if (equal) {
            for (int i = 0; i < n; i++) {
                angles.push_back(i * (360/n));
            }
        } else {
            for (int i = 0; i < n; i++) {
                angles.push_back(ofRandom(1.0) * 360);
            }
        }
        if (sorted) {
            std::sort(angles.begin(), angles.end());
        }

        float min_diff = 360;
        for (int i = 0; i < n-1; i++) {
            float diff = abs(angles[i] - angles[i+1]);
            if (diff < min_diff) {
                min_diff = diff;
            }
        }
        if (min_diff < 20) continue;

        float l = (min + ofRandom(1.0) * max);
        for (int i = 0; i < n; i++) {
            if (!equal) {
                l = (min + ofRandom(1.0) * max);
            }
            r = angles[i];
            ofPoint p = rotate(0, 0, l, 0, r);
            points_array.push_back(p);
            polyline.addVertex(p);
        }

        polyline.close();
        area = abs(polyline.getArea());

//        cout << "area " << area << endl;

        points = points_array;

        if (!check_area) break;
    }
}

void getBoundingBox(vector<ofPoint> &points, ofPoint &min, ofPoint &max) {

    ofRectangle box;
    for(size_t i = 0; i < points.size(); i++) {
        if(i == 0) {
            box.set(points[i],0,0);
        } else {
            box.growToInclude(points[i]);
        }
    }
    min = box.getMin();
    max = box.getMax();
}

void Shape::makeLabel() {
    char l = 'a' + (char)type;
    label = l;
    if (filled) {
        l = 'A' + (char)type;
        label = l;
    }
}

Shape *getRandomShape(int shape_type) {

    Shape *s = NULL;

    if (shape_type == -1) {
        int shape_type = floor(ofRandom(5));
        s = getRandomShape(shape_type);
    } else if (shape_type == 0) {
        s = new Line();
    } else if (shape_type == 1) {
        s = new Triangle();
    } else if (shape_type == 2) {
        s = new Rectangle();
    } else if (shape_type == 3) {
        s = new Circle();
    } else if (shape_type == 4) {
        s = new Square();
    } else if (shape_type == 5) {
        s = new Ellipse();
    } else if (shape_type == 6) {
        s = new Polyline();
    } else if (shape_type == 7) {
        s = new EqualTriangle();
    } else if (shape_type == 8) {
        s = new Pentagon();
    } else if (shape_type == 9) {
        s = new EqualPentagon();
    } else if (shape_type == 10) {
        s = new EqualHexagon();
    } else if (shape_type == 11) {
        s = new CrossedPentagon();
    } else if (shape_type == 12) {
        s = new Quad();
    } else {
        s = new Dot();
    }

    // } else if (shape_type == 0) {
    //     s = new Line();
    // } else if (shape_type == 1) {
    //     s = new Triangle();
    // } else if (shape_type == 2) {
    //     s = new Rectangle();
    // } else if (shape_type == 3) {
    //     s = new Circle();
    // } else if (shape_type == 4) {
    //     s = new Square();
    // } else if (shape_type == 5) {
    //     s = new Ellipse();
    // } else if (shape_type == 6) {
    //     s = new Polyline();
    // } else if (shape_type == 7) {
    //     s = new EqualTriangle();


    // } else if (shape_type == 8) {
    //     s = new Quad();

    // } else if (shape_type == 9) {
    //     s = new Pentagon();
    // } else if (shape_type == 10) {
    //     s = new Hexagon();
    // } else if (shape_type == 11) {
    //     s = new EqualPentagon();
    // } else if (shape_type == 12) {
    //     s = new EqualHexagon();
    // } else if (shape_type == 13) {
    //     s = new CrossedPentagon();
    // } else if (shape_type == 14) {
    //     s = new CrossedHexagon();
    // } else {
    //     s = new Dot();
    // }


    s->makeRandom();


    bool fill = floor(ofRandom(2));
    s->setFilled(fill);

    s->type = shape_type;
    // char l = 'a' + (char)shape_type;
    // s->label = l;
    // if (s->filled) {
    //     l = 'A' + (char)shape_type;
    //     s->label = l;
    // }

    // set a random rotation
    s->angle = ofRandom(0, 180);

    vector<ofPoint> points;
    points.push_back(s->min);
    points.push_back(ofPoint(s->min.x, s->max.y));
    points.push_back(s->max);
    points.push_back(ofPoint(s->max.x, s->min.y));
    for (int i = 0; i < 4; i++) {
        points[i] = rotate(0, 0, points[i].x, points[i].y, -s->angle);
    }
    s->points = points;

    getBoundingBox(points, s->min, s->max);

    if (ofRandom(1.0f) < 0.5) {
        s->tx = -(s->min.x)-0.5f;
    } else {
        s->tx = (1.0f - s->max.x)-0.5f;
    }

    if (ofRandom(1.0f) < 0.5) {
        s->ty = -(s->min.y)-0.5f;
    } else {
        s->ty = (1.0f - s->max.y)-0.5f;
    }
    s->tx *= ofRandom(1.0f);
    s->ty *= ofRandom(1.0f);



    return s;
}

void Image::makeRandom(int i) {

    clear();
    shapes.push_back(getRandomShape(i));

//    int n_shapes = 1;
//    for (int i = 0; i < n_shapes; i++) {
//    }
}
