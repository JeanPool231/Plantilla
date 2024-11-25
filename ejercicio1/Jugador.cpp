#include "Jugador.h"

Jugador::Jugador(int x, int y) : Entidad(x, y) {
	vidas = 3;
	estadoActual = AnimacionJugador::QUIETO;
	indiceFrame = 0;
	dx = dy = 0;
	ancho = 272 / 4;
	alto = 288 / 4;
	escala = 1;
	direccion = Direccion::NINGUNA;
	ultimaDireccion = Direccion::ABAJO;
	inicializarFrames();
}

Jugador::~Jugador() {

}

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
	direccion = direccionInput;

	if (direccion == Direccion::NINGUNA) {
		estadoActual = AnimacionJugador::QUIETO;
	}
	else {
		estadoActual = AnimacionJugador::MOVIENDOSE;
		ultimaDireccion = direccion;
	}

	switch (direccion) {
	case Direccion::NINGUNA:
		dx = 0;
		dy = 0;
		break;
	case Direccion::ARRIBA:
		dx = 0;
		dy = -10;
		break;
	case Direccion::ABAJO:
		dx = 0;
		dy = 10;
		break;
	case Direccion::IZQUIERDA:
		dx = -10;
		dy = 0;
		break;
	case Direccion::DERECHA:
		dx = 10;
		dy = 0;
		break;
	}

	x += dx;
	y += dy;

	if (x < 0) x = 0;
	if (y < 0) y = 0;
	if (x + (ancho * escala) > anchoForm) x = anchoForm - (ancho * escala);
	if (y + (alto * escala) > altoForm) y = altoForm - (alto * escala);

	actualizarAnimacion();

	dibujar(g, bmp);
}


void Jugador::actualizarAnimacion() {
	if (estadoActual == AnimacionJugador::MOVIENDOSE) {
		indiceFrame++;
		if (indiceFrame >= 4) {
			indiceFrame = 0;
		}
	}
	else {
		indiceFrame = 0;
	}
}

void Jugador::dibujar(Graphics^ g, Bitmap^ bmp) {
	int frameX = 0, frameY = 0;

	const std::vector<Frame>* framesActuales = nullptr;

	if (estadoActual == AnimacionJugador::QUIETO) {
		switch (ultimaDireccion) {
		case Direccion::ABAJO:
			framesActuales = &framesAbajo;
			break;
		case Direccion::IZQUIERDA:
			framesActuales = &framesIzquierda;
			break;
		case Direccion::DERECHA:
			framesActuales = &framesDerecha;
			break;
		case Direccion::ARRIBA:
			framesActuales = &framesArriba;
			break;
		default:
			framesActuales = &framesAbajo;
			break;
		}
		frameX = (*framesActuales)[0].indiceX;
		frameY = (*framesActuales)[0].indiceY;
	}
	else {
		switch (direccion) {
		case Direccion::ABAJO:
			framesActuales = &framesAbajo;
			break;
		case Direccion::IZQUIERDA:
			framesActuales = &framesIzquierda;
			break;
		case Direccion::DERECHA:
			framesActuales = &framesDerecha;
			break;
		case Direccion::ARRIBA:
			framesActuales = &framesArriba;
			break;
		default:
			framesActuales = &framesAbajo;
			break;
		}
		frameX = (*framesActuales)[indiceFrame].indiceX;
		frameY = (*framesActuales)[indiceFrame].indiceY;
	}

	Rectangle origen(frameX * ancho, frameY * alto, ancho, alto);
	Rectangle destino(x, y, (ancho * escala), (alto * escala));

	g->DrawImage(bmp, destino, origen, GraphicsUnit::Pixel);
}