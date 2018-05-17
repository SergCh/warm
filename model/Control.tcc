
#include "Control.h"

#include "TModel.h"
#include "IView.h"
#include "RabbitFactory.h"
#include "Rabbit.h"

template <class T_Snake>
Control<T_Snake>::Control(IView& _view, TModel<T_Snake>& _model):  m_model(_model) , m_view(_view) {
	m_quit = false;
    m_pause = true;
    steps4nextRabbit = BEGIN_STEP;
}

template <class T_Snake>
Control<T_Snake>::~Control(void){}

template <class T_Snake>
void Control<T_Snake>::changeWay (Way way) {
    if (!m_pause)
        m_model.changeWay(way);
}

template <class T_Snake>
void Control<T_Snake>::restart() {
	m_model.init();
	m_view.beforeGame();
    m_pause = false;
    steps4nextRabbit = BEGIN_STEP;
    m_view.changeScore(m_model.getSnake().size());
}

template <class T_Snake>
void Control<T_Snake>::nextStep() {
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

template <class T_Snake>
void Control<T_Snake>::init() {
    m_view.setControl(this);
    m_view.setSnake(&m_model.getSnake());           //нарушение MVC избавляемся или избавляемся от MVC :)
    m_view.setRabbitFactory((RabbitFactory*)m_model.getRabbitFactory());
}
