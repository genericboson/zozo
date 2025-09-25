#pragma once

#include <Engine/Tx/TxExecutor.h>

#include "Actor/IActor.h"

namespace GenericBoson
{
	class ISocket;
	class Zone;

	class Character : public IActor, public TxExecutor
	{
	public:
		Character(
			std::shared_ptr< ISocket > pSocket,
			std::weak_ptr< Zone >      wpZone);

		virtual ~Character() = default;

		int64_t Id() const override;
	private:
		int64_t                    m_id;
		std::shared_ptr< ISocket > m_pSocket;
		std::weak_ptr< Zone >      m_wpZone;
		
	};
}