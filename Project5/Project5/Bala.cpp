#include "Bala.h"

Bala::Bala(int x, int y)
{
    this->x = x;
    this->y = y;
    dx = 20; // Velocidad de la bala hacia la derecha
    dy = 0;
    ancho = 10; // Ancho de la bala
    alto = 10;  // Alto de la bala
    indiceX = 0;
    indiceY = 0;
}

Bala::~Bala()
{
    // No hay recursos dinámicos para liberar
}

void Bala::dibujar(BufferedGraphics^ buffer, Bitmap^ bmp)
{
    Rectangle srcRect = Rectangle(0, 0, bmp->Width, bmp->Height);
    Rectangle destRect = Rectangle(x, y, static_cast<int>(ancho *4), static_cast<int>(alto*4));
    buffer->Graphics->DrawImage(bmp, destRect, srcRect, GraphicsUnit::Pixel);
}

void Bala::mover(BufferedGraphics^ buffer, Bitmap^ bmp)
{
    x += dx;
    y += dy;
    dibujar(buffer, bmp);
}
