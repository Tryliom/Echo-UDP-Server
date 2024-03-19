#include "Logger.h"

#include <SFML/Network.hpp>

#include <cstdlib>

int main()
{
	sf::UdpSocket socket;

	// bind the socket to a port
	if (socket.bind(PORT) != sf::Socket::Done)
	{
		return EXIT_FAILURE;
	}

	// set the socket to non-blocking mode
	socket.setBlocking(false);

	while (true)
	{
		// receive a ping from anyone
		sf::IpAddress sender;
		unsigned short port;
		char data[100];
		std::size_t received;

		if (socket.receive(data, sizeof(data), received, sender, port) == sf::Socket::Done)
		{
			LOG("Received " << data << " from " << sender << ':' << port);

			// send a pong to the sender
			socket.send(data, received, sender, port);

			LOG("Sent " << data << " to " << sender << ':' << port);
		}
	}


	return EXIT_SUCCESS;
}