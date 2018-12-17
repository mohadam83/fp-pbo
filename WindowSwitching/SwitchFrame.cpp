#include "SwitchFrame.h"
#include "MainPanel.h"
#include "DirectionPanel.h"
#include "Board.h"
SwitchFrame::SwitchFrame(const wxString & title)
	: wxFrame(NULL, wxID_ANY, title)
{
	this->InitComponents();
}
void SwitchFrame::fitWindowSize()
{
	this->boxSizer->Fit(this);
	this->boxSizer->SetSizeHints(this);
	this->SetSize(wxSize(310, 500));
	this->Layout();

	menubar = new wxMenuBar;
	file = new wxMenu;

	quit = new wxMenuItem(file, wxID_EXIT, wxT("&Keluar\tCtrl+X"));
	home = new wxMenuItem(file, wxID_DEFAULT, wxT("&Home"));
	file->Append(home);
	file->Append(quit);
	Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED,
		wxCommandEventHandler(SwitchFrame::OnQuit));
	Connect(wxID_DEFAULT, wxEVT_COMMAND_MENU_SELECTED,
		wxCommandEventHandler(SwitchFrame::OnHome));
	menubar->Append(file, wxT("&Menu"));
	SetMenuBar(menubar);
}
void SwitchFrame::InitComponents()
{
	boxSizer = new wxBoxSizer(wxVERTICAL);
	this->mainPanel = new MainPanel(this);
	this->mainPanel->Show(false);
	this->boxSizer->Add(mainPanel, 1, wxEXPAND, 0);
	if (board != nullptr) {
		board->Destroy();
	}
	this->board = new Board(this);
	this->board->Show(false);
	this->boxSizer->Add(board, 1, wxEXPAND, 0);
	this->directionPanel = new DirectionPanel(this);
	this->directionPanel->Show(false);
	this->boxSizer->Add(directionPanel, 1, wxEXPAND, 0);
	SetSizer(boxSizer);
	ShowMainPanel();
}
void SwitchFrame::ShowMainPanel()
{
	this->mainPanel->Show(true);
	this->mainPanel->SetFocus();
	this->board->Show(false);
	this->directionPanel->Show(false);
	fitWindowSize();
}
void SwitchFrame::ShowBoard()
{
	this->mainPanel->Show(false);
	this->board->Show(true);
	//wxStatusBar *sb = CreateStatusBar();
	//sb->SetStatusText(wxT("0"));
	this->board->Start();
	this->board->SetFocus();
	this->directionPanel->Show(false);
	
	fitWindowSize();
}
void SwitchFrame::ShowDirectionPanel()
{
	this->mainPanel->Show(false);
	this->board->Show(false);
	this->directionPanel->Show(true);
	this->directionPanel->SetFocus();
	fitWindowSize();
}

void SwitchFrame::OnQuit(wxCommandEvent & event)
{
	this->Close(true);
}

void SwitchFrame::OnHome(wxCommandEvent & event)
{
	this->ShowMainPanel();
}

