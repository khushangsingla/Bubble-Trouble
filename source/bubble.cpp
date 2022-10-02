#include "bubble.h"
Bubble::Bubble(double cx, double cy, double r, double acceleration, double vx_, double vy_, Color color_)
{
    // Bubble constructor
    color = color_;
    circle = Circle(cx, cy, r);
    circle.setColor(color);
    circle.setFill(true);
    g=acceleration;
    vx = vx_;
    vy = vy_;
}

void Bubble::nextStep(double t)
{
    // move the bubble
    double new_x = circle.getX() + vx*t;
    //to change the v_y
    double new_y = circle.getY() + vy*t + g*t*t/2;
    vy+=g*t;

    if ((vx < 0 && new_x < (0 + circle.getRadius())) // bounce along X direction at left border
        ||
        (vx > 0 && new_x > (WINDOW_X - circle.getRadius()))) // bounce along X direction at right border
    {

        vx = -vx;
        new_x = circle.getX() + vx*t;

    }

    if ( (vy > 0 && new_y > (450 - circle.getRadius()))/* bounce along Y direction at bottom border*/)
    {
        new_y=circle.getY();
        vy = -vy;
    }

    circle.moveTo(new_x, new_y);
}

double Bubble::get_radius()
{
    // return the radius of the bubble
    return circle.getRadius();
}

double Bubble::get_center_x()
{
    // return the x coordinate of the center of the bubble
    return circle.getX();
}

double Bubble::get_center_y()
{
    // return the y coordinate of the center of the bubble
    return circle.getY();
}

double Bubble::get_vx()
{
    // return the x velocity of the bubble
    return vx;
}
double Bubble::get_vy()
{
    // return the y velocity of the bubble
    return vy;
}

Color Bubble::get_color()
{
    // return the color of the bubble
    return color;
}

double Bubble::get_acc(){
    return g;
}
