#include "Tombol.h"



Tombol::Tombol()
{
}

Tombol::Tombol(wxPanel * alas)
{
}


Tombol::~Tombol()
{
}

void Tombol::SetTombol(int x, int y, int kode)
{
	pos_x = x;
	pos_y = y;
	this->tombol = new wxBitmapButton(this->ortu, kode, *(tombolGambar), wxPoint(this->pos_x, this->pos_y), wxDefaultSize, wxBORDER_NONE);

}
