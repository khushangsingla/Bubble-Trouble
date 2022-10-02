#include <simplecpp>
#include "bubble.h"
class Bullet
{
private:
    Rectangle rect; // the rectangle representing the bullet
    double vy; // velocity in y direction

public:
	// Constructor Object
    Bullet(double center_x, double center_y, double width=10, double height=10, double vy_=200, Color color=COLOR(255, 0, 0)) ;

	//Utility Functions
    bool nextStep(double t);
    bool hits(Bubble bubble);
    
	// Private variable access functions
    double get_width();
    double get_height();
    double get_center_x();
    double get_center_y();
    

	
};
