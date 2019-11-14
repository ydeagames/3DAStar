#pragma once
#ifndef NONCOPYABLE_DEFINED
#define NONCOPYABLE_DEFINED

// NonCopyable�N���X(More C++ Idioms)
// Effective C++ ������p���Ă���
// private�ȃR�s�[�R���X�g���N�^�ƃR�s�[������Z�q�����N���X

class NonCopyable 
{
protected:
	NonCopyable() = default;
	~NonCopyable() = default;
private:
	NonCopyable(const NonCopyable& nonCopyable) = delete;
	NonCopyable& operator =(const NonCopyable& nonCopyable) = delete;
};

#endif // NONCOPYABLE
