#include "Enemy.h"

// �R���X�g���N�^
Enemy::Enemy(Scene* scene) noexcept
	: m_scene(scene)
	, m_startPosition(0, 0)
	, m_endPosition(0, 0)
	, m_position(0, .5f, .0f)
	, m_translation(DirectX::SimpleMath::Matrix::Identity)
{
	m_mapFile = scene->GetMapFile();
}

// ����������
int Enemy::Initialize() noexcept
{
	m_idlingState = std::make_unique<Idling>();
	m_idlingState->Initialize(this);

	m_searchingState = std::make_unique<Searching>(m_mapFile);
	m_searchingState->Initialize(this);

	m_chasingState = std::make_unique<Chasing>();
	m_chasingState->Initialize(this);

	ChangeState(m_idlingState.get());

	m_primitive = DirectX::GeometricPrimitive::CreateSphere(DirectX11::Get().GetContext().Get(), .8f, 16U, /*false*/true);
	m_basicEffect = m_scene->GetBasicEffect();
	m_primitive->CreateInputLayout(m_basicEffect, &m_inputLayout);
	DirectX::CreateWICTextureFromFile(m_directX.GetDevice().Get(), L"Resources/texture/concrete.png",
		nullptr, m_texture.ReleaseAndGetAddressOf());

	return SUCCESS;
}

// ��Ԃ�ύX����
void Enemy::ChangeState(IState * state)
{
	m_currentState = state;
}

// �X�V����
int Enemy::Update(const DX::StepTimer & timer) noexcept
{
	// ���݂̏�Ԃ��X�V����
	int result = m_currentState->Update(timer);

	// �u�T�[�`�v��ԁi�ŒZ�o�H�̒T����j�̍X�V��
	if (m_currentState == m_searchingState.get())
	{
	// ����ɍŒZ�o�H���T�����ꂽ���ǂ���
		if (result == SUCCESS)
		{
			// �ŒZ�o�H���擾����
			m_route = m_searchingState.get()->GetRoute();
			// ���݂̏�Ԃ��u�ǐՁv��ԂɕύX����
			ChangeState(m_chasingState.get());
		}
		else
		{
			// ���݂̏�Ԃ��u�A�C�h�����O�v��ԂɕύX����
			ChangeState(m_idlingState.get());
		}
	}
	// �u�ǐՁv��Ԃ�����I���̏ꍇ
	else if (m_currentState == m_chasingState.get())
	{
		// �u�ǐՁv��Ԃ�����I���̏ꍇ
		if (result == SUCCESS)
		{
			// �ǐՒ��i��Ԃ�ύX���Ȃ��j
		}
		else
		{
			// �ǐՂ��I�������̂Ō��݂̏�Ԃ��u�A�C�h�����O�v��ԂɕύX����
			ChangeState(m_idlingState.get());
		}
	}
	return 0;
}

// �`�悷��
void Enemy::Render(const DX::StepTimer & timer, const DirectX::SimpleMath::Matrix & view, const DirectX::SimpleMath::Matrix & projection) noexcept
{
	m_translation = DirectX::SimpleMath::Matrix::CreateTranslation(m_position);
	m_basicEffect->SetWorld(m_translation);
	m_basicEffect->SetView(view);
	m_basicEffect->SetProjection(projection);
	m_basicEffect->SetTexture(m_texture.Get());
	m_primitive->Draw(m_basicEffect, m_inputLayout);

	m_currentState->Render(timer);
}

// ��n��������
void Enemy::Finalize() noexcept
{
}
