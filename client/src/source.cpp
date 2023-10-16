#include <chrono>
#include <format>
#include <iostream>
#include <string>
#include <zmq.hpp>

int main() {
	using namespace std::chrono_literals;

	zmq::context_t context{1};

	zmq::socket_t socket{context, zmq::socket_type::req};
	socket.connect("tcp://localhost:8426");

	for (auto request_num = 0; request_num < 10; request_num++) {
		std::string message = std::format("World {}", request_num);
		std::cout << std::format("({})->{}...\n", request_num, message);

		auto result = socket.send(zmq::buffer(message), zmq::send_flags::none);

		if (result) {
			zmq::message_t reply;
			auto result = socket.recv(reply, zmq::recv_flags::none);
			if (result) {
				std::cout << std::format("({}) <- {}\n", request_num,
				                         reply.to_string());
			} else {
				std::cout << "Error: " << zmq_strerror(zmq_errno()) << '\n';
			}
		} else {
			std::cout << "Error: " << zmq_strerror(zmq_errno()) << '\n';
		}
	}
}