#pragma once
#include "Controlador.h"

namespace ejercicio1 {

	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;

	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();

			controlador = new Controlador();
			controlador->inicializar(this->ClientSize.Width, this->ClientSize.Height);

			this->SetStyle(ControlStyles::AllPaintingInWmPaint | ControlStyles::UserPaint | ControlStyles::DoubleBuffer, true);

			timer = gcnew Timer();
			timer->Interval = 16;
			timer->Tick += gcnew EventHandler(this, &MyForm::OnTimerTick);
			timer->Start();

			this->KeyDown += gcnew KeyEventHandler(this, &MyForm::OnKeyDown);
			this->KeyUp += gcnew KeyEventHandler(this, &MyForm::OnKeyUp);

			direccionActual = Direccion::NINGUNA;

			jugadorBmp = gcnew Bitmap("sprites/jugador.png");
		}

	protected:
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
			delete controlador;
			delete jugadorBmp;
		}

	protected:
		virtual void OnPaint(PaintEventArgs^ e) override
		{
			BufferedGraphicsContext^ context = BufferedGraphicsManager::Current;
			BufferedGraphics^ buffer = context->Allocate(e->Graphics, this->ClientRectangle);

			Graphics^ g = buffer->Graphics;

			if (this->BackgroundImage == nullptr) {
				g->Clear(this->BackColor);
			}
			else {
				g->DrawImage(this->BackgroundImage, 0, 0, this->ClientSize.Width, this->ClientSize.Height);
			}

			controlador->dibujar(g, jugadorBmp);

			buffer->Render(e->Graphics);

			delete buffer;
			delete context;
			delete g;
		}

	private:
		System::ComponentModel::Container^ components;
		Controlador* controlador; 
		Timer^ timer;
		Direccion direccionActual;
		Bitmap^ jugadorBmp;

		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->SuspendLayout();
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(784, 727);
			this->Name = L"MyForm";
			this->Text = L"Juego con Jugador";
			this->ResumeLayout(false);
		}

		void OnTimerTick(Object^ sender, EventArgs^ e)
		{
			controlador->actualizar(direccionActual, this->ClientSize.Width, this->ClientSize.Height, this->CreateGraphics(), jugadorBmp);
			this->Invalidate();
		}

		void OnKeyDown(Object^ sender, KeyEventArgs^ e)
		{
			switch (e->KeyCode)
			{
			case Keys::Up:
				direccionActual = Direccion::ARRIBA;
				break;
			case Keys::Down:
				direccionActual = Direccion::ABAJO;
				break;
			case Keys::Left:
				direccionActual = Direccion::IZQUIERDA;
				break;
			case Keys::Right:
				direccionActual = Direccion::DERECHA;
				break;
			default:
				break;
			}
		}

		void OnKeyUp(Object^ sender, KeyEventArgs^ e)
		{
			direccionActual = Direccion::NINGUNA;
		}
	};
}
