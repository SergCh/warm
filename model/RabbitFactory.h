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
     * @brief ~RabbitFactory Деструктор
     */
    ~RabbitFactory();

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

    Rabbit* at(int i);

    std::vector<Rabbit>::iterator begin() {return m_rabbits.begin();}
    std::vector<Rabbit>::iterator end() {return m_rabbits.end();}


    unsigned int size() const {
        return m_rabbits.size();
    }

private:
    /// Вектор кроликов
    std::vector<Rabbit> m_rabbits;
};

