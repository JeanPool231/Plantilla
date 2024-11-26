#pragma once
#include <ctime> // Para srand y rand
#include <cstdlib> // Para srand y rand
#include "Direcciones.h"
using namespace System::Drawing;


class Enemigo
{
public:
    Enemigo(int x, int y) {
        this->x = x;
        this->y = y;
        dx = 0;
        dy = 0;
        ultimaTecla = Abajo;
        direccion = Ninguna;
        ancho = 256 / 4;
        alto = 256 / 4;
        indiceX = 0;
        indiceY = 0;
        tiempoCambioDireccion = 0;
        // No es necesario llamar a srand aquí si ya se ha llamado en Controlador
    }
    ~Enemigo() {}

    Direcciones direccion;

    // Getter para ultimaTecla
    Direcciones getUltimaTecla() const {
        return ultimaTecla;
    }

    Rectangle getRectangulo() {
        return Rectangle(x, y, ancho, alto);
    }
    void setX(int v) { x = v; }
    void setY(int v) { y = v; }

    int getX() const { return x; }
    int getY() const { return y; }

    void dibujar(Graphics^ g, Bitmap^ bmp) {
        Rectangle porcionAUsar = Rectangle(indiceX * ancho, indiceY * alto, ancho, alto);
        Rectangle aumentoPersonaje = Rectangle(x, y, ancho, alto);
        g->DrawImage(bmp, aumentoPersonaje, porcionAUsar, GraphicsUnit::Pixel);
    }

    void mover(Graphics^ g, Bitmap^ bmp, int limiteAncho, int limiteAlto) {
        // Cambiar de dirección aleatoriamente cada cierto tiempo
        if (tiempoCambioDireccion >= 30) { // Cambia de dirección cada 30 llamadas
            direccion = static_cast<Direcciones>(1 + rand() % 4); // Genera una dirección aleatoria (Abajo, Arriba, Izquierda, Derecha)
            tiempoCambioDireccion = 0;
        }
        else {
            tiempoCambioDireccion++;
        }

        // Validación para evitar que salga de los límites
        if ((x + dx >= 0) && (x + dx + ancho <= limiteAncho)) {
            x += dx;
        }
        if ((y + dy >= 0) && (y + dy + alto <= limiteAlto)) {
            y += dy;
        }

        // Animación y cambio de dirección
        switch (direccion) {
        case Ninguna:
            dx = 0;
            dy = 0;
            break;
        case Abajo:
            indiceY = 0;
            if (indiceX >= 0 && indiceX < 3)
                indiceX++;
            else
                indiceX = 0;
            dx = 0;
            dy = 10;
            ultimaTecla = Abajo;
            break;
        case Arriba:
            indiceY = 3;
            if (indiceX >= 0 && indiceX < 3)
                indiceX++;
            else
                indiceX = 0;
            dx = 0;
            dy = -10;
            ultimaTecla = Arriba;
            break;
        case Izquierda:
            indiceY = 1;
            if (indiceX >= 0 && indiceX < 3)
                indiceX++;
            else
                indiceX = 0;
            dx = -10;
            dy = 0;
            ultimaTecla = Izquierda;
            break;
        case Derecha:
            indiceY = 2;
            if (indiceX >= 0 && indiceX < 3)
                indiceX++;
            else
                indiceX = 0;
            dx = 10;
            dy = 0;
            ultimaTecla = Derecha;
            break;
        }

        // Nota: No dibujar aquí, se dibujará desde MyForm
    }

private:
    // Posición
    int x;
    int y;
    // Velocidad
    int dx;
    int dy;
    // Tamaño
    int ancho;
    int alto;
    // Animación
    int indiceX;
    int indiceY;
    // Dirección
    Direcciones ultimaTecla;
    // Temporizador para cambiar dirección
    int tiempoCambioDireccion;
};
