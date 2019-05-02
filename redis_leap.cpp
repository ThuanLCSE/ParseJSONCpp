/**************************************************************************
   Copyright (c) 2017 sewenew

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
 *************************************************************************/

#include <unistd.h>
#include <iostream>
#include <sw/redis++/redis++.h>
using namespace sw::redis;
void print_help();
void _test_sub_channel(std::string host, std::string port, std::string channel) {
    try {
        std::string link = "tcp://";
        link.append(host);   //127.0.0.1
        link.append(":");
        link.append(port); //6379

        std::cout << "Listening to " << link << " channel: " << channel << std::endl;
        // Create an Redis object, which is movable but NOT copyable.
        auto redis = Redis(link);
        auto sub = redis.subscriber();

        // Set callback functi ons.
        sub.on_message([](std::string channel, std::string msg) {
            // Process message of MESSAGE type.
            std::cout << channel<< ":"<< msg << std::endl;
        });
        // Subscribe to channels
        sub.subscribe(channel);
        // Consume messages in a loop.
        while (true) {
            try {
                sub.consume();
            } catch (const Error &e) {
                std::cerr << "Error : " << e.what() << std::endl;
            }
        }
    } catch (const Error &e) {
        std::cerr << "Error : " << e.what() << std::endl;
    }
}

int main(int argc, char **argv) {
    try {
        std::string host,port,channel;
        int opt = 0;
        while ((opt = getopt(argc, argv, "h:p:c:")) != -1) {
            switch (opt) {
            case 'h':
                host = optarg;
                break;

            case 'p':
                port = optarg;
                break;

            case 'c':
                channel = optarg;
                break;

            default:
                print_help();
                throw sw::redis::Error("Failed to parse arguments options");
                break;
            }
        }
        if (host.empty()) {
            host = "127.0.0.1";
        }
        if (port.empty()) {
            port = "6379";
        }
        if (channel.empty()) {
            channel = "thuanleap";
        }
        _test_sub_channel(host,port,channel);
    } catch (const sw::redis::Error &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }
    return 0;
}
void print_help() {
    std::cerr << "Usage: test_redis++ -h host -p port"
        << " -n cluster_node -c cluster_port [-a auth] [-b]\n\n";
    std::cerr << "See https://github.com/sewenew/redis-plus-plus#run-tests-optional"
        << " for details on how to run test" << std::endl;
}
