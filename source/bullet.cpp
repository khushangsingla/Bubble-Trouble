#include "bullet.h"
Bullet::Bullet(double center_x, double center_y, double width, double height, double vy_, Color color) {
    // Bullet constructor
    rect = Rectangle(center_x, center_y, width, height);
    rect.setColor(color);
    rect.setFill(true);
    vy = vy_;
}

bool Bullet::nextStep(double t){
    // move the bullet
    double new_y = rect.getY() - vy*t;
    if(new_y < (0-rect.getHeight()/2.0))   // out of canvas, so delete it
    {
        return false;
    }
    rect.moveTo(rect.getX(), new_y);
    return true;
}

double Bullet::get_width(){
    // return the width of the bullet
    return rect.getWidth();
}

double Bullet::get_height(){
    // return the height of the bullet
    return rect.getHeight();
}

double Bullet::get_center_x(){
    // return the x coordinate of the center of the bullet
    return rect.getX();
}

double Bullet::get_center_y(){
    // return the y coordinate of the center of the bullet
    return rect.getY();
}

bool Bullet::hits(Bubble bubble){
    if(rect.getX()+rect.getWidth()/2>bubble.get_center_x()-bubble.get_radius() && rect.getX()-rect.getWidth()/2<bubble.get_center_x()+bubble.get_radius() && rect.getY()+rect.getHeight()/2>bubble.get_center_y()-bubble.get_radius() && rect.getY()-rect.getHeight()/2<bubble.get_center_y()+bubble.get_radius()){
        return true;
    }
    return false;
}

