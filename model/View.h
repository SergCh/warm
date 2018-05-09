#pragma once

/**
 *      @file
 *      @brief Заголовочный файла абстрактного интерфеса для отображения игрового поля
 *      @author Чугайнов С.В.
 *      @date 09.05.2018
 *      @todo Добавть передачу сигнала от контроллера при изменении длины зменя
 *
 * Абстрактный класс для отображения игрового поля
*/

#include <vector>

#include "Point.h"
#include "Way.h"


class Control;
class Rabbit;

class View
{
public:

    /**
     * @brief View Конструктор
     */
	View(void);

    /**
     * @brief ~View Деструктор
     */
	virtual ~View(void);

    /**
     * @brief setControl установка указателя на контроллер
     * @param[in] _control Указатель на котроллер
     * @todo переделать в inline
     */
    void setControl(Control*);

    /**
     * @brief setSnake Установка указателя на змея
     * @param[in] _snake Указатель на замея (векор точек)
     * @todo переделать в inline
     */
    void setSnake(std::vector<Point> * _snake);

    /**
     * @brief setRabbits Установка уазателя на вескор кроликов
     * @param _rabbits[in] Указатель на вектор кроликов
     */
    void setRabbits(std::vector<Rabbit> * _rabbits);

    /**
     * @brief paint Вызывается контроллером при изменении в модели
     * @todo рассмотреть возможность добавления параметра состояния игры
     */
    virtual void paint() = 0;
	
    /**
     * @brief getHieghtField Возвращает высоту игроого поля
     * @return Высоту игрового поля
     */
    virtual int getHieghtField() = 0;

    /**
     * @brief getWidthField Возвращает ширину игрового поля
     * @return Ширину игрового поля
     */
    virtual int getWidthField() = 0;

    /**
     * @brief setHieght Установка высоты
     * @todo возможно надо избавляться
     */
    void setHieght(int);

    /**
     * @brief setWigth Установка ширины
     * @todo возможно надо избавляться
     */
    void setWigth(int);

    /**
     * @brief beforeGame Метод вызывается контроллером перед началом игры
     */
    virtual void beforeGame() = 0;
    
private:

    int m_hieght;   /// @todo надо избавляться
    int m_wigth;    /// @todo надо избавляться
    
protected:

    Control *m_control;
    std::vector<Point> * m_snake;
    std::vector<Rabbit> * m_rabbits;
    Way m_way;
};
