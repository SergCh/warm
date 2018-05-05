// worm.cpp: определяет точку входа для консольного приложения.
//

//#include "stdafx.h"

#include "Control.h"
#include "Model.h"
#include "CursesView.h"
#include "Point.h"
#include "RabbitFactory.h"

int main(int argc, char* argv[]) {
//int _tmain(int argc, _TCHAR* argv[]) {

	CursesView view;
    RabbitFactory rabbits;
    Model model(Point(view.getWigthField(), view.getHieghtField()), rabbits);

	Control control(view, model);

	control.init();

	int count =10;

	while (!0) {
		view.getCommands();

        if (control.isQuit())
			break;

        if (control.isPause()) {
            view.endGame(model.getSnake().size());
            control.restart();
        } else {
            control.nextStep();
        }
	}

	return 0;
}

