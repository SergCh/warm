#include "MainWindow.h"
#include <QApplication>
#include <ctime>


#include "Qt5View.h"
#include "View.h"
#include "Control.h"
#include "Model.h"
#include "RabbitFactory.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    std::srand(unsigned(std::time(0)));

    Qt5View view;

    RabbitFactory rabbits;
    Model model(Point(view.getWidthField(), view.getHieghtField()), rabbits);

    Control control(view, model);
    std::srand(unsigned(std::time(0)));


    control.init();


    MainWindow w(&view);
    w.show();

    return a.exec();
}
