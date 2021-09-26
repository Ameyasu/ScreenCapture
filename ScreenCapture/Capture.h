#pragma once

#include "framework.h"
#include "RGB24.h"

class Capture
{
public:
	Capture();
	~Capture();

public:
	/*
	* このクラスを生成したらまずはこの関数を呼んでください
	* さもないと他の関数は呼んでも何も起きません
	* 
	* 画面キャプチャするためのメモリ領域を確保します
	* クラスを生成した時点では領域は確保されていません
	* 領域は１つしか確保できません
	* 既に確保している領域があればこの関数を呼んだ時点で必ず解放されます
	* 
	* 引数に渡す値が０以下であったり、メモリが足りないくらい大きいと
	* 領域は確保されません
	* この場合も、既に確保している領域があれば解放されます
	* 
	* @param xSize キャプチャする画面サイズ(横幅)
	* @param ySize キャプチャする画面サイズ(縦幅)
	* @return true:メモリ領域の確保に成功, false:失敗
	*/
	bool createCapBuf(int xSize, int ySize);

	/*
	* 画面キャプチャを終了する(または一時的に使わない)ときはこの関数を呼んでください
	* デストラクタでもこの関数は呼ばれます
	* 
	* 画面キャプチャするためのメモリ領域を解放します
	*/
	void destroyCapBuf();

	/*
	* デスクトップ画面を確保したメモリ領域にコピーします
	*/
	void capDesk();

	/*
	* 確保したメモリ領域上の座標(x, y)のRGBを取得します
	* 
	* @param x 色を取得したいX座標
	* @param y 色を取得したいY座標
	* @return 座標(x, y)の色
	*/
	RGB24 getColor(int x, int y) const;

	/*
	* 確保したメモリ領域の内容をデバイスコンテキストに転送します
	* WM_PAINTでのハンドルを引数に渡せば領域の内容をウィンドウに描画します
	* 
	* @param hdc 目的のデバイスコンテキストのハンドル
	* @param x   転送先の矩形の左上のX座標
	* @param y   転送先の矩形の左上のY座標
	*/
	void paintCap(HDC hdc, int x, int y) const;

	/*
	* @return キャプチャ矩形範囲の左上のX座標
	*/
	int getCapX() const;
	/*
	* @return キャプチャ矩形範囲の左上のY座標
	*/
	int getCapY() const;
	/*
	* @param x 設定するキャプチャ矩形範囲の左上のX座標
	*/
	void setCapX(int x);
	/*
	* @param y 設定するキャプチャ矩形範囲の左上のY座標
	*/
	void setCapY(int y);

	/*
	* @return キャプチャ矩形範囲の横幅
	*/
	int getCapXSize() const;
	/*
	* @return キャプチャ矩形範囲の縦幅
	*/
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
