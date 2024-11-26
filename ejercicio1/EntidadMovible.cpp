#include "EntidadMovible.h"

EntidadMovible::EntidadMovible(int x, int y, int velocidad)
    : Entidad(x, y), dx(0), dy(0), velocidad(velocidad), direccion(Direccion::NINGUNA) {}

EntidadMovible::~EntidadMovible() {}

void EntidadMovible::actualizarPosicion() {
    x += dx;
    y += dy;
}

void EntidadMovible::setDx(int dx) {
    this->dx = dx;
}

int EntidadMovible::getDx() const {
    return dx;
}

void EntidadMovible::setDy(int dy) {
    this->dy = dy;
}

int EntidadMovible::getDy() const {
    return dy;
}

void EntidadMovible::setVelocidad(int velocidad) {
    this->velocidad = velocidad;
}

int EntidadMovible::getVelocidad() const {
    return velocidad;
}

void EntidadMovible::setDireccion(Direccion direccion) {
    this->direccion = direccion;
}

Direccion EntidadMovible::getDireccion() const {
    return direccion;
}
