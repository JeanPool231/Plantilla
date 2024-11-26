#pragma once
using namespace System::Drawing;

class Entidad
{
protected:
	int x, y;
	int dx, dy;
	double ancho, alto;
	int indiceX, indiceY;
	Entidad();
	~Entidad();
	virtual void dibujar(BufferedGraphics^ buffer, Bitmap^ bmp);
	virtual void mover(BufferedGraphics^ buffer, Bitmap^ bmp);
};

