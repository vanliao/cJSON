#ifndef TINYJSON_H
#define TINYJSON_H

#include <iostream>
#include <stack>
#include "cJSON.h"
#include "cJSON.h"

namespace TinyJson {

class TinyJson
{
public:
    TinyJson();
    ~TinyJson();

    bool startObject(void);
    void endObject(void);
    bool startArray(void);
    void endArray(void);
    bool addKey(const std::string &key);
    bool addInt(const int value);
    bool addDouble(const double value);
    bool addString(const std::string &value);
    bool addBool(const bool value);
    bool addNull(void);
    //not support binary
    bool addRaw(const std::string &value);

    std::string print(void);

private:
    cJSON *m_root;
    std::string m_key;
    std::stack<cJSON*> m_stack;
};

}

#endif // TINYJSON_H
