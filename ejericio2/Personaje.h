#pragma once
using namespace System::Drawing;
#include<iostream>
class Personaje
{
public:
	Personaje() {
		x = rand() % 1200;
		y = rand() % 600;
		tamanio = 50;
		color = rand() % 2;
		col = color == 1 ? 1 : 2;
		fil = 0;
		if (rand() % 2 == 1) dx = -5;
		else dx = 5;
		if (rand() % 2 == 1) dy = -5;
		else dy = 5;
		tocado = false;
		total_conquitados = 0;
		finalizado = false;
	}
	~Personaje() {}
	void dibujar(Graphics^ g, Bitmap^ img) {
		int ancho = img->Width / 6;
		int alto = img->Height / 5;
		Rectangle frame = Rectangle(col * ancho, alto * fil, ancho, alto);
		Rectangle zoom = Rectangle(x, y, tamanio, tamanio);
		g->DrawImage(img, zoom, frame, GraphicsUnit::Pixel);
		if (tocado) {
			g->FillRectangle(Brushes::Yellow, x, y, tamanio, 10);
		}

		if (finalizado) {
			Font^ fuente = gcnew Font("Arial", 12);
			g->DrawString("" + total_conquitados, fuente, Brushes::Red, x, y + tamanio);
		}

	}
	void mover(Graphics^ g) {
		fil++;
		if (fil > 4) fil = 0;
		if (x<0 || x + tamanio>g->VisibleClipBounds.Width) {
			dx = -dx;
		}
		if (y<0 || y + tamanio>g->VisibleClipBounds.Height) {
			dy = -dy;
		}
		x += dx;
		y += dy;
	}
	void juegoFin() {
		finalizado = true;
	}
	void setColor(int val) {
		this->color = val;
		col = color == 1 ? 1 : 2;
	}
	void aumentarTamanio() {
		tamanio = tamanio + 10;
	}
	void setTocado() {
		tocado = true;
	}
	bool getTocado() {
		return tocado;
	}
	Rectangle mascara() {
		return Rectangle(x, y, tamanio, tamanio);
	}
	int getColor() {
		return color;
	}
	void aumentarConquistados() {
		total_conquitados++;
	}
private:
	int x, y;
	int dx, dy;
	int color;
	int tamanio;
	bool tocado;
	int fil, col;
	int total_conquitados;
	bool finalizado;
};
