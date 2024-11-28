//=============================================
//
//キャラクターのステートパターン[character_state.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "character_state.h"

//=============================================
//キャラクターのショット
//=============================================
void CCharacterState::Shot(CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type, CCharacter* character)
{
}

//=============================================
//キャラクターの動き
//=============================================
void CCharacterState::Move(CCharacter* character)
{
}

//=============================================
//キャラクターのショット
//=============================================
void CShotState::Shot(CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type, CCharacter* character)
{
	character->m_pAttack->GunAttack(Allegiance,type,character);
}

//=============================================
//キャラクターの動き
//=============================================
void CMoveState::Move(CCharacter* character)
{
	if (character->m_pMove != nullptr)
	{
		character->m_pMove->Move(character);
	}
}
