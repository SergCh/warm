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

Qt5View::Qt5View(QWidget *parent) : QFrame(parent) {

    setFocusPolicy(Qt::StrongFocus);
    emit scoreChanged(0);
}

void Qt5View::paint() {
    update();
}

void Qt5View::changeScore(int _score, int _stateSnake) {
    emit scoreChanged(_score);
    if (Model::NOT_CHANGED == _stateSnake)
        return;

    int remove = 0;
    switch ((Model::StateSnake)_stateSnake) {
    case Model::ADDED:      // переделать в модели, что бы было ADDED === 0, MOVED === 1, MOVED_SHOTER === 2
        remove = 0;
        break;
    case Model::MOVED:
        remove = 1;
        break;
    case Model::MOVED_SHOTER:
        remove = 2;
        break;
    default:
        break;
    }

    if (Model::STARTED == _stateSnake) {
        gSnake.clear();
        for (auto iter = m_snake->rbegin(); iter != m_snake->rend(); ++iter)
            GraphicPoint::addHead(gSnake, *iter, m_control->getWay(), 0);

    } else {
        GraphicPoint::addHead(gSnake, m_snake->front(), m_control->getWay(), remove);
    }
}

int Qt5View::getHieghtField() {
    return BOARD_HEIGHT;
}

int Qt5View::getWidthField() {
    return BOARD_WIDTH;
}


void Qt5View::nextStep() {
    Q_CHECK_PTR(m_control);

    m_control->nextStep();
}

void Qt5View::beforeGame() {}

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

QSize Qt5View::getSquareSize() {
    return QSize(contentsRect().width() / BOARD_WIDTH,
                 contentsRect().height() / BOARD_HEIGHT);
}

void Qt5View::paintEvent(QPaintEvent *event) {
    QFrame::paintEvent(event);

    Q_CHECK_PTR(m_control);

    QPainter painter(this);

    const int height = BOARD_HEIGHT;
    const int width = BOARD_WIDTH;
    const QSize squareSize = getSquareSize();
    const QSize boardSize(squareSize.width()*width-1, squareSize.height()*height-1);
    const Way way=m_control->getWay();

    painter.fillRect(0, 0, boardSize.width()+1, boardSize.height()+1, Qt::darkGray);

    if (m_snake->size() > 0) {
        // draw way
        {
            const Point head = m_snake->at(0);
            QPoint pHead(head.getX() * squareSize.width() + squareSize.width() / 2,
                         head.getY() * squareSize.height() + squareSize.height() / 2);
            QPoint pBorder(pHead);

            switch (way) {
                case Way::LEFT:  pBorder.setX(0);                  break;
                case Way::RIGHT: pBorder.setX(boardSize.width());  break;
                case Way::UP:    pBorder.setY(0);                  break;
                case Way::DOWN:  pBorder.setY(boardSize.height()); break;
                default: break;
            }

            painter.setPen(QPen(Qt::cyan, 1, Qt::DotLine));
            painter.drawLine(pHead, pBorder);
        }

        // draw snake
        for (auto iter = gSnake.begin(); iter != gSnake.end(); ++iter)
            iter->draw(squareSize, &painter, iter - gSnake.begin());
    }

    for (auto iter = m_control->beginRabbit(); iter != m_control->endRabbit(); iter++) {
        painter.fillRect(iter->getX() * squareSize.width() + 1, iter->getY() * squareSize.height() + 1,
                         squareSize.width() - 2, squareSize.height() - 2,
                         Qt::green);
    }

    if (m_control->isPause()) {
        const QRect rect = contentsRect();
        painter.setPen(QPen(Qt::white, 2, Qt::DotLine));
        painter.drawText(rect, Qt::AlignCenter, tr("Pause"));
    }
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
    emit scoreChanged(m_snake->size(), Model::STARTED);
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

