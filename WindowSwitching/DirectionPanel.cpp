#include "DirectionPanel.h"
#include <wx/stdpaths.h>
#include <wx/filename.h>
BEGIN_EVENT_TABLE(DirectionPanel, wxPanel)
//EVT_BUTTON(1001, DirectionPanel::OnBackButtonClick)
EVT_PAINT(DirectionPanel::OnPaint)
END_EVENT_TABLE()
DirectionPanel::DirectionPanel(SwitchFrame * parent) :
	wxPanel(parent, wxID_ANY), parentFrame(parent)
{
	this->SetBackgroundColour(wxColour(*wxWHITE));
	wxImage::AddHandler(new wxPNGHandler);
	wxImage::AddHandler(new wxJPEGHandler);
	//wxBitmapButton* backButton = new wxBitmapButton(this, 1001, wxBitmap(wxT("back.jpg"), wxBITMAP_TYPE_JPEG),
	//	wxPoint(120, 400));
	//load	image
	this->LoadPetunjuk();
}
DirectionPanel::~DirectionPanel()
{
	delete petunjuk;
}
/*void DirectionPanel::OnBackButtonClick(wxCommandEvent & event)
{
	parentFrame->ShowMainPanel();
}*/

void DirectionPanel::OnPaint(wxPaintEvent & event)
{
	wxPaintDC	pdc(this);
	if (petunjuk != nullptr)
	{
		pdc.DrawBitmap(*petunjuk, wxPoint(0, 0), true);
	}
}

void DirectionPanel::LoadPetunjuk()
{
	//jika	menggunakan	relative	path
	//letakkan	file	potato.jpg	pada	folder	Debug
	wxStandardPaths	&stdPaths = wxStandardPaths::Get();
	wxString	fileLocation = stdPaths.GetExecutablePath();
	fileLocation = wxFileName(fileLocation).GetPath() +
		wxT("\\petunjuk11.png");
	wxMessageOutputDebug().Printf("Relative	path of	image is at	%s",
		fileLocation);
	//wxImage	image(fileLocation,	wxBITMAP_TYPE_PNG);
	//jika	menggunakan	absolute	path
	//sesuaikan	path	dimana	lokasi	file	potato.jpg	berada
	wxImage	image(wxT("D:\\MY BIG FAMILY\\petunjuk11.png"),
		wxBITMAP_TYPE_PNG);
	petunjuk = new	wxBitmap(image);
}
