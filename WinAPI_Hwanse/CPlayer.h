#pragma once
#include "CObject.h"


class CPlayer :
    public CObject
{
public:
    virtual void update();
    virtual void render(HDC _dc);

private:
    void CreateMissile();

public:
    CPlayer();
    ~CPlayer();
};
