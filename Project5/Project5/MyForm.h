#pragma once

#include "Controlador.h"
#include "ControladorArchivos.h"
#include "fstream"
namespace Project5 {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class MyForm : public System::Windows::Forms::Form {
    public:
        MyForm(void) {
            InitializeComponent();

            try {
                // Cargar los sprites
                bmpJugador = gcnew Bitmap("sprites/jugador.png");
                bmpProyectil = gcnew Bitmap("sprites/proyectil.png");
                bmpEnemigo = gcnew Bitmap("sprites/enemigo.png");

                buffer = gcnew Bitmap(this->ClientSize.Width, this->ClientSize.Height);
                direccionActual = Ninguna;
                teclaPresionada = false;

                ControladorArchivos controladorArchivosObj;
                controladorArchivosObj.leerTiempo("config.txt");

                tiempoRestante = controladorArchivosObj.getTiempoJuego();

                controlador = new Controlador();

                // Configurar el temporizador del juego
                gameTimer = gcnew Timer();
                gameTimer->Interval = 16; // Aproximadamente 60 FPS (16 ms)
                gameTimer->Tick += gcnew EventHandler(this, &MyForm::OnGameTick);
                gameTimer->Start();

                // Configurar el temporizador de cuenta regresiva
                countdownTimer = gcnew Timer();
                countdownTimer->Interval = 1000; // 1 segundo
                countdownTimer->Tick += gcnew EventHandler(this, &MyForm::OnCountdownTick);
                countdownTimer->Start();

                // Configurar estilos para doble búfer y evitar parpadeo
                this->SetStyle(ControlStyles::UserPaint, true);
                this->SetStyle(ControlStyles::AllPaintingInWmPaint, true);
                this->SetStyle(ControlStyles::DoubleBuffer, true);

                // Actualizar los labels para mostrar el tiempo inicial y las vidas
                label1->Text = "Tiempo: " + tiempoRestante.ToString() + "s";
                label2->Text = "Vidas: " + controlador->getJugador()->getVidas().ToString();
                label3->Text = "Puntos: 0";

                // Conectar eventos de teclado y redimensionamiento
                this->KeyDown += gcnew KeyEventHandler(this, &MyForm::OnKeyDownHandler);
                this->KeyUp += gcnew KeyEventHandler(this, &MyForm::OnKeyUpHandler);
                this->Resize += gcnew EventHandler(this, &MyForm::OnResize);
            }
            catch (Exception^ ex) {
                MessageBox::Show("Error al iniciar el juego: " + ex->Message, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                this->Close();
            }
        }

    protected:
        ~MyForm() {
            if (components) {
                delete components;
            }
            if (countdownTimer != nullptr && countdownTimer->Enabled) {
                countdownTimer->Stop();
            }
            if (gameTimer != nullptr && gameTimer->Enabled) {
                gameTimer->Stop();
            }
            delete controlador;
            delete bmpJugador;
            delete bmpProyectil;
            delete bmpEnemigo;
            delete buffer;
            std::ofstream GuardarBin;
            GuardarBin.open("PuntajesBin.dat", std::ios::app | std::ios::binary);
            if (GuardarBin.is_open()) {

                int puntaje = controlador->getContadorEnemigosMuertos();

                GuardarBin.write((const char*)&puntaje, sizeof(puntaje));
                char saltoDeLinea = '\n';
                GuardarBin.write(&saltoDeLinea, sizeof(saltoDeLinea));
                GuardarBin.close();
            }
        }

    private:
        Controlador* controlador;
        Bitmap^ bmpJugador;
        Bitmap^ bmpProyectil;
        Bitmap^ bmpEnemigo;
        Bitmap^ buffer;
        Direcciones direccionActual;
        Timer^ gameTimer;
        Timer^ countdownTimer;
        int tiempoRestante;
        bool teclaPresionada;

        System::Windows::Forms::Label^ label1;
        System::Windows::Forms::Label^ label2;
        System::Windows::Forms::Label^ label3;

        System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void) {
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->label2 = (gcnew System::Windows::Forms::Label());
            this->label3 = (gcnew System::Windows::Forms::Label());
            this->SuspendLayout();

            // 
            // label1
            // 
            this->label1->AutoSize = true;
            this->label1->Location = System::Drawing::Point(12, 18);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(60, 13);
            this->label1->TabIndex = 0;
            this->label1->Text = L"Tiempo: 120s";
            // 
            // label2
            // 
            this->label2->AutoSize = true;
            this->label2->Location = System::Drawing::Point(12, 40);
            this->label2->Name = L"label2";
            this->label2->Size = System::Drawing::Size(60, 13);
            this->label2->TabIndex = 1;
            this->label2->Text = L"Vidas: 3";
            // 
            // label3
            // 
            this->label3->AutoSize = true;
            this->label3->Location = System::Drawing::Point(12, 70);
            this->label3->Name = L"label3";
            this->label3->Size = System::Drawing::Size(60, 13);
            this->label3->TabIndex = 2;
            this->label3->Text = L"Puntos: 0";
            // 
            // MyForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(800, 600);
            this->Controls->Add(this->label3);
            this->Controls->Add(this->label2);
            this->Controls->Add(this->label1);
            this->Name = L"MyForm";
            this->Text = L"Game";
            this->ResumeLayout(false);
            this->PerformLayout();
        }
#pragma endregion

    public:
        void ReiniciarEstadoDelJuego() {
            // Reiniciar variables y objetos del juego
            if (controlador != nullptr) {
                delete controlador;
            }
            controlador = new Controlador();

            // Reiniciar los temporizadores
            if (!gameTimer->Enabled) {
                gameTimer->Start();
            }
            if (!countdownTimer->Enabled) {
                countdownTimer->Start();
            }

            // Restablecer el tiempo restante
            ControladorArchivos controladorArchivosObj;
            controladorArchivosObj.leerTiempo("config.txt");
            tiempoRestante = controladorArchivosObj.getTiempoJuego();

            // Actualizar labels
            label1->Text = "Tiempo: " + tiempoRestante.ToString() + "s";
            label2->Text = "Vidas: " + controlador->getJugador()->getVidas().ToString();
            label3->Text = "Puntos: 0";

            // Asegurarse de que el formulario principal esté visible
            this->Show();
        }

    private:
        void MostrarGameOverForm(int puntos) {
            // Crear un nuevo formulario de "Game Over"
            Form^ gameOverForm = gcnew Form();
            gameOverForm->Text = "Game Over";
            gameOverForm->ClientSize = System::Drawing::Size(300, 200);
            gameOverForm->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            gameOverForm->StartPosition = FormStartPosition::CenterScreen;
            gameOverForm->MaximizeBox = false;
            gameOverForm->MinimizeBox = false;

            Label^ labelMensaje = gcnew Label();
            labelMensaje->Text = "¡Game Over!\nPuntos: " + puntos.ToString();
            labelMensaje->AutoSize = true;
            labelMensaje->Location = Point(80, 40);
            labelMensaje->TextAlign = ContentAlignment::MiddleCenter;
            gameOverForm->Controls->Add(labelMensaje);

            Button^ buttonReiniciar = gcnew Button();
            buttonReiniciar->Text = "Reiniciar";
            buttonReiniciar->Location = Point(50, 120);
            // Pasar 'this' al manejador de eventos
            buttonReiniciar->Click += gcnew EventHandler(this, &MyForm::ReiniciarJuego);
            gameOverForm->Controls->Add(buttonReiniciar);

            Button^ buttonSalir = gcnew Button();
            buttonSalir->Text = "Salir";
            buttonSalir->Location = Point(150, 120);
            buttonSalir->Click += gcnew EventHandler(this, &MyForm::SalirJuego);
            gameOverForm->Controls->Add(buttonSalir);

            // Ocultar el formulario principal y mostrar el formulario de Game Over
            this->Hide();
            gameOverForm->ShowDialog();
            // Después de cerrar el formulario de Game Over, mostrar el formulario principal nuevamente
            this->Show();
        }

        void ReiniciarJuego(Object^ sender, EventArgs^ e) {
            // Cerrar el formulario de Game Over
            Form^ gameOverForm = (Form^)((Control^)sender)->Parent;
            gameOverForm->Close();

            // Reiniciar el estado del juego
            ReiniciarEstadoDelJuego();
        }

        void SalirJuego(Object^ sender, EventArgs^ e) {
            // Salir de la aplicación
        
            Application::Exit();
            

        }

        // Método para manejar la pulsación de teclas
        void OnKeyDownHandler(Object^ sender, KeyEventArgs^ e) {
            switch (e->KeyCode) {
            case Keys::Space:
                controlador->disparar(bmpProyectil);
                break;
            case Keys::Up:
                direccionActual = Arriba;
                teclaPresionada = true;
                break;
            case Keys::Down:
                direccionActual = Abajo;
                teclaPresionada = true;
                break;
            case Keys::Left:
                direccionActual = Izquierda;
                teclaPresionada = true;
                break;
            case Keys::Right:
                direccionActual = Derecha;
                teclaPresionada = true;
                break;
            default:
                break;
            }
            this->Invalidate();
        }

        // Método para manejar la liberación de teclas
        void OnKeyUpHandler(Object^ sender, KeyEventArgs^ e) {
            direccionActual = Ninguna;
            teclaPresionada = false;
            this->Invalidate();
        }

        // Método para manejar el redimensionamiento del formulario
        void OnResize(Object^ sender, EventArgs^ e) {
            if (buffer != nullptr) {
                delete buffer;
            }
            buffer = gcnew Bitmap(this->ClientSize.Width, this->ClientSize.Height);
        }

        // Método llamado en cada tick del temporizador del juego
        void OnGameTick(Object^ sender, EventArgs^ e) {
            controlador->actualizar(this->ClientSize.Width, this->ClientSize.Height, bmpEnemigo);

            label2->Text = "Vidas: " + controlador->getJugador()->getVidas().ToString();
            label3->Text = "Puntos: " + controlador->getContadorEnemigosMuertos().ToString();

            if (controlador->estaTerminado()) {
                gameTimer->Stop();
                countdownTimer->Stop();
                MostrarGameOverForm(controlador->getContadorEnemigosMuertos());
                return;
            }

            this->Invalidate();
        }

        // Método llamado en cada tick del temporizador de cuenta regresiva
        void OnCountdownTick(Object^ sender, EventArgs^ e) {
            if (tiempoRestante > 0) {
                tiempoRestante--;
                label1->Text = "Tiempo: " + tiempoRestante.ToString() + "s";
            }
            else {
                gameTimer->Stop();
                countdownTimer->Stop();
                MostrarGameOverForm(controlador->getContadorEnemigosMuertos());
                return;
            }
        }

    protected:
        // Método para dibujar en el formulario
        virtual void OnPaint(PaintEventArgs^ e) override {
            Graphics^ bufferGraphics = Graphics::FromImage(buffer);

            bufferGraphics->Clear(this->BackColor);
            controlador->moverJugador(direccionActual, bufferGraphics, bmpJugador, this->ClientSize.Width, this->ClientSize.Height);
            controlador->dibujarJugador(bufferGraphics, bmpJugador);
            controlador->dibujarProyectiles(bufferGraphics, bmpProyectil);
            controlador->dibujarEnemigos(bufferGraphics, bmpEnemigo);

            e->Graphics->DrawImage(buffer, 0, 0);
            delete bufferGraphics;
        }
    };
}
