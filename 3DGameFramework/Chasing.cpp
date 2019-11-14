#include "Chasing.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

Chasing::Chasing() noexcept
{
}

int Chasing::Initialize(IObject* object) noexcept
{
	m_enemy = static_cast<Enemy*>(object);

	return SUCCESS;
}

int Chasing::Update(const DX::StepTimer& timer) noexcept
{
	Vector3 Forward(.05f, 0, 0);

	if (m_route.size()==0)
	{
		Position position = m_enemy->GetStartPosition();
		m_position = Vector3((float)position.column - 5.f, 0.f, (float)position.row - 5.f);
;		m_route = m_enemy->GetRoute();
	}

	if (m_route.size() == 0)
		return FAILURE;

	Position position = m_route[0];
	auto next = Vector3((float)position.column - 5.f, 0.f, (float)position.row - 5.f);
	if (Vector3::Distance(m_position, next) > .1f)
	{
		m_position = Vector3::Lerp(m_position, next, .5f);
	}
	else
	{
		m_route.erase(m_route.begin());
	}

	m_enemy->SetVectorPosition(m_position);

	return SUCCESS;
}

void Chasing::Render(const DX::StepTimer& timer) noexcept
{
}

void Chasing::Finalize() noexcept
{
}
