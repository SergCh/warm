#include "Rabbit.h"


void Rabbit::eat(const Point & _head) {
    if (m_live == 0) //уже мертвый
        return;

    if (check(_head)) { //съели
        m_live = 0;
        return;
    }

    if (m_live < 0)  // сам не умерает
        return;
    if (--m_live == 0) { // сам умер
        m_weight = -1;
    }
}

