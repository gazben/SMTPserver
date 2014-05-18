#include "SMTPserver.h"

#include <SFML/Network.hpp>
#include <iostream>

void SMTPserver::Terminate()
{
	running = false;
}

void SMTPserver::SendEmails()
{
	while (running){
		std::cout << "Sender is running\n";

		sf::sleep(sf::milliseconds(100));
	}
}

void SMTPserver::ReciveRequest()
{
	sf::TcpListener listener;
	sf::Socket::Status connectionStatus;

	while (running){
		if (listener.listen(25) != sf::Socket::Done){
			std::cout << "Connection error";
		}
		else
		{
			std::cout << "Connection established";
			connectionStatus = sf::Socket::Done;
		}

		if (connectionStatus == sf::Socket::Done){
			sf::TcpSocket client;
			if (listener.accept(client) != sf::Socket::Done)
			{
				std::cout << "Connection error while establishing connection!";
			}
			else
			{
				//we established the connection
				taskLock.lock();

				//PROCESS THE DATA

				taskLock.unlock();
			}
		}

		std::cout << "Reciver is running\n";

		sf::sleep(sf::milliseconds(100));
	}
}

SMTPserver::SMTPserver() :ReciveThread(&SMTPserver::ReciveRequest, this),
SendThread(&SMTPserver::SendEmails, this)
{
	running = true;

	ReciveThread.launch();
	SendThread.launch();
}