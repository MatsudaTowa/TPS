//=============================================
//
//�X���[�N����[tactical_somoke.h]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "smoke.h"

#ifndef _TACTICAL_SMOKE_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _TACTICAL_SMOKE_H_

class CTacticalSmoke : public CSmoke
{
public:
	CTacticalSmoke(int nPriority = SMOKE_PRIORITY);
	~CTacticalSmoke()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
private:
	static constexpr float MOVE_X_MAX = 1.5f; //�X���[�N�̈ړ��ʂ̍ő�l_X
	static constexpr float MOVE_X_MIN = -1.5f; //�X���[�N�̈ړ��ʂ̍ŏ��l_X

	static constexpr float MOVE_Y_MAX = 0.4f; //�X���[�N�̈ړ��ʂ̍ő�l_Y
	static constexpr float MOVE_Y_MIN = 0.0f; //�X���[�N�̈ړ��ʂ̍ŏ��l_Y

	static constexpr float MOVE_Z_MAX = 0.1f; //�X���[�N�̈ړ��ʂ̍ő�l_Z
	static constexpr float MOVE_Z_MIN = 0.0f; //�X���[�N�̈ړ��ʂ̍ŏ��l_Z

	static constexpr float X_DECREASE = 0.01f; //X�̈ړ��ʌ����萔

	static const D3DXVECTOR3 SIZE; //�X���[�N�̃T�C�Y

	static const D3DXCOLOR COLOR;
};

#endif