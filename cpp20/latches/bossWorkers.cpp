#include <iostream>
#include <mutex>
#include <latch>
#include <thread>

std::latch workDone(6);
std::latch goHome(1);
std::mutex coutMutex;

void syncOut(const std::string s)
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
		syncOut(name + ": Work done!\n");
		workDone.count_down();

		goHome.wait();
		syncOut(name + ": Good bye!\n");
	}
private:
	std::string name;
};

int main()
{
	std::cout << '\n';
	std::cout << "BOSS: START WORKING! \n";
	Worker herb("  Herb");
	std::thread herbWork(herb);

	Worker scott("   Scott");
	std::thread scottWork(scott);

	Worker bjarne("       Bjarne");
	std::thread bjarneWork(bjarne);

	Worker andrei("            Andrei");
	std::thread andreWork(andrei);

	Worker andrew("               Andrew");
	std::thread andrewWork(andrew);

	Worker david("                   David");
	std::thread davidWork(david);

	workDone.wait();
	std::cout << '\n';
	goHome.count_down();
	std::cout << "BOSS: GO HOME!\n";

	herbWork.join();
	scottWork.join();
	bjarneWork.join();
	andreWork.join();
	davidWork.join();

}









