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
        : IModel(), m_size(_size), m_snake(_snake), m_stateGame(DEAD) {}


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
        inline IModel::StateGame getStateGame() const {return m_stateGame;}
        RabbitFactory * getRabbitFactory() {return & m_rabbits;}


    protected:

        ISnake & m_snake;

        // добавляемая длина при поедании кролика
        int m_length;
        // размеры поля
        Point m_size;

        // целая фабрика для кроликов
        RabbitFactory m_rabbits;

        StateGame m_stateGame;
    };

}
