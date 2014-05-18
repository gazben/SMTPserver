#include "SMTPserver.h"

#include <iostream>

void SMTPserver::Terminate()
{
	running = false;
}

void SMTPserver::SendEmails()
{
	while (running){
		std::cout << "Sender is running\n";

		sf::sleep(sf::milliseconds(1000));
	}

}

void SMTPserver::ReciveRequest()
{
	while (running){
		std::cout << "Reciver is running\n";

		sf::sleep(sf::milliseconds(500));
	}

}

SMTPserver::SMTPserver() :ReciveThread(&SMTPserver::ReciveRequest, this),
SendThread(&SMTPserver::SendEmails, this)
{
	running = true;

	ReciveThread.launch();
	SendThread.launch();
}