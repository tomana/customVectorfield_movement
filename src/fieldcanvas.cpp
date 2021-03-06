#include "fieldcanvas.h"

//--------------------------------------------------------------
void fieldCanvas::setup(int inputwidth, int inputheight)
{
    n_field = 50;
    field.reserve(n_field*n_field);
    control.reserve(n_field*n_field);
    interpolated.reserve(n_field*n_field);
    width = inputwidth;
    height = inputheight;
    for(int i = 0; i < n_field; i++)
    {
        for(int j = 0; j < n_field; j++)
        {
            float x = ofMap(i, 0, n_field, 0, width);
            float y = ofMap(j, 0, n_field, 0, height);
            Fieldline cur(x,y);
            //Fieldline cur = new Fieldline(x, y);
            cur.xm = ofRandom(-10, 10);
            cur.ym = ofRandom(-10, 10);
            cur.color = ofColor(255,127,0,40);
            field.push_back(cur);
        }
    }


    n = 2000;
    maxage = 100;
    rdodge = 80;
    opacity = 40;
    speed = .01;
    zoom = .005;
    a = new float*[n];
    for (int i = 0; i < n; ++i)
        a[i] = new float[2];
    age = new int[n];
    w = width;
    h = height;
    s = 0.14;
    t = 0.0;
    c = 1.0;
    crayons = true;
    soft = true;
    dodge = false;

    counter = 0;

    makepart();
    reset();
    ofSetBackgroundAuto(false);
    colorset = 0;
    glEnable(GL_BLEND);
    ofEnableAlphaBlending();


}

//--------------------------------------------------------------
void fieldCanvas::update()
{
	    Fieldline * cur;
    for(int i = 0; i < field.size(); i++)
    {
        cur =  &field.at(i);
        cur->update(control);
    }

}

//--------------------------------------------------------------
void fieldCanvas::draw()
{

    //ofBackground(0);
    ofSetColor(0,0,0,2);
    ofRect(0,0,w,h);
    ofSetColor(255);
    //ofDrawBitmapString(ofToString(ofGetFrameRate()),20,20);
    Fieldline * cur;


    ofFill();
    ofSetColor(255,255,255,150);
    for(int i = 0; i < field.size(); i++)
    {
    ofSetLineWidth(1);
        cur = &field.at(i);
        ofSetColor(cur->color);
        ofSetColor(0,0,0,0);
        cur->draw();
    }

    ofFill();
    ofSetColor(255, 0, 0, 255);
    for(int i = 0; i < control.size(); i++)
    {
        ofSetLineWidth(4);
        cur = &control.at(i);
        ofSetColor(cur->color);
        cur->draw();
    }

    for(int i = 0; i < interpolated.size(); i++)
    {
    ofSetLineWidth(1);
        cur = &interpolated.at(i);
        ofSetColor(cur->color);
        cur->draw();
    }



// MOVING PARTICLES
    glEnable(GL_BLEND);
    ofEnableAlphaBlending();
    //ofFill();

    ofPushMatrix();

    ofSetColor(255);
    ofPushMatrix();

    //ofRotateX(PI/2.5);
    ofRotateX(-rotY1);
    ofRotateY(rotX1);


    ofPushMatrix();

    ofSetColor(255);


    for(int i = 0; i < particles.size(); i++)
    {
        ofPoint cur = (ofPoint) particles[i];
//  ellipse(cur.x, cur.y,10,10);
    }

    ofBeginShape();
    for(int i = 0; i < particles.size(); i++)
    {
        ofPoint curi = (ofPoint) particles[i];
        float curipos = abs(sqrt(curi.x*curi.x + curi.y*curi.y));
        ofPoint drawpoint = ofPoint(0,0,0);
        ofPoint drawpoint2 = ofPoint(0,0,0);
        float lastdistance = 10000;
        float lastdistance2 = 10000;
        for(int j = 0; j < particles.size(); j++)
        {
            ofPoint curj = (ofPoint) particles[j];
            float distance = abs(sqrt(pow((curi.x - curj.x),2) + (pow((curi.y - curj.y),2))));
            if(distance < lastdistance && distance > 0)
            {
                lastdistance = distance;
                drawpoint = curj;
            }

            if(distance < lastdistance2 && distance != lastdistance && distance > 0)
            {
                lastdistance2 = distance;
                drawpoint2 = curj;
            }
        }
//ofLine(curi.x, curi.y,drawpoint.x, drawpoint.y);
//ofLine(curi.x, curi.y,drawpoint2.x, drawpoint2.y);
    }
    ofEndShape();
    ofPopMatrix();



    ofSetColor(ofRandom(0,255));


    if ( counter < 2)
    {
        counter++;
    }
    else
    {
        counter = 0;
    }
//drawfur(counter);

    drawfur2();

    ofPopMatrix();

    ofPopMatrix();

    ofSetColor(255);
    //ofDrawBitmapString(ofToString(ofGetFrameRate()),20,20);
}

//--------------------------------------------------------------
void fieldCanvas::keyPressed(int key)
{
    if (key == ' ')
    {
        control.clear();
    }

    if (key == 'z') {
        s -= 0.01;
        cout << s << endl;
    }
    if (key == 'x') {
        s += 0.01;
        cout << s << endl;
    }
}

//--------------------------------------------------------------
void fieldCanvas::keyReleased(int key)
{

}

//--------------------------------------------------------------
void fieldCanvas::mouseMoved(int x, int y)
{

}

//--------------------------------------------------------------
void fieldCanvas::mouseDragged(int x, int y, int button)
{

 cout << "mouseDragged: " << x << ", " << y << " button: " << button << endl;

    if (button == 0) {
    Fieldline * cur =  &control.back();
    if (abs(x - cur->x) < 0.01) {

    return;
    }
    if (abs(y - cur->y) < 0.01) {

    return;
    }
    cur->xm = x - cur->x;
    cur->ym = y - cur->y;
    }

    if(button == 2) {
    Fieldline * cur;
        for(int i = 0; i < control.size(); i++)
        {
        cur = &control.at(i);
        ofSetColor(cur->color);
        cur->x = (x - savedX) + cur->x;
        cur->y = (y - savedY) + cur->y;
        }

    }


    savedX = x;
    savedY = y;

}

//--------------------------------------------------------------
void fieldCanvas::mousePressed(int x, int y, int button)
{
    if(button == 0) {
    Fieldline mouse(x, y, 0, 0);
    mouse.color = ofColor(255,255,255,60);
    control.push_back(mouse);
    }

    savedX = x;
    savedY = y;

}

//--------------------------------------------------------------
void fieldCanvas::mouseReleased(int x, int y, int button)
{
Fieldline * cur;
    for(int i = 0; i < field.size(); i++)
    {
        cur =  &field.at(i);
        cur->update(control);
    }
}

ofVec2f fieldCanvas::getInterpV(int x, int y)
{

    int xpos = (float(x) /float(ofGetWidth()))*n_field;
    int ypos = (float(y) /float(ofGetHeight()))*n_field;

    if ((xpos+1) < n_field & (ypos+ 1) < n_field && (xpos) > -1 & (ypos) > -1)
    {

        Fieldline * cur00 = &field.at((xpos*n_field) + ypos);
        float x1 = cur00->x;
        float y1 = cur00->y;


        Fieldline * cur10 = &field.at((xpos+1)*n_field + (ypos));
        float x2 = cur10->x;


        Fieldline * cur01 = &field.at((xpos)*n_field + (ypos +1));
        float y2 = cur01->y;


        Fieldline * cur11 = &field.at(((xpos+1)*n_field) + (ypos +1));


        float norm = 1./((x2-x1)*(y2-y1));

        float v_xy_x = norm*(cur00->xm*((x2 - x)*(y2 - y))
                             + cur10->xm*((x - x1)*(y2 - y))
                             + cur01->xm*((x2 - x)*(y - y1))
                             + cur11->xm*((x - x1)*(y - y1)));
        float v_xy_y = norm*(cur00->ym*((x2 - x)*(y2 - y))
                             + cur10->ym*((x - x1)*(y2 - y))
                             + cur01->ym*((x2 - x)*(y - y1))
                             + cur11->ym*((x - x1)*(y - y1)));

        float length = sqrt(v_xy_x*v_xy_x + v_xy_y*v_xy_y);

        //Fieldline interp(x, y, v_xy_x, v_xy_y);
        //interp.color = ofColor(0,255,0,255);
        //interpolated.push_back(interp);

        if (length == 0)
        {
        return ofVec2f(0,0);
        }
        //float test[2] =
        //{v_xy_x, v_xy_y};
        return ofVec2f(v_xy_x, v_xy_y);
    }
        return ofVec2f(0,0);
}
//--------------------------------------------------------------
void fieldCanvas::windowResized(int w, int h)
{

}

//--------------------------------------------------------------
void fieldCanvas::gotMessage(ofMessage msg)
{

}

//--------------------------------------------------------------
void fieldCanvas::dragEvent(ofDragInfo dragInfo)
{

}

void fieldCanvas::makepart()
{
    particles = {};
    for(int i = 0; i < 1000; i++)
    {

        particles.push_back(ofPoint(ofRandom(0,w), ofRandom(0,h)));

    }
}

void fieldCanvas::reset()
{
//  background(crayons ? 0 : #ffffff);
    if(zoom != 0)
    {
        s = 0.14;
        c = 0;
    }

    t = 58.9;

    ofSeedRandom(ofRandom(100));
    cout << t << endl;
    // 58.9 er bra
    ofSetColor(0,5);
    //ofRect(0,0,width,height);
}

void fieldCanvas::newp(int p,float x, float y)
{
    if(dodge)
    {
        // particle inside a circle around the mouse position
        float r = ofRandom(80);
        ang = ofRandom(TWO_PI*10);
        a[p][0] = x + r * cos(ang);
        a[p][1] = y + r * sin(ang);
    }
    else
    {
        // particle anywhere on screen
        a[p][0] = ofRandom(0,width);
        a[p][1] = ofRandom(0,height);
    }
    age[p] = 0;
}

void fieldCanvas::drawfur2( )
{
    int np = n / maxage;
    ofPoint xp2 = (ofPoint) particles[int(ofRandom(particles.size()))];
    float xpos2 = xp2.x;
    float ypos2 = xp2.y;;
    for(int i=0; i<np & c<n; i++, c++) newp(c,xpos2, ypos2);
    // draw particle traces
    for(int i=0; i<n; i++)
    {
        age[i]++;
        float* p = a[i];

        ofPoint xp = (ofPoint) particles[int(ofRandom(particles.size()))];
        float xpos = xp.x;
        float ypos = xp.y;;
        if (age[i] > maxage) newp(i,xpos,ypos);
        else
        {
            float f[] =  { getInterpV(p[0], p[1])[0], getInterpV(p[0], p[1])[1] };
            // opacity based on speed (soft mode) or age (hard mode)
            int m = maxage/2.0;
            //float o = soft ? ofDist(0,0,f[0], f[1]) * 2 * opacity : (m - abs(m - age[i])) * opacity/m;
            // hue based on direction
            //float h =  atan2(f[0], f[1]) + PI;
            //cout << f[0] << endl;
            //cout << f[1] << endl;
//      stroke(h, crayons ? 0 : 0, crayons ? 0 : 0, o);
            ofColor testc = ofColor(ofClamp(255,0,age[i]));
            //testc.setBrightness();

            float* c = new float[2];
            memcpy(c, p, 2 * sizeof(float));
//      fill(constrain(age[i]*10,0,170),constrain(age[i]*10,0,170) ,constrain(age[i]*10,0,170), 150);

            ofNoFill();

            //noSmooth();
//      noStroke();
            //ofColor farge = face.getColor(int(1)+width/2,int(1)+height/2);
            //ofSetColor(farge);

            /**
            glBegin(GL_POLYGON);
            glVertex3f(p[0]-0.1, p[1]-0.1,0);
            glVertex3f(p[0] += s*f[0],  p[1] += s*f[1],age[i] += s*f[1]);
            glVertex3f(p[0]+0.1, p[1]+0.1,0);
            glEnd();
            glBegin(GL_POLYGON);
            glVertex3f(p[0]-0.1, p[1]-0.1,0);
            glVertex3f(p[0] += s*f[0],  p[1] += s*f[1],0);
            glVertex3f(p[0]+0.1, p[1]+0.1,0);
            glEnd();
            **/

            p[0] = p[0] + s*f[0];
            p[1] = p[1] + s*f[1];
            testc.setSaturation(0);

            ofColor farge;
            ofFill();
                testc = ofColor(255);

            ofColor musclec;
             musclec = ofColor(255);
//farge.setHue(ofMap(ofClamp(age[i]*5, 0, 255),0,255,100,255));
//farge.setSaturation(colorset);
//farge.setSaturation(255);
//cout <<ofMap(ofClamp(age[i]*10, 0, 255),0,255,0,10)<< endl;

            farge = musclec;

            float val1 =  255 - 2*abs(255/2.0 - ofMap((ofClamp(age[i], 0, maxage)),0,maxage,0,255));
//cout << val1 << endl;
//cout << age[i] << endl;
            //farge.setBrightness(val1);
            ofSetColor(255,val1);
            //float val1s =  10 - 2*abs(10/2.0 - ofMap((ofClamp(age[i], 0, maxage)),0,maxage,0,10));
            ofSetLineWidth(1);
            ofLine(p[0],p[1], 0, c[0], c[1],0);

            //float val2 =  ofMap(ofClamp(age[i]+1, 0, maxage),0,maxage,0,255);
//cout << val2 << endl;
            //farge.setBrightness(val2);

            //ofSetColor(farge,testc.getBrightness());
            //ofSetLineWidth(4);
            //ofLine(p[0],p[1],0, c[0], c[1],0);


            //ofLine(p[0],p[1],-(age[i]-1), c[0], c[1],-age[i]);
            delete c;
        }
//    stroke(0);
        ofSetColor(255);
    }


}

