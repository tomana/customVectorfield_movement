#include "fieldline.h""


Fieldline::Fieldline() {

}

Fieldline::Fieldline(float x, float y)
{
    this->x = x;
    this->y = y;
}

Fieldline::Fieldline(float x, float y, float xm, float ym)
{
    this->x = x;
    this->y = y;
    this->xm = xm;
    this->ym = ym;
}

float Fieldline::distance(Fieldline * fieldLine)
{
    return ofDist(x, y, fieldLine->x, fieldLine->y);
}

void Fieldline::update(vector<Fieldline> control)
{
    if(control.size() > 0)
    {
        float weights[control.size()];
        float sum = 0;
        for(int i = 0; i < control.size(); i++)
        {
            Fieldline * cur = &control.at(i);
            weights[i] = distance(cur);
            weights[i] = 1 / weights[i]; // inverse
            weights[i] *= weights[i]; // square
            sum += weights[i];
        }

        xm = 0;
        ym = 0;
        for(int i = 0; i < control.size(); i++)
        {
            weights[i] /= sum;
            Fieldline * cur = & control.at(i);
            xm += cur->xm * weights[i];
            ym += cur->ym * weights[i];
        }
    }
}

void Fieldline::draw()
{
    ofLine(x, y, x + xm, y + ym);
}

