#pragma once

#include "ofMain.h"
#include "Shape.h"
//#include "Rules.h"

class ofApp : public ofBaseApp{
public:

//    Pane p[12]; // p1, p2, p3, p4;
//    Pane pane;

    Image img[5][5];

    std::vector<std::string> arguments;
    string path;
    int train_images_n;
    int test_images_n;

    // for simple dataset
    //Image i1;
    //Image i2;

    ofFbo fbo;
    //ofFbo fbo_panes;

    ofPixels pixels;

 //   ofFbo fbo_4images;

    bool generate_dataset = false;
    
    ofTrueTypeFont font;

    ofImage b_images[12];
    void saveImagesColumn(string filename, string save_name);

    void setup();
    void update();
    void draw();

    void randomPanes();
    //void generateDataset(string dir_name, int images_n);
    void generateDataset(string path, int train_images_n, int test_images_n);
    void generateImages(string path, string images_dir_name,
        string list_name, int images_n);

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );

    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void mouseDragged(int x, int y, int button);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

};
