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

//int Qt5View::getHieghtField() {
//    return BOARD_HEIGHT;
//}

//int Qt5View::getWidthField() {
//    return BOARD_WIDTH;
//}

//void Qt5View::setSnake(ISnake * _snake){
//    m_snake = static_cast<GraphicSnake*> (_snake);
//}

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

//    const int height = BOARD_HEIGHT;
//    const int width = BOARD_WIDTH;
//    const QSize squareSize = getSquareSize();
//    const QSize boardSize(squareSize.width()*width-1, squareSize.height()*height-1);

//    painter.fillRect(0, 0, boardSize.width()+1, boardSize.height()+1, Qt::darkGray);

//    if (m_snake->size() > 0) {

//        // draw path
//        {
//            int i = 100 + MAX_PATH - m_snake->sizePath();
//            for (auto iter = m_snake->rbeginPath(); iter != m_snake->rendPath(); ++iter) {
//                QColor color = Qt::darkGray;
//                color = color.light(i++);
//                drawSnake(&*iter, squareSize, &painter, color);
//            }
//        }

//        // draw way
//        {
//            const Point head = m_snake->front();
//            QPoint pHead(head.getX() * squareSize.width() + squareSize.width() / 2,
//                         head.getY() * squareSize.height() + squareSize.height() / 2);
//            QPoint pBorder(pHead);

//            switch (m_snake->getWay()) {
//                case Way::LEFT:  pBorder.setX(0);                  break;
//                case Way::RIGHT: pBorder.setX(boardSize.width());  break;
//                case Way::UP:    pBorder.setY(0);                  break;
//                case Way::DOWN:  pBorder.setY(boardSize.height()); break;
//                default: break;
//            }

//            painter.setPen(QPen(Qt::cyan, 1, Qt::DotLine));
//            painter.drawLine(pHead, pBorder);
//        }

//        // draw snake
//        for (auto iter = m_snake->begin(); iter != m_snake->end(); ++iter) {
//            const QColor color = (iter - m_snake->begin()) % 5 == 3 ? Qt::yellow: Qt::red;
//            drawSnake(&*iter, squareSize, &painter, color);
//        }
//    }

//    for (auto iter = m_rabbitFactory->begin(); iter != m_rabbitFactory->end(); iter++) {
//        painter.fillRect(iter->getX() * squareSize.width() + 1, iter->getY() * squareSize.height() + 1,
//                         squareSize.width() - 2, squareSize.height() - 2,
//                         Qt::green);
//    }

//    if (m_control->isPause()) {
//        const QRect rect = contentsRect();
//        painter.setPen(QPen(Qt::white, 2, Qt::DotLine));
//        painter.drawText(rect, Qt::AlignCenter, tr("Pause"));
//    }
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


//void Qt5View::drawSnake(GraphicPoint* _point, const QSize & _squareSize, QPainter * _painter, QColor _color) {
//    QRect body1(_point->getX() * _squareSize.width(), _point->getY() * _squareSize.height(),
//                _squareSize.width(), _squareSize.height());

////    const QColor color = _index % 5 == 3 ? Qt::yellow: Qt::red;

//    int ddx = _squareSize.width() / 5, ddx2 = ddx + ddx;
//    int ddy = _squareSize.height() / 5, ddy2 = ddy + ddy;

//    switch (_point->getType()) {
//    case GraphicPoint::HEAD:
//        _painter->fillRect(body1, _color);
//        return;

//    case GraphicPoint::HORISONTAL:
//        body1.translate(0, ddy * _point->getPosition());
//        body1.setHeight(_squareSize.width() - ddy2);
//        _painter->fillRect(body1, _color);
//        return;

//    case GraphicPoint::VERTICAL:
//        body1.translate(ddx * _point->getPosition(), 0);
//        body1.setWidth(_squareSize.height() - ddx2);
//        _painter->fillRect(body1, _color);
//        break;

//    case GraphicPoint::CORNER:
//        body1.setSize(_squareSize - QSize(ddx2, ddy2));
//        if (_point->getPosition()) {

//            QRect body2 = body1.translated(_point->getToLeft() ? 0:ddx2, ddy);
//            _painter->fillRect(body2, _color);

//            body1.translate(ddx, _point->getToUp() ? 0:ddy2);
//            _painter->fillRect(body1, _color);

//            return;
//        }
//        body1.translate(_point->getToLeft() ? 0 : ddx2, _point->getToUp() ? 0 : ddy2);
//        _painter->fillRect(body1, _color);
//        return;
//    }
//}

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

