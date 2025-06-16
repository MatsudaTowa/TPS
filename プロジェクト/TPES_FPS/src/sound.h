//=============================================
//
//�T�E���h[sound.h]
//Author Matsuda Towa
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
	enum SOUND_LABEL
	{
		SOUND_LABEL_BGM_TITLE = 0,		// BGM0
		SOUND_LABEL_BGM_GAME,		// BGM1
		SOUND_LABEL_SE_HIT,		// HitSE
		SOUND_LABEL_SE_SHOT,		// ShotSE
		SOUND_LABEL_SE_TACKLE,		// �^�b�N��SE
		SOUND_LABEL_SE_BREAK,		// ����SE
		SOUND_LABEL_SE_BLINK,		// ����SE
		SOUND_LABEL_SE_SMOKE,		// �X���[�NSE
		SOUND_LABEL_MAX
	};

	//*****************************************************************************
	// �T�E���h���̍\���̒�`
	//*****************************************************************************
	struct SOUNDINFO
	{
		const char* pFilename;	// �t�@�C����
		int nCntLoop;			// ���[�v�J�E���g
		float fVolume;
	};

	static const SOUNDINFO m_aSoundInfo[SOUND_LABEL_MAX];
	/**
	 * @brief �R���X�g���N�^
	 */
	CSound();
	/**
	 * @brief �f�X�g���N�^
	 */
	~CSound();
	/**
	 * @brief ������
	 * @param [in]�n���h�������h
	 * @return ����������
	 */
	HRESULT InitSound(HWND hWnd);
	/**
	 * @brief �I��
	 */
	void UninitSound(void);
	/**
	 * @brief �Đ�
	 * @param [in]�T�E���h���x��
	 * @return ����������
	 */
	HRESULT PlaySound(SOUND_LABEL label);
	/**
	 * @brief ����̃T�E���h���~�߂�
	 * @param [in]�T�E���h���x��
	 */
	void StopSound(SOUND_LABEL label);
	/**
	 * @brief �S�ẴT�E���h���~�߂�
	 */
	void StopSound(void);
private:
	IXAudio2* m_pXAudio2 = NULL;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice* m_pMasteringVoice = NULL;			// �}�X�^�[�{�C�X
	IXAudio2SourceVoice* m_apSourceVoice[SOUND_LABEL_MAX] = {};	// �\�[�X�{�C�X
	BYTE* m_apDataAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^�T�C�Y

	/**
	 * @brief �`�����N�̃`�F�b�N
	 * @param [in]�t�@�C��
	 * @param [in]�t�H�[�}�b�g
	 * @param [in]�`�����N�̃T�C�Y�|�C���^
	 * @param [in]�`�����N�̏��ʒu�|�C���^
	 * @return ����������
	 */
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD* pChunkSize, DWORD* pChunkDataPosition);
	/**
	 * @brief �`�����N�f�[�^�ǂݍ���
	 * @param [in]�t�@�C��
	 * @param [in]�o�b�t�@
	 * @param [in]�o�b�t�@�T�C�Y
	 * @param [in]�o�b�t�@�w��ʒu
	 * @return 
	 */
	HRESULT ReadChunkData(HANDLE hFile, void* pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
};
#endif