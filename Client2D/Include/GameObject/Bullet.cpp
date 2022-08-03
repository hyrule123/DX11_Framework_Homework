
#include "Bullet.h"

#include "Scene/Scene.h"

//ȭ��ǥ ��� Mesh
#include "Component/ArrowComponent.h"

CBullet::CBullet():
	m_ExplosionFlag(),
	m_ExplosionLeftValue(-1.f),
	m_Range(1000.f)
{
	SetTypeID<CBullet>();
}

CBullet::CBullet(const CBullet& Obj) :
	CGameObject(Obj),
	m_ExplosionFlag(Obj.m_ExplosionFlag),
	m_ExplosionLeftValue(Obj.m_ExplosionLeftValue),
	m_Range(Obj.m_Range)
{
}

CBullet::~CBullet()
{
}

void CBullet::Start()
{
	CGameObject::Start();	
}

bool CBullet::Init()
{
	CGameObject::Init();

	m_Sprite = CreateComponent<CArrowComponent>("Sprite");

	m_Sprite->SetRelativeScale(50.f, 50.f);

	return true;
}

void CBullet::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	AddWorldPosition(GetWorldAxis(AXIS_Y) * 2000.f * DeltaTime);

	//��Ÿ� �̻� �̵����� ��� ����
	if (GetWorldPos().Distance(m_StartPos) > m_Range)
		Destroy();



	if (m_ExplosionFlag & (UINT8)EExplosionFlag::isOn)
	{
		if (m_ExplosionFlag & (UINT8)EExplosionFlag::ExplodeByTime)
		{
			m_ExplosionLeftValue -= DeltaTime;

			if (m_ExplosionLeftValue < 0.f)
			{
				Explode();
			}
				
		}
		else if (m_ExplosionFlag & (UINT8)EExplosionFlag::ExplodeByDist)
		{
			//���� ������ �� ���������κ����� �Ÿ��� ������ �Ÿ����� �־����� ��� �����Ѵ�.
			if (m_StartPos.Distance(m_Sprite->GetWorldPos()) > m_ExplosionLeftValue)
			{
				Explode();
			}
				
		}
	}

}

void CBullet::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CBullet* CBullet::Clone() const
{
	return new CBullet(*this);
}

void CBullet::Explode()
{
	//8�� ����
	int iMax = 6;
	for (int i = 0; i < iMax; ++i)
	{
		CBullet* Bullet = m_Scene->CreateObject<CBullet>("Bullet");

		Bullet->SetWorldPosition(GetWorldPos());
		Bullet->SetStartPos(GetWorldPos());
		Bullet->SetWorldRotation(GetWorldRot());
		Bullet->AddWorldRotationZ(360.f * ((float)i / (float)iMax));
	}

	Destroy();
}

void CBullet::SetExplode(EExplosionFlag Flag, float Val)
{
	m_ExplosionFlag = (UINT8)Flag;

	switch (Flag)
	{
	case EExplosionFlag::isOn:
		Explode();
		break;
	case EExplosionFlag::ExplodeByTime:
		m_ExplosionFlag |= (UINT8)EExplosionFlag::isOn;
		m_ExplosionLeftValue = Val;
		break;
	case EExplosionFlag::ExplodeByDist:
		m_ExplosionFlag |= (UINT8)EExplosionFlag::isOn;
		m_ExplosionLeftValue = Val;
		m_StartPos = m_Sprite->GetWorldPos();
		break;
	default:
		break;
	}
}

void CBullet::SetStartPos(const Vector3& StartPos)
{
	m_StartPos = StartPos;
}

void CBullet::SetRange(float Range)
{
	m_Range = Range;
}
