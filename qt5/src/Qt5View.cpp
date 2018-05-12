#include <QtWidgets>

#include <vector>
#include <algorithm>

#include "Qt5View.h"

#include "Control.h"
#include "Point.h"
#include "Rabbit.h"
#include "RabbitFactory.h"
#include "Way.h"
#include "Config.h"

#include "GraphicPoint.h"

Qt5View::Qt5View(QWidget *parent) : QFrame(parent) {

    setFocusPolicy(Qt::StrongFocus);
    emit scoreChanged(0);
}

void Qt5View::paint() {
    update();
}

void Qt5View::changeScore(int _score, int ) {
    emit scoreChanged(_score);
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

    painter.fillRect(0, 0, boardSize.width()+1, boardSize.height()+1, Qt::darkGray);

    if (m_snake->size() > 0) {
        // draw way
        {
            const Point head = m_snake->front();
            QPoint pHead(head.getX() * squareSize.width() + squareSize.width() / 2,
                         head.getY() * squareSize.height() + squareSize.height() / 2);
            QPoint pBorder(pHead);

            switch (m_snake->getWay()) {
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
        for (auto iter = m_snake->begin(); iter != m_snake->end(); ++iter)
            draw(&*iter, squareSize, &painter, iter - m_snake->begin());
//        iter->draw(squareSize, &painter, iter - m_snake->begin());
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


void Qt5View::draw(GraphicPoint* _point, const QSize & _squareSize, QPainter * _painter, int _index) {
    QRect body1(_point->getX() * _squareSize.width(), _point->getY() * _squareSize.height(),
                _squareSize.width(), _squareSize.height());

    const QColor color = _index % 5 == 3 ? Qt::yellow: Qt::red;

    int ddx = _squareSize.width() / 5, ddx2 = ddx + ddx;
    int ddy = _squareSize.height() / 5, ddy2 = ddy + ddy;

    switch (_point->getType()) {
    case GraphicPoint::HEAD:
        _painter->fillRect(body1, color);
        return;

    case GraphicPoint::HORISONTAL:
        body1.translate(0, ddy * _point->getPosition());
        body1.setHeight(_squareSize.width() - ddy2);
        _painter->fillRect(body1, color);
        return;

    case GraphicPoint::VERTICAL:
        body1.translate(ddx * _point->getPosition(), 0);
        body1.setWidth(_squareSize.height() - ddx2);
        _painter->fillRect(body1, color);
        break;

    case GraphicPoint::CORNER:
        body1.setSize(_squareSize - QSize(ddx2, ddy2));
        if (_point->getPosition()) {

            QRect body2 = body1.translated(_point->getToLeft() ? 0:ddx2, ddy);
            _painter->fillRect(body2, color);

            body1.translate(ddx, _point->getToUp() ? 0:ddy2);
            _painter->fillRect(body1, color);

            return;
        }
        body1.translate(_point->getToLeft() ? 0 : ddx2, _point->getToUp() ? 0 : ddy2);
        _painter->fillRect(body1, color);
        return;
    }
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

