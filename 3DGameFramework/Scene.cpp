#include "Scene.h"

// �R���X�g���N�^
Scene::Scene() noexcept/* : m_mapFile("map.csv")*/ // �}�b�v�t�@�C����Scene�I�u�W�F�N�g�Ō��肷��
{
}

// ����������
void Scene::Initialize() noexcept
{
	// Keyboard�I�u�W�F�N�g�𐶐����� 
	m_keyboard = std::make_unique<DirectX::Keyboard>();
	// KeyboardStateTracker�I�u�W�F�N�g�𐶐�����
	m_keyboardStateTracker = std::make_unique<DirectX::Keyboard::KeyboardStateTracker>();

	// BasicEffect�I�u�W�F�N�g�𐶐�����
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

	// TitledMpa�I�u�W�F�N�g�𐶐�����
	m_tiledMap = std::make_unique<TiledMap>();
	// TitledMpa�I�u�W�F�N�g������������
	//m_tiledMap->Load(m_mapFile);
	m_tiledMap->SetSize(11, 11);
	m_tiledMap->Generate(5, 5);

	// CubeMap�I�u�W�F�N�g�𐶐�����
	m_cubeMap = std::make_unique<CubeMap>(this);
	// CubeMap�I�u�W�F�N�g������������
	m_cubeMap->Initialize();
	m_cubeMap->InitializeMap(GetMap());

	// Enemy�I�u�W�F�N�g�𐶐�����
	m_enemy = std::make_unique<Enemy>(this);
	// Enemy�I�u�W�F�N�g������������
	m_enemy->Initialize();
}


// �X�V����
void Scene::Update(const DX::StepTimer& timer, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) noexcept
{
	// �r���[�s���ݒ肷��
	m_view = view;
	// �v���W�F�N�V�����s���ݒ肷��
	m_projection = projection;


	// �L�[�{�[�h�̏�Ԃ��擾����
	DirectX::Keyboard::State state = m_keyboard->GetState();
	// �L�[�{�[�h��ԃg���b�J�[���X�V����
	m_keyboardStateTracker->Update(state);

	// SPACE�L�[�����������ꍇ
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
						// �}�X��o�^
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

	// �������������ꍇ
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

	// Enemy�I�u�W�F�N�g���X�V����
	m_enemy->Update(timer);
}

// �`�悷��
void Scene::Render(const DX::StepTimer& timer, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) noexcept
{
	// CubeMap�I�u�W�F�N�g��`�悷��
	m_cubeMap->Render(timer, m_view, m_projection);

	// Enemy�I�u�W�F�N�g��`�悷��
	m_enemy->Render(timer, view, projection);
}

// ��n��������
void Scene::Finalize() noexcept
{
	// Floor�I�u�W�F�N�g���������
	m_cubeMap.reset();
}