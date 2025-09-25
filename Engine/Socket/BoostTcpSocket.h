#pragma once

namespace GenericBoson
{
	class ISocket;

	class BoostTcpSocket : public ISocket
	{
		BoostTcpSocket(
			std::shared_ptr< boost::asio::ip::tcp::socket > pSocket);

		void Start() override;
		void Write(const Message& msg) override;

		void Close();
		bool IsOpen() const;

	private:
		std::shared_ptr< boost::asio::ip::tcp::socket > m_pSocket;
	};
}