#pragma once
/*
	Класс реадизует модель поведения змея

*/


#include <queue>
#include <utility>

#include "Point.h"
#include "Way.h"

//#include "RabbitFactory.h"

class RabbitFactory;
class Rabbit;

class Model {

public:
	// передача параметров ширины и высоты поля
    Model(Point _size, RabbitFactory &_rabbits);
	~Model(void);
	
    // состояние змея
    typedef enum {
        DEAD,           ///< Двигаться дальше не может
        GOOD            ///< Может двигаться, длина не изменилась
//        GOOD_CHANGED    ///< Может двигаться, длина изменилась
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
	void init();

	// получить змея для передачи его на прорисовку
    std::vector<Point> & getSnake() {
        return m_snake;
    }

	// сменить путь направления змея
    void changeWay(Way _way);

	// чисто для любопытства, а куда сейчас двигается змей :)
	Way getWay();

	// добавить кролика (на поле может быть несколько кроликов)
	void addRabbit();

	// получить кроликов для прорисовки
    std::vector<Rabbit> & getRabbits();

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
	std::vector<Point> m_snake;
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
