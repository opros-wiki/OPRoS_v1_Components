#pragma once

extern unsigned char *ReadBmp256 (const char *fileName, int &width, int &height, unsigned char palette[256][4]);
extern int WriteBmp256 (const char *fileName, int width, int height, unsigned char *image, unsigned char palette[256][4]);
extern void FreeImage (unsigned char *image);
extern void DrawBmp256 (HDC hDC, int _offsetX, int _offsetY, int imageWidth, int imageHeight, float imageScale, unsigned char *image, unsigned char palette[256][4]);