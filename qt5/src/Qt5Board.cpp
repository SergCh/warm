#include <QtWidgets>

#include "Qt5Board.h"

#include <vector>

#include "Qt5View.h"
#include "Point.h"
#include "Rabbit.h"
#include "Way.h"

Qt5Board::Qt5Board(Qt5View * _view, QWidget *parent):QFrame(parent){
    m_view = _view;
    Q_CHECK_PTR(_view);
    m_view->setBoard(this);
    step = 0;

    setFocusPolicy(Qt::StrongFocus);
}


QSize Qt5Board::sizeHint() const {
    return QSize(m_view->getWigthField() * 20 + frameWidth() * 2,
                 m_view->getHieghtField() * 20 + frameWidth() * 2);
}


QSize Qt5Board::minimumSizeHint() const {
    return QSize(m_view->getWigthField() * 10 + frameWidth() * 2,
                 m_view->getHieghtField() * 10 + frameWidth() * 2);
}


void Qt5Board::keyPressEvent(QKeyEvent *event) {

    switch (event->key()) {
    case Qt::Key_Left:
        m_view->command(Way::LEFT);
        break;
    case Qt::Key_Right:
        m_view->command(Way::RIGHT);
        break;
    case Qt::Key_Down:
        m_view->command(Way::DOWN);
        break;
    case Qt::Key_Up:
        m_view->command(Way::UP);
        break;
    case Qt::Key_Space:
        restart();
        break;
    default:
        QFrame::keyPressEvent(event);
    }
}

QSize Qt5Board::getSquareSize() {
    return QSize(contentsRect().width() / m_view->getWigthField(),
                 contentsRect().height() / m_view->getHieghtField());
}

void Qt5Board::paintEvent(QPaintEvent *event) {
    QFrame::paintEvent(event);

    QPainter painter(this);

    const int height = m_view->getHieghtField();
    const int width = m_view->getWigthField();
    const QSize squareSize = getSquareSize();
    const QSize boardSize(squareSize.width()*width-1, squareSize.height()*height-1);

    std::vector<Point> * snake = m_view->getSnake();
    Q_CHECK_PTR(snake);

    std::vector<Rabbit> * rabbits = m_view->getRabbits();
    Q_CHECK_PTR(rabbits);

    painter.fillRect(0, 0, boardSize.width(), boardSize.height(), Qt::darkGray);

    if (snake->size() > 0) {
        // draw way
        {
            Point head = snake->at(0);
            QPoint pHead(head.getX() * squareSize.width() + squareSize.width() / 2,
                         head.getY() * squareSize.height() + squareSize.height() / 2);
            QPoint pBorder(pHead);

            switch (m_view->getWay()) {
                case Way::LEFT:  pBorder.setX(0);                  break;
                case Way::RIGHT: pBorder.setX(boardSize.width());  break;
                case Way::UP:    pBorder.setY(0);                  break;
                case Way::DOWN:  pBorder.setY(boardSize.height()); break;
                default: break;
            }

            painter.setPen(QPen(Qt::blue, 1, Qt::DotLine));
            painter.drawLine(pHead, pBorder);
        }

        // draw snake
        {
            int ddy = squareSize.height()/5;
            int ddx = squareSize.width()/5;

            Point p_curr = snake->at(0);
            Point p_pred = p_curr;

            Point p_next = (snake->size()>1) ? snake->at(1) : snake->at(0);
            for (int i=0, s=snake->size(), j=step; i < s; i++, j = (j+1) & 3) {
                QColor color = i % 5 == 3 ? Qt::yellow: Qt::red;
                QRect body(p_curr.getX() * squareSize.width(),
                           p_curr.getY() * squareSize.height(),
                           squareSize.width(),
                           squareSize.height());
                if (i != 0) {   // !head
                    if (p_next.getY() == p_pred.getY()) {
                        body.setTop(body.y() + ddy * ((j == 3) ? 1 : j));
                        body.setHeight(squareSize.height() - 2*ddy);
                    } else if (p_next.getX() == p_pred.getX()) {
                        body.setLeft(body.x() + ddx * ((j == 3) ? 1 : j));
                        body.setWidth(squareSize.width() - 2*ddx);
                    } else {
                        const int dx = p_next.getX() + p_pred.getX() - 2 * p_curr.getX();
                        const int dy = p_next.getY() + p_pred.getY() - 2 * p_curr.getY();
                        const int DX = (dx<0) ? 0 : 2*ddx;
                        const int DY = (dy<0) ? 0 : 2*ddy;
                        body.setTop(body.y() + DY);
                        body.setLeft(body.x() + DX);
                        body.setHeight(squareSize.height() - 2*ddy);
                        body.setWidth(squareSize.width() - 2*ddx);
                    }
                }
                painter.fillRect(body, color);
                p_pred = p_curr;    // i
                p_curr = p_next;    // i+1
                if (i+2 < s)        // i+2
                    p_next = snake->at(i+2);
            }
        }
    }

    for (auto p=rabbits->begin(); p != rabbits->end(); p++) {
        painter.fillRect(p->getX() * squareSize.width() + 1, p->getY() * squareSize.height() + 1,
                         squareSize.width() - 2, squareSize.height() - 2,
                         Qt::green);
    }


    if (m_view->isPause()) {
        QRect rect = contentsRect();
        painter.setPen(QPen(Qt::white, 2, Qt::DotLine));
        painter.drawText(rect, Qt::AlignCenter, tr("Pause"));
    }
}


void Qt5Board::timerEvent(QTimerEvent *event) {
    if (event->timerId() == timer.timerId()) {
        m_view->nextStep();
        step = (step+1) & 3;
        if (!m_view->isPause()) {
            timer.start(timeoutTime(), this);
        } else {
            timer.stop();
        }
    } else {
        QFrame::timerEvent(event);
    }
}

void Qt5Board::restart() {
    step = 0;
    m_view->restart();
    timer.start(timeoutTime(), this);
}

