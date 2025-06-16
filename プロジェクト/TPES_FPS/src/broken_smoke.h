//=============================================
//
//�u���b�N���琶������X���[�N����[broken_somoke.h]
//Author Matsuda Towa
//
//=============================================
#include "main.h"
#include "smoke.h"

#ifndef _BROKEN_SMOKE_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _BROKEN_SMOKE_H_

//=============================================
//�u���b�N���琶������X���[�N�N���X
//=============================================
class CBrokenSmoke : public CSmoke
{
public:
	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CBrokenSmoke(int nPriority = SMOKE_PRIORITY);
	/**
	 * @brief �f�X�g���N�^
	 */
	~CBrokenSmoke()override;
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
private:
	static constexpr float MOVE_X_MAX = 0.3f; //�X���[�N�̈ړ��ʂ̍ő�l_X
	static constexpr float MOVE_X_MIN = -0.3f; //�X���[�N�̈ړ��ʂ̍ŏ��l_X

	static constexpr float MOVE_Y_MAX = 0.7f; //�X���[�N�̈ړ��ʂ̍ő�l_Y
	static constexpr float MOVE_Y_MIN = 0.1f; //�X���[�N�̈ړ��ʂ̍ŏ��l_Y

	static constexpr float MOVE_Z_MAX = 0.1f; //�X���[�N�̈ړ��ʂ̍ő�l_Z
	static constexpr float MOVE_Z_MIN = 0.0f; //�X���[�N�̈ړ��ʂ̍ŏ��l_Z

	static const D3DXVECTOR3 SIZE;	//�X���[�N�̃T�C�Y

	static const D3DXCOLOR COLOR;	//�J���[
};

#endif