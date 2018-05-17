#pragma once

#include <vector>
#include <algorithm>

#include "Point.h"
#include "Way.h"

namespace SNAKE_MODEL {

    class GraphicPoint : public Point{

    public:
        typedef enum {
            HEAD,
            HORISONTAL,
            VERTICAL,
            CORNER
        } Type;

        GraphicPoint(int _x, int _y, Type _type=HEAD, int _step=0) : Point(_x, _y){
            m_type = _type;
            m_step = _step;
        }

        inline void setPosition(int _position, bool _toLeft = true, bool _toUp = true) {
            m_position = _position; m_toLeft = _toLeft; m_toUp = _toUp;
        }

        inline int getStep() const {return m_step;}

        inline void setStep(int _step) {m_step = _step;}

        inline int getPosition() const {return m_position;}

        inline Type getType() const {return m_type;}
        inline bool getToLeft() const {return m_toLeft;}
        inline bool getToUp() const {return m_toUp;}

        void changeToHorisontal();

        void changeToVertical();

        void changeToCorner(bool _toLeft, bool _toUp);

    private:
        int m_step;
        Type m_type;
        int m_position;
        bool m_toLeft;      //может переделать в enum?
        bool m_toUp;
    };

}
