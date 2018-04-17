#pragma once

#include "Ways.h"

class Model;
class View;

class Control
{
public:
	Control(View&, Model&);
	~Control(void);

	Model & getModel();
	void changeWay(Way);
	Way getWay();
	void quit();
	bool isQuit();
	bool move();
	void restart();
	void init();

	void addRabbit();

private:
	Model &m_model;
	View &m_view;
	bool m_quit;

};
