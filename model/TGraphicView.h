/**
 * @file GraphicView.h
 * @brief GraphicView
 * @author Чугайнов С.В.
 * @date 14.06.2018
 *
 *
 */
#pragma once

#include "Way.h"
#include "GraphicPoint.h"
#include "IView.h"
#include "GraphicSnake.h"
#include "IControl.h"
#include "RabbitFactory.h"


namespace Snake {


    template <class GVI>
    class TGraphicView : public IView
    {
    public:
        TGraphicView(): m_snake(0) {}

        /**
         * @brief getHieghtField Возвращает высоту игроого поля
         * @return Высоту игрового поля
         */
        virtual int getHieghtField() {
            return BOARD_HEIGHT;
        }

        /**
         * @brief getWidthField Возвращает ширину игрового поля
         * @return Ширину игрового поля
         */
        virtual int getWidthField() {
            return BOARD_WIDTH;
        }

        int timeoutTime() const {return TIME;}

        virtual void setSnake(ISnake * _snake) {
            m_snake = static_cast<GraphicSnake*> (_snake);
        }

        virtual void paintGame() {

            const unsigned int squareSize = static_cast<GVI*>(this) -> getSquareSize();
            const Point boardSize(squareSize * BOARD_WIDTH, squareSize * BOARD_HEIGHT);

            static_cast<GVI*>(this) -> fillRectangle(0, 0, boardSize.getX(), boardSize.getY(), COLOR_FIELD);

            if (m_control == 0)
                return;


            if (m_snake->size() > 0) {

                // draw path
                {
                    int i = MAX_PATH - m_snake->sizePath();
                    for (std::vector<GraphicPoint>::reverse_iterator iter = m_snake->rbeginPath(); iter != m_snake->rendPath(); ++iter, ++i) {
                        static_cast<GVI*>(this) -> drawSnake(&*iter, COLOR_TAIL + i);
                    }
                }

                // draw way
                {
                    const Point head = m_snake->front();
                    int x1 = head.getX() * squareSize + squareSize / 2;
                    int y1 = head.getY() * squareSize + squareSize / 2;
                    int x2 = x1;
                    int y2 = y1;

                    switch (m_snake->getWay()) {
                    case Way::LEFT:  x2 = 0;                break;
                    case Way::RIGHT: x2 = boardSize.getX(); break;
                    case Way::UP:    y2 = 0;                break;
                    case Way::DOWN:  y2 = boardSize.getY(); break;
                    default: break;
                    }

                    static_cast<GVI*>(this) -> drawLine(x1, y1, x2, y2, COLOR_PATH);
                }

                // draw snake
                for (std::vector<GraphicPoint>::iterator iter = m_snake->begin(); iter != m_snake->end(); ++iter) {
                    const unsigned int color = (iter - m_snake->begin()) % 5 == 3 ? COLOR_SNAKE1: COLOR_SNAKE0;
                    drawSnake(&*iter, color);
                }
            }

            // draw rabbits
            for (std::vector<Rabbit>::iterator  iter = m_rabbitFactory->begin(); iter != m_rabbitFactory->end(); ++iter) {
                static_cast<GVI*>(this) -> fillRectangle(iter->getX() * squareSize + 1,
                                                         iter->getY() * squareSize + 1,
                                                         squareSize - 2, squareSize - 2 , COLOR_RABBIT);
            }

            if (m_control->isPause()) {
                static_cast<GVI*>(this) -> drawTextPause();
            }

        }

        enum {COLOR_FIELD,  //dark gray
              COLOR_RABBIT, //green
              COLOR_SNAKE0, //red
              COLOR_SNAKE1, //yellow
              COLOR_PATH,   //cyan
              COLOR_TAIL,   //from dark_greay to gray
             };

    protected:
        enum { BOARD_WIDTH = 50, BOARD_HEIGHT = 50, MAX_PATH = 10, TIME = 100};

        void drawSnake(GraphicPoint* _point, int _color) {
            const unsigned int s = static_cast<GVI*>(this) -> getSquareSize();
            const unsigned int s15 = s/5;                   // 1/5
            const unsigned int s25 = s15 + s15;             // 2/5
            const unsigned int s35 = s - s25;               // 3/5

            const unsigned int x = _point->getX() * s;
            const unsigned int y = _point->getY() * s;


            switch (_point->getType()) {
            case GraphicPoint::HEAD:
                static_cast<GVI*>(this) -> fillRectangle(x, y, s, s, _color);
                return;

            case GraphicPoint::HORISONTAL:
                static_cast<GVI*>(this) -> fillRectangle(x, y + s15 * _point->getPosition(), s, s35, _color);
                return;

            case GraphicPoint::VERTICAL:
                static_cast<GVI*>(this) -> fillRectangle(x + s15 * _point->getPosition(), y, s35, s, _color);
                return;

            case GraphicPoint::CORNER:
                if (_point->getPosition()) {
                    static_cast<GVI*>(this) -> fillRectangle(x + (_point->getToLeft() ? 0 : s25), y + s15, s35, s35, _color);
                    static_cast<GVI*>(this) -> fillRectangle(x + s15, y + (_point->getToUp() ? 0 : s25),   s35, s35, _color);
                    return;
                }
                static_cast<GVI*>(this) -> fillRectangle(x + (_point->getToLeft() ? 0 : s25),
                                                         y + (_point->getToUp() ? 0 : s25),
                                                         s35, s35, _color);
                return;
            }
        }

        GraphicSnake * m_snake;

    };
}

