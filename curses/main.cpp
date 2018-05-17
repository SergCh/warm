// worm.cpp: определяет точку входа для консольного приложения.
//

#include <ctime>

#include "Control.h"
#include "Model.h"
#include "CursesView.h"
#include "Point.h"
#include "RabbitFactory.h"
#include "Config.h"
#include "TSnake.h"
#include "TSnake.tcc"

//m_rabbitFactorytypedef TSnake<Point> Snake;

int main(int /*argc*/, char* /*argv*/[]) {
//int _tmain(int argc, _TCHAR* argv[]) {

    std::srand(unsigned(std::time(0)));
	CursesView view;
    Snake snake;

    Model model(Point(view.getWidthField(), view.getHieghtField()), snake);

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

