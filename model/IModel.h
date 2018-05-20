#pragma once

/**
 * @file Imodel.h
 * @brief %{Cpp:License:ClassName}
 * @author Чугайнов С.В.
 * @date 17.05.2018
 *
 *
 */

#include "ISnake.h"
#include "Point.h"
#include "Way.h"
#include "RabbitFactory.h"

namespace Snake {

    class IModel {

    public:
        // передача параметров ширины и высоты поля
        IModel(){}

        // состояние змея
        typedef enum {
            DEAD,           ///< Двигаться дальше не может
            GOOD            ///< Может двигаться, длина не изменилась
        } StateGame;

        // изменение змея, надо будкт создать класс змея и убрать в него
        typedef enum {
            NOT_CHANGED,    ///< Не измениля
            ADDED,          ///< Добавился один элемент спереди
            MOVED,          ///< Добавился один элемент спереди и ублася один элемент сзади
            MOVED_SHOTER,   ///< Добавился один элемент спереди и убралось 2 элемента сзади
            STARTED         ///< Начальный короткий змей
        } StateSnake;


        virtual void init() = 0;

        // получить змея для передачи его на прорисовку
        virtual ISnake & getSnake() = 0;

        // сменить путь направления змея
        virtual void changeWay(Way _way) = 0;

        // добавить кролика (на поле может быть несколько кроликов)
        virtual void addRabbit() = 0;

        virtual RabbitFactory * getRabbitFactory() = 0;

        // сделать шаг (Выдача состояние модели)
        virtual std::pair<typename IModel::StateGame, typename IModel::StateSnake> move() = 0;

        virtual IModel::StateGame getStateGame() const = 0;

    };

}
