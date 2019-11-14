#include "CubeMap.h"

// コンストラクタ
CubeMap::CubeMap(Scene* scene) noexcept : m_scene(scene)
{
}

// 初期化する
void CubeMap::Initialize(const std::string& mapFile) noexcept
{
	// テクスチャファイル
	wstring textureFile[] =
	{
		L"resources\\texture\\concrete.png",	// コンクリート
		L"resources\\texture\\corkBoard.png",	// コルクボード
		L"resources\\texture\\grass.png",		// グラス
		L"resources\\texture\\substance.png"	// サブスタンス
	};

	// テクスチャを生成する
	DirectX::CreateWICTextureFromFile(m_directX.GetDevice().Get(), textureFile[2].c_str(), nullptr, m_grass.ReleaseAndGetAddressOf());
	DirectX::CreateWICTextureFromFile(m_directX.GetDevice().Get(), textureFile[1].c_str(), nullptr, m_corkBoard.ReleaseAndGetAddressOf());
	
	// Boxモデルを生成する
	m_cube = DirectX::GeometricPrimitive::CreateBox(m_directX.GetContext().Get(), DirectX::XMFLOAT3(0.99f, 0.2f, 0.99f), true, true);
	// BasicEffectオブジェクトを参照する
	m_basicEffect = m_scene->GetBasicEffect();
	// InputLayoutオブジェクトを生成する
	m_cube->CreateInputLayout(m_basicEffect, &m_inputLayout);
	
	// TiledMapオブジェクトを生成する
	m_tiledMap = std::make_unique<TiledMap>();
	// マップをロードする
	m_tiledMap->Load(mapFile);
}

// 更新する
void CubeMap::Update(const DX::StepTimer& timer) noexcept
{
}

// 描画する
void CubeMap::Render(const DX::StepTimer& timer, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) noexcept
{
	// 位置
	DirectX::SimpleMath::Vector3 position = DirectX::SimpleMath::Vector3::Zero;
	// 移動行列
	DirectX::SimpleMath::Matrix translation = DirectX::SimpleMath::Matrix::Identity;

	for (int row = 0; row < m_tiledMap->GetMapRow(); row++)
	{
		for (int column = 0; column < m_tiledMap->GetMapColumn(); column++)
		{
			// 位置を計算する
			position = DirectX::SimpleMath::Vector3(((float)column - 5.0f), 0.0f, ((float)row - 5.0f));
			// 移動行列を作成する
			translation = DirectX::SimpleMath::Matrix::CreateTranslation(position);
			// 移動行列を設定する
			m_basicEffect->SetWorld(translation);
			// ビュー行列を設定する
			m_basicEffect->SetView(view);
			// プロジェクション行列を設定する
			m_basicEffect->SetProjection(projection);

			// マップの属性に応じてテクスチャを選択する
			switch (m_tiledMap->GetMap()[row][column])
			{
				case MAP_ATTRIBUTE::O:
					// 障害物テクスチャを設定する
					m_basicEffect->SetTexture(m_corkBoard.Get());
					break;
				case MAP_ATTRIBUTE::P:
					// 通路テクスチャを設定する
					m_basicEffect->SetTexture(m_grass.Get());
					break;
			}			
			// モデルを描画する
			m_cube->Draw(m_basicEffect, m_inputLayout);
		}
	}
}

// 後始末をする
void CubeMap::Finalize() noexcept
{
	// CorkBoardテクスチャを解放する
	m_corkBoard.Reset();
	// Grassテクスチャを解放する
	m_grass.Reset();
	// GeometricPrimitiveオブジェクトを解放する
	m_cube.reset();
}
