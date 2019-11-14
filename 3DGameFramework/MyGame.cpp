//#define _CRT_SECURE_NO_WARNINGS
#include "MyGame.h"

// �R���X�g���N�^
MyGame::MyGame(int width, int height) noexcept : m_width(width), m_height(height), Game(width, height)
{
}

// MyGame�I�u�W�F�N�g����������
void MyGame::Initialize() noexcept
{
	// ���N���X��Initialize���Ăяo�� 
	Game::Initialize();

	// Keyboard�I�u�W�F�N�g�𐶐�����
	//KeyboardPrim::Get();
	// Mouse�I�u�W�F�N�g�𐶐�����
	MousePrim::Get();
	// DebugCamera�I�u�W�F�N�g�𐶐�����
	m_debugCamera = std::make_unique<DebugCamera>(m_width, m_height);
	
	// Scene�I�u�W�F�N�g�𐶐�����
	m_scene = std::make_shared<Scene>();

	// Scene�I�u�W�F�N�g������������
	m_scene->Initialize();
	// ���[���h�s�������������
	m_world = DirectX::SimpleMath::Matrix::Identity;
}

// ���\�[�X�𐶐�����
void MyGame::CreateResources() noexcept
{
	// ���N���X��CreateResources���Ăяo��
	Game::CreateResources();

	// �ˉe���W�ϊ��s��𐶐�����
	m_projection = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(DirectX::XMConvertToDegrees(60.0f),
		float(m_width) / float(m_height), 0.1f, 100.0f);
}

// �Q�[�����X�V����
void MyGame::Update(const DX::StepTimer& timer) noexcept
{
	// �o�ߎ��Ԃ��擾����
	float elapsedTime = float(timer.GetTotalSeconds());

	// DebugCamera�I�u�W�F�N�g���X�V����
	m_debugCamera->Update();
	// �f�o�b�O�J��������r���[�s��𐶐�����
	m_view = m_debugCamera->GetViewMatrix();
	// Scene�I�u�W�F�N�g���X�V����
	m_scene->Update(timer, m_view, m_projection);
}

// �Q�[����`�悷��
void MyGame::Render(const DX::StepTimer& timer) noexcept
{
	// �ŏ��̍X�V�̑O�͉����`�悵�Ȃ��悤�ɂ���
	if (timer.GetFrameCount() == 0) 
		return;

	// TODO: �����_�����O�R�[�h��ǉ�����
	// �o�b�t�@���N���A����
	Clear();
	// �V�[����`�悷��
	m_scene->Render(timer, m_view, m_projection);
	// �o�b�N�o�b�t�@��\������
	Present();
}

// ��n��������
void MyGame::Finalize() noexcept
{
	// Scene�I�u�W�F�N�g���������
	m_scene.reset();
	// DebugCamera�I�u�W�F�N�g��j������
	m_debugCamera.reset();

	// ���N���X��Finalize���Ăяo��
	Game::Finalize();
}

