#pragma once

/**
 *      @file
 *      @brief Фабрика кроликов
 *      @author Чугайнов С.В.
 *      @date 09.05.2018
 *      @todo Абстрагировать от класса Rabbit (сделать шаблоном)
 *
 */

#include <vector>
#include "Rabbit.h"
#include "Point.h"

class RabbitFactory
{
public:
    /**
     * @brief RabbitFactory Конструктор
     */
    RabbitFactory();

    /**
     * @brief clear Удалить всех кроликов (перед началом игры)
     */
    void clear();

    /**
     * @brief newRabbit Сгенерировать случайным образом нового кролика
     * @param size Размер поля
     * @param occuped Занятые точки змеем
     */
    void newRabbit(Point & size, std::vector<Point> & occuped);

    /**
     * @brief step Делаем шаг
     * @todo Возможно надо добавить возвращение буллевского значения, если было изменено количество кроликов
     *
     * Делаем шаг, передаем шаг всем кролика, которые умерли удаляем
     */
    void step();

    /**
     * @brief eat Кушаем кпроликов
     * @param координаты кроликов
     * @return кодичество добавляемы элементов змею (если ничего не съели то 0)
     */
    int eat(Point & _head);

    /**
     * @brief getLive Количество жизней новому кролику
     * @return Количество жизней новому кролику
     */
    int getLive() const {return 134;}

    /**
     * @brief getWeight Вес новому кролику
     * @return Вес новому кролику
     */
    int getWeight() const {return 5;}

    /**
     * @brief getData Возвращаем вектор кпроликов
     * @return Вектор кроликов
     */
    std::vector<Rabbit> & getData();

private:
    /// Вектор кроликов
    std::vector<Rabbit> m_rabbits;
};

