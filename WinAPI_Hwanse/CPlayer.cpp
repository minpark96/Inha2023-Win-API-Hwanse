#include "pch.h"
#include "CPlayer.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CMissile.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CRigidBody.h"
#include "CGravity.h"

CPlayer::CPlayer()
	: m_eCurState(PLAYER_STATE::IDLE)
	, m_ePrevState(PLAYER_STATE::WALK)
	, m_iDir(1)
	, m_iPrevDir(1)
{
	// Texture 로딩하기
	//m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\player.bmp");

	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 15.f));
	GetCollider()->SetScale(Vec2(20.f, 30.f));

	CreateRigidBody();

	// Texture 로딩하기
	CTexture* pIdleTex = CResMgr::GetInst()->LoadTexture(L"PlayerIdle", L"texture\\player_idle.bmp");
	CTexture* pLeftTex = CResMgr::GetInst()->LoadTexture(L"PlayerLeft", L"texture\\player_left.bmp");
	CTexture* pRightTex = CResMgr::GetInst()->LoadTexture(L"PlayerRight", L"texture\\player_right.bmp");
	
	CreateAnimator();

	
	GetAnimator()->CreateAnimation(L"IDLE", pIdleTex, Vec2(0.f, 0.f), Vec2(48.f, 64.f), Vec2(48.f, 0.f), 0.1f, 5);
	
	GetAnimator()->CreateAnimation(L"WALK_LEFT", pLeftTex, Vec2(0.f, 0.f), Vec2(48.f, 64.f), Vec2(48.f, 0.f), 0.1f, 5);
	GetAnimator()->CreateAnimation(L"WALK_RIGHT", pRightTex, Vec2(0.f, 0.f), Vec2(48.f, 64.f), Vec2(48.f, 0.f), 0.1f, 5);
	
	CreateGravity();

	//GetAnimator()->Play(L"IDLE", true);

	/*CAnimation* pAnim = GetAnimator()->FindAnimation(L"IDLE");
	for (UINT i = 0; i < pAnim->GetMaxFrame(); i++)
	{
		pAnim->GetFrame(i).vOffset = Vec2(0.f, -20.f);
	}*/
}

CPlayer::~CPlayer()
{

}

void CPlayer::update()
{
	update_move();

	update_state();

	update_animation();

	if (KEY_TAP(KEY::SPACE))
	{
		CreateMissile();
	}

	GetAnimator()->update();

	m_ePrevState = m_eCurState;
	m_iPrevDir = m_iDir;
}

void CPlayer::render(HDC _dc)
{
	// 컴포넌트(충돌체, etc...) 가 있는 경우 렌더
	component_render(_dc);

	/*CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"Plane", L"texture\\water_idle1.bmp");

	Vec2 vPos = GetPos();
	vPos = CCamera::GetInst()->GetRenderPos(vPos);

	float width = (float)pTex->Width();
	float height = (float)pTex->Height();

	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = AC_SRC_ALPHA;
	bf.SourceConstantAlpha = 127;

	AlphaBlend(_dc 
		, int(vPos.x - width / 2.f)
		, int(vPos.y - height / 2.f)
		, int(width), int(height)
		, pTex->GetDC()
		, 0, 0
		, int(width), int(height)
		, bf);*/
}

void CPlayer::CreateMissile()
{
	Vec2 vMissilePos = GetPos();
	vMissilePos.y -= GetScale().y / 2.f;

	// Missile Object
	CMissile* pMissile = new CMissile;
	pMissile->SetName(L"Missile_Player");
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(25.f, 25.f));
	pMissile->SetDir(Vec2(0.f, -1.f));

	CreateObject(pMissile, GROUP_TYPE::PROJ_PLAYER);
}

void CPlayer::update_state()
{
	if (KEY_TAP(KEY::A))
	{
		m_iDir = -1;
		m_eCurState = PLAYER_STATE::WALK;
	}

	if (KEY_TAP(KEY::D))
	{
		m_iDir = 1;
		m_eCurState = PLAYER_STATE::WALK;
	}

	if (GetRigidBody()->GetSpeed() == 0.f)
	{
		m_eCurState = PLAYER_STATE::IDLE;
	}
}

void CPlayer::update_move()
{
	CRigidBody* pRigid = GetRigidBody();

	if (KEY_HOLD(KEY::A))
	{
		pRigid->AddForce(Vec2(-200.f, 0.f));
	}

	if (KEY_HOLD(KEY::D))
	{
		pRigid->AddForce(Vec2(200.f, 0.f));
	}

	if (KEY_TAP(KEY::A))
	{
		pRigid->AddVelocity(Vec2(-100.f, 0.f));
	}

	if (KEY_TAP(KEY::D))
	{
		pRigid->AddVelocity(Vec2(100.f, 0.f));
	}
}

void CPlayer::update_animation()
{
	if (m_ePrevState != m_eCurState && m_iPrevDir == m_iDir)
		return;

	switch (m_eCurState)
	{
	case PLAYER_STATE::IDLE:
	{
		if (m_iDir == -1)
			GetAnimator()->Play(L"IDLE", true);
		else
			GetAnimator()->Play(L"IDLE", true);
	}
		break;
	case PLAYER_STATE::WALK:
	{
		if (m_iDir == -1)
			GetAnimator()->Play(L"WALK_LEFT", true);
		else
			GetAnimator()->Play(L"WALK_RIGHT", true);
	}
		break;
	case PLAYER_STATE::ATTACK:

		break;
	case PLAYER_STATE::DEAD:

		break;
	}
}

void CPlayer::update_gravity()
{
	GetRigidBody()->AddForce(Vec2(0.f, 500.f));
}
