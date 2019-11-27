#ifndef ENEMY_DEFINED
#define ENEMY_DEFINED

#include <d3d11.h>
#include <SimpleMath.h>

#include "Position.h"
#include "IObject.h"
#include "IState.h"
#include "Idling.h"
#include "Searching.h"
#include "Chasing.h"

#include "Scene.h"

class Idling;
class Searching;
class Chasing;
class Scene;

class Enemy : public IObject
{
public:
	// Idling��Ԃ��擾����
	Idling* GetIdlingState() const 
	{
		return m_idlingState.get();
	}

	// Searching��Ԃ��擾����
	Searching* GetSearchingState() const
	{
		return m_searchingState.get();
	}

	// Chasing��Ԃ��擾����
	Chasing* GetChasingState() const
	{
		return m_chasingState.get();
	}

	// �ʒu���擾����
	DirectX::SimpleMath::Vector3 GetVectorPosition() const
	{
		return m_position;
	}

	// �ʒu��ݒ肷��
	void SetVectorPosition(const DirectX::SimpleMath::Vector3& position)
	{
		m_position = position;
	}
	
	// �J�n�ʒu���擾����
	Position GetStartPosition() const
	{
		return m_startPosition;
	}
	
	// �J�n�ʒu��ݒ肷��
	void SetStartPosition(const Position& startPosition)
	{
		m_startPosition = startPosition;
	}

	// �I���ʒu���擾����
	Position GetEndPosition() const
	{
		return m_endPosition;
	}

	// �I���ʒu��ݒ肷��
	void SetEndPosition(const Position& endPosition)
	{
		m_endPosition = endPosition;
	}
	
	// �ŒZ�o�H���擾����
	std::vector<Position> GetRoute() const
	{
		return m_route;
	}
	
	// �R���X�g���N�^
	Enemy(Scene* scene) noexcept;
	// ����������
	int Initialize() noexcept override;
	// �X�V����
	int Update(const DX::StepTimer& timer) noexcept override;
	// �`�悷��
	void Render(const DX::StepTimer& timer, 
		const DirectX::SimpleMath::Matrix& view, 
		const DirectX::SimpleMath::Matrix& projection) noexcept override;
	// ��n��������
	void Finalize() noexcept override;
	// ��Ԃ�ύX����
	void ChangeState(IState* state);

private:
	// �A�C�h�����
	std::unique_ptr<Idling> m_idlingState;
	// �T�����
	std::unique_ptr<Searching> m_searchingState;
	// �ǐՏ��
	std::unique_ptr<Chasing> m_chasingState;
	// ���݂̏��
	IState* m_currentState;

	// �e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	// �}�b�v
	ITiledMap* m_tiledMap;

	// �J�n�ʒu
	Position m_startPosition;
	// �I���ʒu
	Position m_endPosition;
	// �ŒZ�o�H
	std::vector<Position> m_route;

	// �ʒu
	DirectX::SimpleMath::Vector3 m_position;
	// �ʒu
	DirectX::SimpleMath::Vector3 m_position_end;
	// �ړ��s��
	DirectX::SimpleMath::Matrix m_translation;
	// ���f���I�u�W�F�N�g
	std::unique_ptr<DirectX::GeometricPrimitive> m_primitive;
	// �x�C�V�b�N�G�t�F�N�g
	DirectX::BasicEffect* m_basicEffect;
	// �C���v�b�g���C�A�E�g
	ID3D11InputLayout* m_inputLayout;
	// Scene�I�u�W�F�N�g�ւ̃|�C���^
	Scene* m_scene;

	// DirectX11�N���X�̃C���X�^���X���擾����
	DirectX11& m_directX = DirectX11::Get();
};

#endif // ENEMY_DEFINED

