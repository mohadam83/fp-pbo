#pragma once
#include "wx/wx.h"
#include <wx/stdpaths.h>
#include <wx/filename.h>

class Tombol
{
protected:
	wxBitmapButton* tombol;
	wxBitmap *tombolGambar;
	int pos_x, pos_y;
	wxPanel *ortu;
	wxStandardPaths &stdPaths = wxStandardPaths::Get();
	wxString fileLocation = stdPaths.GetExecutablePath();
	virtual void LoadTombol() = 0;

public:
	Tombol();
	Tombol(wxPanel *alas);
	~Tombol();
	void SetTombol(int x, int y, int kode);
};

