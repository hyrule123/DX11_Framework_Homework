#include "ArrowComponent.h"

CArrowComponent::CArrowComponent()
{
	SetTypeID<CArrowComponent>();
}

CArrowComponent::CArrowComponent(const CArrowComponent& component) :
	CPrimitiveComponent(component)
{
}

CArrowComponent::~CArrowComponent()
{
}

void CArrowComponent::Start()
{
	CPrimitiveComponent::Start();
}

bool CArrowComponent::Init()
{
	if (!CPrimitiveComponent::Init())
		return false;

	SetMesh("ArrowShape");
	SetShader("SpriteColorShader");

	return true;
}

void CArrowComponent::Update(float DeltaTime)
{
	CPrimitiveComponent::Update(DeltaTime);
}

void CArrowComponent::PostUpdate(float DeltaTime)
{
	CPrimitiveComponent::PostUpdate(DeltaTime);
}

void CArrowComponent::Render()
{
	CPrimitiveComponent::Render();
}

CArrowComponent* CArrowComponent::Clone() const
{
	return new CArrowComponent(*this);
}
