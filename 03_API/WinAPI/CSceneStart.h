#pragma once

#include "CScene.h"

class CSceneStart : public CScene
{
public:
	void enter() override;
	void exit() override;

public:
	CSceneStart();
	~CSceneStart();
};

