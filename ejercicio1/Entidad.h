#pragma once

using namespace System::Drawing;

enum class Direccion
{
    NINGUNA,
    ARRIBA,
    ABAJO,
    DERECHA,
    IZQUIERDA
};

struct Frame
{
    int indiceX;
    int indiceY;
};

class Entidad {
protected:
    int x, y;
    int getX() const { return x; }
    int getY() const { return y; }
    void setX(int nuevoX) { x = nuevoX; }
    void setY(int nuevoY) { y = nuevoY; }

public:
    Entidad(int x, int y) : x(x), y(y) {}

    virtual ~Entidad() {}

    virtual void mostrar(Graphics^ g, Bitmap^ bmp) = 0;
    int getX()  { return x; }
    int getY()  { return y; }

};
