#pragma once

namespace GenericBoson
{
	template<typename T>
	class Readable : public T {};

	template<typename T>
	class Writable : public T {};

	class GenericBoson {};

	using GenericBosonPtr = std::shared_ptr<GenericBoson>;
}