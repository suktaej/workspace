#pragma once

class CObject
{
private:
	Vec2 m_ptPos;
	Vec2 m_ptScale;

public:
	CObject();
	~CObject();

public:
	GETSET(Vec2, m_ptPos);
	GETSET(Vec2, m_ptScale);
};
