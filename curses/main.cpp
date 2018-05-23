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

//using namespace Snake;

int main(int /*argc*/, char* /*argv*/[]) {
//int _tmain(int argc, _TCHAR* argv[]) {

    std::srand(unsigned(std::time(0)));
    Snake::CursesView view;
    Snake::TSnake<Snake::Point> snake;

    Snake::Model model(Snake::Point(view.getWidthField(), view.getHieghtField()), snake);

    Snake::Control control(view, model);

	control.init();

    while (true) {
		view.getCommands();

        if (control.isQuit())
			break;

        control.nextStep();
	}

	return 0;
}

