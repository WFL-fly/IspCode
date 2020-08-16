#pragma once
#ifndef BMP_TYPEDEF_H
#define BMP_TYPEDEF_H

//tagBmpFileHeader
typedef struct {
	unsigned char bfType[2];
	unsigned int  bfSize;
	unsigned short bfReserved1;
	unsigned short bfReserved2;
	unsigned int  bfOffBits;
}BmpFileHeader;
//tagBitMapInfo
typedef struct {
	unsigned int biSize;
	int			  biWidth;
	int		      biHeight;
	unsigned short biPlanes;
	unsigned short biBitCount;
	unsigned int biCompression;
	unsigned int biSizeImage;
	int          biXPelsPerMeter;
	int          biYPelsPerMeter;
	unsigned int biClrUsed;
	unsigned int biClrImportant;
}BitMapInfo;
//tagBitMapInfo
typedef struct {
	unsigned char rgbBlue;
	unsigned char rgbGreen;
	unsigned char rgbRed;
	unsigned char rgbReserved;
}ColorPalette;
typedef struct {
	unsigned int wight;
	unsigned int height;
	unsigned int channels;
	unsigned char* imagedata;
}ClImage;
typedef struct {
	unsigned int wight;
	unsigned int height;
	unsigned int channels;
	unsigned char* imagedata;
}ColorBmp;
typedef struct {
	BmpFileHeader mBmpFileHeader;
	BitMapInfo    mBitMapInfo;
	ColorPalette  mColorPalette[256];
	unsigned char* pImageData;
}Bmp;

#endif