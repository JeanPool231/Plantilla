#pragma once
#include "Entidad.h"

class Bala : public Entidad
{
public:
    Bala(int x, int y);
    ~Bala();
    void dibujar(BufferedGraphics^ buffer, Bitmap^ bmp) override;
    void mover(BufferedGraphics^ buffer, Bitmap^ bmp) override;
    int getX() { return x; }
    int getY() { return y; }
    int getAncho() { return static_cast<int>(ancho); }
    int getAlto() { return static_cast<int>(alto); }
};
