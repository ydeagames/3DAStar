#include "Scene.h"

// コンストラクタ
Scene::Scene() noexcept/* : m_mapFile("map.csv")*/ // マップファイルをSceneオブジェクトで決定する
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

	// TitledMpaオブジェクトを生成する
	m_tiledMap = std::make_unique<TiledMap>();
	// TitledMpaオブジェクトを初期化する
	//m_tiledMap->Load(m_mapFile);
	m_tiledMap->SetSize(11, 11);
	m_tiledMap->Generate(5, 5);

	// CubeMapオブジェクトを生成する
	m_cubeMap = std::make_unique<CubeMap>(this);
	// CubeMapオブジェクトを初期化する
	m_cubeMap->Initialize();
	m_cubeMap->InitializeMap(GetMap());

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
		auto rand_odd = [](int min, int max) {
			min = min / 2 * 2 + 1;
			max = (max + 1) / 2 * 2 - 1;
			int rnd = rand() % (max - min) + min;
			rnd = rnd / 2 * 2 + 1;
			return rnd;
		};

		Position pos1, pos2;
		GetMap()->SetSize(rand_odd(10, 30), rand_odd(10, 30));
		pos2 = GetMap()->Generate(pos1.column = rand_odd(1, GetMap()->GetMapColumn() - 1), pos1.row = rand_odd(1, GetMap()->GetMapRow() - 1));
		m_cubeMap->InitializeMap(GetMap());

		/*
		{
			std::vector<Position> candidates;

			auto& map = m_tiledMap->GetMap();
			int mapRow = m_tiledMap->GetMapRow();
			int mapColumn = m_tiledMap->GetMapColumn();
			for (int row = 0; row < mapRow; row++)
			{
				for (int column = 0; column < mapColumn; column++)
				{
					if (map[row][column] == 0)
					{
						// マスを登録
						candidates.push_back(Position(row, column));
					}
				}
			}

			size_t size = candidates.size();
			size_t num1 = rand() % size;
			size_t num2 = rand() % (size - 1);
			if (num1 <= num2) num2++;

			pos1 = candidates[num1];
			pos2 = candidates[num2];
		}
		*/

		m_enemy->SetStartPosition(pos1);
		m_enemy->SetEndPosition(pos2);
		//m_enemy->SetStartPosition(Position(2, 2));
		//m_enemy->SetEndPosition(Position(9, 9));
		std::stringstream sb;
		sb << "Start: {" << "X: " << m_enemy->GetStartPosition().row << "Y: " << m_enemy->GetStartPosition().column << "}, ";
		sb << "End: {" << "X: " << m_enemy->GetEndPosition().row << "Y: " << m_enemy->GetEndPosition().column << "}";
		SetWindowTextA(DirectX11::Get().GetHWnd(), sb.str().c_str());


		m_enemy->GetSearchingState()->InitializeMap();
		m_enemy->GetSearchingState()->GetAstar()->ClearMap();
		m_enemy->GetChasingState()->Interrupt();
		m_enemy->ChangeState(m_enemy->GetSearchingState());
	}

	// 矢印を押下げた場合
	Position move;
	if (m_keyboardStateTracker->IsKeyPressed(DirectX::Keyboard::Keys::Up))
		move = Position{ move.row - 1, move.column };
	if (m_keyboardStateTracker->IsKeyPressed(DirectX::Keyboard::Keys::Down))
		move = Position{ move.row + 1, move.column };
	if (m_keyboardStateTracker->IsKeyPressed(DirectX::Keyboard::Keys::Left))
		move = Position{ move.row, move.column - 1 };
	if (m_keyboardStateTracker->IsKeyPressed(DirectX::Keyboard::Keys::Right))
		move = Position{ move.row, move.column + 1 };
	if (!(move == Position()))
	{
		auto route = m_enemy->GetChasingState()->m_route;
		auto p = m_enemy->GetEndPosition();
		if (route.size() > 0)
			m_enemy->SetStartPosition(route[0]);
		m_enemy->SetEndPosition(Position{ p.row + move.row, p.column + move.column });

		m_enemy->GetSearchingState()->InitializeMap();
		m_enemy->GetSearchingState()->GetAstar()->ClearMap();
		m_enemy->GetChasingState()->ResetRoute();
		m_enemy->ChangeState(m_enemy->GetSearchingState());
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