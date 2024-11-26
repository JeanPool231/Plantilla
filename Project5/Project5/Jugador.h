// Jugador.h
#pragma once
using namespace System::Drawing;

#include "Direcciones.h"

class Jugador
{
public:
    Jugador(int x, int y) {
        this->x = x;
        this->y = y;
        dx = 0;
        dy = 0;
        ultimaTecla = Abajo;
        direccion = Ninguna;
        ancho = 272 / 4;
        alto = 288 / 4;
        indiceX = 0;
        indiceY = 0;
        vidas = 3;
    }
    ~Jugador() {}
    
    Direcciones direccion;

    // Getter para ultimaTecla
    Direcciones getUltimaTecla() const {
        return ultimaTecla;
    }

    // Getter para vidas
    int getVidas() const {
        return vidas;
    }

    // Reducir una vida
    void reducirVida() {
        if (vidas > 0) {
            vidas--;
        }
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
            switch (ultimaTecla) {
            case Abajo:
                indiceX = 0;
                indiceY = 0;
                break;
            case Arriba:
                indiceX = 0;
                indiceY = 3;
                break;
            case Izquierda:
                indiceX = 0;
                indiceY = 1;
                break;
            case Derecha:
                indiceX = 0;
                indiceY = 2;
                break;
            }
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

        dibujar(g, bmp);
    }

    int getVidas() { return vidas; }
    void setVidas(int vidas) { this->vidas = vidas; }
    void disminuirVida() {
        if (vidas > 0) {
            vidas--;
        }
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
    // Vidas
    int vidas;
};
