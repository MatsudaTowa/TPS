//=============================================
//
//�E�F�[�u���Ƃ̌���[wave_result.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _WAVE_RESULT_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _WAVE_RESULT_H_
#include "main.h"
#include "block.h"
#include "enemy.h"
#include"wave.h"
#include "wave_score.h"
#include"wave_result_screen.h"

//=============================================
//  �E�F�[�u���U���g�N���X��`
//=============================================
class CWave_Result:public CWave
{
public:

	CWave_Result();
	~CWave_Result() override;
	HRESULT Init() override;
	void Uninit() override ;
	void Update() override;
	void SetNextWave(CWave::WAVE wave);
	void LoadScore(const char* pFileName);

	void Create(CWave::WAVE wave, char* pFileName)
	{
		SetNextWave(wave);
	}
private:
	int m_nScore;
	CWave_Result_Screen* m_pScreen;
};

#endif

