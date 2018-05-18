#pragma once

#include "VCView.h"

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



	protected: 

	private:
		/// <summary>
		SNAKE_MODEL::VCView * m_view;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::Panel^  panelField;

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
			this->panelField = (gcnew System::Windows::Forms::Panel());
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
			// panelField
			// 
			this->panelField->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->panelField->AutoSize = true;
			this->panelField->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panelField->Location = System::Drawing::Point(12, 12);
			this->panelField->Name = L"panelField";
			this->panelField->Size = System::Drawing::Size(292, 301);
			this->panelField->TabIndex = 2;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(416, 317);
			this->Controls->Add(this->panelField);
			this->Controls->Add(this->panel1);
			this->Name = L"Form1";
			this->Text = L"Form1";
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
					//repaint();
				if (!m_view->isPause())
					timer1->Enabled = true;
				}
	};
}

