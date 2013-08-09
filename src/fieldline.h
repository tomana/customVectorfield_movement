#include "ofMain.h"

class Fieldline {
    public:

    Fieldline();
    Fieldline(float x, float y);
    Fieldline(float x, float y, float xm, float ym);

    float distance(Fieldline * fieldline);
    void update(vector<Fieldline> control);
    void draw();


    float x, y, xm, ym;
    ofColor color;
};
