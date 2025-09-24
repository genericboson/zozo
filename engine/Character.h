#pragma once

#include "TxExecutor.h"

namespace GenericBoson
{
	class ISocket;
	class Room;

	class Character : public TxExecutor
	{
	public:
		Character(
			std::shared_ptr< ISocket > pSocket,
			std::weak_ptr< Room >      wpRoom);

		int64_t Id() const;
	private:
		int64_t m_id;
		std::shared_ptr< ISocket > m_pSocket;
		std::weak_ptr< Room >      m_wpRoom;
		
	};
}