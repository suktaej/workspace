#pragma once

// 전방선언
class CObject;

class CScene
{
private:
	// 오브젝트 저장 및 관리할 벡터를 그룹 개수만큼 선언
	std::array<std::vector<CObject*>,(UINT)EGROUP_TYPE::END> m_arrObj;
	std::wstring m_strName; // Scene name

public:
	void update();
	void render(HDC _dc);
	virtual void enter() = 0;	// 해당 scene에 진입 시 호출
	virtual void exit() = 0;	// scene 종료 시 호출

protected:
	void AddObject(CObject* _obj, EGROUP_TYPE _type) { m_arrObj[(UINT)_type].push_back(_obj); }

public:
	GETSET(Name, std::wstring, m_strName);

public:
	CScene();
	virtual ~CScene();
};

