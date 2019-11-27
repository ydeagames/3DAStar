#include "Chasing.h"

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
	DirectX::SimpleMath::Vector3 Forward(.05f, 0, 0);

	if (m_route.size()==0)
	{
		Position position = m_enemy->GetStartPosition();
		m_position = DirectX::SimpleMath::Vector3((float)position.column - 5.f, .5f, (float)position.row - 5.f);
;		m_route = m_enemy->GetRoute();
	}

	if (m_route.size() == 0)
		return FAILURE;

	Position position = m_route[0];
	DirectX::SimpleMath::Vector3 next = DirectX::SimpleMath::Vector3((float)position.column - 5.f, .5f, (float)position.row - 5.f);
	if (DirectX::SimpleMath::Vector3::DistanceSquared(m_position, next) > Forward.LengthSquared())
	{
		auto diff = next - m_position;
		float angle = std::atan2f(-diff.z, diff.x);
		m_position += DirectX::SimpleMath::Vector3::Transform(Forward, DirectX::SimpleMath::Matrix::CreateRotationY(angle));

		//m_position = DirectX::SimpleMath::Vector3::SmoothStep(m_position, next, .5f);
	}
	else
	{
		m_route.erase(m_route.begin());
	}

	m_enemy->SetVectorPosition(m_position);

	if (m_route.size() == 0)
		return FAILURE;

	return SUCCESS;
}

int Chasing::Interrupt() noexcept
{
	Position position = m_enemy->GetEndPosition();
	m_position = DirectX::SimpleMath::Vector3((float)position.column - 5.f, .5f, (float)position.row - 5.f);
	m_enemy->SetVectorPosition(m_position);
	m_route.clear();
	return SUCCESS;
}

int Chasing::ResetRoute() noexcept
{
	m_route.clear();
	return SUCCESS;
}

void Chasing::Render(const DX::StepTimer& timer) noexcept
{
}

void Chasing::Finalize() noexcept
{
}
