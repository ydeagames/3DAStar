#ifndef ISTATE_DEFINED
#define ISTATE_DEFINED

#include "StepTimer.h"
#include "IObject.h"

constexpr int SUCCESS = 0;
constexpr int FAILURE = -1;

class IObject;

class IState
{
public:
	// ����������
	virtual int Initialize(IObject* object) noexcept = 0;
	// �X�V����
	virtual int Update(const DX::StepTimer& timer) noexcept = 0;
	// �`�悷��
	virtual void Render(const DX::StepTimer& timer) noexcept = 0;
	// ��n��������
	virtual void Finalize() noexcept = 0;
	// �f�X�g���N�^
	virtual ~IState() = 0;
};
inline IState::~IState(){}

#endif	// ISTATE

