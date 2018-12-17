#include "MainPanel.h"
#include <wx/menu.h>
#include <wx/stdpaths.h>
#include <wx/filename.h>

BEGIN_EVENT_TABLE(MainPanel, wxPanel)
EVT_BUTTON(1001, MainPanel::OnBoardButtonClick)
EVT_BUTTON(1002, MainPanel::OnDirectionButtonClick)
EVT_BUTTON(1003, MainPanel::OnScore)
EVT_PAINT(MainPanel::OnPaint)
END_EVENT_TABLE()
MainPanel::MainPanel(SwitchFrame * parent) :
	wxPanel(parent, wxID_ANY), parentFrame(parent)
{
	this->SetBackgroundColour(wxColour(*wxWHITE));
	//load	JPEGHandler	untuk	membaca	file	JPEG.
	wxImageHandler	*jpegLoader = new	wxJPEGHandler();
	wxImage::AddHandler(jpegLoader);
	wxImage::AddHandler(new wxPNGHandler);
	//load	image
	this->LoadPotatoBitmap();
	wxBitmapButton* boardButton = new wxBitmapButton(this, 1001, wxBitmap(wxT("play1.png"), wxBITMAP_TYPE_PNG),
		wxPoint(95, 156));
	wxBitmapButton* directionButton = new wxBitmapButton(this, 1002, wxBitmap(wxT("direction.png"), wxBITMAP_TYPE_PNG),
		wxPoint(60, 250));
	wxBitmapButton* Skor = new wxBitmapButton(this, 1003, wxBitmap(wxT("highscores1.png"), wxBITMAP_TYPE_PNG),
		wxPoint(60, 287));
}
MainPanel::~MainPanel()
{
	delete	potatoBitmap;
}
void MainPanel::OnBoardButtonClick(wxCommandEvent & event)
{
	parentFrame->ShowBoard();
}
void MainPanel::OnScore(wxCommandEvent & event)
{
	wxMessageBox(wxT("Nilai Tertinggi : "), wxT("High Score"), wxOK);
}
void MainPanel::OnDirectionButtonClick(wxCommandEvent & event)
{
	parentFrame->ShowDirectionPanel();
}

void MainPanel::OnPaint(wxPaintEvent & event)
{
	wxPaintDC	pdc(this);
	if (potatoBitmap != nullptr)
	{
		pdc.DrawBitmap(*potatoBitmap, wxPoint(0, 0), true);
	}
}

void MainPanel::LoadPotatoBitmap()
{
	//jika	menggunakan	relative	path
	//letakkan	file	potato.jpg	pada	folder	Debug
	wxStandardPaths	&stdPaths = wxStandardPaths::Get();
	wxString	fileLocation = stdPaths.GetExecutablePath();
	fileLocation = wxFileName(fileLocation).GetPath() + wxT("\\gambar1.jpg");
	wxMessageOutputDebug().Printf("Relative	path of	image is at	%s", fileLocation);
	//wxImage	image(fileLocation,	wxBITMAP_TYPE_JPEG);
	//jika	menggunakan	absolute	path
	//sesuaikan	path	dimana	lokasi	file	potato.jpg	berada
	wxImage	image(wxT("D:\\MY BIG FAMILY\\gambar1.jpg"), wxBITMAP_TYPE_JPEG);
	potatoBitmap = new	wxBitmap(image);
}
