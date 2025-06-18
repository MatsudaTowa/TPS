//=============================================
//
//�}�l�[�W���[[maneger.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _MANAGER_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _MANAGER_H_
#include "main.h"
#include "input.h"
#include "camera.h"
#include "light.h"
#include "texture.h"
#include "model.h"
#include "scene.h"
#include "fade.h"
#include "sound.h"
#include "colision.h"
#include "useful.h"

//=============================================
//�}�l�[�W���[�N���X
//=============================================
class CManager
{
public:
	static const int NUM_RESULT_FILE = 4;
	static const std::string RESULT_SCORE_FILE[NUM_RESULT_FILE]; //���U���g�̃t�@�C���l�[��

	/**
	 * @brief �R���X�g���N�^
	 */
	CManager();
	/**
	 * @brief �f�X�g���N�^
	 */
	~CManager();
	/**
	 * @brief ������
	 * @param [in]�C���X�^���X
	 * @param [in]�n���h�������h
	 * @param [in]�E�B���h�E�����ł�����
	 * @return ����������
	 */
	HRESULT Init(HINSTANCE hInstance,HWND hWnd,BOOL bWindow);
	/**
	 * @brief �I��
	 */
	void Uninit();
	/**
	 * @brief �X�V
	 */
	void Update();
	/**
	 * @brief �`��
	 */
	void Draw();

	/**
	 * @brief �V�[���ݒ�
	 * @param [in]�V�[��
	 */
	void SetMode(CScene::MODE mode);

	/**
	 * @brief �C���X�^���X����
	 * @return �C���X�^���X
	 */
	static CManager* GetInstance()
	{
		static CManager instance; //�ÓI�C���X�^���X
		return &instance;
	}

	/**
	 * @brief �V�[���擾
	 * @return �V�[���|�C���^
	 */
	CScene* GetScene();

	/**
	 * @brief �����_���[�擾
	 * @return �����_���[�|�C���^
	 */	
	CRenderer*GetRenderer();

	/**
	* @brief �L�[�{�[�h�擾
	* @return �L�[�{�[�h�|�C���^
	*/
	CInputKeyboard* GetKeyboard();

	/**
	* @brief �}�E�X�擾
	* @return �}�E�X�|�C���^
	*/	
	CInputMouse* GetMouse();

	/**
	* @brief �p�b�h�擾
	* @return �p�b�h�|�C���^
	*/
	CInputPad* GetPad();

	/**
	* @brief �J�����擾
	* @return �J�����|�C���^
	*/
	CCamera* GetCamera();

	/**
	* @brief ���C�g�擾
	* @return ���C�g�|�C���^
	*/
	CLight* GetLight();

	/**
	* @brief �e�N�X�`���擾
	* @return �e�N�X�`���|�C���^
	*/
	CTexture* GetTexture();

	/**
	* @brief ���f���擾
	* @return ���f���|�C���^
	*/
	CModel* GetModel();

	/**
	* @brief �T�E���h�擾
	* @return �T�E���h�|�C���^
	*/
	CSound* GetSound();

	/**
	* @brief �t�F�[�h�擾
	* @return �t�F�[�h�|�C���^
	*/
	CFade* GetFade();

	/**
	* @brief �����蔻��擾
	* @return �����蔻��|�C���^
	*/
	CColision* GetColision();

	/**
	* @brief �n���h�������h�擾
	* @return �n���h�������h
	*/
	HWND GetHWnd();
	/**
	* @brief �X�R�A��0�����o��
	* @return �t�@�C���l�[��
	*/
	static void ExportScoreReset(const std::string* pFileName);

private:

	HWND m_hWnd;
	CScene* m_pScene;
	CRenderer* m_pRenderer;
	CInputKeyboard* m_pKeyboard;
	CInputMouse* m_pMouse;
	CInputPad* m_pPad;
	CCamera* m_pCamera;
	CLight* m_pLight;
	CTexture* m_pTexture;
	CModel* m_pModel;
	CSound* m_pSound;
	CColision* m_pColision;
	CFade* m_pFade;
};

#endif