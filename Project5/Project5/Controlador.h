// Controlador.h

#pragma once
#include "Jugador.h"
#include "Proyectil.h"
#include "Enemigo.h" // Incluir la clase Enemigo
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace System::Drawing;


class Controlador {
private:
    Jugador* jugador;
    vector<Proyectil*> proyectiles;
    vector<Enemigo*> enemigos;

    int contadorSpawn;
    int intervaloSpawn;
    bool invulnerable;
    int invulnerableTimer;
    const int tiempoInvulnerable = 120;
    int contadorEnemigosMuertos = 0;

    bool juegoTerminado;

public:
    // Constructor
    Controlador() : invulnerable(false), invulnerableTimer(0), juegoTerminado(false) {
        jugador = new Jugador(100, 100); // Posición inicial del jugador

        // Inicializar enemigos con posiciones aleatorias
        srand(static_cast<unsigned>(time(NULL)));
        for (int i = 0; i < 5; ++i) { // Crear 5 enemigos iniciales
            int ex = rand() % 700 + 50; // Asumiendo un límite de ancho de 800
            int ey = rand() % 500 + 50; // Asumiendo un límite de alto de 600
            enemigos.push_back(new Enemigo(ex, ey));
        }

        // Inicializar variables de spawn
        contadorSpawn = 0;
        intervaloSpawn = 180; // Por ejemplo, cada ~3 segundos si el timer es de 60 FPS
    }

    // Destructor
    ~Controlador() {
        delete jugador;
        for (auto proyectil : proyectiles) {
            delete proyectil;
        }
        for (auto enemigo : enemigos) {
            delete enemigo;
        }
    }

    // Método para obtener el jugador
    Jugador* getJugador() const {
        return jugador;
    }

    int getContadorEnemigosMuertos() const {
        return contadorEnemigosMuertos;
    }

    // Método para verificar si el juego ha terminado
    bool estaTerminado() const {
        return juegoTerminado;
    }

    // Método para mover al jugador
    void moverJugador(Direcciones direccion, Graphics^ g, Bitmap^ bmp, int limiteAncho, int limiteAlto) {
        jugador->direccion = direccion;
        jugador->mover(g, bmp, limiteAncho, limiteAlto);
    }

    // Método para dibujar al jugador
    void dibujarJugador(Graphics^ g, Bitmap^ bmp) {
        jugador->dibujar(g, bmp);
    }

    // Disparar proyectiles
    void disparar(Bitmap^ bmpProyectil) {
        if (proyectiles.size() < 10) { // Limitar la cantidad de proyectiles en pantalla
            int px = jugador->getX() + (jugador->getRectangulo().Width / 2) - (bmpProyectil->Width / 2);
            int py = jugador->getY() + (jugador->getRectangulo().Height / 2) - (bmpProyectil->Height / 2);
            int dx = 0, dy = 0;

            // Obtener la última dirección del jugador
            Direcciones dir = jugador->getUltimaTecla();

            switch (dir) {
            case Arriba:
                dx = 0; dy = -10;
                py = jugador->getY() - bmpProyectil->Height;
                break;
            case Abajo:
                dx = 0; dy = 10;
                py = jugador->getY() + jugador->getRectangulo().Height;
                break;
            case Izquierda:
                dx = -10; dy = 0;
                px = jugador->getX() - bmpProyectil->Width;
                break;
            case Derecha:
                dx = 10; dy = 0;
                px = jugador->getX() + jugador->getRectangulo().Width;
                break;
            default: // Si no hay última dirección, usamos "Arriba" por defecto
                dx = 0; dy = -10;
                py = jugador->getY() - bmpProyectil->Height;
                break;
            }

            // Crear el proyectil con tamaño basado en el sprite sin modificar
            proyectiles.push_back(new Proyectil(px, py, dx, dy, bmpProyectil->Width, bmpProyectil->Height));
        }
    }

    // Mover proyectiles
    void moverProyectiles(int limiteAncho, int limiteAlto) {
        for (auto it = proyectiles.begin(); it != proyectiles.end();) {
            (*it)->mover();
            if ((*it)->fueraDePantalla(limiteAncho, limiteAlto)) {
                delete (*it);
                it = proyectiles.erase(it);
            }
            else {
                ++it;
            }
        }
    }

    // Dibujar proyectiles
    void dibujarProyectiles(Graphics^ g, Bitmap^ bmpProyectil) {
        for (auto proyectil : proyectiles) {
            proyectil->dibujar(g, bmpProyectil);
        }
    }

    // Gestionar el spawn aleatorio de enemigos
    void gestionarSpawnEnemigos(int limiteAncho, int limiteAlto) {
        contadorSpawn++;
        if (contadorSpawn >= intervaloSpawn) {
            // Spawn un nuevo enemigo en una posición aleatoria
            int ex = rand() % (limiteAncho - 100) + 50; // Evitar spawn muy cerca de los bordes
            int ey = rand() % (limiteAlto - 100) + 50;
            enemigos.push_back(new Enemigo(ex, ey));
            contadorSpawn = 0;

            // Opcional: ajustar el intervalo para incrementar la dificultad
            // intervaloSpawn = max(60, intervaloSpawn - 5); // Disminuye el intervalo hasta un mínimo
        }
    }

    // Mover enemigos (recibe el sprite de enemigo como parámetro)
    void moverEnemigos(Graphics^ g, int limiteAncho, int limiteAlto, Bitmap^ bmpEnemigo) {
        for (auto enemigo : enemigos) {
            enemigo->mover(g, bmpEnemigo, limiteAncho, limiteAlto);
        }
    }

    // Dibujar enemigos (recibe el sprite de enemigo como parámetro)
    void dibujarEnemigos(Graphics^ g, Bitmap^ bmpEnemigo) {
        for (auto enemigo : enemigos) {
            enemigo->dibujar(g, bmpEnemigo);
        }
    }

    // Detectar y manejar colisiones entre proyectiles y enemigos
    void detectarColisionesProyectilesEnemigos() {
        for (auto projIt = proyectiles.begin(); projIt != proyectiles.end();) {
            bool proyectilEliminado = false;
            Rectangle rectProyectil = (*projIt)->getRectangulo();

            for (auto enemIt = enemigos.begin(); enemIt != enemigos.end();) {
                Rectangle rectEnemigo = (*enemIt)->getRectangulo();
                if (rectProyectil.IntersectsWith(rectEnemigo)) {
                    // Colisión detectada: eliminar ambos
                    delete (*enemIt);
                    enemIt = enemigos.erase(enemIt);

                    delete (*projIt);
                    projIt = proyectiles.erase(projIt);
                    proyectilEliminado = true;
                    contadorEnemigosMuertos++;
                    break; // Salir del loop de enemigos, avanzar al siguiente proyectil
                }
                else {
                    ++enemIt;
                }
            }

            if (!proyectilEliminado) {
                ++projIt;
            }
        }
    }

    // Detectar y manejar colisiones entre jugador y enemigos
    void detectarColisionesJugadorEnemigos() {
        if (invulnerable || juegoTerminado) {
            if (invulnerable) {
                invulnerableTimer++;
                if (invulnerableTimer >= tiempoInvulnerable) {
                    invulnerable = false;
                    invulnerableTimer = 0;
                }
            }
            return; // No detectar colisiones mientras es invulnerable o si el juego ya terminó
        }

        Rectangle rectJugador = jugador->getRectangulo();

        for (auto it = enemigos.begin(); it != enemigos.end();) {
            Rectangle rectEnemigo = (*it)->getRectangulo();
            if (rectJugador.IntersectsWith(rectEnemigo)) {
                // Colisión detectada: disminuir vida del jugador
                jugador->disminuirVida();

                // Activar invulnerabilidad
                invulnerable = true;
                invulnerableTimer = 0;

                // Eliminar el enemigo tras la colisión
                delete (*it);
                it = enemigos.erase(it);

                // Verificar si las vidas llegan a 0
                if (jugador->getVidas() <= 0) {
                    juegoTerminado = true;
                    break; // Salir del loop, ya no es necesario verificar más enemigos
                }
            }
            else {
                ++it;
            }
        }
    }

    // Actualizar el estado del juego
    void actualizar(int limiteAncho, int limiteAlto, Bitmap^ bmpEnemigo) {
        if (juegoTerminado) {
            return; // No actualizar más si el juego ya ha terminado
        }

        // Gestionar spawn de enemigos
        gestionarSpawnEnemigos(limiteAncho, limiteAlto);

        // Mover enemigos
        moverEnemigos(nullptr, limiteAncho, limiteAlto, bmpEnemigo);

        // Mover proyectiles
        moverProyectiles(limiteAncho, limiteAlto);

        // Detectar colisiones entre proyectiles y enemigos
        detectarColisionesProyectilesEnemigos();

        // Detectar colisiones entre jugador y enemigos
        detectarColisionesJugadorEnemigos();
    }
};
