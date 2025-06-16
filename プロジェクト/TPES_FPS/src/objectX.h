//=============================================
//
//X�t�@�C���I�u�W�F�N�g[objectX.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _OBJECTX_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _OBJECTX_H_
#include "main.h"
#include "object.h"

//=============================================
//X�t�@�C���I�u�W�F�N�g�N���X
//=============================================
class CObjectX : public CObject
{
public:
	static const int MAX_TEX = 256; //�e�N�X�`���̐�

	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CObjectX(int nPriority);
	/**
	 * @brief �f�X�g���N�^
	 */
	~CObjectX()override;
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
	 * @param [in]�e�N�X�`�����
	 * @param [in]�ԍ�
	 */
	void BindTexture(LPDIRECT3DTEXTURE9 pTex,int Idx);

	/**
	 * @brief X�t�@�C���ݒ�
	 * @param [in]�}�e���A�����
	 * @param [in]�}�e���A����
	 * @param [in]���b�V�����
	 */
	void BindXFile(LPD3DXBUFFER pBuffMat, DWORD dwNumMat, LPD3DXMESH pMesh);

	/**
	 * @brief �X�P�[�����
	 * @param [in]�X�P�[���{��
	 */
	inline void SetScale(D3DXVECTOR3 scale)
	{
		m_scale = scale;
	}

	/**
	 * @brief �ʒu�̑��
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
	 * @brief �ŏ��l���
	 * @param [in]�ŏ��l
	 */
	inline void SetMinPos(D3DXVECTOR3 MinPos)
	{
		m_minpos = MinPos;
	}

	/**
	 * @brief �ő�l���
	 * @param [in]�ő�l
	 */
	inline void SetMaxPos(D3DXVECTOR3 MaxPos)
	{
		m_maxpos = MaxPos;
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
	 * @brief �F�̑��
	 * @param [in]�F
	 */
	inline void SetColor(D3DXCOLOR col)
	{
		m_col = col;
	}

	/**
	 * @brief �X�P�[���̎擾
	 * @return �X�P�[��
	 */
	inline D3DXVECTOR3& GetScale()
	{
		return m_scale;
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
	 * @brief �ŏ��l�擾
	 * @return �ŏ��l
	 */
	D3DXVECTOR3& GetMinPos();

	/**
	 * @brief �ő�l�擾
	 * @return �ő�l
	 */
	D3DXVECTOR3& GetMaxPos();

	/**
	 * @brief ���b�V�����擾
	 * @return ���b�V�����
	 */
	inline LPD3DXMESH& GetpMesh()
	{
		return m_pMesh;
	}

	/**
	 * @brief �}�e���A�����擾
	 * @return �}�e���A�����
	 */
	inline LPD3DXBUFFER& GetpBuffMat()
	{
		return m_pBuffMat;
	}

	/**
	 * @brief �}�e���A�����擾
	 * @return �}�e���A����
	 */
	inline DWORD& GetNumMat()
	{
		return m_dwNumMat;
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
	 * @brief �J���[�擾
	 * @return �J���[
	 */
	inline D3DXCOLOR& GetCol()
	{
		return m_col;
	}

private:

	LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEX]; //�e�N�X�`���ւ̃|�C���^

	D3DXVECTOR3 m_scale;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_minpos; //pos�ŏ��l
	D3DXVECTOR3 m_maxpos; //pos�ő�l

	D3DXMATRIX m_mtxWorld; //���[���h�}�g���b�N�X
	
	LPD3DXMESH m_pMesh; //���b�V�����
	LPD3DXBUFFER m_pBuffMat; //�}�e���A�����
	DWORD m_dwNumMat; //�}�e���A����

	D3DXCOLOR m_col; //�J���[�̒l
};
#endif