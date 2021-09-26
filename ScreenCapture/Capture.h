#pragma once

#include "framework.h"
#include "RGB24.h"

class Capture
{
public:
	Capture();
	~Capture();

public:
	void createCapBuf(int xSize, int ySize);
	void destroyCapBuf();

	void capDesk();
	RGB24 getColor(int x, int y) const;
	void paintCap(HDC hdc, int x, int y) const;

	int getCapX() const;
	int getCapY() const;
	void setCapX(int x);
	void setCapY(int y);

	int getCapXSize() const;
	int getCapYSize() const;

private:
	HBITMAP createDIBBuf(int xSize, int ySize);

private:
	HDC m_hCapDC;
	HBITMAP m_hCapBmpPrev;
	LPBYTE m_capBmpTopLeft;
	int m_capX;
	int m_capY;
	int m_capXSize;
	int m_capYSize;
};


inline int Capture::getCapX() const
{
	return m_capX;
}
inline int Capture::getCapY() const
{
	return m_capY;
}
inline void Capture::setCapX(int x)
{
	m_capX = x;
}
inline void Capture::setCapY(int y)
{
	m_capY = y;
}
inline int Capture::getCapXSize() const
{
	return m_capXSize;
}
inline int Capture::getCapYSize() const
{
	return m_capYSize;
}
