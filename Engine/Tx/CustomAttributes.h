#pragma once

namespace GenericBoson
{
	template<typename T>
	class Readable : public T {};

	template<typename T>
	class Writable : public T {};

	class EmptyBoson {};

	using EmptyBosonPtr = std::shared_ptr<EmptyBoson>;
}