#pragma once
#include "Entidad.h"
#include <vector>

enum class AnimacionJugador {
    QUIETO, MOVIENDOSE
};

class Jugador : public Entidad {
private:
    int vidas, ancho, alto, dx, dy, velocidad;
    double escala;

    AnimacionJugador estadoActual;
    Direccion direccion;
    std::vector<Frame> framesQuieto;
    std::vector<Frame> framesArriba;
    std::vector<Frame> framesAbajo;
    std::vector<Frame> framesDerecha;
    std::vector<Frame> framesIzquierda;
    int indiceFrame;
    Direccion ultimaDireccion;

    void inicializarFrames();
    void actualizarAnimacion();
    void calcularMovimiento(Direccion direccionInput);
    void limitarMovimiento(int anchoForm, int altoForm);
    const std::vector<Frame>* obtenerFramesActuales() const;
    void calcularFrame(int& frameX, int& frameY, const std::vector<Frame>* framesActuales) const;

public:
    Jugador(int x, int y);
    ~Jugador();

    void mostrar(Graphics^ g, Bitmap^ bmp) override;
    void mover(Direccion direccion, int anchoForm, int altoForm, Graphics^ g, Bitmap^ bmp);
    void dibujar(Graphics^ g, Bitmap^ bmp);

    int getVidas() const { return vidas; }
    void setVidas(int vidas) { this->vidas = vidas; }

    int getAncho() const { return ancho; }
    void setAncho(int ancho) { this->ancho = ancho; }

    int getAlto() const { return alto; }
    void setAlto(int alto) { this->alto = alto; }

    int getDx() const { return dx; }
    void setDx(int dx) { this->dx = dx; }

    int getDy() const { return dy; }
    void setDy(int dy) { this->dy = dy; }

    int getVelocidad() const { return velocidad; }
    void setVelocidad(int velocidad) { this->velocidad = velocidad; }
};