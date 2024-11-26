#pragma once
#include "Entidad.h"

enum Direccion { NINGUNA, IZQUIERDA, DERECHA, ARRIBA, ABAJO };

class Militar :
    public Entidad
{
private:
    Direccion ultimaTecla;
public:
    Direccion direccion;
    Militar(int x, int y);
    ~Militar();
    void dibujar(BufferedGraphics^ buffer, Bitmap^ bmp) override;
    void mover(BufferedGraphics^ buffer, Bitmap^ bmp) override;
    int getX() { return x; }
    int getY() { return y; }
    int getAncho() { return static_cast<int>(ancho * 0.5); } // Asegúrate de usar el mismo factor de escala que en dibujar
    int getAlto() { return static_cast<int>(alto * 0.5); }
};

