#ifndef SMTPserver_h__
#define SMTPserver_h__

#include <SFML/System.hpp>

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
};
#endif // SMTPserver_h__