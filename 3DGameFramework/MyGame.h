#pragma once
#ifndef MYGAME_DEFINED
#define MYGAME_DEFINED

#include "Window.h"
#include "MousePrim.h"
#include "Game.h"
#include "DebugCamera.h"
#include "Scene.h"

class MyGame : public Game
{
public:
	// �R���X�g���N�^
	MyGame(int width, int height) noexcept;
	// Game�I�u�W�F�N�g����������
	void Initialize() noexcept override;
	// ���\�[�X�𐶐�����
	void CreateResources()noexcept override;
	// �Q�[�����X�V����
	void Update(const DX::StepTimer& timer) noexcept override;
	// �Q�[����`�悷��
	void Render(const DX::StepTimer& timer) noexcept override;
	// �I�������������Ȃ�
	void Finalize() noexcept override;

private:
	// ��
	int m_width;
	// ����
	int m_height;
	// ���[���h�s��
	DirectX::SimpleMath::Matrix m_world;
	// �r���[�s��
	DirectX::SimpleMath::Matrix m_view;
	// �ˉe�s��
	DirectX::SimpleMath::Matrix m_projection;

	// �X�v���C�g�o�b�`
	DirectX::SpriteBatch* m_spriteBatch;

	// �f�o�b�O�J����
	std::unique_ptr<DebugCamera> m_debugCamera;
	// �V�[��
	std::shared_ptr<Scene> m_scene;

	// DirectX11�N���X�̃C���X�^���X���擾����
	DirectX11& m_directX = DirectX11::Get();
};

#endif	// MYGAME_DEFINED