//=============================================
//
//2D�I�u�W�F�N�g[object2D.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _OBJECT2D_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _OBJECT2D_H_
#include "main.h"
#include "object.h"

//=============================================
//2D�I�u�W�F�N�g�N���X
//=============================================
class CObject2D : public CObject
{
public:
	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CObject2D(int nPriority = 3);
	/**
	 * @brief �f�X�g���N�^
	 */
	~CObject2D()override;
	/**
	 * @brief ������
	 * @return ����������
	 */
	HRESULT Init()override;
	/**
	 * @brief �I��
	 */
	void Uninit()override;
	/**
	 * @brief �X�V
	 */
	void Update()override;
	/**
	 * @brief �`��
	 */
	void Draw()override;
	/**
	 * @brief �e�N�X�`���ݒ�
	 * @param [in]�e�N�X�`��
	 */
	void BindTexture(LPDIRECT3DTEXTURE9 pTex);

	/**
	 * @brief �ʒu�̑��
	 * @param [in]�ʒu
	 */
	inline void SetPos(D3DXVECTOR3 pos)
	{
		m_pos = pos;
	}

	/**
	 * @brief �����̑��
	 * @param [in]����
	 */
	inline void SetRot(D3DXVECTOR3 rot)
	{
		m_rot = rot;
	}

	/**
	 * @brief �T�C�Y�̑��
	 * @param [in]�T�C�Y
	 */
	inline void SetSize(D3DXVECTOR2 size)
	{
		m_size = size;
	}

	/**
	 * @brief �e�N�X�`�����W�̑��
	 * @param [in]�e�N�X�`�����W
	 */
	inline void SetTexPos(D3DXVECTOR2 tex)
	{
		m_tex_pos = tex;
	}

	/**
	 * @brief ���_�o�b�t�@�ݒ�
	 * @param [in]���_�o�b�t�@
	 */
	inline void SetVtxBuff(LPDIRECT3DVERTEXBUFFER9 Buff)
	{
		m_pVtxBuff = Buff;
	}

	/**
	 * @brief �F�̑��
	 * @param [in]�F
	 */
	inline void SetColor(D3DXCOLOR col)
	{
		m_col = col;
	}

	/**
	 * @brief ���_����
	 * @param [in]rhw
	 */
	void SetVtx(float rhw);

	/**
	 * @brief ���_����
	 * @param [in]rhw
	 * @param [in]����
	 * @param [in]����
	 */
	void SetVtx(float rhw,float fAngle,float fLength);

	/**
	 * @brief �Q�[�W�p�̒��_����
	 * @param [in]rhw
	 */
	void SetGaugeVtx(float rhw);

	/**
	 * @brief ��_�����̒��_����
	 * @param [in]rhw
	 * @param [in]����
	 * @param [in]����
	 */
	void SetVtx_FootPos(float rhw,float fAngle,float fLength);

	/**
	 * @brief �ʒu�擾
	 * @return �ʒu
	 */
	inline D3DXVECTOR3& GetPos()
	{
		return m_pos;
	}

	/**
	 * @brief �����擾
	 * @return ����
	 */
	inline D3DXVECTOR3& GetRot()
	{
		return m_rot;
	}

	/**
	 * @brief �T�C�Y�擾
	 * @return �T�C�Y
	 */
	inline D3DXVECTOR2& GetSize()
	{
		return m_size;
	}

	/**
	 * @brief �e�N�X�`�����W�擾
	 * @return �e�N�X�`�����W
	 */
	inline D3DXVECTOR2& GetTexPos()
	{
		return m_tex_pos;
	}
	
	/**
	 * @brief �F�̎擾
	 * @return �F
	 */
	inline D3DXCOLOR& GetColor()
	{
		return m_col;
	}

	/**
	 * @brief ���_�o�b�t�@�擾
	 * @return ���_�o�b�t�@
	 */
	inline LPDIRECT3DVERTEXBUFFER9& GetVtxBuff()
	{
		return m_pVtxBuff;
	}


private:

	LPDIRECT3DTEXTURE9 m_pTexture; //�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff; //���_�o�b�t�@�ւ̃|�C���^

	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR2 m_size;
	D3DXVECTOR2 m_tex_pos; //tex���W
	D3DXCOLOR m_col;
};
#endif