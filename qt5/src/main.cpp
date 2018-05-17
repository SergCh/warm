#include "MainWindow.h"
#include <QApplication>
#include <ctime>

#include "GraphicSnake.h"

#include "Qt5View.h"
#include "IView.h"
#include "Control.h"
#include "TModel.h"
#include "RabbitFactory.h"

#include "Config.h"

#include "TModel.tcc"
#include "Control.tcc"



int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    std::srand(unsigned(std::time(0)));

    Qt5View view;

    TModel<GraphicSnake> model(Point(view.getWidthField(), view.getHieghtField()));

    Control<GraphicSnake> control(view, model);
    std::srand(unsigned(std::time(0)));

    control.init();

    MainWindow w(&view);
    w.show();

    return a.exec();
}
