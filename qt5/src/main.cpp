#include "MainWindow.h"
#include <QApplication>
#include <ctime>

#include "GraphicSnake.h"

#include "Qt5View.h"
#include "IView.h"
#include "Control.h"
#include "Model.h"
#include "RabbitFactory.h"

#include "TSnake.tcc"


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    std::srand(unsigned(std::time(0)));

    Qt5View view;

    GraphicSnake snake;

    Model model(Point(view.getWidthField(), view.getHieghtField()), snake);

    Control control(view, model);
    std::srand(unsigned(std::time(0)));

    control.init();

    MainWindow w(&view);
    w.show();

    return a.exec();
}
