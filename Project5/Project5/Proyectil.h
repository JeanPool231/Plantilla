#pragma once
using namespace System::Drawing;

class Proyectil {
public:
    Proyectil(int x, int y, int dx, int dy, int ancho, int alto) {
        this->x = x;
        this->y = y;
        this->dx = dx;
        this->dy = dy;
        this->ancho = ancho;
        this->alto = alto;
    }

    ~Proyectil() {}

    Rectangle getRectangulo() {
        return Rectangle(x, y, ancho, alto);
    }

    void mover() {
        x += dx;
        y += dy;
    }

    void dibujar(Graphics^ g, Bitmap^ bmp) {
        g->DrawImage(bmp, x, y, ancho, alto);
    }

    bool fueraDePantalla(int limiteAncho, int limiteAlto) {
        return (x + ancho < 0 || x > limiteAncho || y + alto < 0 || y > limiteAlto);
    }

private:
    // Posición
    int x;
    int y;
    // Velocidad
    int dx;
    int dy;
    // Tamaño
    int ancho;
    int alto;
};
