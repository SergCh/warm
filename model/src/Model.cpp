/**
 * @file tmodel
 * @brief %{Cpp:License:ClassName}
 * @author Чугайнов С.В.
 * @date 17.05.2018
 *
 *
 */

#include "Model.h"

using namespace Snake;

void Model::init() {

    m_rabbits.clear();
    m_snake.start(m_size);
    m_length = 0;
    m_stateGame = IModel::GOOD;
}

void Model::addRabbit() {
    m_rabbits.newRabbit(m_size, m_snake);
}

// сделать шаг (Выдача состояние модели)
std::pair<typename IModel::StateGame, typename IModel::StateSnake> Model::move() {

    if (m_stateGame == IModel::DEAD)
        return std::make_pair(IModel::DEAD, IModel::NOT_CHANGED);

    if (!m_snake.generateNewHead(m_size))
        return std::make_pair(m_stateGame=IModel::DEAD, IModel::NOT_CHANGED);

    m_length += m_rabbits.eat(m_snake.front());

    IModel::StateSnake stateSnake = IModel::MOVED;
    if (m_length < 0) {                         // длина змея уменьшилась
        m_snake.removeTail(2);
        m_length++;
        stateSnake = IModel::MOVED_SHOTER;
    } else if (m_length == 0) {                 // не изменилась длина
        m_snake.removeTail(1);
    } else {                                    // длина змея увеличилась
        m_length--;
        stateSnake = IModel::ADDED;
    }

    if (m_snake.size() < 2)                     // если осталась одна голова, то змей тоже умер
        return std::make_pair(m_stateGame=IModel::DEAD, IModel::NOT_CHANGED);

    return std::make_pair(IModel::GOOD, stateSnake);
}


