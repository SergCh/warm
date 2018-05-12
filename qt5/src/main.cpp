#include "MainWindow.h"
#include <QApplication>
#include <ctime>


#include "Qt5View.h"
#include "View.h"
#include "Control.h"
#include "TModel.h"
#include "RabbitFactory.h"
#include "Config.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    std::srand(unsigned(std::time(0)));

    Qt5View view;

    Model model(Point(view.getWidthField(), view.getHieghtField()));

    Control control(view, model);
    std::srand(unsigned(std::time(0)));

    control.init();

    MainWindow w(&view);
    w.show();

    return a.exec();
}
