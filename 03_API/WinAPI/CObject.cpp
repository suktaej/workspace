#include "pch.h"
#include "CObject.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"

CObject::CObject()
	: m_vPos{}, m_vScale{}, m_Speed(200.f)
{
}

CObject::~CObject()
{
}

void CObject::update()
{
	if (CKeyMgr::GetInst()->GetKeyState(EKEY_TYPE::W) == EKEY_STATE::HOLD)
		m_vPos.y -= m_Speed * FDT;
	if(CKeyMgr::GetInst()->GetKeyState(EKEY_TYPE::S) == EKEY_STATE::HOLD)
		m_vPos.y += m_Speed * FDT;
	if(CKeyMgr::GetInst()->GetKeyState(EKEY_TYPE::A) == EKEY_STATE::HOLD)
		m_vPos.x -= m_Speed * FDT;
	if(CKeyMgr::GetInst()->GetKeyState(EKEY_TYPE::D) == EKEY_STATE::HOLD)
		m_vPos.x += m_Speed * FDT;
}

void CObject::render(HDC _dc) 
{
	Rectangle(_dc,
		(int)(m_vPos.x - m_vScale.x / 2.f),
		(int)(m_vPos.y - m_vScale.y / 2.f),
		(int)(m_vPos.x + m_vScale.x / 2.f),
		(int)(m_vPos.y + m_vScale.y / 2.f));
}
