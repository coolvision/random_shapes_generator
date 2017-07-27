#include "ofMain.h"
#include "ofApp.h"
#include "Shape.h"

//========================================================================
int main(int argc, char *argv[]){
	//ofSetupOpenGL(400+10+10,300+10,OF_WINDOW);			// <-------- setup the GL context
//	ofSetupOpenGL(4*IMAGE_SIZE*4+IMAGE_PADDING*2*4,
//                  3*IMAGE_SIZE*3+IMAGE_PADDING*3+IMAGE_PADDING*2+IMAGE_PADDING*2,
//                  OF_WINDOW);

    // vector for storing args
    vector<string> myArgs;
    if(argc > 1){
        for(int i = 1; i < argc; i++){
            cout << "arg " << i << " " << argv[i] << endl;
            myArgs.push_back(argv[i]);
        }
    }
    
    ofSetupOpenGL(IMAGE_SIZE*5,
                  IMAGE_SIZE*5,
                  OF_WINDOW);
    
    ofApp *app = new ofApp();
    app->arguments = myArgs;
    ofRunApp(app);
}
