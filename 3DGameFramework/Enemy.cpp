#include "Enemy.h"

// コンストラクタ
Enemy::Enemy(Scene* scene) noexcept
	: m_scene(scene)
	, m_startPosition(0, 0)
	, m_endPosition(0, 0)
	, m_position(0, .5f, .0f)
	, m_translation(DirectX::SimpleMath::Matrix::Identity)
	, m_tiledMap(scene->GetMap())
{
}

// 初期化する
int Enemy::Initialize() noexcept
{
	m_idlingState = std::make_unique<Idling>();
	m_idlingState->Initialize(this);

	m_searchingState = std::make_unique<Searching>(m_tiledMap);
	m_searchingState->Initialize(this);

	m_chasingState = std::make_unique<Chasing>();
	m_chasingState->Initialize(this);

	ChangeState(m_idlingState.get());

	m_primitive = DirectX::GeometricPrimitive::CreateSphere(DirectX11::Get().GetContext().Get(), .8f, 16U, /*false*/true);
	m_basicEffect = m_scene->GetBasicEffect();
	m_primitive->CreateInputLayout(m_basicEffect, &m_inputLayout);
	DirectX::CreateWICTextureFromFile(m_directX.GetDevice().Get(), L"Resources/texture/concrete.png",
		nullptr, m_texture.ReleaseAndGetAddressOf());

	return SUCCESS;
}

// 状態を変更する
void Enemy::ChangeState(IState * state)
{
	m_currentState = state;
}

// 更新する
int Enemy::Update(const DX::StepTimer & timer) noexcept
{
	// 現在の状態を更新する
	int result = m_currentState->Update(timer);

	// 「サーチ」状態（最短経路の探索後）の更新後
	if (m_currentState == m_searchingState.get())
	{
	// 正常に最短経路が探索されたかどうか
		if (result == SUCCESS)
		{
			// 最短経路を取得する
			m_route = m_searchingState.get()->GetRoute();
			// 現在の状態を「追跡」状態に変更する
			ChangeState(m_chasingState.get());
		}
		else
		{
			// 現在の状態を「アイドリング」状態に変更する
			ChangeState(m_idlingState.get());
		}
	}
	// 「追跡」状態が正常終了の場合
	else if (m_currentState == m_chasingState.get())
	{
		// 「追跡」状態が正常終了の場合
		if (result == SUCCESS)
		{
			// 追跡中（状態を変更しない）
		}
		else
		{
			// 追跡が終了したので現在の状態を「アイドリング」状態に変更する
			ChangeState(m_idlingState.get());
		}
	}
	return 0;
}

// 描画する
void Enemy::Render(const DX::StepTimer & timer, const DirectX::SimpleMath::Matrix & view, const DirectX::SimpleMath::Matrix & projection) noexcept
{
	m_translation = DirectX::SimpleMath::Matrix::CreateTranslation(m_position);
	m_basicEffect->SetWorld(m_translation);
	m_basicEffect->SetView(view);
	m_basicEffect->SetProjection(projection);
	m_basicEffect->SetTexture(m_texture.Get());
	m_primitive->Draw(m_basicEffect, m_inputLayout);

	{
		auto pos = DirectX::SimpleMath::Vector3((float)m_startPosition.column - 5.f, .5f, (float)m_startPosition.row - 5.f);
		auto mat = DirectX::SimpleMath::Matrix::CreateScale(1.f, .01f, 1.f) * DirectX::SimpleMath::Matrix::CreateTranslation(pos + DirectX::SimpleMath::Vector3::Down * .4f);
		m_basicEffect->SetWorld(mat);
		m_basicEffect->SetTexture(nullptr);
		m_primitive->Draw(m_basicEffect, m_inputLayout);
	}
	{
		auto pos = DirectX::SimpleMath::Vector3((float)m_endPosition.column - 5.f, .5f, (float)m_endPosition.row - 5.f);
		m_position_end = DirectX::SimpleMath::Vector3::Lerp(m_position_end, pos, .1f);
		auto mat = DirectX::SimpleMath::Matrix::CreateScale(1.f, .01f, 1.f) * DirectX::SimpleMath::Matrix::CreateTranslation(m_position_end + DirectX::SimpleMath::Vector3::Down * .4f);
		m_basicEffect->SetWorld(mat);
		m_basicEffect->SetTexture(m_texture.Get());
		m_primitive->Draw(m_basicEffect, m_inputLayout);
	}

	m_currentState->Render(timer);
}

// 後始末をする
void Enemy::Finalize() noexcept
{
}
