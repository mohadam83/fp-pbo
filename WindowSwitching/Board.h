#pragma once
#ifndef BOARD_H
#define BOARD_H
#include "wx\wx.h"
#include <iostream>
#include "Shape.h"
#include "SwitchFrame.h"
class Board : public wxPanel
{
public:
	Board(SwitchFrame* parent);
	void OnPaint(wxPaintEvent &event);
	void Start();
	void Pause();
	void linesRemovedChanged(int numLines);

protected:
	void OnKeyDown(wxKeyEvent& event);
	void OnTimer(wxCommandEvent& event);

private:
	SwitchFrame *parentFrame;

	DECLARE_EVENT_TABLE()
	// Pembatas
	enum { BoardWidth = 13, BoardHeight = 26 };

	Tetrominoes & ShapeAt(int x, int y) { return board[(y * BoardWidth) + x]; }

	int SquareWidth() { return GetClientSize().GetWidth() / BoardWidth; }
	int SquareHeight() { return GetClientSize().GetHeight() / BoardHeight; }
	int level = 6, next_level = 6, tingkat, temp;
	int waktu = 800;
	void ClearBoard();
	void DropDown();
	void OneLineDown();
	void PieceDropped();
	void RemoveFullLines();
	void NewPiece();
	bool TryMove(const Shape& newPiece, int newX, int newY);
	void DrawSquare(wxPaintDC &dc, int x, int y, Tetrominoes shape);

	void LoadBackground();
	wxBitmap *backgroundGame = nullptr;

	wxTimer *timer;
	bool isStarted;
	bool isPaused;
	bool isFallingFinished;
	Shape curPiece;
	int curX;
	int curY;
	int numLinesRemoved;
	Tetrominoes board[BoardWidth * BoardHeight];
};

#endif