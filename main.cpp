#include <iostream>
#include <fstream>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <iostream>

using namespace rapidjson;

int main() {
    // 1. Parse a JSON string into DOM.
    const char* json = "{\"project\":\"rapidjson\",\"stars\":10,\"arr\":[{\"a\":1},{\"a\":2}]}";
    Document document;
    document.Parse(json);

    // 2. Modify it by DOM.
    Value& s = document["stars"];
    s.SetInt(s.GetInt() + 1);
    Value& p = document["project"];
    std::cout << p.GetString() << std::endl;

    //Array of Object
    const Value& a = document["arr"];

    for (SizeType i = 0; i < a.Size(); i++){
        const Value& attribute = a[i];
        assert(attribute.IsObject()); // each attribute is an object
        for (Value::ConstMemberIterator itr2 = attribute.MemberBegin(); itr2 != attribute.MemberEnd(); ++itr2) {
            std::cout << itr2->name.GetString() << " : " << itr2->value.GetInt() << std::endl;
        }
    }

    // 3. Stringify the DOM
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    document.Accept(writer);

    // Output {"project":"rapidjson","stars":11}
    std::cout << buffer.GetString() << std::endl;
    return 0;
}
