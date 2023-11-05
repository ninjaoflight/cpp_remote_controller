#include "SDL_error.h"
#include <chrono>
#include <controller.hpp>
#include <format>
#include <iostream>
#include <string>
#include <zmq.hpp>

int main(int argc, char **argv) {
	using namespace std::chrono_literals;
	// check if there is a command line argument for the server address
	std::string server_address = "tcp://localhost:8426";

	if (argc > 2) {
		std::cout << std::format("Usage: {} <server address>\n", argv[0]);
		std::cout << std::format("Example: {} {}\n", argv[0], server_address);
		return 1;
	}

	if (argc == 2) {
		server_address = argv[1];
	}

	Controller controller;

	if (!controller.setController()) {
		if (controller.getControllers().size() == 0) {
			std::cout << "No controllers connected\n";
		} else {
			std::cout << "Error: " << SDL_GetError() << '\n';
		}
		return 1;
	} else {
		std::cout << "Controller connected\n";
		std::cout << std::format("Controller name: {}\n",
		                         controller.getControllerName());
	}

	zmq::context_t context{1};

	zmq::socket_t socket{context, zmq::socket_type::req};
	socket.connect(server_address);

	std::string message = "";

	std::cout << ">";
	while (std::cin >> message) {
		if (message == "exit") {
			break;
		}
		auto result = socket.send(zmq::buffer(message), zmq::send_flags::none);

		if (result) {
			zmq::message_t reply;
			auto result = socket.recv(reply, zmq::recv_flags::none);
			if (result) {
				std::cout << std::format("-[Server]> {}\n", reply.to_string());
			} else {
				std::cout << "Error: " << zmq_strerror(zmq_errno()) << '\n';
			}
		} else {
			std::cout << "Error: " << zmq_strerror(zmq_errno()) << '\n';
		}
		std::cout << ">";
	}
}