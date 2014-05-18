#include "SMTPserver.h"
#include "EmailRequest.h"

#include <SFML/Network.hpp>
#include <iostream>
#include <fstream>

void SMTPserver::Terminate()
{
	running = false;
	SaveToFile();
}

void SMTPserver::SendEmails()
{
	while (running){
		std::cout << "Sender is running\n";

		//The smtp sender should be here.

		sf::sleep(sf::milliseconds(100));
	}
}

void SMTPserver::ReciveRequest()
{
	LoadFromFile();

	sf::TcpListener listener;
	sf::Socket::Status connectionStatus;

	while (listener.listen(3245) != sf::Socket::Done){
		std::cout << "Connection error";

		sf::sleep(sf::milliseconds(100));
	}

	while (running){
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
				taskLock.lock();

				//we recive the data from the socket
				client.receive(recived);

				Email recivedEmail;
				recived >> recivedEmail;	//we uppack the racived data

				taskQueue.push(recivedEmail);	//we save the recived email

				taskLock.unlock();
			}
		}

		sf::sleep(sf::milliseconds(100));
	}
}

SMTPserver::SMTPserver() :ReciveThread(&SMTPserver::ReciveRequest, this),
SendThread(&SMTPserver::SendEmails, this)
{
	running = true;

	ReciveThread.launch();
	sf::sleep(sf::milliseconds(100));
	SendThread.launch();
}

void SMTPserver::SaveToFile()
{
	std::ofstream file(".\\tasks.dat");		//relativa path to the file

	for (int i = 0; i < taskQueue.size(); i++){
		file << taskQueue._Get_container()[i].getSenderAddress() << std::endl;
		file << taskQueue._Get_container()[i].getReciverAddress() << std::endl;
		file << taskQueue._Get_container()[i].getEmailSubject() << std::endl;
		file << taskQueue._Get_container()[i].getEmailBody() << std::endl;
	}

	file.close();
}

void SMTPserver::LoadFromFile()
{
	std::ifstream file(".\\tasks.dat");		//relativa path to the file

	std::string emailSubject;
	std::string emailBody;
	std::string senderAddress;
	std::string reciverAddress;

	for (int i = 0; i < taskQueue.size(); i++){
		file >> senderAddress;
		file >> reciverAddress;
		file >> emailSubject;
		file >> emailBody;
		
		taskQueue.push(Email(emailSubject, emailBody, senderAddress, reciverAddress));
	}

	

	file.close();
}