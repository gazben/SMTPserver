#ifndef SMTPserver_h__
#define SMTPserver_h__

#include <SFML/System.hpp>
#include <queue>

#include "EmailRequest.h"

class SMTPserver{
public:

	SMTPserver();

	void ReciveRequest();

	void SendEmails();

	void Terminate();

private:

	bool running;

	sf::Thread ReciveThread;
	sf::Thread SendThread;

	void SaveToFile();
	void LoadFromFile();


	sf::Mutex taskLock;
	std::queue<Email> taskQueue;
};
#endif // SMTPserver_h__