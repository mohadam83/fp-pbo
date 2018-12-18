#include "Tombol.h"
#pragma once

class DirectionButton :
	public Tombol
{
public:
	DirectionButton();
	
	~DirectionButton();
	DirectionButton(wxPanel *ortu);
	virtual void LoadTombol();
};

