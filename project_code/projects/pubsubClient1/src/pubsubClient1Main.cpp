#include <iostream>
#include <thread>
#include <chrono>

#include "zmq.hpp"
#include "zmq_addon.hpp"




int main(int argc, char** argv)
{
	//prepare subscriber
	/*zmq::socket_t subscriber(*pctx, zmq::socket_type::sub);
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
	}*/
	

	

	zmq::context_t subContex(1);
	zmq::socket_t subscribeSocket(subContex, zmq::socket_type::sub);
	subscribeSocket.connect("tcp://127.0.0.1:8976");


	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	subscribeSocket.set(zmq::sockopt::subscribe, "AAAA");

	while (true)
	{
		std::vector<zmq::message_t> recvMsgs;
		zmq::recv_result_t result = zmq::recv_multipart(subscribeSocket, std::back_inserter(recvMsgs));

		std::cout << recvMsgs[0].to_string() << "==" << recvMsgs[1].to_string() << std::endl;
	}

	system("pause");
	return 0;
}