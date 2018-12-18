#pragma once
#include "Tombol.h"
#include <wx/stdpaths.h>
#include <wx/filename.h>
class PlayingButton : public Tombol
{
public:
	PlayingButton();
	PlayingButton(wxPanel *ortu);
	~PlayingButton();
	virtual void LoadTombol();
};

