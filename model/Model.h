#pragma once
/*
	Класс реадизует модель поведения змея

*/


#include <queue>

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
	
	// начало игры
	void init();

	// получить змея для передачи его на прорисовку
	std::vector<Point> & getSnake();

	// сменить путь направления змея
	void changeWay(Way);

	// чисто для любопытства, а куда сейчас двигается змей :)
	Way getWay();

	// добавить кролика (на поле может быть несколько кроликов)
	void addRabbit();

	// получить кроликов для прорисовки
    std::vector<Rabbit> & getRabbits();

	// сделать шаг (если ложь, то игра закончена)
	bool move();

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

};
