#include <iostream>
#include <fstream>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <string.h>

using namespace rapidjson;
class Sensor {
    public:
        std::string ip, dump, toString;
        double positionX, positionY;
    public:
        void print() {std::cout << "sensor of ip " << ip <<  std::endl; }
};

int main() {
    // 1. Parse a JSON string into DOM.
    const char* json = "{\"sensors\":[{\"ip\":\"127.0.0.1\",\"positionX\":1,\"positionY\":2,\"dump\":\"dsa\",\"toString\":\"dsa\"}]}";
    Document document;
    document.Parse(json);

    // 2. Get number of sensor connected
    const Value& sensors = document["sensors"];
    std::cout << sensors.Size() << std::endl;

    // 3. Modify it by DOM.
    for (SizeType i = 0; i < sensors.Size(); i++){
        Sensor sen;
        const Value& sensor = sensors[i];
        for (Value::ConstMemberIterator iter = sensor.MemberBegin(); iter != sensor.MemberEnd(); ++iter) {
            std::string attName = iter->name.GetString();
            if (attName.compare("ip") == 0) {
                sen.ip = iter->value.GetString();
            }
            if (attName.compare("positionX") == 0) {
                std::cout << attName << " : " << iter->value.GetDouble() << std::endl;
            }
            if (attName.compare("positionY") == 0) {
                std::cout << attName << " : " << iter->value.GetDouble() << std::endl;
            }
            if (attName.compare("dump") == 0) {
                std::cout << attName << " : " << iter->value.GetString() << std::endl;
            }
            if (attName.compare("toString") == 0) {
                std::cout << attName << " : " << iter->value.GetString() << std::endl;
            }
        }
        sen.print();
    }

    return 1;
}
