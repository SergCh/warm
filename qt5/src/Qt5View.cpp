#include <QtWidgets>

#include <vector>
#include "Qt5View.h"

#include "Control.h"
#include "Point.h"
#include "Rabbit.h"
#include "Way.h"

Qt5View::Qt5View(QWidget *parent) : QFrame(parent) {
    step = 0;

    setFocusPolicy(Qt::StrongFocus);
    snakeChanged = true;    //set 0
}

void Qt5View::paint() {
    update();
    if (snakeChanged)
        emit scoreChanged(m_snake->size());
}

int Qt5View::getHieghtField() {
    return BOARD_HEIGHT;
}

int Qt5View::getWigthField() {
    return BOARD_WIDTH;
}

void Qt5View::command(Way _way) {
    if (m_control)
        m_control->changeWay(_way);
}

bool Qt5View::isPause() {
    if (!m_control)
        return true;
    return m_control->isPause();
}

void Qt5View::nextStep() {
    if (m_snake) {
        const unsigned int len = m_snake->size();
        m_control->nextStep();
        snakeChanged = len != m_snake->size();
    } else {
        snakeChanged = false;
    }
}

void Qt5View::beforeGame() {}


QSize Qt5View::sizeHint() const {
    return QSize(BOARD_HEIGHT * 20 + frameWidth() * 2,
                 BOARD_WIDTH + frameWidth() * 2);
}


QSize Qt5View::minimumSizeHint() const {
    return QSize(BOARD_HEIGHT * 10 + frameWidth() * 2,
                 BOARD_WIDTH * 10 + frameWidth() * 2);
}


void Qt5View::keyPressEvent(QKeyEvent *event) {

    switch (event->key()) {
    case Qt::Key_Left:
        command(Way::LEFT);
        break;
    case Qt::Key_Right:
        command(Way::RIGHT);
        break;
    case Qt::Key_Down:
        command(Way::DOWN);
        break;
    case Qt::Key_Up:
        command(Way::UP);
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

QSize Qt5View::getSquareSize() {
    return QSize(contentsRect().width() / getWigthField(),
                 contentsRect().height() / getHieghtField());
}

void Qt5View::paintEvent(QPaintEvent *event) {
    QFrame::paintEvent(event);

    QPainter painter(this);

    const int height = getHieghtField();
    const int width = getWigthField();
    const QSize squareSize = getSquareSize();
    const QSize boardSize(squareSize.width()*width-1, squareSize.height()*height-1);

    std::vector<Point> * snake = m_snake;
    Q_CHECK_PTR(snake);

    std::vector<Rabbit> * rabbits = m_rabbits;
    Q_CHECK_PTR(rabbits);

    painter.fillRect(0, 0, boardSize.width()+1, boardSize.height()+1, Qt::darkGray);

    if (snake->size() > 0) {
        // draw way
        {
            const Point head = snake->at(0);
            QPoint pHead(head.getX() * squareSize.width() + squareSize.width() / 2,
                         head.getY() * squareSize.height() + squareSize.height() / 2);
            QPoint pBorder(pHead);

            switch (getWay()) {
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
                QRect body1;

                if (i != 0) {   // !head

                    if (p_next.getY() == p_pred.getY()) {
                        body.moveTop(body.y() + ddy * (iStep == 3 ? 1 : iStep));
                        body.setHeight(squareSize.height() - ddy2);
                    } else if (p_next.getX() == p_pred.getX()) {
                        body.moveLeft(body.x() + ddx * (iStep == 3 ? 1 : iStep));
                        body.setWidth(squareSize.width() - ddx2);
                    } else {
                        body.setSize(squareSize - QSize(ddx2, ddy2));

                        const bool toLeft = (p_next.getX() + p_pred.getX() - 2 * p_curr.getX()) < 0;
                        const bool toUp   = (p_next.getY() + p_pred.getY() - 2 * p_curr.getY()) < 0;

                        if ((iStep&1) == 1) {
                            body1 = body;
                            body1.moveTopLeft(QPoint(body.x() + (toLeft?0:ddx2), body.y()+ddy));
                            body.moveTopLeft(QPoint(body.x() + ddx, body.y() + (toUp?0:ddy2)));
                        } else {
                            body.moveTop(body.y() + (toUp ? 0 : ddy2));
                            body.moveLeft(body.x() + (toLeft ? 0 : ddx2));
                        }
                    }
                }

                painter.fillRect(body, color);
                if (!body1.isNull())
                    painter.fillRect(body1, color);

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

    if (isPause()) {
        const QRect rect = contentsRect();
        painter.setPen(QPen(Qt::white, 2, Qt::DotLine));
        painter.drawText(rect, Qt::AlignCenter, tr("Pause"));
    }
}

void Qt5View::timerEvent(QTimerEvent *event) {
    if (event->timerId() == timer.timerId()) {
        nextStep();
        if (!snakeWasChanged())
            incStep(step);
        if (!isPause()) {
            timer.start(timeoutTime(), this);
        } else {
            timer.stop();
        }
    } else {
        QFrame::timerEvent(event);
    }
}

void Qt5View::restart() {
    if (!m_control) return;

    step = 0;
    m_control->restart();
    timer.start(timeoutTime(), this);
}

#ifdef QT_DEBUG
void Qt5View::pause(bool p) {
    if (isPause())
        return;
    if (p) {
        timer.stop();
        nextStep();
        if (!snakeWasChanged())
            incStep(step);
    }
    else
        timer.start(timeoutTime(), this);
}
#endif

