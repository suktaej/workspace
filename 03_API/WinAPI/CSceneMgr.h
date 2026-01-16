#pragma once

class CScene;

class CSceneMgr
{
	DECLARE_SINGLE(CSceneMgr);

private:
	std::array<CScene*,(UINT)ESCENE_TYPE::END> m_arrScene;
	CScene* m_pCurScene;

public:
	void init();
	void update();
	void render(HDC _dc);
};

