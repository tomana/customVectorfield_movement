#pragma once

#include "ofMain.h"
#include "fieldline.h"

class fieldCanvas
{
public:
    void setup(int width, int height);
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    float* getInterpV(int x, int y);

    vector<Fieldline> field;
    vector<Fieldline> control;
    vector<Fieldline> interpolated;
    int n_field;

    int width;
    int height;
    int n;
    int maxage;
    int rdodge;
    int opacity;
    float speed;
    float zoom;
    float** a;
    int* age;
    float w, h, s;
    float t, c;
    bool crayons, soft, dodge;

    int counter;

    float rotX1;
    float rotY1;

    int savedX;
    int savedY;

    vector<ofPoint> particles;
    void makepart();
    void reset();
    void drawfur2();
    void newp(int p,float x, float y);
    float* f_thing(float x, float y);
    float* f2_thing(float x, float y);
    int colorset;
    float ang;
};
