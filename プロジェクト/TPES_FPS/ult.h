//=============================================
//
//�A���e�B���b�g[ult.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _ULT_
#define _ULT_
#include "character_behavior.h"
#include "player.h"
#include "ult_icon.h"
#include "ult_range.h"
#include "ult_camera_effect.h"

class CPlayer;
//=============================================
//�A���e�B���b�g�����X�g���e�W�[
//=============================================
class CUlt
{
public:
	CUlt();
	virtual ~CUlt();
	virtual HRESULT Init();
	virtual void Uninit();
	virtual void Update();
	virtual bool Action(CPlayer* player) = 0;

	//�N�[���^�C�����
	inline void SetCoolTime(int CoolTime)
	{
		m_CoolTime = CoolTime;
	}

	//�N�[���^�C�����
	inline void SetCoolTimeCnt(int CoolTimeCnt)
	{
		m_CoolTimeCnt = CoolTimeCnt;
	}

	inline int& GetCoolTime()
	{
		return m_CoolTime;
	}

	inline int& GetCoolTimeCnt()
	{
		return m_CoolTimeCnt;
	}
protected:
	bool m_isFinish;
private:
	int m_CoolTime;
	int m_CoolTimeCnt;
};

//=============================================
//�~�f�B�A���L�����A���e�B���b�g�����X�g���e�W�[
//=============================================
class CMediumUlt:public CUlt
{
public:
	CMediumUlt();
	~CMediumUlt() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	bool Action(CPlayer* player) override;
private:
	static const int MEDIUM_ULT_COOL_TIME = 900;
	static const float FLYING_HIGHT; //�ǂ��܂Ŕ�Ԃ�
	static const D3DXVECTOR3 SPEED;

	float m_move_y; //y���̈ړ���
	CUltRange* m_pUltRange; //�E���g�̔���
	CUltCameraEffect* m_pUltCameraEffect; //�E���g�̃J�����G�t�F�N�g
};

#endif // !_ULT_
