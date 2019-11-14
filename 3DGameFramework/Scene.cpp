#include "Scene.h"

// コンストラクタ
Scene::Scene() noexcept : m_mapFile("map.csv") // マップファイルをSceneオブジェクトで決定する
{
}

// 初期化する
void Scene::Initialize() noexcept
{
	// Keyboardオブジェクトを生成する 
	m_keyboard = std::make_unique<DirectX::Keyboard>();
	// KeyboardStateTrackerオブジェクトを生成する
	m_keyboardStateTracker = std::make_unique<DirectX::Keyboard::KeyboardStateTracker>();
	
	// BasicEffectオブジェクトを生成する
	m_basicEffect = std::make_unique<DirectX::BasicEffect>(m_directX.GetDevice().Get());
	m_basicEffect->SetTextureEnabled(true);
	m_basicEffect->SetPerPixelLighting(true);
	m_basicEffect->SetLightingEnabled(true);
	m_basicEffect->SetColorAndAlpha(DirectX::Colors::White);

	// Light 0
	m_basicEffect->SetLightEnabled(0, true);
	m_basicEffect->SetLightSpecularColor(0, DirectX::Colors::White);
	m_basicEffect->SetLightDiffuseColor(0, DirectX::Colors::White);
	m_basicEffect->SetLightDirection(0, DirectX::SimpleMath::Vector3(0.0f, 1.0f, 0.0f));
	// Light 1
	m_basicEffect->SetLightEnabled(1, true);
	m_basicEffect->SetLightSpecularColor(1, DirectX::Colors::White);
	m_basicEffect->SetLightDiffuseColor(1, DirectX::Colors::White);
	m_basicEffect->SetLightDirection(1, DirectX::SimpleMath::Vector3(0.0f, -1.0f, 0.0f));

	// CubeMapオブジェクトを生成する
	m_cubeMap = std::make_unique<CubeMap>(this);
	// CubeMapオブジェクトを初期化する
	m_cubeMap->Initialize(m_mapFile);

	// Enemyオブジェクトを生成する
	m_enemy = std::make_unique<Enemy>(this);
	// Enemyオブジェクトを初期化する
	m_enemy->Initialize();
}


// 更新する
void Scene::Update(const DX::StepTimer& timer, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) noexcept
{
	// ビュー行列を設定する
	m_view = view;
	// プロジェクション行列を設定する
	m_projection = projection;


	// キーボードの状態を取得する
	DirectX::Keyboard::State state = m_keyboard->GetState();
	// キーボード状態トラッカーを更新する
	m_keyboardStateTracker->Update(state);

	// SPACEキーを押下げた場合
	if (m_keyboardStateTracker->IsKeyPressed(DirectX::Keyboard::Keys::Space))
	{
	}

	// Enemyオブジェクトを更新する
	m_enemy->Update(timer);
}

// 描画する
void Scene::Render(const DX::StepTimer& timer, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) noexcept
{
	// CubeMapオブジェクトを描画する
	m_cubeMap->Render(timer, m_view, m_projection);

	// Enemyオブジェクトを描画する
	m_enemy->Render(timer, view, projection);
}

// 後始末をする
void Scene::Finalize() noexcept
{
	// Floorオブジェクトを解放する
	m_cubeMap.reset();
}