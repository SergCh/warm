#pragma once

/**
 * @file GraphicSnake.h
 * @brief GraphicSnake
 * @author Чугайнов С.В.
 * @date 12.05.2018
 *
 *
 */

#include "GraphicPoint.h"
#include "TSnake.h"

namespace SNAKE_MODEL {

    class GraphicSnake : public TSnake<GraphicPoint>
    {
    public:

        GraphicSnake();

        virtual void addNewHead(GraphicPoint _newHead);

        virtual void removeTail(int _count);

        inline std::vector<GraphicPoint>::iterator beginPath() {return m_path.begin();}
        inline std::vector<GraphicPoint>::iterator endPath() {return m_path.end();}
        inline std::vector<GraphicPoint>::reverse_iterator rbeginPath() {return m_path.rbegin();}
        inline std::vector<GraphicPoint>::reverse_iterator rendPath() {return m_path.rend();}
        inline int sizePath() const {return m_path.size();}

        virtual void start(Point _sizeField);

        void setMaxPath(unsigned int _maxPath);

    private:
        std::vector<GraphicPoint> m_path;
        unsigned int m_maxPath;
    };

}
