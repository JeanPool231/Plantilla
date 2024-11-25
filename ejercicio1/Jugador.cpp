#include "Jugador.h"

Jugador::Jugador(int x, int y) : Entidad(x, y) {
    vidas = 3;
    estadoActual = AnimacionJugador::QUIETO;
    indiceFrame = 0;
    dx = dy = 0;
    ancho = 272 / 4;
    alto = 288 / 4;
    escala = 1;
    velocidad = 10;
    direccion = Direccion::NINGUNA;
    ultimaDireccion = Direccion::ABAJO;
    inicializarFrames();
}

Jugador::~Jugador() {}

void Jugador::inicializarFrames() {
    framesAbajo = { {0, 0}, {1, 0}, {2, 0}, {3, 0} };
    framesIzquierda = { {0, 1}, {1, 1}, {2, 1}, {3, 1} };
    framesDerecha = { {0, 2}, {1, 2}, {2, 2}, {3, 2} };
    framesArriba = { {0, 3}, {1, 3}, {2, 3}, {3, 3} };
}

void Jugador::mostrar(Graphics^ g, Bitmap^ bmp) {
    dibujar(g, bmp);
}

void Jugador::mover(Direccion direccionInput, int anchoForm, int altoForm, Graphics^ g, Bitmap^ bmp) {
    calcularMovimiento(direccionInput);
    limitarMovimiento(anchoForm, altoForm);
    actualizarAnimacion();
    dibujar(g, bmp);
}

void Jugador::calcularMovimiento(Direccion direccionInput) {
    direccion = direccionInput;

    if (direccion == Direccion::NINGUNA) {
        estadoActual = AnimacionJugador::QUIETO;
        dx = dy = 0;
    }
    else {
        estadoActual = AnimacionJugador::MOVIENDOSE;
        ultimaDireccion = direccion;

        switch (direccion) {
        case Direccion::ARRIBA:
            dx = 0;
            dy = -velocidad;
            break;
        case Direccion::ABAJO:
            dx = 0;
            dy = velocidad;
            break;
        case Direccion::IZQUIERDA:
            dx = -velocidad;
            dy = 0;
            break;
        case Direccion::DERECHA:
            dx = velocidad;
            dy = 0;
            break;
        default:
            dx = dy = 0;
            break;
        }
    }

    x += dx;
    y += dy;
}

void Jugador::limitarMovimiento(int anchoForm, int altoForm) {
    if (x < 0) x = 0;
    if (y < 0) y = 0;
    if (x + (ancho * escala) > anchoForm) x = anchoForm - (ancho * escala);
    if (y + (alto * escala) > altoForm) y = altoForm - (alto * escala);
}

void Jugador::actualizarAnimacion() {
    if (estadoActual == AnimacionJugador::MOVIENDOSE) {
        indiceFrame = (indiceFrame + 1) % 4;
    }
    else {
        indiceFrame = 0;
    }
}

const std::vector<Frame>* Jugador::obtenerFramesActuales() const {
    switch (estadoActual == AnimacionJugador::QUIETO ? ultimaDireccion : direccion) {
    case Direccion::ARRIBA:
        return &framesArriba;
    case Direccion::ABAJO:
        return &framesAbajo;
    case Direccion::IZQUIERDA:
        return &framesIzquierda;
    case Direccion::DERECHA:
        return &framesDerecha;
    default:
        return &framesAbajo;
    }
}

void Jugador::calcularFrame(int& frameX, int& frameY, const std::vector<Frame>* framesActuales) const {
    frameX = (*framesActuales)[estadoActual == AnimacionJugador::QUIETO ? 0 : indiceFrame].indiceX;
    frameY = (*framesActuales)[estadoActual == AnimacionJugador::QUIETO ? 0 : indiceFrame].indiceY;
}

void Jugador::dibujar(Graphics^ g, Bitmap^ bmp) {
    int frameX, frameY;
    const std::vector<Frame>* framesActuales = obtenerFramesActuales();

    calcularFrame(frameX, frameY, framesActuales);

    Rectangle origen(frameX * ancho, frameY * alto, ancho, alto);
    Rectangle destino(x, y, ancho * escala, alto * escala);

    g->DrawImage(bmp, destino, origen, GraphicsUnit::Pixel);
}
