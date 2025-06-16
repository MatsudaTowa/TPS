//=============================================
//
//���e�B�N��[reticle.h]
//Author Matsuda Towa
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
	/**
	 * @brief �R���X�g���N�^
	 */
	CReticle();
	/**
	 * @brief �f�X�g���N�^
	 */
	~CReticle();
	/**
	 * @brief ������
	 * @return ����������
	 */
	HRESULT Init();
	/**
	 * @brief �I��
	 */
	void Uninit();
	/**
	 * @brief �X�V
	 */
	void Update();

	/**
	 * @brief �ʒu���
	 * @param [in]�ʒu
	 */
	inline void SetPos(D3DXVECTOR3 pos)
	{
		m_ReticlePos = pos;
	}

	/**
	 * @brief �T�C�Y�ݒ�
	 * @param [in]�T�C�Y
	 */
	inline void SetSize(D3DXVECTOR3 size)
	{
		m_ReticleSize = size;
	}

	/**
	 * @brief �F�ݒ�
	 * @param [in]�F
	 */
	inline void SetCol(D3DXCOLOR col)
	{
		m_ReticleCol = col;
	}

	/**
	 * @brief �ʒu�擾
	 * @return �ʒu
	 */
	inline D3DXVECTOR3& GetReticlePos()
	{
		return m_ReticlePos;
	}

	/**
	 * @brief �T�C�Y�擾
	 * @return �T�C�Y
	 */
	inline D3DXVECTOR3& GetReticleSize()
	{
		return m_ReticleSize;
	}

	/**
	 * @brief �F�擾
	 * @return �F
	 */
	inline D3DXCOLOR& GetReticleCol()
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