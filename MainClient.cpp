#include "Logger.h"

#include <SFML/Network.hpp>

#include <cstdlib>

int main()
{
	sf::UdpSocket socket;
	socket.setBlocking(false);

	sf::IpAddress server = HOST_NAME;
	unsigned short port = PORT;

	for (int i = 0; i < 5; ++i)
	{
		// send a packet to the server
		char data[100] = "Ping";
		if (socket.send(data, sizeof(data), server, port) != sf::Socket::Done)
		{
			return EXIT_FAILURE;
		}

		// wait for a response for 5 seconds
		sf::Clock timeout;

		while (timeout.getElapsedTime().asSeconds() < 5)
		{
			char buffer[100];
			std::size_t received;
			sf::IpAddress sender;
			unsigned short senderPort;

			if (socket.receive(buffer, sizeof(buffer), received, sender, senderPort) == sf::Socket::Done)
			{
				LOG("Received " << buffer << " from " << sender << ':' << senderPort << " in " << timeout.getElapsedTime().asMilliseconds() << " ms.");
				break;
			}
		}

		if (timeout.getElapsedTime().asSeconds() >= 5)
		{
			LOG("Request timed out");
		}
	}

	return EXIT_SUCCESS;
}