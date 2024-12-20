//=============================================
//
//���e�B�N��[reticle.h]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "billboard.h"
#include "crosshair.h"
#include"centerdot.h"
#include "hitmaker.h"

#ifndef _RETICLE_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _RETICLE_H_

//=============================================
//���e�B�N���N���X
//=============================================
class CReticle
{
public:
	CReticle();
	~CReticle();
	HRESULT Init();
	void Uninit();
	void Update();

	void SetPos(D3DXVECTOR3 pos)
	{
		m_ReticlePos = pos;
	}

	void SetSize(D3DXVECTOR3 size)
	{
		m_ReticleSize = size;
	}

	void SetCol(D3DXCOLOR col)
	{
		m_ReticleCol = col;
	}

	D3DXVECTOR3& GetReticlePos()
	{
		return m_ReticlePos;
	}

	D3DXVECTOR3& GetReticleSize()
	{
		return m_ReticleSize;
	}

	D3DXCOLOR& GetReticleCol()
	{
		return m_ReticleCol;
	}

	CCrossHair* m_pCrosshair;
	CCenterDot* m_pCenterDot;
	CHitMaker* m_pHitMaker;
private:

	D3DXVECTOR3 m_ReticlePos;
	D3DXVECTOR3 m_ReticleSize;
	D3DXCOLOR m_ReticleCol;
};

#endif