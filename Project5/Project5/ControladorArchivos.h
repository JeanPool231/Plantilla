#pragma once

#include <fstream>
#include <iostream>
#include <string>

class ControladorArchivos {
private:
    int tiempoJuego;

public:
    ControladorArchivos() : tiempoJuego(0) {}

    void leerTiempo(const std::string& rutaArchivo) {
        std::ifstream archivo(rutaArchivo, std::ios::in);

        if (archivo.is_open()) {
            archivo >> tiempoJuego; // Leer el primer valor como tiempo
            if (tiempoJuego <= 0) {
                std::cerr << "Error: Tiempo inválido en el archivo. Se usará el valor predeterminado de 120 segundos.\n";
                tiempoJuego = 120; // Valor predeterminado
            }
            archivo.close();
        }
        else {
            std::cerr << "Error: No se pudo abrir el archivo '" << rutaArchivo << "'. Se usará el valor predeterminado de 120 segundos.\n";
            tiempoJuego = 120; // Valor predeterminado
        }
    }

    // Getter para el tiempo del juego
    int getTiempoJuego() const {
        return tiempoJuego;
    }
};
