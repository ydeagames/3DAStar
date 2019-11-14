#ifndef IDLING_DEFINED
#define IDLING_DEFINED

#include "StepTimer.h"

#include "Enemy.h"
#include "IState.h"

class Enemy;

class Idling : public IState
{
public:
	// �R���X�g���N�^
	Idling() noexcept;
	// ����������
	int Initialize(IObject* object) noexcept;
	// �X�V����
	int Update(const DX::StepTimer& timer) noexcept;
	// �`�悷��
	void Render(const DX::StepTimer& timer) noexcept;
	// ��n��������
	void Finalize() noexcept;
private:
	// Enemy�I�u�W�F�N�g�ւ̃|�C���^
	Enemy* m_enemy;
};

#endif	// IDLING_DEFINED

