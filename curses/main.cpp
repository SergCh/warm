// worm.cpp: определяет точку входа для консольного приложения.
//

#include <ctime>

#include "Control.h"
#include "TModel.h"
#include "CursesView.h"
#include "Point.h"
#include "RabbitFactory.h"
#include "Config.h"

int main(int /*argc*/, char* /*argv*/[]) {
//int _tmain(int argc, _TCHAR* argv[]) {

    std::srand(unsigned(std::time(0)));
	CursesView view;
    RabbitFactory rabbits;
    Model model(Point(view.getWidthField(), view.getHieghtField()), rabbits);

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

