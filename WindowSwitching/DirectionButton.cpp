#include "DirectionButton.h"

DirectionButton::DirectionButton()
{
}


DirectionButton::~DirectionButton()
{
}

DirectionButton::DirectionButton(wxPanel * ortu)
{
	this->ortu = ortu;
	this->LoadTombol();
}

void DirectionButton::LoadTombol()
{
	fileLocation = wxFileName(fileLocation).GetPath() + wxT("\\..\\asset\\direction.png");
	wxImage	image(fileLocation, wxBITMAP_TYPE_PNG);

	this->tombolGambar = new wxBitmap(image);
}
