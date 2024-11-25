#include "Controlador.h"

Controlador::Controlador() {
    jugador = new Jugador(100, 100); 
}

Controlador::~Controlador() {
    delete jugador; 
}

void Controlador::inicializar(int anchoForm, int altoForm) {
    
}

void Controlador::actualizar(Direccion direccion, int anchoForm, int altoForm, Graphics^ g, Bitmap^ jugadorBmp) {
    if (jugador != nullptr) {
        jugador->mover(direccion, anchoForm, altoForm, g, jugadorBmp);
    }
}

void Controlador::dibujar(Graphics^ g, Bitmap^ jugadorBmp) {
    if (jugadorBmp != nullptr && jugador != nullptr) {
        jugador->mostrar(g, jugadorBmp);
    }
}
