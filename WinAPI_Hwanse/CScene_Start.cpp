#include "pch.h"
#include "CScene_Start.h"

#include "CCore.h"
#include "CPlayer.h"
#include "CMonster.h"

#include "CPathMgr.h"
#include "CTexture.h"

CScene_Start::CScene_Start()
{
}

CScene_Start::~CScene_Start()
{
}

void CScene_Start::Enter()
{
	// Texture �ε��ϱ�
	CTexture* pTex = new CTexture;
	
	wstring strFilepath = CPathMgr::GetInst()->GetContentPath();
	strFilepath += L"texture\\btl_at.cns.bmp";
	pTex->Load(strFilepath);

	delete pTex;

	// Object �߰�
	CObject* pObj = new CPlayer;
	pObj->SetPos(Vec2(640.f, 384.f));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, GROUP_TYPE::DEFAULT);

	// ���� ��ġ
	int iMonCount = 16;
	float fMoveDist = 25.f;
	float fObjScale = 50.f;


	Vec2 vResolution = CCore::GetInst()->GetResolution();
	float fTerm = (vResolution.x - ((fMoveDist + fObjScale / 2.f) * 2)) / (float)(iMonCount - 1);

	CMonster* pMosterObj = nullptr;

	for (int i = 0; i < iMonCount; ++i)
	{
		// Monster Object �߰�
		pMosterObj = new CMonster;
		pMosterObj->SetPos(Vec2((fMoveDist + fObjScale / 2.f) + (float)i * fTerm, 50.f));
		pMosterObj->SetCenterPos(pMosterObj->GetPos());
		pMosterObj->SetMoveDistance(fMoveDist);
		pMosterObj->SetScale(Vec2(fObjScale, fObjScale));
		AddObject(pMosterObj, GROUP_TYPE::DEFAULT);
	}
}

void CScene_Start::Exit()
{
}