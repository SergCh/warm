#pragma once
/*
	Класс реадизует модель поведения змея

*/


#include <queue>
#include <utility>

#include "Point.h"
#include "Way.h"
#include "TSnake.h"
#include "Rabbit.h"
#include "RabbitFactory.h"


//class RabbitFactory;
//class Rabbit;

template <class TSnake>
class TModel {

public:
    // передача параметров ширины и высоты поля и фабрики кроликов а надо?
    TModel(Point _size, RabbitFactory &_rabbits)
    : m_size(_size), m_rabbits(_rabbits) {}
	
    // состояние змея
    typedef enum {
        DEAD,           ///< Двигаться дальше не может
        GOOD            ///< Может двигаться, длина не изменилась
    } StateGame;

    // изменение змея, надо будкт создать класс змея и убрать в него
    typedef enum {
        NOT_CHANGED,    ///< Не измениля
        ADDED,          ///< Добавился один элемент спереди
        MOVED,          ///< Добавился один элемент спереди и ублася один элемент сзади
        MOVED_SHOTER,   ///< Добавился один элемент спереди и убралось 2 элемента сзади
        STARTED         ///< Начальный короткий змей
    } StateSnake;


    // начало игры
    void init() {

        m_rabbits.clear();
        m_snake.clear();
        int x = m_size.getX() / 2, y = m_size.getY() / 2;
        m_snake.addNewHead(Point(x+1, y));
        m_snake.addNewHead(Point(x, y));
        changeWay(Way::LEFT);
        m_length = 0;
        m_stateGame = TModel::GOOD;
    }

	// получить змея для передачи его на прорисовку
//    std::vector<Point> & getSnake() {return m_snake.date();}
    TSnake & getSnake() {return m_snake;}

	// сменить путь направления змея
    inline void changeWay(Way _way) {m_snake.setWay(_way);}

	// чисто для любопытства, а куда сейчас двигается змей :)
    inline const Way getWay() const {return m_snake.getWay();}

	// добавить кролика (на поле может быть несколько кроликов)
    inline void addRabbit() {m_rabbits.newRabbit(m_size, m_snake);}

    // получить кроликов для прорисовки Надо избавляться от этого метода, оставить только выдачю фабрики
    std::vector<Rabbit> & getRabbits() {
        return m_rabbits.data();
    }

    inline RabbitFactory * getRabbitFactory(){
        return & m_rabbits;
    }

    // сделать шаг (Выдача состояние модели)
    std::pair<TModel::StateGame, TModel::StateSnake> move() {

        if (m_stateGame == TModel::DEAD)
            return std::make_pair(TModel::DEAD, TModel::NOT_CHANGED);

//        Point newHead = m_snake.front();                 // голова змея
//        newHead += getWay().getPoint();

//        if (!newHead.between(m_size))
//            return std::make_pair(m_stateGame=TModel::DEAD, TModel::NOT_CHANGED);

//        if (!m_snake.checkPoint(newHead))
//            return std::make_pair(m_stateGame=TModel::DEAD, TModel::NOT_CHANGED);

        if (!m_snake.generateNewHead(m_size))
            return std::make_pair(m_stateGame=TModel::DEAD, TModel::NOT_CHANGED);

        m_length += m_rabbits.eat(m_snake.front());

//        m_length += m_rabbits.eat(newHead);

//        m_snake.addNewHead(newHead);                // двигаем червя

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

    // надо ли этот метод
    inline TModel::StateGame getStateGame() const {return m_stateGame;}

private:
    // размеры поля
    Point m_size;

	// сам змей, может выделить змея в отдельный класс
    TSnake m_snake;

    // целая фабрика для кроликов
    RabbitFactory &m_rabbits;

	// добавляемая длина при поедании кролика
	int m_length;

    StateGame m_stateGame;
};
