#include "pch.h"
#include "CSceneMgr.h"
#include "CSceneStart.h"

DEFINITION_SINGLE(CSceneMgr);

CSceneMgr::CSceneMgr()
	: m_pCurScene(nullptr)
{ 
}
CSceneMgr::~CSceneMgr()
{
	for (UINT i = 0; i < (UINT)ESCENE_TYPE::END; ++i)
		if (nullptr != m_arrScene[i])
			delete m_arrScene[i];
}

void CSceneMgr::init()
{
	// Scene 생성
	m_arrScene[(UINT)ESCENE_TYPE::START] = new CSceneStart;
	m_arrScene[(UINT)ESCENE_TYPE::START]->SetName(L"Start Scene");
	//m_arrScene[(UINT)ESCENE_TYPE::TOOL] = new CSceneTool;
	//m_arrScene[(UINT)ESCENE_TYPE::STAGE_01] = new CSceneStage1;
	//m_arrScene[(UINT)ESCENE_TYPE::STAGE_02] = new CSceneStage2;

	// default scene 지정
	m_pCurScene = m_arrScene[(UINT)ESCENE_TYPE::START];
	m_pCurScene->enter();
}

void CSceneMgr::update()
{
	m_pCurScene->update();
}

void CSceneMgr::render(HDC _dc)
{
	m_pCurScene->render(_dc);
}
