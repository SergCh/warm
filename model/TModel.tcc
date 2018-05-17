#pragma once

/**
 * @file tmodel
 * @brief %{Cpp:License:ClassName}
 * @author Чугайнов С.В.
 * @date 17.05.2018
 *
 *
 */

template <class T_Snake>
void TModel<T_Snake>::init() {

    m_rabbits.clear();
    m_snake.start(m_size);
    m_length = 0;
    m_stateGame = TModel::GOOD;
}


template <class T_Snake>
void TModel<T_Snake>::changeWay(Way _way) {
    m_snake.m_way = _way;
}


template <class T_Snake>
void TModel<T_Snake>::addRabbit() {
//    std::vector<Point> points;
    m_rabbits.newRabbit(m_size, m_snake);
}


// сделать шаг (Выдача состояние модели)
template <class T_Snake>
std::pair<int, int> TModel<T_Snake>::move() {
//std::pair<TModel<T_Snake>::StateGame, TModel<T_Snake>::StateSnake> TModel<T_Snake>::move() {

    if (m_stateGame == TModel::DEAD)
        return std::make_pair(TModel::DEAD, TModel::NOT_CHANGED);

    if (!m_snake.generateNewHead(m_size))
        return std::make_pair(m_stateGame=TModel::DEAD, TModel::NOT_CHANGED);

    m_length += m_rabbits.eat(m_snake.front());

    TModel::StateSnake stateSnake = TModel::MOVED;
    if (m_length < 0) {                         // длина змея уменьшилась
        m_snake.removeTail(2);
        m_length++;
        stateSnake = TModel::MOVED_SHOTER;
    } else if (m_length == 0) {                 // не изменилась длина
        m_snake.removeTail(1);
    } else {                                    // длина змея увеличилась
        m_length--;
        stateSnake = TModel::ADDED;
    }

    if (m_snake.size() < 2)                     // если осталась одна голова, то змей тоже умер
        return std::make_pair(m_stateGame=TModel::DEAD, TModel::NOT_CHANGED);

    return std::make_pair(TModel::GOOD, stateSnake);
}


