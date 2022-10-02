#include <simplecpp>
#include "bullet.h"

/* Shooter Vars */
const int SHOOTER_START_X = 250;
const int SHOOTER_START_Y = 425;
const int SHOOTER_VX = 400;




class Shooter
{
private:
    Rectangle body; // The body of the shooter
    Circle head;    // The head of the shooter
    double vx;      // The x-velocity of the shooter
    Color color;    // The color of the shooter

public:
    Shooter(double position_x, double position_y, double vx_=100, double height=30, double width=18, double head_radius=9, Color color_=COLOR(0, 255, 0));
    

    Bullet shoot();
    

    void move(double t, bool is_moving_left);
    

    double get_head_center_x();
    

    double get_head_center_y();
    

    double get_head_radius();
    

    double get_body_center_x();
    

    double get_body_center_y();
    

    double get_body_width();
    

    double get_body_height();
    
    bool check_if_dead(Bubble bubble);
};
