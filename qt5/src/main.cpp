#include "MainWindow.h"
#include <QApplication>

#include "Qt5View.h"
#include "View.h"
#include "Control.h"
#include "Model.h"
#include "RabbitFactory.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Qt5View view;

    RabbitFactory rabbits;
//    View *v = (View *) view;
    Model model(Point(view.getWigthField(), view.getHieghtField()), rabbits);

//    ThreadControl control(view, model);
    Control control(view, model);

    control.init();


    MainWindow w(&view);
    w.show();

    return a.exec();
}
