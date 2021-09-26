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
	* ���̃N���X�𐶐�������܂��͂��̊֐����Ă�ł�������
	* �����Ȃ��Ƒ��̊֐��͌Ă�ł������N���܂���
	* 
	* ��ʃL���v�`�����邽�߂̃������̈���m�ۂ��܂�
	* �N���X�𐶐��������_�ł͗̈�͊m�ۂ���Ă��܂���
	* �̈�͂P�����m�ۂł��܂���
	* ���Ɋm�ۂ��Ă���̈悪����΂��̊֐����Ă񂾎��_�ŕK���������܂�
	* 
	* �����ɓn���l���O�ȉ��ł�������A������������Ȃ����炢�傫����
	* �̈�͊m�ۂ���܂���
	* ���̏ꍇ���A���Ɋm�ۂ��Ă���̈悪����Ή������܂�
	* 
	* @param xSize �L���v�`�������ʃT�C�Y(����)
	* @param ySize �L���v�`�������ʃT�C�Y(�c��)
	* @return true:�������̈�̊m�ۂɐ���, false:���s
	*/
	bool createCapBuf(int xSize, int ySize);

	/*
	* ��ʃL���v�`�����I������(�܂��͈ꎞ�I�Ɏg��Ȃ�)�Ƃ��͂��̊֐����Ă�ł�������
	* �f�X�g���N�^�ł����̊֐��͌Ă΂�܂�
	* 
	* ��ʃL���v�`�����邽�߂̃������̈��������܂�
	*/
	void destroyCapBuf();

	/*
	* �f�X�N�g�b�v��ʂ��m�ۂ����������̈�ɃR�s�[���܂�
	*/
	void capDesk();

	/*
	* �m�ۂ����������̈��̍��W(x, y)��RGB���擾���܂�
	* 
	* @param x �F���擾������X���W
	* @param y �F���擾������Y���W
	* @return ���W(x, y)�̐F
	*/
	RGB24 getColor(int x, int y) const;

	/*
	* �m�ۂ����������̈�̓��e���f�o�C�X�R���e�L�X�g�ɓ]�����܂�
	* WM_PAINT�ł̃n���h���������ɓn���Η̈�̓��e���E�B���h�E�ɕ`�悵�܂�
	* 
	* @param hdc �ړI�̃f�o�C�X�R���e�L�X�g�̃n���h��
	* @param x   �]����̋�`�̍����X���W
	* @param y   �]����̋�`�̍����Y���W
	*/
	void paintCap(HDC hdc, int x, int y) const;

	/*
	* @return �L���v�`����`�͈͂̍����X���W
	*/
	int getCapX() const;
	/*
	* @return �L���v�`����`�͈͂̍����Y���W
	*/
	int getCapY() const;
	/*
	* @param x �ݒ肷��L���v�`����`�͈͂̍����X���W
	*/
	void setCapX(int x);
	/*
	* @param y �ݒ肷��L���v�`����`�͈͂̍����Y���W
	*/
	void setCapY(int y);

	/*
	* @return �L���v�`����`�͈͂̉���
	*/
	int getCapXSize() const;
	/*
	* @return �L���v�`����`�͈͂̏c��
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
