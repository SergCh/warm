#pragma once

/**
 *      @file IView.h
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
#include "ISnake.h"

class IControl;
class Rabbit;
class RabbitFactory;

class IView
{
public:

    /**
     * @brief IView Конструктор
     */
    IView(void)
    : m_control(0){
        m_way = Way::LEFT;
        m_rabbitFactory = 0;
    }

    /**
     * @brief setControl установка указателя на контроллер
     * @param[in] _control Указатель на котроллер
     */
    virtual void setControl(IControl * _control) {
        m_control = _control;
    }

    /**
     * @brief setSnake Чисто виртуальный метод, установка указателя на змея
     * @param[in] _snake Указатель на замея
     */
    virtual void setSnake(ISnake * _snake) = 0;

    /**
     * @brief setRabbitFactory Установка уазателя на вескор кроликов
     * @param _rabbits[in] Указатель на вектор кроликов
     */
    virtual void setRabbitFactory(RabbitFactory * _rabbitFabrica) {
        m_rabbitFactory = _rabbitFabrica;
    }

    /**
     * @brief paint Вызывается контроллером при изменении в модели
     * @todo рассмотреть возможность добавления параметра состояния игры
     */
    virtual void paint() = 0;
	
    /**
     * @brief changeScore Изменение результата
     * @param _score результат
     */
    virtual void changeScore(int _score) = 0;

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
     *
     * Метод вызывается контроллером перед началом игры.
     * Возможно необходимо сделать иницыализирующие дествия перед началом игры.
     */
    virtual void beforeGame() = 0;
    
private:

    int m_hieght;   /// @todo надо избавляться
    int m_wigth;    /// @todo надо избавляться
    
protected:

    IControl *m_control;
    RabbitFactory * m_rabbitFactory;
    Way m_way;
};
