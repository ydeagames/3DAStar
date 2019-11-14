#pragma once
#ifndef SCENE_DEFINED
#define SCENE_DEFINED

#include <d3d11.h>
#include <Effects.h>
#include "DirectX11.h"
#include <memory.h>
#include <Keyboard.h>
#include "Enemy.h"
#include "CubeMap.h"
#include "Position.h"

class MyGame;
class CubeMap;

class Scene 
{
public:
	// �}�b�v�t�@�C�����擾����
	string GetMapFile() const
	{
		return m_mapFile;
	}
	// �x�C�V�b�N�G�t�F�N�g
	DirectX::BasicEffect* GetBasicEffect() 
	{
		return m_basicEffect.get();
	}
	// �C���v�b�g���C�A�E�g
	ID3D11InputLayout* GetInputLayout()
	{
		return m_inputLayout.Get();
	}
	// �R���X�g���N�^
	Scene() noexcept;
	// ����������
	void Initialize() noexcept;
	// �X�V����
	void Update(const DX::StepTimer& timer, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) noexcept;
	// �`�悷��
	void Render(const DX::StepTimer& timer, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) noexcept;
	// ��n��������
	void Finalize() noexcept;

private:
	// �L�[�{�[�h
	std::unique_ptr<DirectX::Keyboard> m_keyboard;
	// �L�[�{�[�h�X�e�[�g�g���b�J�[
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker> m_keyboardStateTracker;
	// �r���[�s��
	DirectX::SimpleMath::Matrix m_view;
	// �v���W�F�N�V�����s��
	DirectX::SimpleMath::Matrix m_projection;
	// �x�C�V�b�N�G�t�F�N�g
	std::unique_ptr<DirectX::BasicEffect> m_basicEffect;
	// �C���v�b�g���C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	// �L���[�u�}�b�v
	std::unique_ptr<CubeMap> m_cubeMap;
	// �G
	std::unique_ptr<Enemy> m_enemy;
	// �}�b�v�t�@�C��
	std::string m_mapFile;

	// DirectX11�N���X�̃C���X�^���X���擾����
	DirectX11& m_directX = DirectX11::Get();
};

#endif	// SCENE_DEFINED