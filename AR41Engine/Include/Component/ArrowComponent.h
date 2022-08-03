#pragma once
#include "PrimitiveComponent.h"
class CArrowComponent :
    public CPrimitiveComponent
{
    friend class CGameObject;

protected:
    CArrowComponent();
    CArrowComponent(const CArrowComponent& component);
    virtual ~CArrowComponent();

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CArrowComponent* Clone()    const;
};

