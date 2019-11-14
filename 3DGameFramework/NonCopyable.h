#pragma once
#ifndef NONCOPYABLE_DEFINED
#define NONCOPYABLE_DEFINED

// NonCopyableクラス(More C++ Idioms)
// Effective C++ から引用している
// privateなコピーコンストラクタとコピー代入演算子をもつクラス

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
