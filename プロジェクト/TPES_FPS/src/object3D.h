//=============================================
//
//3D�I�u�W�F�N�g[object3D.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _OBJECT3D_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _OBJECT3D_H_
#include "main.h"
#include "object.h"

//=============================================
//3D�I�u�W�F�N�g�N���X
//=============================================
class CObject3D : public CObject
{
public:
	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CObject3D(int nPriority);
	/**
	 * @brief �f�X�g���N�^
	 */
	~CObject3D()override;
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
	 * @brief �F�ݒ�
	 * @param [in]�F
	 */
	inline void SetColor(D3DXCOLOR col)
	{
		m_col = col;
	}

	/**
	 * @brief �ʒu�̐ݒ�
	 * @param [in]�ʒu
	 */
	inline void SetPos(D3DXVECTOR3 pos)
	{
		m_pos = pos;
	}

	/**
	 * @brief �����̐ݒ�
	 * @param [in]����
	 */
	inline void SetRot(D3DXVECTOR3 rot)
	{
		m_rot = rot;
	}

	/**
	 * @brief �T�C�Y�ݒ�
	 * @param [in]�T�C�Y
	 */
	inline void SetSize(D3DXVECTOR3 size)
	{
		m_size = size;
	}

	/**
	 * @brief �e�N�X�`�����W���
	 * @param [in]�e�N�X�`�����W
	 */
	inline void SetTexPos(D3DXVECTOR2 tex)
	{
		m_tex_pos = tex;
	}

	/**
	 * @brief ���[���h�}�g���b�N�X���
	 * @param [in]���[���h�}�g���b�N�X
	 */
	inline void SetMtxWorld(D3DXMATRIX mtxWorld)
	{
		m_mtxWorld = mtxWorld;
	}

	/**
	 * @brief ���_�o�b�t�@���
	 * @param [in]���_�o�b�t�@���
	 */
	inline void SetVtxBuff(LPDIRECT3DVERTEXBUFFER9 vtxBuff)
	{
		m_pVtxBuff = vtxBuff;
	}

	/**
	 * @brief �A�j���[�V�����t���[�����
	 * @param [in]�A�j���[�V�����t���[��
	 */
	inline void SetAnimFrame(int nAnimFrame)
	{
		m_nAnimFrame = nAnimFrame;
	}

	/**
	 * @brief �e�N�X�`���ړ��ʑ��
	 * @param [in]�e�N�X�`���ړ���
	 */
	inline void SetTexMove(D3DXVECTOR2 tex_move)
	{
		m_tex_move = tex_move;
	}


	/**
	 * @brief ���_����
	 * @param [in]�@���x�N�g��
	 */
	void SetVtx(D3DXVECTOR3 nor);

	/**
	 * @brief ���_����
	 * @param [in]�@���x�N�g��
	 * @param [in]����
	 * @param [in]����
	 */
	void SetVtx(D3DXVECTOR3 nor,float fAngle, float fLength);

	/**
	 * @brief ���_����
	 * @param [in]�@���x�N�g��
	 * @param [in]�e�N�X�`�����W
	 * @param [in]�e�N�X�`���ړ���
	 */
	void SetVtxAnim(D3DXVECTOR3 nor,D3DXVECTOR2 tex_pos, D3DXVECTOR2 tex_move);

	/**
	 * @brief �Q�[�W�p���_����
	 * @param [in]��_�ʒu
	 * @param [in]�@���x�N�g��
	 */
	void SetGaugeVtx(D3DXVECTOR3 ReferencePos,D3DXVECTOR3 nor);
	/**
	 * @brief ��_�����p���_����
	 * @param [in]�@���x�N�g��
	 */
	void SetVtx_FootPos(D3DXVECTOR3 nor);

	/**
	 * @brief �F�̎擾
	 * @return �F
	 */
	inline D3DXCOLOR& GetColor()
	{
		return m_col;
	}

	/**
	 * @brief �ʒu�̎擾
	 * @return �ʒu
	 */
	inline D3DXVECTOR3& GetPos()
	{
		return m_pos;
	}

	/**
	 * @brief �����̎擾
	 * @return ����
	 */
	inline D3DXVECTOR3& GetRot()
	{
		return m_rot;
	}

	/**
	 * @brief �T�C�Y�̎擾
	 * @return �T�C�Y
	 */
	inline D3DXVECTOR3& GetSize()
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
	 * @brief ���_�o�b�t�@�擾
	 * @return ���_�o�b�t�@
	 */
	inline LPDIRECT3DVERTEXBUFFER9& GetVtxBuff()
	{
		return m_pVtxBuff;
	}

	/**
	 * @brief �e�N�X�`�����W���擾
	 * @return �e�N�X�`�����
	 */
	inline LPDIRECT3DTEXTURE9& GetTexture()
	{
		return m_pTexture;
	}

	/**
	 * @brief ���[���h�}�g���b�N�X�擾
	 * @return ���[���h�}�g���b�N�X
	 */
	inline D3DXMATRIX& GetMtxWorld()
	{
		return m_mtxWorld;
	}

	/**
	 * @brief �A�j���[�V�����t���[���擾
	 * @return �A�j���[�V�����t���[��
	 */
	inline int GetAnimFrame()
	{
		return m_nAnimFrame;
	}

	/**
	 * @brief �e�N�X�`���ړ��ʎ擾
	 * @return �e�N�X�`���ړ���
	 */
	inline D3DXVECTOR2& GetTexMove()
	{
		return m_tex_move;
	}

private:

	LPDIRECT3DTEXTURE9 m_pTexture; //�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff; //���_�o�b�t�@�ւ̃|�C���^

	D3DXCOLOR m_col; //�F
	D3DXVECTOR3 m_pos; //�ʒu
	D3DXVECTOR3 m_rot; //����
	D3DXVECTOR3 m_size; //�T�C�Y
	D3DXVECTOR2 m_tex_pos; //tex���W

	//�A�j���[�V����
	int m_nAnimFrame; //�A�j���[�V�����t���[��
	int m_nAnimCnt; //�A�j���[�V�����J�E���g
	D3DXVECTOR2 m_tex_move; //tex�ړ���

	D3DXMATRIX m_mtxWorld; //���[���h�}�g���b�N�X
};
#endif