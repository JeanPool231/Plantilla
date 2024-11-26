#pragma once
#include "Juego.h"
namespace ejericio2 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			juego = new Juego(2, 1);
			imgPersonaje = gcnew Bitmap("personaje.png");
			imgPersonaje->SetPixel(0, 0, Color::Transparent);
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		Juego* juego;
		Bitmap^ imgPersonaje;
	private: System::Windows::Forms::Timer^ timer1;
	private: System::Windows::Forms::Label^ txttiempo;
	private: System::ComponentModel::IContainer^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary
		void InitializeComponent(void)	{
				this->components = (gcnew System::ComponentModel::Container());
				this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
				this->txttiempo = (gcnew System::Windows::Forms::Label());
				this->SuspendLayout();
				// 
				// timer1
				// 
				this->timer1->Enabled = true;
				this->timer1->Interval = 100;
				this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
				// 
				// txttiempo
				// 
				this->txttiempo->AutoSize = true;
				this->txttiempo->Location = System::Drawing::Point(1307, 19);
				this->txttiempo->Name = L"txttiempo";
				this->txttiempo->Size = System::Drawing::Size(57, 16);
				this->txttiempo->TabIndex = 0;
				this->txttiempo->Text = L"Tiempo:";
				// 
				// MyForm
				// 
				this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
				this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				this->ClientSize = System::Drawing::Size(1434, 716);
				this->Controls->Add(this->txttiempo);
				this->Name = L"MyForm";
				this->Text = L"MyForm";
				this->ResumeLayout(false);
				this->PerformLayout();
		}
#pragma endregion
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		Graphics^ g = this->CreateGraphics();
		BufferedGraphicsContext^ espacioBuffer = BufferedGraphicsManager::Current;
		BufferedGraphics^ buffer = espacioBuffer->Allocate(g, this->ClientRectangle);
		buffer->Graphics->Clear(Color::White);
		if (!juego->juegoActivo()) {
			juego->mostrarPuntajes();
			timer1->Enabled = false;
			MessageBox::Show("El juego ha terminado");
		}
		juego->animarJuego(buffer->Graphics, imgPersonaje);
		txttiempo->Text = "Tiempo: " + (juego->getTotal() * 60 - (juego->getTiempo() / 10));
		buffer->Render(g);
		delete espacioBuffer;
		delete g;
	}
	};
}
