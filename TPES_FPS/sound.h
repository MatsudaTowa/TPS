//=============================================
//
//�T�E���h[sound.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _SOUND_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _SOUND_H_
#include "main.h"

class CSound
{
public:
	//*****************************************************************************
	// �T�E���h�ꗗ
	//*****************************************************************************
	typedef enum
	{
		SOUND_LABEL_BGM_TITLE = 0,		// BGM0
		SOUND_LABEL_MAX
	} SOUND_LABEL;

	//*****************************************************************************
	// �T�E���h���̍\���̒�`
	//*****************************************************************************
	typedef struct
	{
		const char* pFilename;	// �t�@�C����
		int nCntLoop;			// ���[�v�J�E���g
		float fVolume;
	} SOUNDINFO;

	static const SOUNDINFO m_aSoundInfo[SOUND_LABEL_MAX];
	CSound();
	~CSound();
	HRESULT InitSound(HWND hWnd);
	void UninitSound(void);
	HRESULT PlaySound(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void StopSound(void);
private:
	IXAudio2* m_pXAudio2 = NULL;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice* m_pMasteringVoice = NULL;			// �}�X�^�[�{�C�X
	IXAudio2SourceVoice* m_apSourceVoice[SOUND_LABEL_MAX] = {};	// �\�[�X�{�C�X
	BYTE* m_apDataAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^�T�C�Y

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD* pChunkSize, DWORD* pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void* pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
};
#endif