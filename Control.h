#pragma once

#include "Way.h"

class Model;
class View;

// ���������� ����� View � Model

class Control
{
public:
	Control(View&, Model&);
	~Control(void);

	Model & getModel();

	// �������� �����������
	void changeWay(Way);

	// �������� ������� �����������
	Way getWay();

	// ����� ��� View, �����������, ����� ������ ����� �����.
	void quit();

	// ������ ��� m_quit
	bool isQuit();

	// ������ ���� ���
	bool move();

	// ���������� ����
	void restart();

	// ����� ����
	void endGame();

	// ������������� 
	void init();

	void addRabbit();

private:
	
	Model &m_model;
	View &m_view;

	// ���� ������ 
	bool m_quit;
};
