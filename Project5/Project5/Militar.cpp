// Militar.cpp
#include "Militar.h"

Militar::Militar(int x, int y) {
    this->x = x;
    this->y = y;
    dx = 0;
    dy = 0;
    ultimaTecla = ABAJO;
    direccion = NINGUNA;
    ancho = 264;
    alto = 213;
    indiceX = 0;
    indiceY = 0;
}

Militar::~Militar() {
    // No hay recursos dinámicos para liberar
}

void Militar::dibujar(BufferedGraphics^ buffer, Bitmap^ bmp) {
    Rectangle pocisionAUsar = Rectangle(indiceX * ancho, indiceY * alto, ancho, alto);
    Rectangle aumentoPersonaje = Rectangle(x, y, static_cast<int>(ancho * 0.5), static_cast<int>(alto * 0.5));
    buffer->Graphics->DrawImage(bmp, aumentoPersonaje, pocisionAUsar, GraphicsUnit::Pixel);
    x += dx;
    y += dy;
}

void Militar::mover(BufferedGraphics^ buffer, Bitmap^ bmp) {
    switch (direccion)
    {
    case NINGUNA:
        dx = 0;
        dy = 0;
        switch (ultimaTecla)
        {
        case IZQUIERDA:
            indiceX = 1;
            indiceY = 1;
            break;
        case DERECHA:
            indiceX = 1;
            indiceY = 2;
            break;
        case ARRIBA:
            indiceX = 1;
            indiceY = 3;
            break;
        case ABAJO:
            indiceX = 1;
            indiceY = 0;
            break;
        }
        break;
    case IZQUIERDA:
        indiceY = 1;
        if (indiceX >= 0 && indiceX < 2)
        {
            indiceX++;
        }
        else {
            indiceX = 0;
        }
        dx = -10;
        dy = 0;
        ultimaTecla = IZQUIERDA;
        break;
    case DERECHA:
        indiceY = 2;
        if (indiceX >= 0 && indiceX < 2)
        {
            indiceX++;
        }
        else {
            indiceX = 0;
        }
        dx = 10;
        dy = 0;
        ultimaTecla = DERECHA;
        break;
    case ARRIBA:
        indiceY = 3;
        if (indiceX >= 0 && indiceX < 2)
        {
            indiceX++;
        }
        else {
            indiceX = 0;
        }
        dx = 0;
        dy = -10;
        ultimaTecla = ARRIBA;
        break;
    case ABAJO:
        indiceY = 0;
        if (indiceX >= 0 && indiceX < 2)
        {
            indiceX++;
        }
        else {
            indiceX = 0;
        }
        dx = 0;
        dy = 10;
        ultimaTecla = ABAJO;
        break;
    }

    dibujar(buffer, bmp);
}
