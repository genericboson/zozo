#pragma once

namespace GenericBoson
{
	template<typename T>
	class Readable : public T {};

	template<typename T>
	class Writable : public T {};

	class EmptyBoson {
		virtual Execute(DBResult& dbResult)->asio::awaitable<bool> = 0;
	};

	using EmptyBosonPtr = std::shared_ptr<EmptyBoson>;
}