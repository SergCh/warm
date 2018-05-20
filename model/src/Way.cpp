
#include "Way.h"
#include "Point.h"

using namespace Snake;

const Point Way::POINTS_WAY[Way::COUNT_WAYS] = {
    /*UP*/    Point( 0, -1),                /// UP
    /*DOWN*/  Point( 0,  1),                /// DOWN
    /*LEFT*/  Point(-1,  0),                /// LEFT
    /*RIGHT*/ Point( 1,  0)                 /// RIGHT
};
