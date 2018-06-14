// vcworm.cpp: главный файл проекта.

#include <ctime>

#include "Form1.h"
#include "VCView.h"
#include "GraphicSnake.h"
#include "Control.h"
#include "Model.h"

using namespace vcworm;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
    std::srand(unsigned(std::time(0)));
	
	Snake::VCView view;
    Snake::GraphicSnake snake;
	Snake::Model model(Snake::Point(view.getWidthField(), view.getHieghtField()), snake);
    Snake::Control control(view, model);
    control.init();

	// Включение визуальных эффектов Windows XP до создания каких-либо элементов управления
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Создание главного окна и его запуск
	Application::Run(gcnew Form1(&view));
	return 0;
}
