#pragma once

namespace GenericBoson
{
	class IActor
	{
	public:
		virtual ~IActor() = default;
		virtual int64_t Id() const = 0;

		virtual void OnDisconnected() = 0;
		virtual void OnAccepted() = 0;
		
		virtual bool Initialize() = 0;

		virtual void Read(const uint8_t* pData, std::size_t dataSize) = 0;
	};
}