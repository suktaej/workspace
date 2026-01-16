#pragma once
#include "pch.h"

#define	DECLARE_SINGLE(Type)	\
private:\
	Type();\
	~Type();\
private:\
	static Type*	mInst;\
public:\
	static Type* GetInst()\
	{\
		if(!mInst)\
			mInst = new Type;\
		return mInst;\
	}\
	static void DestroyInst()\
	{\
		SAFE_DELETE(mInst);\
	}
#define	DEFINITION_SINGLE(Type)	Type* Type::mInst = nullptr;
#define	SAFE_DELETE(p)	if(p)	{ delete p; p = nullptr; }
#define	SAFE_RELEASE(p)	if(p)	{ p->Release(); p = nullptr; }

#define GETSET(name, type, val) \
public:\
	void Set##name(type mem) { val = mem; }\
	const type& Get##name() const { return val; }

#define FDT CTimeMgr::GetInst()->GetFDT()
#define DT CTimeMgr::GetInst()->GetDT()

// scene에서 관리할 object의 그룹
enum class EGROUP_TYPE
{
	DEFAULT,
	PLAYER,
	MISSILE,
	MONSTER,
	END = 32
};

enum class ESCENE_TYPE
{
	TOOL,
	START,
	STAGE_01,
	STAGE_02,
	END
};
