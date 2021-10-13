#include "Tiles.h"


using namespace Tmpl8;

Tiles::Tiles(void)
{
}

//tile creation
void Tiles::CopyTo( Surface* a_Dst,Surface* a_Src, int a_X, int a_Y )
{
	Pixel* src = a_Src->GetBuffer()+(a_Y * a_Src->GetPitch() + a_X);
	Pixel* dst = a_Dst->GetBuffer();
	if ((src) && (dst)) 
	{
		int srcwidth = 32;
		int srcheight = 32;

		int srcpitch = a_Src->GetPitch();
		int dstwidth = a_Dst->GetWidth();

		int dstheight = a_Dst->GetHeight();
		int dstpitch = a_Dst->GetPitch();

		for ( int y = 0; y < dstheight; y++ )
		{
			memcpy( dst, src, dstwidth * sizeof(Pixel) );
			dst += dstpitch;
			src += srcpitch;
		}
	}
}

Tiles::Tiles(Surface* tempTile,int x,int y)
{
	tile = tempTile;
	xPos = x;
	yPos = y;
}

Tiles::~Tiles(void)
{
}


