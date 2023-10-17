#include <chrono>
#include <format>
#include <iostream>
#include <string>
#include <zmq.hpp>

int main() {
	using namespace std::chrono_literals;

	zmq::context_t context{1};

	zmq::socket_t socket{context, zmq::socket_type::rep};
	socket.bind("tcp://*:8426");

	while (true) {
		zmq::message_t request;

		auto result = socket.recv(request, zmq::recv_flags::none);

		if (result) {
			std::cout << std::format("-[Client]> {}\n", request.to_string());

			socket.send(
			    zmq::buffer(std::format("Hello {}!", request.to_string())),
			    zmq::send_flags::none);
		} else {
			std::cout << "Error: " << zmq_strerror(zmq_errno()) << '\n';
		}
	}
}