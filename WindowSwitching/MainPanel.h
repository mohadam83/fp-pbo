#pragma once
#include "wx\wx.h"
#include "SwitchFrame.h"
#include "Tombol.h"
#include "PlayingButton.h"
#include "DirectionButton.h"
#include "ScoreButton.h"
class MainPanel : public wxPanel
{
public:
	MainPanel(SwitchFrame* parent);
	~MainPanel();

	void OnBoardButtonClick(wxCommandEvent& event);
	void OnScore(wxCommandEvent& event);
	void OnDirectionButtonClick(wxCommandEvent& event);

	void OnPaint(wxPaintEvent &event);

private:
	SwitchFrame *parentFrame;
	DECLARE_EVENT_TABLE()
	wxBitmap *potatoBitmap = nullptr;

	void LoadPotatoBitmap();
	Tombol *playButton;
	Tombol *petunjukButton;
	Tombol *scoreButton;
};