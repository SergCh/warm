
#include "Control.h"

#include "TModel.h"
#include "View.h"
#include "RabbitFactory.h"
#include "Rabbit.h"

Control::Control(View& _view, Model& _model):  m_model(_model) , m_view(_view) {
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
    std::pair<Model::StateGame, Model::StateSnake> state(Model::GOOD, Model::NOT_CHANGED);
    if (!m_pause)  {
        state = m_model.move();
        if (state.first == Model::DEAD) {
            m_pause = true;
        } else {
            if (--steps4nextRabbit<=0) {
                steps4nextRabbit = NEXT_STEP;
                m_model.addRabbit();
            }
        }
    }
    if (state.second != Model::NOT_CHANGED)
        m_view.changeScore(m_model.getSnake().size());
    m_view.paint();
}

void Control::init() {
    m_view.setControl(this);
    m_view.setSnake(&m_model.getSnake());
    m_view.setRabbitFactory((RabbitFactory*)m_model.getRabbitFactory());
}
