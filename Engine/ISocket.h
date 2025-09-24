#pragma once

namesapce GenericBoson
{
	class ISocket
	{
	public:
		virtual ~ISocket() = default;
		virtual int64_t Id() const = 0;
	};
}