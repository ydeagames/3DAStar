//#define _CRT_SECURE_NO_WARNINGS
#include "MyGame.h"

// コンストラクタ
MyGame::MyGame(int width, int height) noexcept : m_width(width), m_height(height), Game(width, height)
{
}

// MyGameオブジェクトを初期する
void MyGame::Initialize() noexcept
{
	// 基底クラスのInitializeを呼び出す 
	Game::Initialize();

	// Keyboardオブジェクトを生成する
	//KeyboardPrim::Get();
	// Mouseオブジェクトを生成する
	MousePrim::Get();
	// DebugCameraオブジェクトを生成する
	m_debugCamera = std::make_unique<DebugCamera>(m_width, m_height);
	
	// Sceneオブジェクトを生成する
	m_scene = std::make_shared<Scene>();

	// Sceneオブジェクトを初期化する
	m_scene->Initialize();
	// ワールド行列を初期化する
	m_world = DirectX::SimpleMath::Matrix::Identity;
}

// リソースを生成する
void MyGame::CreateResources() noexcept
{
	// 基底クラスのCreateResourcesを呼び出す
	Game::CreateResources();

	// 射影座標変換行列を生成する
	m_projection = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(DirectX::XMConvertToDegrees(60.0f),
		float(m_width) / float(m_height), 0.1f, 100.0f);
}

// ゲームを更新する
void MyGame::Update(const DX::StepTimer& timer) noexcept
{
	// 経過時間を取得する
	float elapsedTime = float(timer.GetTotalSeconds());

	// DebugCameraオブジェクトを更新する
	m_debugCamera->Update();
	// デバッグカメラからビュー行列を生成する
	m_view = m_debugCamera->GetViewMatrix();
	// Sceneオブジェクトを更新する
	m_scene->Update(timer, m_view, m_projection);
}

// ゲームを描画する
void MyGame::Render(const DX::StepTimer& timer) noexcept
{
	// 最初の更新の前は何も描画しないようにする
	if (timer.GetFrameCount() == 0) 
		return;

	// TODO: レンダリングコードを追加する
	// バッファをクリアする
	Clear();
	// シーンを描画する
	m_scene->Render(timer, m_view, m_projection);
	// バックバッファを表示する
	Present();
}

// 後始末をする
void MyGame::Finalize() noexcept
{
	// Sceneオブジェクトを解放する
	m_scene.reset();
	// DebugCameraオブジェクトを破棄する
	m_debugCamera.reset();

	// 基底クラスのFinalizeを呼び出す
	Game::Finalize();
}

