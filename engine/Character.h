#pragma once

#include <boost/asio/ip/tcp.hpp>

#include "TxExecutor.h"

namespace GenericBoson
{
	class Character : public TxExecutor
	{
	public:
		//Character(boost::asio::ip::tcp::socket socket, )

		int64_t Id() const;
	private:
		int64_t m_id;
	};
}