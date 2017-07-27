//
//  Shape.cpp
//  image_generator
//
//  Created by mb on 30/07/2016.
//
//

#include "Shape.h"
//#include "Rules.h"

std::string shapeLabel(ShapeType t) {
    switch(t) {
        case LINE:
            return "line";
        case TRIANGLE:
            return "triangle";
        case RECTANGLE:
            return "rectangle";
        case CIRCLE:
            return "circle";
        case SQUARE:
            return "square";
        case DOT:
            return "dot";
        default:
            return "any";
    }
}

Shape *getRandomShape(ShapeType shape_type) {

    Shape *s = NULL;

    if (shape_type == ANY) {
        int shape_type = floor(ofRandom(6));
        s = getRandomShape((ShapeType)shape_type);
    } else if (shape_type == LINE) {
        s = new Line();
    } else if (shape_type == TRIANGLE) {
        s = new Triangle();
    } else if (shape_type == RECTANGLE) {
        s = new Rectangle();
    } else if (shape_type == CIRCLE) {
        s = new Circle();
    } else if (shape_type == SQUARE) {
        s = new Square();
    } else {
        
        
        s = new Dot();
    }

    s->makeRandom();

    bool fill = floor(ofRandom(2));
    s->setFilled(fill);

    return s;
}

void Image::makeRandom() {

    clear();

    //int n_shapes = floor(ofRandom(1, 4));
    int n_shapes = 1;
    
    //cout << "n_shapes " << n_shapes << endl;

    for (int i = 0; i < n_shapes; i++) {
        shapes.push_back(getRandomShape(ANY));
    }
}
