#include <QtWidgets>

#include <vector>
#include <algorithm>

#include "Qt5View.h"

#include "Control.h"
#include "Point.h"
#include "Rabbit.h"
#include "RabbitFactory.h"
#include "Way.h"

Qt5View::Qt5View(QWidget *parent) : QFrame(parent) {
    step = 0;
    steps.clear();

    setFocusPolicy(Qt::StrongFocus);
    emit scoreChanged(0);
}

void Qt5View::paint() {
    update();
}

void Qt5View::changeScore(int _score) {
    emit scoreChanged(_score);
}

int Qt5View::getHieghtField() {
    return BOARD_HEIGHT;
}

int Qt5View::getWidthField() {
    return BOARD_WIDTH;
}

//TODO: Убрать генерацию сигнала об изменение длины червя в модель
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

            switch (way.getWay()) {
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
        {
            const int ddy = squareSize.height()/5;
            const int ddx = squareSize.width()/5;
            const int ddy2 = ddy + ddy;
            const int ddx2 = ddx + ddx;

            auto curr = m_snake->begin();
            auto pred = curr;
            auto next = curr+1;
            auto iterStep = steps.begin();

            for(int i=0, iStep=step; curr != m_snake->end(); next++, curr++, i++){
                if (next == m_snake->end())
                    next = curr;

                const QColor color = i % 5 == 3 ? Qt::yellow: Qt::red;

                QRect body(curr->getX() * squareSize.width(),
                           curr->getY() * squareSize.height(),
                           squareSize.width(),
                           squareSize.height());
                QRect body1;

                if (i != 0) {   // !head

                    if (next->getY() == pred->getY()) {
                        body.translate(0, ddy * (iStep == 3 ? 1 : iStep));
                        body.setHeight(squareSize.height() - ddy2);
                    } else if (next->getX() == pred->getX()) {
                        body.translate(ddx * (iStep == 3 ? 1 : iStep), 0);
                        body.setWidth(squareSize.width() - ddx2);
                    } else {
                        body.setSize(squareSize - QSize(ddx2, ddy2));

                        const bool toLeft = (next->getX() + pred->getX() - 2 * curr->getX()) < 0;
                        const bool toUp   = (next->getY() + pred->getY() - 2 * curr->getY()) < 0;

                        if ((iStep&1) == 1) {
                            body1 = body.translated(toLeft?0:ddx2, ddy);
                            body.translate(ddx, toUp?0:ddy2);

                            if (i == 1 && !m_control->isPause()) {
                                steps.insert(steps.begin(), iStep);         //Сохраняем положение тела на угловых точках
                                iterStep = steps.begin();

                                if (way.isHorisontal()) step = toUp? 2:0;    //Определяем положение головы
                                else                    step = toLeft? 2:0;
                            }

                            if (iterStep != steps.end())                    //Восстанавливаем положение тела
                                iStep = *iterStep++;

                        } else {
                            body.translate(toLeft ? 0 : ddx2, toUp ? 0 : ddy2);
                        }

                    }
                }

                painter.fillRect(body, color);
                if (!body1.isNull())
                    painter.fillRect(body1, color);

                pred = curr;
                incStep(iStep);
            } //for
            steps.erase(iterStep, steps.end());
        }
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
        if (!m_control->isPause()) {
            decStep(step);
            timer.start(timeoutTime(), this);
        } else {
            timer.stop();
        }
    } else {
        QFrame::timerEvent(event);
    }
}

void Qt5View::restart() {
    Q_CHECK_PTR(m_control);

    step = 0;
    m_control->restart();
    emit scoreChanged(m_snake->size());
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
        decStep(step);
    }
    else
        timer.start(timeoutTime(), this);
}
#endif

