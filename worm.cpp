// worm.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#include "Control.h"
#include "Model.h"
#include "View.h"

int _tmain(int argc, _TCHAR* argv[]) {

	View view;
	Model model(view.getWigthField(), view.getHieghtField());

	Control control(view, model);
	view.setControl(&control);

	control.init();

	int count =10;

	while (!0) {
		view.getCommands();

		if (control.isQuit()) 
			break;
		
		if (!control.move()) {
			control.endGame();
			control.restart();
		}
		
		if (!--count) {
			count = 50;
			control.addRabbit();
		}
	}

	return 0;
}

