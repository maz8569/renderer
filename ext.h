#pragma once
#include <memory>


template <typename T>
using Ref = std::shared_ptr<T>;

template<typename T, typename ... Args>
constexpr Ref<T> CreateRef(Args&& ... args)
{
	return std::make_shared<T>(std::forward<Args>(args)...);
}

template<typename T, typename ... Args>
constexpr Ref<T> Cast(Args&& ... args)
{
	return std::dynamic_pointer_cast<T>(std::forward<Args>(args)...);
}


template<class T>
constexpr const T& clamp(const T& v, const T& lo, const T& hi)
{
    return v < lo ? lo : v > hi ? hi : v;
}