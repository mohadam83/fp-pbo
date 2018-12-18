#include "PlayingButton.h"



PlayingButton::PlayingButton()
{
}

PlayingButton::PlayingButton(wxPanel * ortu)
{
	this->ortu = ortu;
	this->LoadTombol();
}

PlayingButton::~PlayingButton()
{
}
void PlayingButton::LoadTombol()
{
	fileLocation = wxFileName(fileLocation).GetPath() + wxT("\\..\\asset\\play1.png");
	wxImage	image(fileLocation, wxBITMAP_TYPE_PNG);

	this->tombolGambar = new wxBitmap(image);

	//	wxBitmapButton* boardButton = new wxBitmapButton(this, 1001, wxBitmap(wxT("play1.png"), wxBITMAP_TYPE_PNG),
		//	wxPoint(95, 156));
}