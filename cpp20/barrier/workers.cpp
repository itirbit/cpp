#include <iostream>
#include <mutex>
#include <barrier>
#include <string>
#include <thread>

std::barrier workDone(6);
std::mutex coutMutex;

void syncOut(const std::string& s) noexcept
{
	std::lock_guard<std::mutex> lo(coutMutex);
	std::cout << s;
}

class Worker
{
public:
	Worker(std::string n): name(n) {};
	void operator()()
	{
		syncOut(name + ": Morning work done!\n");
		workDone.arrive_and_wait();
		syncOut(name + ": Afternoon work done!\n");
		workDone.arrive_and_wait();
	}
private:
	std::string name;
};

class PartTimeWorker
{
public:
	PartTimeWorker(std::string n): name(n){}
	
	void operator()()
	{
		syncOut(name + ": Morning work done!\n");
		workDone.arrive_and_drop();
	}
private: 
	std::string name;
};

int main()
{
	std::cout << '\n';

	Worker herb("  Herb");
	std::thread herbWork(herb);

	Worker scott("   Scott");
	std::thread scottWork(scott);

	Worker bjarne("       Bjarne");
	std::thread bjarneWork(bjarne);

	PartTimeWorker andrei("            Andrei");
	std::thread andreWork(andrei);

	PartTimeWorker andrew("               Andrew");
	std::thread andrewWork(andrew);

	PartTimeWorker david("                   David");
	std::thread davidWork(david);


	herbWork.join();
	scottWork.join();
	bjarneWork.join();
	andreWork.join();
	davidWork.join();

}









