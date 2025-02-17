//=============================================
//
//�X���[�N����[broken_somoke.h]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "smoke.h"

#ifndef _BROKEN_SMOKE_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _BROKEN_SMOKE_H_

class CBrokenSmoke : public CSmoke
{
public:
	CBrokenSmoke(int nPriority = SMOKE_PRIORITY);
	~CBrokenSmoke()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
private:
	static constexpr float MOVE_X_MAX = 0.3f; //�X���[�N�̈ړ��ʂ̍ő�l_X
	static constexpr float MOVE_X_MIN = -0.3f; //�X���[�N�̈ړ��ʂ̍ŏ��l_X

	static constexpr float MOVE_Y_MAX = 0.7f; //�X���[�N�̈ړ��ʂ̍ő�l_Y
	static constexpr float MOVE_Y_MIN = 0.1f; //�X���[�N�̈ړ��ʂ̍ŏ��l_Y

	static constexpr float MOVE_Z_MAX = 0.1f; //�X���[�N�̈ړ��ʂ̍ő�l_Z
	static constexpr float MOVE_Z_MIN = 0.0f; //�X���[�N�̈ړ��ʂ̍ŏ��l_Z

	static const D3DXVECTOR3 SIZE; //�X���[�N�̃T�C�Y

	static const D3DXCOLOR COLOR;
};

#endif