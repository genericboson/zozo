#pragma once

namesapce GenericBoson
{
	class Message;

	class ISocket
	{
	public:
		virtual ~ISocket() = default;

		virtual void Start() = 0;
		virtual void Write(const Message& msg) = 0;
	};
}