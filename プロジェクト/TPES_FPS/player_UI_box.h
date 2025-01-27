//=============================================
//
//�v���C���[��UI�̘g[player_UI_box.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _PLAYER_UI_BOX_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _PLAYER_UI_BOX_H_
#include "main.h"
#include "object2D.h"

//�v���C���[��UI�̘g�N���X
class CPlayerUIBox : public CObject2D
{
public:
	static const int UI_BOX_PRIORITY = 20;  //�`�揇

	enum BOX_TYPE
	{
		BOX_TYPE_LIFE,
		BOX_TYPE_AMMO,
		BOX_TYPE_SCORE,
		BOX_TYPE_MAX,
	};
	CPlayerUIBox(int nPriority = UI_BOX_PRIORITY);
	~CPlayerUIBox()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CPlayerUIBox* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size,D3DXCOLOR col, BOX_TYPE type);
private:
};


//�v���C���[��UI�̗̘̑͂g�N���X
class CLifeUIBox : public CPlayerUIBox
{
public:
	static const std::string TEXTURE_NAME;	//�e�N�X�`���̖��O

	CLifeUIBox(int nPriority = UI_BOX_PRIORITY);
	~CLifeUIBox()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
private:
};

//�v���C���[��UI�̎c�e�̘g�N���X
class CAmmoUIBox : public CPlayerUIBox
{
public:
	static const std::string TEXTURE_NAME;	//�e�N�X�`���̖��O

	CAmmoUIBox(int nPriority = UI_BOX_PRIORITY);
	~CAmmoUIBox()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
private:
};

//�v���C���[��UI�̃X�R�A�̘g�N���X
class CScoreUIBox : public CPlayerUIBox
{
public:
	static const std::string TEXTURE_NAME;	//�e�N�X�`���̖��O

	CScoreUIBox(int nPriority = UI_BOX_PRIORITY);
	~CScoreUIBox()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
private:
};
#endif