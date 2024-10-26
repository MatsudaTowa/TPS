//=============================================
//
//3DTemplate[renderer.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _RENDERER_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _RENDERER_H_

//�����_���[�N���X
class CRenderer
{
public:
	CRenderer();
	~CRenderer();
	HRESULT Init(HWND hWnd,BOOL bWindow);
	void Uninit();
	void Update();
	void Draw();
	void DrawFPS(int nCntFPS);
	static LPDIRECT3DDEVICE9 GetDevice(); //3D�f�o�C�X�擾

	LPD3DXFONT GetFont();
	LPD3DXFONT m_pFont; //�t�H���g�ւ̃|�C���^

private:
	float m_fFogStartPos;
	float m_fFogEndPos;
	//���x�w��
	float m_fFogDensity = 0.001f;
	LPDIRECT3D9	m_pD3D; //Direct3D�I�u�W�F�N�g�ւ̃|�C���^
	static LPDIRECT3DDEVICE9 m_pD3DDevice; //Direct3D�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffMain; //���_�o�b�t�@�ւ̃|�C���^
};
#endif