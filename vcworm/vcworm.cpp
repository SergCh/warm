// vcworm.cpp: ������� ���� �������.

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

	// ��������� ���������� �������� Windows XP �� �������� �����-���� ��������� ����������
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// �������� �������� ���� � ��� ������
	Application::Run(gcnew Form1(&view));
	return 0;
}
