#include "Scene.h"

// �R���X�g���N�^
Scene::Scene() noexcept : m_mapFile("map.csv") // �}�b�v�t�@�C����Scene�I�u�W�F�N�g�Ō��肷��
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

	// CubeMap�I�u�W�F�N�g�𐶐�����
	m_cubeMap = std::make_unique<CubeMap>(this);
	// CubeMap�I�u�W�F�N�g������������
	m_cubeMap->Initialize(m_mapFile);

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