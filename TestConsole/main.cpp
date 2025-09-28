#include <iostream>
#include <thread>

#include <boost/asio.hpp>

int main()
{
	boost::asio::io_context ioContext;
	boost::asio::ip::tcp::socket socket(ioContext);

	boost::asio::ip::tcp::resolver resolver(ioContext);

	boost::asio::async_connect(socket, resolver.resolve("127.0.0.1", "8001"),
		[](boost::system::error_code error, boost::asio::ip::tcp::endpoint)
		{
			if (error)
			{
				std::cout << "Connect failed: " << error.message() << std::endl;
			}
			else
			{
				std::cout << "Connected to server." << std::endl;
			}
		});

	std::thread t([&ioContext] { ioContext.run(); });

	static_cast<void>(getchar());

	ioContext.stop();

	t.join();
	
	return 0;
}