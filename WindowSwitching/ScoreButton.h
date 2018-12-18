#pragma once
#include "Tombol.h"
#include <wx/stdpaths.h>
#include <wx/filename.h>
class ScoreButton : public Tombol
{
public:
	ScoreButton();
	~ScoreButton();
	ScoreButton(wxPanel *ortu);
	virtual void LoadTombol();
};

