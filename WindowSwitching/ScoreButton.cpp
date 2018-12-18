#include "ScoreButton.h"



ScoreButton::ScoreButton()
{
}


ScoreButton::~ScoreButton()
{
}

ScoreButton::ScoreButton(wxPanel * ortu)
{
	this->ortu = ortu;
	this->LoadTombol();
}

void ScoreButton::LoadTombol()
{
	fileLocation = wxFileName(fileLocation).GetPath() + wxT("\\..\\asset\\highscores1.png");
	wxImage	image(fileLocation, wxBITMAP_TYPE_PNG);

	this->tombolGambar = new wxBitmap(image);
}
