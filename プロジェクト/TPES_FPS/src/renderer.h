//=============================================
//
//�`�揈��[renderer.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _RENDERER_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _RENDERER_H_

//=============================================
//�����_���[�N���X
//=============================================
class CRenderer
{
public:
	/**
	 * @brief �R���X�g���N�^
	 */
	CRenderer();
	/**
	 * @brief �f�X�g���N�^
	 */
	~CRenderer();
	/**
	 * @brief ������
	 * @param [in]�n���h�������h
	 * @param [in]�E�B���h�E�������o������
	 * @return ����������
	 */
	HRESULT Init(HWND hWnd,BOOL bWindow);
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
	 * @brief FPS�\��
	 * @param [in]FPS�J�E���g
	 */
	void DrawFPS(int nCntFPS);

	/**
	 * @brief �f�o�C�X�擾
	 * @return �f�o�C�X
	 */
	static LPDIRECT3DDEVICE9 GetDevice();

	/**
	 * @brief �t�H���g�擾
	 * @return �t�H���g
	 */
	LPD3DXFONT GetFont();
private:
	int m_DrawCnt;		//�J�[�\���`��J�E���g
	LPD3DXFONT m_pFont; //�t�H���g�ւ̃|�C���^

	LPDIRECT3D9	m_pD3D; //Direct3D�I�u�W�F�N�g�ւ̃|�C���^
	static LPDIRECT3DDEVICE9 m_pD3DDevice; //Direct3D�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffMain; //���_�o�b�t�@�ւ̃|�C���^
};
#endif