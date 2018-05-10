
#include "View.h"
#include "Control.h"
#include "Rabbit.h"

View::View() : m_control(0){
    m_rabbits = 0;
    m_snake = 0;
    m_way = Way::LEFT;
}

