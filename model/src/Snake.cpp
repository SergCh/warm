/**
 * @file Snake.cpp
 * @brief Snake
 * @author Чугайнов С.В.
 * @date 11.05.2018
 *
 *
 */
#include "Snake.h"

Snake::Snake() {
//    m_factory = 0;
}


void Snake::removeTail(int _count) {
    while (_count-- > 0 && !m_snake.empty())
        m_snake.pop_back();
}


