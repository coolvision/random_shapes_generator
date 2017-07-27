#include "ofApp.h"

float bg_color = 255;

void ofApp::setup(){

    ofBackground(bg_color);
    ofSetFrameRate(60);
    ofSeedRandom();

    fbo.allocate(IMAGE_SIZE, IMAGE_SIZE, GL_RGB);

    ofTrueTypeFont::setGlobalDpi(72);
    font.load("DejaVuSansMono.ttf", 8, true, true);

    path = "";
    train_images_n = 10;
    test_images_n = 10;

    if (arguments.size() >= 3) {
        path = arguments[0];
        train_images_n = ofToInt(arguments[1]);
        test_images_n = ofToInt(arguments[2]);
    }
    randomPanes();
}


void ofApp::generateImages(string path, string images_dir_name,
    string list_name, int images_n) {

    ofstream file_list;
    string file_list_path = path + "/" + list_name;
    file_list.open(file_list_path);
    cout << "open " << file_list_path << endl;

    int batch_size = MIN(images_n, 5000);
    int batches_n = MAX(1, images_n/batch_size);

    cout << "batches_n " << batches_n << " batch_size " << batch_size << endl;

    ofDirectory dir;
    string images_path = path + "/" + images_dir_name;
    dir.createDirectory(images_path, false);
    cout << "create " << images_path << endl;

    for (int tk = 0; tk < batches_n; tk++) {

        ofDirectory sub_dir;
        string sub_dir_path = images_path + "/images_" + ofToString(tk);
        sub_dir.createDirectory(sub_dir_path, false);

        cout << "create " << sub_dir_path << endl;

        // make a dir for 5k images
        for (int i = 0; i < batch_size; i++) {

            Image img;
            img.makeRandom();

            //cout << "makeRandom" << endl;

            fbo.begin();
            ofClear(bg_color);

            img.draw(0, 0, IMAGE_SIZE, IMAGE_SIZE);

            fbo.end();

            //cout << "fbo.end()" << endl;

            fbo.readToPixels(pixels);

            //cout << "fbo.readToPixels" << endl;
            string filename;
            // if (img.shapes[0]->filled) {
            //     filename = ofToString(i) + "_" + img.shapes[0]->label + "_filled.png";
            // } else {
                filename = ofToString(i) + "_" + img.shapes[0]->label + ".png";
            // }
            ofSaveImage(pixels, ofToString(sub_dir_path + "/" + filename));

            file_list << sub_dir_path + "/" + filename << endl;

            if (i % 100 == 0)
                cout << "save " << sub_dir_path + "/" + filename << endl;
        }
    }
    file_list.close();
}

void ofApp::generateDataset(string path, int train_images_n, int test_images_n) {

    if (train_images_n == 0) return;

    ofDirectory dir;
    dir.createDirectory(path, false);
    cout << "create " << path << endl;

    ofstream labels_list;
    labels_list.open(path + "/labels.txt");
    for (int i = 0; i < SHAPES_N; i++) {
        labels_list << shapeLabel((ShapeType)i) << endl;
    }
    // for (int i = 0; i < SHAPES_N; i++) {
    //     labels_list << shapeLabel((ShapeType)i) << "_filled" << endl;
    // }
    labels_list.close();

    generateImages(path, "train", "train.list", train_images_n);
    generateImages(path, "test", "test.list", test_images_n);
}

void ofApp::randomPanes() {

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            img[i][j].makeRandom();
        }
    }
}

void ofApp::update(){


}

void ofApp::draw(){

    int size = IMAGE_SIZE;
    int pad = IMAGE_PADDING;
    int pad_y = IMAGE_PADDING*2;

    int pane_w = 0;
    int pane_h = 0;

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            img[i][j].draw(i*size, j*size, size, size);
        }
    }

    ofSetColor(ofColor::blueSteel);
    ofDisableAntiAliasing();
    ofSetLineWidth(1.0f);

    if (generate_dataset) {
        generate_dataset = false;
        //generateDataset(path, train_images_n, test_images_n);
        generateDataset("/Users/sk/data/shapes", 10, 10);
    }
    
    for (int i = 0; i < 5; i++) {
        ofDrawLine(size*i, 0,
                   size*i, ofGetWindowHeight());
        ofDrawLine(0, size*i,
                   ofGetWindowWidth(), size*i);
    }
}

//------  --------------------------------------------------------
void ofApp::keyPressed(int key){
    if( key == 'u' ) {
        randomPanes();
    }
    if( key == 'd' ) {
        generate_dataset = true;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
