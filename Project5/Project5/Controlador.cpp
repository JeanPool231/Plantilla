#include "Controlador.h"

Controlador::Controlador()
{
    militar = new Militar(100, 100);
    score = 0;
    numEnemiesEliminated = 0;
}

Controlador::~Controlador()
{
    delete militar;
    for (auto bala : balas)
        delete bala;
    for (auto enemigo : enemigos)
        delete enemigo;
}

void Controlador::agregarBala()
{
    Bala* bala = new Bala(militar->getX() + militar->getAncho() / 2, militar->getY() + militar->getAlto() / 2);
    balas.push_back(bala);
}

void Controlador::agregarEnemigo(int clientWidth, int clientHeight)
{
    int y = rand() % (clientHeight - 50); // Ajustar según el tamaño del enemigo
    Enemigo* enemigo = new Enemigo(clientWidth - 50, y);
    enemigos.push_back(enemigo);
}

void Controlador::moverTodo(BufferedGraphics^ buffer, Bitmap^ bmpMilitar, Bitmap^ bmpBala, Bitmap^ bmpEnemigo, int clientWidth, int clientHeight)
{
    // Mover y dibujar militar
    militar->mover(buffer, bmpMilitar);

    // Mover y dibujar balas
    for (int i = 0; i < balas.size(); )
    {
        balas[i]->mover(buffer, bmpBala);

        if (balas[i]->getX() > clientWidth)
        {
            delete balas[i];
            balas.erase(balas.begin() + i);
        }
        else
        {
            i++;
        }
    }

    // Mover y dibujar enemigos
    for (int i = 0; i < enemigos.size(); )
    {
        enemigos[i]->mover(buffer, bmpEnemigo);

        if (enemigos[i]->getX() + enemigos[i]->getAncho() < 0)
        {
            delete enemigos[i];
            enemigos.erase(enemigos.begin() + i);
        }
        else
        {
            i++;
        }
    }

    // Comprobar colisiones
    for (int i = 0; i < balas.size(); )
    {
        bool balaEliminada = false;
        for (int j = 0; j < enemigos.size(); )
        {
            Rectangle rectBala(balas[i]->getX(), balas[i]->getY(), balas[i]->getAncho(), balas[i]->getAlto());
            Rectangle rectEnemigo(enemigos[j]->getX(), enemigos[j]->getY(), enemigos[j]->getAncho(), enemigos[j]->getAlto());

            if (rectBala.IntersectsWith(rectEnemigo))
            {
                delete balas[i];
                balas.erase(balas.begin() + i);
                balaEliminada = true;

                delete enemigos[j];
                enemigos.erase(enemigos.begin() + j);

                score += 2;
                numEnemiesEliminated++;

                break;
            }
            else
            {
                j++;
            }
        }

        if (!balaEliminada)
        {
            i++;
        }
    }
}
