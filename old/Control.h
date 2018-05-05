#pragma once

#include "Way.h"

class Model;
class View;

// контроллер между View и Model

class Control
{
public:
	Control(View&, Model&);
	~Control(void);

	Model & getModel();

	// поменять направление
	void changeWay(Way);

	// получить текущее направление
	Way getWay();

	// метод для View, срабатывает, когда клиент хочет выйти.
	void quit();

	// геттер для m_quit
	bool isQuit();

	// делаем один шаг
	bool move();

	// перезапуск игры
	void restart();

	// конец игры
	void endGame();

	// инициализация 
	void init();

	void addRabbit();

private:
	
	Model &m_model;
	View &m_view;

	// флаг выхода 
	bool m_quit;
};
