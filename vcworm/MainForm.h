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
		Form1(Snake::VCView * _view)
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


	private: System::Windows::Forms::Label^  labelScore;


	private:
		/// <summary>
		Snake::VCView * m_view;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::PictureBox^  pictureBoxField;

	private: System::Windows::Forms::Button^  buttonQuit;
	private: System::Windows::Forms::Button^  buttonStart;


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
			this->pictureBoxField = (gcnew System::Windows::Forms::PictureBox());
			this->panel1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBoxField))->BeginInit();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(27, 12);
			this->label1->Margin = System::Windows::Forms::Padding(3, 10, 3, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(44, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"SCORE";
			// 
			// panel1
			// 
			this->panel1->AutoSize = true;
			this->panel1->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->panel1->Controls->Add(this->buttonQuit);
			this->panel1->Controls->Add(this->buttonStart);
			this->panel1->Controls->Add(this->labelScore);
			this->panel1->Controls->Add(this->label1);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Right;
			this->panel1->Location = System::Drawing::Point(498, 0);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(94, 466);
			this->panel1->TabIndex = 1;
			// 
			// buttonQuit
			// 
			this->buttonQuit->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->buttonQuit->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->buttonQuit->Location = System::Drawing::Point(16, 98);
			this->buttonQuit->Name = L"buttonQuit";
			this->buttonQuit->Size = System::Drawing::Size(75, 23);
			this->buttonQuit->TabIndex = 4;
			this->buttonQuit->TabStop = false;
			this->buttonQuit->Text = L"Quit";
			this->buttonQuit->UseVisualStyleBackColor = true;
			this->buttonQuit->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &Form1::buttonStart_PreviewKeyDown);
			this->buttonQuit->Click += gcnew System::EventHandler(this, &Form1::buttonQuit_Click);
			// 
			// buttonStart
			// 
			this->buttonStart->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->buttonStart->Location = System::Drawing::Point(16, 69);
			this->buttonStart->Name = L"buttonStart";
			this->buttonStart->Size = System::Drawing::Size(75, 23);
			this->buttonStart->TabIndex = 3;
			this->buttonStart->TabStop = false;
			this->buttonStart->Text = L"Start";
			this->buttonStart->UseVisualStyleBackColor = true;
			this->buttonStart->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &Form1::buttonStart_PreviewKeyDown);
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
			// pictureBoxField
			// 
			this->pictureBoxField->BackColor = System::Drawing::SystemColors::Control;
			this->pictureBoxField->Cursor = System::Windows::Forms::Cursors::Default;
			this->pictureBoxField->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pictureBoxField->Location = System::Drawing::Point(0, 0);
			this->pictureBoxField->Name = L"pictureBoxField";
			this->pictureBoxField->Size = System::Drawing::Size(498, 466);
			this->pictureBoxField->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->pictureBoxField->TabIndex = 2;
			this->pictureBoxField->TabStop = false;
			this->pictureBoxField->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::pictureBox1_Paint);
			this->pictureBoxField->SizeChanged += gcnew System::EventHandler(this, &Form1::pictureBox1_SizeChanged);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(592, 466);
			this->Controls->Add(this->pictureBoxField);
			this->Controls->Add(this->panel1);
			this->KeyPreview = true;
			this->MinimumSize = System::Drawing::Size(600, 500);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::Form1_KeyDown);
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBoxField))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void buttonQuit_Click(System::Object^  sender, System::EventArgs^  e) {
				 this->Close();
			 }
	private: System::Void buttonStart_Click(System::Object^  sender, System::EventArgs^  e) {
				timer1->Enabled = false;
				m_view->start();
				labelScore->Text = "" + m_view->getScore();
				timer1->Enabled = true;
			}
	private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
				timer1->Enabled = false;
				m_view->nextStep();
				labelScore->Text = "" + m_view->getScore();
				pictureBox1->Invalidate();
				if (!m_view->isPause())
					timer1->Enabled = true;
				}

	private: System::Void pictureBox1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
			Graphics^ g = e->Graphics;

			const int bh = m_view->getHieghtField();
			const int bw = m_view->getWidthField();

			const int s = std::min(pictureBox1->Height/bh, pictureBox1->Width/bw);

			m_view->initDraw(s);
			m_view->paintGame();
			const std::vector<int> &  primetives = m_view->getPrimitives();

			g->Clear(System::Drawing::SystemColors::Control);

			unsigned int i=0;
			while (i < primetives.size()) {
				switch(primetives[i++]) {
				case Snake::VCView::RECTANGLE:
					{
						int x = primetives.at(i++);
						int y = primetives.at(i++);
						int w = primetives.at(i++);
						int h = primetives.at(i++);
						Color c = getColor(primetives.at(i++));

						SolidBrush^ brush = gcnew SolidBrush(c);
						g->FillRectangle(brush, x, y, w, h);
					}
					break;
				case Snake::VCView::LINE:
					{
						int x1 = primetives.at(i++);
						int y1 = primetives.at(i++);
						int x2 = primetives.at(i++);
						int y2 = primetives.at(i++);
						Color c = getColor(primetives.at(i++));
	
						Pen ^ pen = gcnew Pen(c, 1.0F);
						pen->DashStyle = System::Drawing::Drawing2D::DashStyle::Dot;
						g->DrawLine(pen, x1, y1, x2, y2);
					}
					break;
				case Snake::VCView::TEXT:
					{
					}
				}
			}
		 }

private: System::Void pictureBox1_SizeChanged(System::Object^  sender, System::EventArgs^  e) {
			pictureBox1->Invalidate();
		 }

private: Color getColor(int _c) 
		 {
			 switch (_c) {
				 case Snake::VCView::COLOR_FIELD:  return Color::DarkGray;
				 case Snake::VCView::COLOR_RABBIT: return Color::Green;
				 case Snake::VCView::COLOR_SNAKE0: return Color::Red;
				 case Snake::VCView::COLOR_SNAKE1: return Color::Yellow;
				 case Snake::VCView::COLOR_PATH:   return Color::Cyan;
				 default: break;
			 }
			 if (_c >= Snake::VCView::COLOR_TAIL) {
				 Color color = Color::FromArgb((_c - Snake::VCView::COLOR_TAIL) * 4, Color::Gray);
				 return color;
			 }
			 return Color::DarkGray;
		 }

private: System::Void Form1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
				 switch (e->KeyCode) {
				 case Keys::Left:
					 m_view->changeWay(Snake::Way::LEFT);
					e->Handled = true;
					break;
				 case Keys::Right:
					 m_view->changeWay(Snake::Way::RIGHT);
					e->Handled = true;
					break;
				 case Keys::Up:
					 m_view->changeWay(Snake::Way::UP);
					e->Handled = true;
					break;
				 case Keys::Down:
					 m_view->changeWay(Snake::Way::DOWN);
					e->Handled = true;
					break;
			 }
		 }
private: System::Void buttonStart_PreviewKeyDown(System::Object^  sender, System::Windows::Forms::PreviewKeyDownEventArgs^  e) {
			 e->IsInputKey = true;
		 }
};
}

