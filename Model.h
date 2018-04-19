#pragma once
/*
	Класс реадизует модель поведения змея

*/


#include <queue>

#include "Point.h"
#include "Way.h"

class Model {
private:
	// Добавляемая длина змея при поедании кролика
	static const int ADD_LENGTH = 5;

public:
	// передача параметров ширины и высоты поля
	Model(int /*w*/, int /*h*/);	
	~Model(void);
	
	// начало игры
	void init();

	// получить змея для передачи его на прорисовку
	std::vector<Point> & getSnake();

	// отдельно получить голову, тоже нужга для прорисовки
	Point &getHead();

	// сменить путь паправления змея
	void changeWay(Way);

	// чисто для любопытства, а куда сейчсас двигается змей :)
	Way getWay();

	// добывть кролика (на поле может дыть несколько кроликов)
	void addRabbit();

	// получить кроликов для прорисовки
	std::vector<Point> & getRabbits();

	// сделать шаг (если лож, то игра закончена)
	bool move();

private:

	// проверка можноли двигаться (если нет, то выдать false)
	// и добавить новое расположение головы
	bool check();

	// сам змей
	std::vector<Point> m_snake;
	// кролики
	std::vector<Point> m_rabbits;

	// высота поля
	int m_hieght;

	// ширина поля
	int m_wigth;

	// направление движения
	Way m_way;

	// добавляемая длина при поедании кролика
	int m_length;

};
