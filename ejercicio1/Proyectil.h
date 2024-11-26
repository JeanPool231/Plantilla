#include "Entidad.h"
#include <vector>

class Proyectil : public Entidad
{
private:
	int alto, ancho, dx, dy, velocidad;
	double escala;

	Direccion direccion;
	std::vector<Frame> frames;
	int indiceFrame;
	
public:
	Proyectil(int x, int y);
	~Proyectil();

	void mostrar(Graphics^ g, Bitmap^ bmp) override;
	void mover(Direccion direccion, int anchoForm, int altoForm, Graphics^ g, Bitmap^ bmp);
	void dibujar(Graphics^ g, Bitmap^ bmp);
};
