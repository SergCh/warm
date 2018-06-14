#include <QtWidgets>

#include <vector>
#include <algorithm>

#include "Qt5View.h"

#include "Control.h"
#include "Point.h"
#include "Rabbit.h"
#include "RabbitFactory.h"
#include "Way.h"


#include "GraphicPoint.h"

using namespace Snake;

Qt5View::Qt5View(QWidget *parent) : QFrame(parent) {
    setFocusPolicy(Qt::StrongFocus);
    emit scoreChanged(0);
}

void Qt5View::paint() {
    update();
}

void Qt5View::changeScore(int _score) {
    emit scoreChanged(_score);
}

void Qt5View::nextStep() {
    Q_CHECK_PTR(m_control);

    m_control->nextStep();
}

void Qt5View::beforeGame() {
    m_snake->setMaxPath(MAX_PATH);
}

QSize Qt5View::sizeHint() const {
    return QSize(BOARD_HEIGHT * 20 + frameWidth() * 2,
                 BOARD_WIDTH * 20+ frameWidth() * 2);
}

QSize Qt5View::minimumSizeHint() const {
    return QSize(BOARD_HEIGHT * 10 + frameWidth() * 2,
                 BOARD_WIDTH * 10 + frameWidth() * 2);
}

void Qt5View::keyPressEvent(QKeyEvent *event) {
    if (!m_control) {
        QFrame::keyPressEvent(event);
        return;
    }

    switch (event->key()) {
    case Qt::Key_Left:         m_control->changeWay(Way::LEFT);        break;
    case Qt::Key_Right:        m_control->changeWay(Way::RIGHT);       break;
    case Qt::Key_Down:         m_control->changeWay(Way::DOWN);        break;
    case Qt::Key_Up:           m_control->changeWay(Way::UP);          break;

    case Qt::Key_Space:
        restart();
        break;

#ifdef QT_DEBUG
    case Qt::Key_P:
        pause(true);
        break;
    case Qt::Key_C:
        pause(false);
        break;
#endif

    default:
        QFrame::keyPressEvent(event);
    }
}

int Qt5View::getSquareSize() {
    return std::min(contentsRect().width() / BOARD_WIDTH, contentsRect().height() / BOARD_HEIGHT);
}

void Qt5View::fillRectangle(int _x, int _y, int _w, int _h, int _c) {
    m_painter->fillRect(_x, _y, _w, _h, getColor(_c));
}

void Qt5View::drawLine(int _x1, int _y1, int _x2, int _y2, int _c) {
    m_painter->setPen(QPen(getColor(_c), 1, Qt::DotLine));
    m_painter->drawLine(_x1, _y1, _x2, _y2);
}

void Qt5View::drawTextPause() {
    const QRect rect = contentsRect();
    m_painter->setPen(QPen(Qt::white, 2, Qt::SolidLine));
    m_painter->drawText(rect, Qt::AlignCenter, tr("Pause"));
}

QColor Qt5View::getColor(unsigned int _c) {
    switch (_c) {
    case COLOR_FIELD:   return Qt::darkGray;
    case COLOR_PATH:    return Qt::cyan;
    case COLOR_RABBIT:  return Qt::green;
    case COLOR_SNAKE0:  return Qt::red;
    case COLOR_SNAKE1:  return Qt::yellow;
    default:
        break;
    }

    if (_c >= COLOR_TAIL) {
        QColor color = Qt::darkGray;
        return color.light(100 + (_c - COLOR_TAIL));
    }

    return Qt::darkGray;
}

void Qt5View::paintEvent(QPaintEvent *event) {
    QFrame::paintEvent(event);

    QPainter painter(this);
    m_painter = &painter;

    paintGame();
}

void Qt5View::timerEvent(QTimerEvent *event) {
    if (event->timerId() == timer.timerId()) {
        nextStep();
        if (!m_control->isPause())
            timer.start(timeoutTime(), this);
        else
            timer.stop();

    } else {
        QFrame::timerEvent(event);
    }
}

void Qt5View::restart() {
    Q_CHECK_PTR(m_control);

    m_control->restart();
    emit scoreChanged(m_snake->size(), IModel::STARTED);
    timer.start(timeoutTime(), this);
}


#ifdef QT_DEBUG
void Qt5View::pause(bool p) {
    Q_CHECK_PTR(m_control);

    if (m_control->isPause())
        return;
    if (p) {
        timer.stop();
        nextStep();
    }
    else
        timer.start(timeoutTime(), this);
}
#endif

