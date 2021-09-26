#include "Capture.h"

Capture::Capture()
	: m_hCapDC()
	, m_hCapBmpPrev()
	, m_capBmpTopLeft()
	, m_capX()
	, m_capY()
	, m_capXSize()
	, m_capYSize()
{
}

Capture::~Capture()
{
	destroyCapBuf();
}

bool Capture::createCapBuf(int xSize, int ySize)
{
	destroyCapBuf();

	if (xSize <= 0 || ySize <= 0)
	{
		return false;
	}

	HDC hDeskDC = GetDC(nullptr);
	if (hDeskDC == nullptr)
	{
		return false;
	}

	m_hCapDC = CreateCompatibleDC(hDeskDC);
	if (m_hCapDC == nullptr)
	{
		ReleaseDC(nullptr, hDeskDC);
		return false;
	}

	HBITMAP hBmp = createDIBBuf(xSize, ySize);
	if (hBmp == nullptr)
	{
		DeleteDC(m_hCapDC);
		m_hCapDC = nullptr;
		ReleaseDC(nullptr, hDeskDC);
		return false;
	}

	BITMAP bmp = {};
	GetObject(hBmp, sizeof(BITMAP), &bmp);
	m_capBmpTopLeft = (LPBYTE)bmp.bmBits;

	m_hCapBmpPrev = (HBITMAP)SelectObject(m_hCapDC, hBmp);
	ReleaseDC(nullptr, hDeskDC);
	m_capXSize = xSize;
	m_capYSize = ySize;

	return true;
}

void Capture::destroyCapBuf()
{
	if (m_hCapDC == nullptr)
	{
		return;
	}

	HBITMAP hBmp = (HBITMAP)SelectObject(m_hCapDC, m_hCapBmpPrev);
	DeleteObject(hBmp);
	DeleteDC(m_hCapDC);
	m_hCapDC = nullptr;
	m_hCapBmpPrev = nullptr;
	m_capBmpTopLeft = nullptr;

	m_capX = 0;
	m_capY = 0;
	m_capXSize = 0;
	m_capYSize = 0;
}

void Capture::capDesk()
{
	HDC hDeskDC = GetDC(nullptr);
	BitBlt(m_hCapDC, 0, 0, m_capXSize, m_capYSize, hDeskDC, m_capX, m_capY, SRCCOPY);
	ReleaseDC(nullptr, hDeskDC);
}

RGB24 Capture::getColor(int x, int y) const
{
	if (x < 0 || m_capXSize <= x || y < 0 || m_capYSize <= y)
	{
		return RGB24();
	}

	LPBYTE lp = m_capBmpTopLeft;
	lp += (m_capYSize - y - 1) * ((3 * m_capXSize + 3) / 4) * 4;
	lp += 3 * x;

	return RGB24{lp[2], lp[1], lp[0]};
}

void Capture::paintCap(HDC hdc, int x, int y) const
{
	BitBlt(hdc, x, y, m_capXSize, m_capYSize, m_hCapDC, 0, 0, SRCCOPY);
}

HBITMAP Capture::createDIBBuf(int xSize, int ySize)
{
	LPVOID           lp = {};
	BITMAPINFO       bmi = {};
	BITMAPINFOHEADER bmiHeader = {};

	ZeroMemory(&bmiHeader, sizeof(BITMAPINFOHEADER));
	bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmiHeader.biWidth = xSize;
	bmiHeader.biHeight = ySize;
	bmiHeader.biPlanes = 1;
	bmiHeader.biBitCount = 24;

	bmi.bmiHeader = bmiHeader;

	return CreateDIBSection(nullptr, &bmi, DIB_RGB_COLORS, &lp, nullptr, 0);
}

