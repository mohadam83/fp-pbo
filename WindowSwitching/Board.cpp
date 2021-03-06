#include "Board.h"
#include <wx/filename.h>
#include <wx/stdpaths.h>
BEGIN_EVENT_TABLE(Board, wxPanel)
EVT_PAINT(Board::OnPaint)
END_EVENT_TABLE()

Board::Board(SwitchFrame * parent) :
	wxPanel(parent, wxID_ANY, wxDefaultPosition,
		wxDefaultSize, wxBORDER_NONE), parentFrame(parent)
{
	timer = new wxTimer(this, 1);
	
	isFallingFinished = false;
	isStarted = false;
	isPaused = false;
	numLinesRemoved = 0;
	curX = 0;
	curY = 0;

	ClearBoard();
	this->SetBackgroundColour(wxColour(*wxBLACK));
	Connect(wxEVT_PAINT, wxPaintEventHandler(Board::OnPaint));
	Connect(wxEVT_KEY_DOWN, wxKeyEventHandler(Board::OnKeyDown));
	Connect(wxEVT_TIMER, wxCommandEventHandler(Board::OnTimer));
	
	/*wxImageHandler	*jpegLoader = new	wxJPEGHandler();
	wxImage::AddHandler(jpegLoader);
	//this->LoadBackground();*/
}

void Board::Start()
{
	if (isPaused)
		return;

	isStarted = true;
	isFallingFinished = false;
	numLinesRemoved = 0;
	ClearBoard();

	NewPiece();
	timer->Start(waktu);
}

void Board::Pause()
{
	if (!isStarted)
		return;
	isPaused = !isPaused;
	if (isPaused) {
		timer->Stop();

	}
	else {
		timer->Start(waktu);
	}
	Refresh();
}

void Board::OnPaint(wxPaintEvent& event)
{
	wxPaintDC dc(this);

	//dc.DrawBitmap(*this->backgroundGame, wxPoint(0, 0), true);

	wxSize size = GetClientSize();
	int boardTop = size.GetHeight() - BoardHeight * SquareHeight();


	for (int i = 0; i < BoardHeight; ++i) {
		for (int j = 0; j < BoardWidth; ++j) {
			Tetrominoes shape = ShapeAt(j, BoardHeight - i - 1);
			if (shape != NoShape)
				DrawSquare(dc, 0 + j * SquareWidth(),
					boardTop + i * SquareHeight(), shape);
		}
	}

	if (curPiece.GetShape() != NoShape) {
		for (int i = 0; i < 5; ++i) {
			int x = curX + curPiece.x(i);
			int y = curY - curPiece.y(i);
			DrawSquare(dc, 0 + x * SquareWidth(),
				boardTop + (BoardHeight - y - 1) * SquareHeight(),
				curPiece.GetShape());
		}
	}
	dc.SetBrush(*wxWHITE_BRUSH);
	dc.SetPen(wxPen(*wxRED, 4, wxPENSTYLE_SOLID));
	dc.DrawRectangle(wxPoint(180, 0), wxSize(115, 35));

	wxString x;
	x << "Skor : ";
	x << numLinesRemoved;
	wxFont font(20, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false);
	dc.SetFont(font);
	dc.SetTextForeground(wxColour(221, 34, 34));
	dc.DrawText(x, wxPoint(190, 0));

	dc.SetBrush(*wxWHITE_BRUSH);
	dc.SetPen(wxPen(*wxRED, 4, wxPENSTYLE_SOLID));
	dc.DrawRectangle(wxPoint(0, 0), wxSize(115, 35));

	wxString y;
	y << "Level : ";
	y << tingkat;
	wxFont fonts(20, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false);
	dc.SetFont(fonts);
	dc.SetTextForeground(wxColour(221, 34, 34));
	dc.DrawText(y, wxPoint(5, 0));

	dc.SetPen(wxNullPen);
}

void Board::OnKeyDown(wxKeyEvent& event)
{
	if (!isStarted || curPiece.GetShape() == NoShape) {
		event.Skip();
		return;
	}

	int keycode = event.GetKeyCode();

	if (keycode == 'p' || keycode == 'P') {
		Pause();
		return;
	}

	if (isPaused)
		return;

	switch (keycode) {
	case WXK_LEFT:
		TryMove(curPiece, curX - 1, curY);
		break;
	case WXK_RIGHT:
		TryMove(curPiece, curX + 1, curY);
		break;
	case WXK_DOWN:
		TryMove(curPiece.RotateRight(), curX, curY);
		break;
	case WXK_UP:
		TryMove(curPiece.RotateLeft(), curX, curY);
		break;
	case WXK_SPACE:
		DropDown();
		break;
	case 'd':
		OneLineDown();
		break;
	case 'D':
		OneLineDown();
		break;
	default:
		event.Skip();
	}

}

void Board::OnTimer(wxCommandEvent& event)
{
	if (isFallingFinished) {
		isFallingFinished = false;
		NewPiece();
	}
	else {
		OneLineDown();
	}
}

void Board::ClearBoard()
{
	for (int i = 0; i < BoardHeight * BoardWidth; ++i)
		board[i] = NoShape;
}

void Board::DropDown()
{
	int newY = curY;
	while (newY > 0) {
		if (!TryMove(curPiece, curX, newY - 1))
			break;
		--newY;
	}
	PieceDropped();
}

void Board::OneLineDown()
{
	if (!TryMove(curPiece, curX, curY - 1))
		PieceDropped();
}

void Board::PieceDropped()
{
	for (int i = 0; i < 5; ++i) {
		int x = curX + curPiece.x(i);
		int y = curY - curPiece.y(i);
		ShapeAt(x, y) = curPiece.GetShape();
	}

	RemoveFullLines();

	if (!isFallingFinished)
		NewPiece();
}

void Board::RemoveFullLines()
{
	int numFullLines = 0;

	for (int i = BoardHeight - 1; i >= 0; --i) {
		bool lineIsFull = true;

		for (int j = 0; j < BoardWidth; ++j) {
			if (ShapeAt(j, i) == NoShape) {
				lineIsFull = false;
				break;
			}
		}

		if (lineIsFull) {
			++numFullLines;
			for (int k = i; k < BoardHeight - 1; ++k) {
				for (int j = 0; j < BoardWidth; ++j)
					ShapeAt(j, k) = ShapeAt(j, k + 1);
			}
		}
	}
	if (numFullLines >= 3) {
		++numFullLines;
		for (int k = 0; k < BoardHeight - 1; ++k) {
			for (int j = 0; j < BoardWidth; ++j)
				ShapeAt(j, k) = ShapeAt(j, k + 1);
		}
	}
	if (numFullLines == 2) {
		int tegak = rand() % BoardWidth;
		for (int k = 0; k < BoardHeight; ++k) {
			ShapeAt(tegak, k) = NoShape;
		}
	}
	if (numFullLines > 0) {
		numLinesRemoved += numFullLines;
		temp = tingkat;
		if (numLinesRemoved >= level) {
			level += next_level;
			tingkat = numLinesRemoved / 6;
			if (temp != tingkat) {
				waktu = waktu * 4 / 5;
			}		
			timer->Start(waktu);
		}
		
		isFallingFinished = true;
		curPiece.SetShape(NoShape);
		Refresh();
	}
}

void Board::NewPiece()
{
	curPiece.SetRandomShape();
	curX = BoardWidth / 2 + 1;
	curY = BoardHeight - 1 + curPiece.MinY();

	if (!TryMove(curPiece, curX, curY)) {
		curPiece.SetShape(NoShape);
		timer->Stop();
		isStarted = false;
		wxMessageBox(wxT("=====> GAME OVER <====="), wxT("Game Over"));
		ClearBoard();
	}
}

bool Board::TryMove(const Shape& newPiece, int newX, int newY)
{
	for (int i = 0; i < 5; ++i) {
		int x = newX + newPiece.x(i);
		int y = newY - newPiece.y(i);
		if (x < 0 || x >= BoardWidth || y < 0 || y >= BoardHeight)
			return false;
		if (ShapeAt(x, y) != NoShape)
			return false;
	}

	curPiece = newPiece;
	curX = newX;
	curY = newY;
	Refresh();
	return true;
}

void Board::DrawSquare(wxPaintDC& dc, int x, int y, Tetrominoes shape)
{
	static wxColour colors[] = { wxColour(0, 0, 0), wxColour(204, 102, 102),
			 wxColour(102, 204, 102), wxColour(102, 102, 204),
			 wxColour(204, 204, 102), wxColour(204, 102, 204),
			 wxColour(102, 204, 204), wxColour(218, 170, 0),
			 wxColour(102, 204, 102), wxColour(102, 102, 204),
			 wxColour(204, 204, 102), wxColour(204, 102, 204),
			 wxColour(102, 204, 204), wxColour(218, 170, 0), } ;

	static wxColour light[] = { wxColour(0, 0, 0), wxColour(248, 159, 171),
			 wxColour(121, 252, 121), wxColour(121, 121, 252),
			 wxColour(252, 252, 121), wxColour(252, 121, 252),
			 wxColour(121, 252, 252), wxColour(252, 198, 0),
			 wxColour(121, 252, 121), wxColour(121, 121, 252),
			 wxColour(252, 252, 121), wxColour(252, 121, 252),
			 wxColour(121, 252, 252), wxColour(252, 198, 0), };

	static wxColour dark[] = { wxColour(0, 0, 0), wxColour(128, 59, 59),
			 wxColour(59, 128, 59), wxColour(59, 59, 128),
			 wxColour(128, 128, 59), wxColour(128, 59, 128),
			 wxColour(59, 128, 128), wxColour(128, 98, 0),
			 wxColour(59, 128, 59), wxColour(59, 59, 128),
			 wxColour(128, 128, 59), wxColour(128, 59, 128),
			 wxColour(59, 128, 128), wxColour(128, 98, 0), };


	wxPen pen(light[int(shape)]);
	pen.SetCap(wxCAP_PROJECTING);
	dc.SetPen(pen);

	dc.DrawLine(x, y + SquareHeight() - 1, x, y);
	dc.DrawLine(x, y, x + SquareWidth() - 1, y);

	wxPen darkpen(dark[int(shape)]);
	darkpen.SetCap(wxCAP_PROJECTING);
	dc.SetPen(darkpen);

	dc.DrawLine(x + 1, y + SquareHeight() - 1,
		x + SquareWidth() - 1, y + SquareHeight() - 1);
	dc.DrawLine(x + SquareWidth() - 1,
		y + SquareHeight() - 1, x + SquareWidth() - 1, y + 1);

	dc.SetPen(*wxTRANSPARENT_PEN);
	dc.SetBrush(wxBrush(colors[int(shape)]));
	dc.DrawRectangle(x + 1, y + 1, SquareWidth() - 2,
		SquareHeight() - 2);
}

/*void Board::LoadBackground()
{
	//jika	menggunakan	relative	path
	//letakkan	file	potato.jpg	pada	folder	Debug
	wxStandardPaths	&stdPaths = wxStandardPaths::Get();
	wxString	fileLocation = stdPaths.GetExecutablePath();
	fileLocation = wxFileName(fileLocation).GetPath() + wxT("\\gambar1.jpg");
	wxMessageOutputDebug().Printf("Relative	path of	image is at	%s", fileLocation);
	//wxImage	image(fileLocation,	wxBITMAP_TYPE_JPEG);
	wxImage	image(wxT("D:\\MY BIG FAMILY\\gambar1.jpg"), wxBITMAP_TYPE_JPEG);
	backgroundGame = new wxBitmap(image);
}*/
