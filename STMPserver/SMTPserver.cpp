#include "SMTPserver.h"
#include "EmailRequest.h"

#include <SFML/Network.hpp>
#include <iostream>

void SMTPserver::Terminate()
{
	running = false;

}

void SMTPserver::SendEmails()
{
	// 	while (running){
	// 		std::cout << "Sender is running\n";
	//
	// 		sf::sleep(sf::milliseconds(100));
	// 	}
}

void SMTPserver::ReciveRequest()
{
	sf::TcpListener listener;
	sf::Socket::Status connectionStatus;

	//listener.setBlocking(false);

	while (listener.listen(3245) != sf::Socket::Done){
		std::cout << "Connection error";

		sf::sleep(sf::milliseconds(100));
	}

	while (running){
		std::cout << "Connection established";
		connectionStatus = sf::Socket::Done;

		if (connectionStatus == sf::Socket::Done){
			sf::TcpSocket client;
			if (listener.accept(client) != sf::Socket::Done)
			{
				std::cout << "Connection error while establishing connection!";
			}
			else
			{
				sf::Packet recived;
				//we established the connection
				//taskLock.lock();

				client.receive(recived);



				Email recivedEmail;
				recived >> recivedEmail;

				recivedEmail.toString();

				taskQueue.push(recivedEmail);

				//taskLock.unlock();
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