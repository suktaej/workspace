#pragma once

class CObject
{
private:
	Vec2 m_vPos;
	Vec2 m_vScale;
	float m_Speed;

public:
	void update();
	void render(HDC _dc);

public:
	CObject();
	virtual ~CObject();

public:
	GETSET(Pos, Vec2, m_vPos);
	GETSET(Scale, Vec2, m_vScale);
};
