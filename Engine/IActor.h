#pragma once

namespace GenericBoson
{
	class IActor
	{
	public:
		virtual ~IActor() = default;
		virtual int64_t Id() const = 0;

		virtual void OnDisconnected() = 0;
	};
}