// vcworm.cpp: ������� ���� �������.

#include "Form1.h"
#include "VCView.h"
#include "GraphicSnake.h"
#include "Control.h"
#include "Model.h"

using namespace vcworm;
//using namespace SNAKE_MODEL;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
//    std::srand(unsigned(std::time(0)));
	
	SNAKE_MODEL::VCView view;
    SNAKE_MODEL::GraphicSnake snake;
	SNAKE_MODEL::Model model(SNAKE_MODEL::Point(view.getWidthField(), view.getHieghtField()), snake);
    SNAKE_MODEL::Control control(view, model);
    control.init();

//    MainWindow w(&view);


	// ��������� ���������� �������� Windows XP �� �������� �����-���� ��������� ����������
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// �������� �������� ���� � ��� ������
	Application::Run(gcnew Form1(&view));
	return 0;
}
