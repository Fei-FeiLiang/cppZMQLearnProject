#include <iostream>
#include <chrono>
#include <iostream>
#include <thread>


#include "zmq.hpp"


int main(int arcg, char** argv)
{
	zmq::context_t context(1);

	zmq::socket_t serverSocket(context, zmq::socket_type::pub);
	serverSocket.bind("tcp://*:8976");

	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	 
	while (true)
	{
		serverSocket.send(zmq::str_buffer("AAAA"), zmq::send_flags::sndmore);
		serverSocket.send(zmq::str_buffer("Message in AAAA envelope"));

		serverSocket.send(zmq::str_buffer("BBBB"), zmq::send_flags::sndmore);
		serverSocket.send(zmq::str_buffer("Message in BBBB envelope"));

		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	}


	system("pause");

	return 0;

}