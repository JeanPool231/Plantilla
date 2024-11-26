#pragma once
#include "Personaje.h"
#include <vector>
using namespace std;
class Juego
{
public:
	Juego(int s, int t) {
		iniciarJuego();
		contador = 0;
		tiempo = s;
		c = 0;
		this->t = t;
	}
	~Juego() {}
	void agregarPersonaje() {
		personajes.push_back(new Personaje());
	}
	void iniciarJuego() {
		int n = rand() % 7 + 6;
		int i = 0;
		while (i < n) {
			agregarPersonaje();
			i++;
		}
	}
	void dibujarPersonajes(Graphics^ g, Bitmap^ img) {
		for (int i = 0; i < personajes.size(); i++) {
			personajes[i]->dibujar(g, img);
		}
	}
	void moverPersonajes(Graphics^ g) {
		for (int i = 0; i < personajes.size(); i++) {
			personajes[i]->mover(g);
		}
	}
	void irAgregandoPersonajes() {
		contador++;
		if (contador >= tiempo * 10) {
			agregarPersonaje();
			contador = 0;
		}
	}
	void verColisiones() {
		for (int i = 0; i < personajes.size(); i++) {
			for (int j = 0; j < personajes.size(); j++) {
				if (i != j) {
					if (personajes[i]->mascara().IntersectsWith(personajes[j]->mascara())) {
						if (personajes[i]->getColor() == 1 && !personajes[j]->getTocado() && personajes[j]->getColor() == 0) {
							personajes[i]->setColor(0);
							personajes[j]->aumentarTamanio();
							personajes[i]->setTocado();
							personajes[j]->aumentarConquistados();
						}
						else if (personajes[i]->getColor() == 0 && !personajes[i]->getTocado() && personajes[j]->getColor() == 1) {
							personajes[j]->setColor(0);
							personajes[i]->aumentarTamanio();
							personajes[j]->setTocado();
							personajes[i]->aumentarConquistados();
						}
					}
				}
			}
		}
	}
	bool juegoActivo() {
		c++;
		return c < t * 10 * 60;
	}
	void animarJuego(Graphics^ g, Bitmap^ img) {
		dibujarPersonajes(g, img);
		moverPersonajes(g);
		verColisiones();
		irAgregandoPersonajes();
	}
	int getTiempo() {
		return c;
	}
	int getTotal() {
		return t;
	}
	void mostrarPuntajes() {
		for (int i = 0; i < personajes.size(); i++) {
			personajes[i]->juegoFin();
		}
	}
private:
	vector<Personaje*>personajes;
	int tiempo;
	int contador;
	int c;
	int t;
};
