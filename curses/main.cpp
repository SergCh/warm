// worm.cpp: определяет точку входа для консольного приложения.
//

//#include "stdafx.h"

#include "Control.h"
#include "TModel.h"
#include "CursesView.h"
#include "Point.h"
#include "RabbitFactory.h"

int main(int /*argc*/, char* /*argv*/[]) {
//int _tmain(int argc, _TCHAR* argv[]) {

	CursesView view;
    RabbitFactory rabbits;
    TModel model(Point(view.getWidthField(), view.getHieghtField()), rabbits);

	Control control(view, model);

	control.init();

    while (true) {
		view.getCommands();

        if (control.isQuit())
			break;

        control.nextStep();
	}

	return 0;
}

