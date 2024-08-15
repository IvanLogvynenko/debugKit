#include <iostream>

#include "Logger.hpp"
#include "LogMessage.hpp"

int main() {
	Logger logger("main()");
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	logger << "placeholder";
	// auto mes = LogMessage("some", "main");
	// std::cout << mes.print(false) << std::endl;
}