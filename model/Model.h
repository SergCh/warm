#pragma once
/*
	Класс реадизует модель поведения змея

*/


#include <queue>
#include <utility>

#include "Point.h"
#include "Way.h"
#include "Snake.h"
#include "Rabbit.h"
#include "RabbitFactory.h"


//class RabbitFactory;
//class Rabbit;

class Model {

public:
    // передача параметров ширины и высоты поля и фабрики кроликов а надо?
    Model(Point _size, RabbitFactory &_rabbits)
    : m_size(_size), m_rabbits(_rabbits) {}
//    ~Model(void) {}
	
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
        m_way = Way::LEFT;
        m_length = 0;
        m_stateGame = Model::GOOD;
    }

	// получить змея для передачи его на прорисовку
    std::vector<Point> & getSnake() {return m_snake.data();}

	// сменить путь направления змея
    inline void changeWay(Way _way) {m_way = _way;}

	// чисто для любопытства, а куда сейчас двигается змей :)
    inline const Way getWay() const {return m_way;}

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
    std::pair<Model::StateGame, Model::StateSnake> move();

    // надо ли этот метод
    inline Model::StateGame getStateGame() const {return m_stateGame;}

private:
    // размеры поля
    Point m_size;

	// сам змей, может выделить змея в отдельный класс
//	std::vector<Point> m_snake;
    Snake<Point> m_snake;

	// кролики, может выделить кролика в отдельный класс
    //	std::vector<Point> m_rabbits;

    // целая фабрика для кроликов
    RabbitFactory &m_rabbits;

	// направление движения
	Way m_way;

	// добавляемая длина при поедании кролика
	int m_length;

    Model::StateGame m_stateGame;
};
