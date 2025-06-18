//=============================================
//
//�I�u�W�F�N�g[object.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _OBJECT_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _OBJECT_H_
#include "main.h"

//=============================================
//�I�u�W�F�N�g�N���X
//=============================================
class CObject
{
public:
	static const int MAX_OBJECT = 256; //�I�u�W�F�N�g�̍ő吔

	static const int PRI_MAX = 30; //�v���C�I���e�B�̍ő�l

	enum OBJECT_TYPE
	{
		OBJECT_TYPE_NONE = 0,
		OBJECT_TYPE_TITLE,
		OBJECT_TYPE_TUTORIAL,
		OBJECT_TYPE_RESULT,
		OBJECT_TYPE_FADE,
		OBJECT_TYPE_UI_BOX,
		OBJECT_TYPE_ULT_ICON,
		OBJECT_TYPE_PAUSE_SELECT,
		OBJECT_TYPE_HIT_CAMERA_EFFECT,
		OBJECT_TYPE_ULT_CAMERA_EFFECT,
		OBJECT_TYPE_GAUGE,
		OBJECT_TYPE_NUMBER,
		OBJECT_TYPE_PLAYER,
		OBJECT_TYPE_ENEMY,
		OBJECT_TYPE_BLOCK,
		OBJECT_TYPE_BLOCK_PIECE,
		OBJECT_TYPE_MUZZLE_FLUSH,
		OBJECT_TYPE_FIELD,
		OBJECT_TYPE_WALL,
		OBJECT_TYPE_EFFECT,
		OBJECT_TYPE_DUSH_EFFECT,
		OBJECT_TYPE_BG,
		OBJECT_TYPE_BULLET,
		OBJECT_TYPE_RETICLE,
		OBJECT_TYPE_SMOKE,
		OBJECT_TYPE_SMOKE_GRENADE,
		OBJECT_TYPE_SMOKE_RANGE,
		OBJECT_TYPE_SHADOW,
		OBJECT_TYPE_ULT_EFFECT,
		OBJECT_TYPE_MAX,
	};

	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CObject(int nPriority = PRI_MAX);
	/**
	 * @brief �f�X�g���N�^
	 */
	virtual ~CObject();
	/**
	 * @brief ������
	 * @return ����������
	 */
	virtual HRESULT Init() = 0;
	/**
	 * @brief �I��
	 */
	virtual void Uninit() = 0;
	/**
	 * @brief �X�V
	 */
	virtual void Update() = 0;
	/**
	 * @brief �`��
	 */
	virtual void Draw() = 0;
	/**
	 * @brief �S�I�u�W�F�N�g���
	 */
	static void ReleaseAll();
	/**
	 * @brief �S�I�u�W�F�N�g�X�V
	 */
	static void UpdateAll();
	/**
	 * @brief �S�I�u�W�F�N�g�`��
	 */
	static void DrawAll();
	/**
	 * @brief �I�u�W�F�N�g
	 * @param [in]�v���C�I���e�B
	 * @param [in]�ԍ�
	 * @return 
	 */
	static CObject* Getobject(int nPri,int nIdx);

	/**
	 * @brief �^�C�v�擾
	 * @return �I�u�W�F�N�g�^�C�v
	 */
	inline OBJECT_TYPE GetType()
	{
		return m_type;
	}

	/**
	 * @brief �`�悷�邩�ǂ����ݒ�
	 * @param [in]�`�悷�邩
	 */
	inline void SetisDraw(bool isDraw)
	{
		m_isDraw = isDraw;
	}

	/**
	 * @brief �������~�߂邩�ǂ����ݒ�
	 * @param [in]�������~�߂邩
	 */
	inline void SetisActive(bool isActive)
	{
		m_isActive = isActive;
	}

	/**
	 * @brief �`�悷�邩�ǂ����擾
	 * @return �`�悷�邩
	 */
	inline bool& GetisDraw()
	{
		return m_isDraw;
	}

	/**
	 * @brief �������ǂ����擾
	 * @return ��������
	 */
	inline bool& GetisActive()
	{
		return m_isActive;
	}

	/**
	 * @brief �I�u�W�F�N�g�^�C�v�ݒ� 
	 * @param [in]�I�u�W�F�N�g�^�C�v
	 */
	inline void SetType(OBJECT_TYPE type)
	{
		m_type = type;
	}

	/**
	 * @brief �������g�̉��
	 */
	void Release();
private:
	static CObject* m_apObject[CObject::PRI_MAX][MAX_OBJECT];

	int m_nPriority; //�`��D��x

	OBJECT_TYPE m_type;

	static int m_nNumAll; //����

	bool m_isActive;	//�������邩

	bool m_isDraw;	//�`�悷�邩

	int m_nID; //�I�u�W�F�N�g��ID
};
#endif