#ifndef CHASING_DEFINED
#define CHASING_DEFINED

#include "math.h"
#include "Enemy.h"
#include "IState.h"
#include "StepTimer.h"

class Enemy;

class Chasing : public IState
{
public:
	// �R���X�g���N�^
	Chasing() noexcept;
	// ����������
	int Initialize(IObject* object) noexcept;
	// �X�V����
	int Update(const DX::StepTimer& timer) noexcept;
	// �`�悷��
	void Render(const DX::StepTimer& timer) noexcept;
	// ��n��������
	void Finalize() noexcept;
private:
	// �ŒZ�o�H
	std::vector<Position> m_route;
	// �ʒu
	DirectX::SimpleMath::Vector3 m_position;
	// Enemy�I�u�W�F�N�g�ւ̃|�C���^
	Enemy* m_enemy;
};

#endif	// CHASING_DEFINED
