#pragma once
#include "wx\wx.h"
#include "SwitchFrame.h"
class DirectionPanel : public wxPanel
{
public:
	DirectionPanel(SwitchFrame* parent);
	~DirectionPanel();
	void OnBackButtonClick(wxCommandEvent& event);

	void OnPaint(wxPaintEvent	&event);
private:
	SwitchFrame *parentFrame;
	DECLARE_EVENT_TABLE()

	wxBitmap *petunjuk = nullptr;

	void LoadPetunjuk();
};