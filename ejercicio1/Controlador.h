#pragma once
#include "Jugador.h"

class Controlador {
private:
    Jugador* jugador;

public:
    Controlador();
    ~Controlador();

    void inicializar(int anchoForm, int altoForm);
    void actualizar(Direccion direccion, int anchoForm, int altoForm, Graphics^ g, Bitmap^ jugadorBmp);
    void dibujar(Graphics^ g, Bitmap^ jugadorBmp);
};
