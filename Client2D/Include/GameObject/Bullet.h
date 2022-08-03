#pragma once

#include "GameObject.h"

enum class EExplosionFlag : UINT8
{
	isOn = 1 << 0,
	ExplodeByTime = 1 << 1,
	ExplodeByDist = 1 << 2
};

class CBullet :
    public CGameObject
{
	friend class CScene;

protected:
	CBullet();
	CBullet(const CBullet& Obj);
	virtual ~CBullet();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CBullet* Clone()    const;

private:
	CSharedPtr<class CArrowComponent>	m_Sprite;
	UINT8 m_ExplosionFlag;	//������ ��Ѹ� ������
	float m_ExplosionLeftValue;	//������ �Ÿ� Ȥ�� �ð��� ���� ������.
	void Explode();
public:
	void SetExplode(EExplosionFlag Flag, float Val = 0.f);

private:
	float m_Range;
	Vector3 m_StartPos;	//�Ÿ� ������ ���� �� ���۵� ��ġ.
public:
	void SetStartPos(const Vector3& StartPos);
	void SetRange(float Range);
};

