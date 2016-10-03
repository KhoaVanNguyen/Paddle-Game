#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "Constants.h"
#include <string>
using namespace std;
class GUI
{
	
public:

	// Fonts
	ID3DXFont *font;
	HRESULT fontResult;
	RECT rectText;
	string message;
	void DrawLabel(string, RECT, DWORD);
	bool Init();
	GUI();
	~GUI();
};

