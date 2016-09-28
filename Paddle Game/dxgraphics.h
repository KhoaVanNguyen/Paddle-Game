// Beginning Game Programming, Second Edition
// dxgraphics.h - Direct3D framework header file


#ifndef _DXGRAPHICS_H
#define _DXGRAPHICS_H 1
#include "Constants.h"

//function prototypes
int Init_Direct3D(HWND, int, int, int);
LPDIRECT3DSURFACE9 LoadSurface(char *, D3DCOLOR);
LPDIRECT3DTEXTURE9 LoadTexture(char *, D3DCOLOR);



#endif

