#include <future>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#include "zmq.hpp"
#include "zmq_addon.hpp"


void publisherThread(zmq::context_t *pctx)
{
	//prepare publisher
	zmq::socket_t publisher(*pctx, zmq::socket_type::pub);
	publisher.bind("inproc://#1");

	//give the subscribes a change to connect, so they don't lose any messages
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	
	while (true)
	{
		publisher.send(zmq::str_buffer("A"), zmq::send_flags::sndmore);
		publisher.send(zmq::str_buffer("Message in A envelope"));
		publisher.send(zmq::str_buffer("B"), zmq::send_flags::sndmore);
		publisher.send(zmq::str_buffer("Message in B envelope"));
		publisher.send(zmq::str_buffer("C"), zmq::send_flags::sndmore);
		publisher.send(zmq::str_buffer("Message in C envelope"));

		std::this_thread::sleep_for(std::chrono::milliseconds(9000));
	}
}

void subscriberThread1(zmq::context_t* pctx)
{
	//prepare subscriber
	zmq::socket_t subscriber(*pctx, zmq::socket_type::sub);
	subscriber.connect("inproc://#1");

	//Thread2 opens "A" and "B" envelopes
	subscriber.set(zmq::sockopt::subscribe, "A");
	subscriber.set(zmq::sockopt::subscribe, "B");

	while (true)
	{
		//receive all parts of the message
		std::vector<zmq::message_t> recv_msgs;
		zmq::recv_result_t result = zmq::recv_multipart(subscriber, std::back_inserter(recv_msgs));

		assert(result && "recv failed");
		assert(*result == 2);
		
		std::cout << "Thread2:[" << recv_msgs[0].to_string() << "]==" 
			<< recv_msgs[1].to_string() << std::endl;
	}
}

void subscriberThread2(zmq::context_t* pctx)
{
	//prepare our context and subscirber
	zmq::socket_t subscriber(*pctx, zmq::socket_type::sub);
	subscriber.connect("inproc://#1");

	//Thread3 opens all envelopes
	subscriber.set(zmq::sockopt::subscribe, "");

	while (true)
	{
		//receive all parts of the message
		std::vector<zmq::message_t> recv_msgs;
		zmq::recv_result_t result = zmq::recv_multipart(subscriber, std::back_inserter(recv_msgs));

		assert(result && "recv failed");
		assert(*result == 2);

		std::cout << "Thread3:[" << recv_msgs[0].to_string() << "]===" <<
			recv_msgs[1].to_string() << std::endl;
	}
}

int main(int argc, char** argv)
{
	zmq::context_t ctx{ 0 };

	auto thread1 = std::async(std::launch::async, publisherThread, &ctx);      //这其实是一个future

	//give the publisher a chance to bind, since improc requires it
	std::this_thread::sleep_for(std::chrono::milliseconds(200));

	auto thread2 = std::async(std::launch::async, subscriberThread1, &ctx);
	auto thread3 = std::async(std::launch::async, subscriberThread2, &ctx);

	thread1.wait();
	thread2.wait();
	thread3.wait();
	

	return 0;
}