#pragma once
#include "Entidad.h"

class EntidadMovible : public Entidad {
protected:
    int dx, dy;
    int velocidad;
    Direccion direccion;

public:
    EntidadMovible(int x, int y, int velocidad);
    virtual ~EntidadMovible();

    void actualizarPosicion();

    // Getters y Setters
    void setDx(int dx);
    int getDx() const;
    void setDy(int dy);
    int getDy() const;
    void setVelocidad(int velocidad);
    int getVelocidad() const;
    void setDireccion(Direccion direccion);
    Direccion getDireccion() const;

    // Método virtual para movimiento (puede ser implementado por las clases derivadas)
    virtual void mover() = 0;
};
