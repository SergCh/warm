#pragma once
/*
	Класс реадизует модель поведения змея

*/


#include <queue>
#include <utility>

#include "IModel.h"
#include "Point.h"
#include "Way.h"
//#include "TSnake.h"
#include "Rabbit.h"
#include "RabbitFactory.h"

namespace SNAKE_MODEL {

    class ISnake;

    class Model : public IModel {

    public:
        // передача параметров ширины и высоты поля
        Model(Point _size, ISnake & _snake)
        : IModel(_size), m_snake(_snake) {}


        // начало игры
        void init();

        // получить змея для передачи его на прорисовку
        ISnake & getSnake() {
            return m_snake;
        }

        // сменить путь направления змея
        void changeWay(Way _way) {
            m_snake.m_way = _way;
        }

        // добавить кролика (на поле может быть несколько кроликов)
        void addRabbit();

        // сделать шаг (Выдача состояние модели)
        std::pair<IModel::StateGame, IModel::StateSnake> move();

    protected:

        ISnake & m_snake;

        // добавляемая длина при поедании кролика
        int m_length;

    };

}
