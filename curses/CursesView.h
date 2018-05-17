#pragma once

/*

	Тут весь вывод на экран и получения реакции от игрока

*/

#include <vector>

#include "IView.h"
#include "Point.h"
//#include "Rabbit.h"

namespace SNAKE_MODEL {

    class Control;
    class Rabbit;
    template <class T_Point> class TSnake;

    typedef TSnake<Point> Snake;



    class CursesView : public IView
    {
    public:
        CursesView();
        ~CursesView();

        virtual void setSnake(ISnake * _snake);

        int getHieghtField();
        int getWidthField();

        void setHieght(int);
        void setWigth(int);

        int getSystemHieght();
        int getSystemWigth();

        void getCommands();

        void beforeGame();
        void endGame(int);

        virtual void paint();
        virtual void changeScore(int _score);

    private:
        typedef enum {EMPTY = 1, HEAD, BODY, BODY2, RABBIT, POINT} Draw;	//TODO: не удачное название Draw
        typedef enum {FRAME = Draw::POINT+1, DIALOG} Color;

        void drawDraw(Point &, Draw);

        void initColors();

        int m_hieght;
        int m_width;
        int m_score;
        Snake * m_snake;

    protected:
        void beforePaintField();
        void afterPaintField();
        void paintWay();
        void paintSnake();
        void paintRabbit(Rabbit &);

    };

}
