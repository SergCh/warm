#pragma once
#include "VCView.h"
#include "GraphicSnake.h"
#include "Way.h"

namespace vcworm {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для Form1
	///
	/// Внимание! При изменении имени этого класса необходимо также изменить
	///          свойство имени файла ресурсов ("Resource File Name") для средства компиляции управляемого ресурса,
	///          связанного со всеми файлами с расширением .resx, от которых зависит данный класс. В противном случае,
	///          конструкторы не смогут правильно работать с локализованными
	///          ресурсами, сопоставленными данной форме.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(SNAKE_MODEL::VCView * _view)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
			m_view = _view;
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::Button^  buttonQuit;
	private: System::Windows::Forms::Button^  buttonStart;
	private: System::Windows::Forms::Label^  labelScore;


	private:
		/// <summary>
		SNAKE_MODEL::VCView * m_view;
	private: System::Windows::Forms::Timer^  timer1;


	private: System::ComponentModel::IContainer^  components;
			 /// Требуется переменная конструктора.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Обязательный метод для поддержки конструктора - не изменяйте
		/// содержимое данного метода при помощи редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->buttonQuit = (gcnew System::Windows::Forms::Button());
			this->buttonStart = (gcnew System::Windows::Forms::Button());
			this->labelScore = (gcnew System::Windows::Forms::Label());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->panel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(27, 12);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(44, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"SCORE";
			// 
			// panel1
			// 
			this->panel1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->panel1->AutoSize = true;
			this->panel1->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->panel1->Controls->Add(this->buttonQuit);
			this->panel1->Controls->Add(this->buttonStart);
			this->panel1->Controls->Add(this->labelScore);
			this->panel1->Controls->Add(this->label1);
			this->panel1->Location = System::Drawing::Point(310, 12);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(94, 124);
			this->panel1->TabIndex = 1;
			// 
			// buttonQuit
			// 
			this->buttonQuit->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->buttonQuit->Location = System::Drawing::Point(16, 98);
			this->buttonQuit->Name = L"buttonQuit";
			this->buttonQuit->Size = System::Drawing::Size(75, 23);
			this->buttonQuit->TabIndex = 4;
			this->buttonQuit->Text = L"Quit";
			this->buttonQuit->UseVisualStyleBackColor = true;
			this->buttonQuit->Click += gcnew System::EventHandler(this, &Form1::buttonQuit_Click);
			// 
			// buttonStart
			// 
			this->buttonStart->Location = System::Drawing::Point(16, 69);
			this->buttonStart->Name = L"buttonStart";
			this->buttonStart->Size = System::Drawing::Size(75, 23);
			this->buttonStart->TabIndex = 3;
			this->buttonStart->Text = L"Start";
			this->buttonStart->UseVisualStyleBackColor = true;
			this->buttonStart->Click += gcnew System::EventHandler(this, &Form1::buttonStart_Click);
			// 
			// labelScore
			// 
			this->labelScore->AutoSize = true;
			this->labelScore->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->labelScore->Location = System::Drawing::Point(52, 34);
			this->labelScore->Name = L"labelScore";
			this->labelScore->Size = System::Drawing::Size(19, 20);
			this->labelScore->TabIndex = 2;
			this->labelScore->Text = L"0";
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->CancelButton = this->buttonQuit;
			this->ClientSize = System::Drawing::Size(416, 317);
			this->Controls->Add(this->panel1);
			this->KeyPreview = true;
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::Form1_Paint);
			this->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Form1::Form1_KeyPress);
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void buttonQuit_Click(System::Object^  sender, System::EventArgs^  e) {
			 }
	private: System::Void buttonStart_Click(System::Object^  sender, System::EventArgs^  e) {
				timer1->Enabled = false;
				m_view->start();
				labelScore->Text = "" + m_view->getSnake()->size();
				timer1->Enabled = true;
			}
	private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
				timer1->Enabled = false;
				m_view->nextStep();
				labelScore->Text = "" + m_view->getSnake()->size();
				Invalidate();
				if (!m_view->isPause())
					timer1->Enabled = true;
				}
	private: System::Void Form1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
				SNAKE_MODEL::GraphicSnake * snake = m_view->getSnake();
				SNAKE_MODEL::RabbitFactory * rabbits = m_view->getRabbitFactory();
				Graphics^ g = e->Graphics;
				Pen^ blackPen = gcnew Pen( Color::Black,3.0f );
//				g->DrawLine( System::Drawing::Pens::Red,0,0,10,10);
//				g->DrawLine( System::Drawing::Pens::Red, pictureBox1->Left, pictureBox1->Top,
//				pictureBox1->Right, pictureBox1->Bottom );
				for (std::vector<SNAKE_MODEL::GraphicPoint>::iterator iter = snake->begin(); iter != snake->end(); iter++) {
					Rectangle rect = Rectangle(iter->getX()*10, iter->getY() * 10,10,10);
					g->DrawRectangle( blackPen, rect );
				}

				for (std::vector<SNAKE_MODEL::Rabbit>::iterator iter = rabbits->begin(); iter != rabbits->end(); iter++) {
					Rectangle rect = Rectangle(iter->getX()*10, iter->getY() * 10,10,10);
					g->DrawRectangle( blackPen, rect );
				}

 //Pen^ blackPen = gcnew Pen( Color::Black,3.0f );

      // Create rectangle.
//      Rectangle rect = Rectangle(0,0,200,200);

      // Draw rectangle to screen.
      //e->Graphics->DrawRectangle( blackPen, rect );
			 }
private: System::Void Form1_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
			 switch (e->KeyChar) {
//				 case Keys::Left:
				 case '4':
					 m_view->changeWay(SNAKE_MODEL::Way::LEFT);
					e->Handled = true;
					break;
//				 case Keys::Right:
				 case '6':
					 m_view->changeWay(SNAKE_MODEL::Way::RIGHT);
					e->Handled = true;
					break;
//				 case Keys::Up:
				 case '8':
					 m_view->changeWay(SNAKE_MODEL::Way::UP);
					e->Handled = true;
					break;
//				 case Keys::Down:
				 case '2':
					 m_view->changeWay(SNAKE_MODEL::Way::DOWN);
					e->Handled = true;
					break;
			 }
		 }
};
}

