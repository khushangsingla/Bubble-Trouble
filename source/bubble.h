#include <simplecpp>

/* Bubble Vars */
const int BUBBLE_START_X = 250;
const int BUBBLE_START_Y = 50;
const int BUBBLE_DEFAULT_RADIUS = 10;
const int BUBBLE_RADIUS_THRESHOLD = 10;
const int BUBBLE_DEFAULT_VX = 100;
const int BUBBLE_DEFAULT_VY = 0;
/* Game Window Vars */
const int WINDOW_X = 500;
const int WINDOW_Y = 500;

class Bubble
{
private:
    Circle circle;  // the circle representing the bubble
    double vx, vy;  // velocity in x and y direction
    Color color;    // color of the bubble
    double g;       //acceleration of the vall
public:
	// Constructor Object
    Bubble(double cx, double cy, double r, double acceleration, double vx_=BUBBLE_DEFAULT_VX, double vy_=BUBBLE_DEFAULT_VY, Color color_=COLOR(0, 0, 255));
    

	// Utility Functions
    void nextStep(double t);

	// Get functions
    double get_radius();
    double get_center_x();
    double get_center_y();
    double get_vx();
    double get_vy();
    Color get_color();
    double get_acc();
};
