/**
 ** This file is part of the qt5worm project.
 ** Copyright 2018 Sergei Chugainov <chsev@yandex.ru>.
 **
 ** This program is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU General Public License as published by
 ** the Free Software Foundation, either version 3 of the License, or
 ** (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU General Public License for more details.
 **
 ** You should have received a copy of the GNU General Public License
 ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **/


#include "Control.h"

#include "Model.h"
#include "IView.h"
#include "RabbitFactory.h"
#include "Rabbit.h"

using namespace Snake;

Control::Control(IView& _view, IModel& _model): IControl(), m_model(_model) , m_view(_view) {
	m_quit = false;
    m_pause = true;

    steps4nextRabbit = BEGIN_STEP;
}

Control::~Control(void){}

void Control::changeWay (Way way) {
    if (!m_pause)
        m_model.changeWay(way);
}

void Control::restart() {
	m_model.init();
	m_view.beforeGame();
    m_pause = false;
    steps4nextRabbit = BEGIN_STEP;
    m_view.changeScore(m_model.getSnake().size());
}

void Control::nextStep() {
      std::pair<IModel::StateGame, IModel::StateSnake> state(IModel::GOOD, IModel::NOT_CHANGED);
    if (!m_pause)  {
        state = m_model.move();
        if (state.first == IModel::DEAD) {
            m_pause = true;
        } else {
            if (--steps4nextRabbit<=0) {
                steps4nextRabbit = NEXT_STEP;
                m_model.addRabbit();
            }
        }
    }
    if (state.second != IModel::NOT_CHANGED)
        m_view.changeScore(m_model.getSnake().size());
    m_view.paint();
}

void Control::init() {
    m_view.setControl(this);
    m_view.setSnake(&m_model.getSnake());           //нарушение MVC избавляемся или избавляемся от MVC :)
    m_view.setRabbitFactory((RabbitFactory*)m_model.getRabbitFactory());
}
