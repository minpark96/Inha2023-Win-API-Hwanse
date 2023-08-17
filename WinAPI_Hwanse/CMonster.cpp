#include "pch.h"
#include "CMonster.h"

#include "AI.h"

#include "CTimeMgr.h"
#include "CCollider.h"

CMonster::CMonster()
	: m_tInfo{}
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(40.f, 40.f));
}

CMonster::~CMonster()
{
	if (m_pAI != nullptr)
		delete m_pAI;
}

void CMonster::update()
{
	m_pAI->update();
}


void CMonster::SetAI(AI* _AI)
{
	m_pAI = _AI;
	m_pAI->m_pOwner = this;
}

void CMonster::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Missile_Player")
	{
	}
}