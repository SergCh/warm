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

    painter.fillRect(0, 0, boardSize.width()+1, boardSize.height()+1, Qt::darkGray);

    if (snake->size() > 0) {
        // draw way
        {
            const Point head = snake->at(0);
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
            const int ddy = squareSize.height()/5;
            const int ddx = squareSize.width()/5;
            const int ddy2 = ddy + ddy;
            const int ddx2 = ddx + ddx;

            const int snakeLen = snake->size();

            Point p_curr = snake->at(snakeLen-1);     //*(snake->end()-1);
            Point p_pred = p_curr;

            Point p_next = (snakeLen>1) ? snake->at(snakeLen-2) : snake->at(0);
            for (int i=snakeLen, iStep=step; i--; ) {

                const QColor color = i % 5 == 3 ? Qt::yellow: Qt::red;

                QRect body(p_curr.getX() * squareSize.width(),
                           p_curr.getY() * squareSize.height(),
                           squareSize.width(),
                           squareSize.height());

                if (i != 0) {   // !head

                    if (p_next.getY() == p_pred.getY()) {
                        body.moveTop(body.y() + ddy * (iStep == 3 ? 1 : iStep));
                        body.setHeight(squareSize.height() - ddy2);
                    } else if (p_next.getX() == p_pred.getX()) {
                        body.moveLeft(body.x() + ddx * (iStep == 3 ? 1 : iStep));
                        body.setWidth(squareSize.width() - ddx2);
                    } else {
                        iStep = 0;

                        body.setSize(squareSize - QSize(ddx2, ddy2));

                        const bool toLeft = (p_next.getX() + p_pred.getX() - 2 * p_curr.getX()) < 0;
                        const bool toUp   = (p_next.getY() + p_pred.getY() - 2 * p_curr.getY()) < 0;

                        if ((iStep&1) == 1) {
                            QRect body1(body);
                            body1.moveTopLeft(QPoint(body.x() + (toLeft?0:ddx2), body.y()+ddy));

                            painter.fillRect(body1, color);

                            body.moveTopLeft(QPoint(body.x() + ddx, body.y() + (toUp?0:ddy2)));

                        } else {
                            body.moveTop(body.y() + (toUp ? 0 : ddy2));
                            body.moveLeft(body.x() + (toLeft ? 0 : ddx2));
                        }
                    }
                }

                painter.fillRect(body, color);

                p_pred = p_curr;    // i
                p_curr = p_next;    // i-1
                if (1 < i)   // i-2
                    p_next = snake->at(i-2);
                incStep(iStep);
            }
        }
    }

    for (auto p=rabbits->begin(); p != rabbits->end(); p++) {
        painter.fillRect(p->getX() * squareSize.width() + 1, p->getY() * squareSize.height() + 1,
                         squareSize.width() - 2, squareSize.height() - 2,
                         Qt::green);
    }

    if (m_view->isPause()) {
        const QRect rect = contentsRect();
        painter.setPen(QPen(Qt::white, 2, Qt::DotLine));
        painter.drawText(rect, Qt::AlignCenter, tr("Pause"));
    }
}

void Qt5Board::timerEvent(QTimerEvent *event) {
    if (event->timerId() == timer.timerId()) {
        m_view->nextStep();
        if (!m_view->snakeWasChanged())
            incStep(step);
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

#ifdef QT_DEBUG
void Qt5Board::pause(bool p) {
    if (m_view->isPause())
        return;
    if (p) {
        timer.stop();
        m_view->nextStep();
        if (!m_view->snakeWasChanged())
            incStep(step);
    }
    else
        timer.start(timeoutTime(), this);
}
#endif
