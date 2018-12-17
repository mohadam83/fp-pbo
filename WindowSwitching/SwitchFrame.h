#pragma once
#include "wx/wx.h"
#include <wx/menu.h>
class MainPanel;
class Board;
class DirectionPanel;
class SwitchFrame : public wxFrame {
private:
	wxBoxSizer* boxSizer;
	MainPanel* mainPanel;
	Board* board;
	DirectionPanel* directionPanel;
	
	void fitWindowSize();
public:
	SwitchFrame(const wxString &title);
	void InitComponents();
	void ShowMainPanel();
	void ShowBoard();
	void ShowDirectionPanel();
	void OnQuit(wxCommandEvent & event);
	void OnHome(wxCommandEvent & event);

	wxMenuBar *menubar;
	wxMenu *file;

	wxMenuItem *quit;
	wxMenuItem *home;
};