#include <stdlib.h>
#include "tinyjson.h"

namespace TinyJson {

TinyJson::TinyJson()
{
    m_root = NULL;
    return;
}

TinyJson::~TinyJson()
{
    cJSON_Delete(m_root);
    return;
}

bool TinyJson::startObject()
{
    cJSON *obj = cJSON_CreateObject();
    if (NULL == obj)
    {
        return false;
    }

    int ret = 1;
    if (NULL == m_root)
    {
        m_root = obj;
    }
    else
    {
        cJSON *parent = m_stack.top();
        if (cJSON_Object == parent->type)
        {
            ret = cJSON_AddItemToObject(parent, m_key.c_str(), obj);
            m_key.clear();
        }
        else if (cJSON_Array == parent->type)
        {
            ret = cJSON_AddItemToArray(parent, obj);
        }
        else
        {
            ret = 0;
        }
    }

    m_stack.push(obj);
    return ret;
}

void TinyJson::endObject()
{
    m_stack.pop();
    return;
}

bool TinyJson::startArray()
{
    cJSON *array = cJSON_CreateArray();
    if (NULL == array)
    {
        return false;
    }

    int ret = 1;
    if (NULL == m_root)
    {
        m_root = array;
    }
    else
    {
        cJSON *parent = m_stack.top();
        if (cJSON_Object == parent->type)
        {
            ret = cJSON_AddItemToObject(parent, m_key.c_str(), array);
            m_key.clear();
        }
        else if (cJSON_Array == parent->type)
        {
            ret = cJSON_AddItemToArray(parent, array);
        }
        else
        {
            ret = 0;
        }
    }

    m_stack.push(array);
    return ret;
}

void TinyJson::endArray()
{
    m_stack.pop();
    return;
}

bool TinyJson::addKey(const std::string &key)
{
    cJSON *parent = m_stack.top();
    if (cJSON_Object != parent->type)
    {
        return false;
    }

    m_key = key;

    return true;
}

bool TinyJson::addInt(const int value)
{
    cJSON *num = cJSON_CreateNumber((double)value);
    if (NULL == num)
    {
        return false;
    }

    cJSON *parent = m_stack.top();
    int ret = 0;
    if (cJSON_Object == parent->type)
    {
        ret = cJSON_AddItemToObject(parent, m_key.c_str(), num);
        m_key.clear();
    }
    else if (cJSON_Array == parent->type)
    {
        ret = cJSON_AddItemToArray(parent, num);
    }

    return ret;
}

bool TinyJson::addDouble(const double value)
{
    cJSON *num = cJSON_CreateNumber(value);
    if (NULL == num)
    {
        return false;
    }

    cJSON *parent = m_stack.top();
    int ret = 0;
    if (cJSON_Object == parent->type)
    {
        ret = cJSON_AddItemToObject(parent, m_key.c_str(), num);
        m_key.clear();
    }
    else if (cJSON_Array == parent->type)
    {
        ret = cJSON_AddItemToArray(parent, num);
    }

    return ret;
}

bool TinyJson::addString(const std::string &value)
{
    cJSON *str = cJSON_CreateString(value.c_str());
    if (NULL == str)
    {
        return false;
    }

    cJSON *parent = m_stack.top();
    int ret = 0;
    if (cJSON_Object == parent->type)
    {
        ret = cJSON_AddItemToObject(parent, m_key.c_str(), str);
        m_key.clear();
    }
    else if (cJSON_Array == parent->type)
    {
        ret = cJSON_AddItemToArray(parent, str);
    }

    return ret;
}

bool TinyJson::addBool(const bool value)
{
    cJSON *item = cJSON_CreateBool((int)value);
    if (NULL == item)
    {
        return false;
    }

    cJSON *parent = m_stack.top();
    int ret = 0;
    if (cJSON_Object == parent->type)
    {
        ret = cJSON_AddItemToObject(parent, m_key.c_str(), item);
        m_key.clear();
    }
    else if (cJSON_Array == parent->type)
    {
        ret = cJSON_AddItemToArray(parent, item);
    }

    return ret;
}

bool TinyJson::addNull()
{
    cJSON *none = cJSON_CreateNull();
    if (NULL == none)
    {
        return false;
    }

    cJSON *parent = m_stack.top();
    int ret = 0;
    if (cJSON_Object == parent->type)
    {
        ret = cJSON_AddItemToObject(parent, m_key.c_str(), none);
        m_key.clear();
    }
    else if (cJSON_Array == parent->type)
    {
        ret = cJSON_AddItemToArray(parent, none);
    }

    return ret;
}

bool TinyJson::addRaw(const std::string &value)
{
    cJSON *raw = cJSON_CreateRaw(value.c_str());
    if (NULL == raw)
    {
        return false;
    }

    cJSON *parent = m_stack.top();
    int ret = 0;
    if (cJSON_Object == parent->type)
    {
        ret = cJSON_AddItemToObject(parent, m_key.c_str(), raw);
        m_key.clear();
    }
    else if (cJSON_Array == parent->type)
    {
        ret = cJSON_AddItemToArray(parent, raw);
    }

    return ret;
}

std::string TinyJson::print()
{
    char *data = cJSON_Print(m_root);
    std::string str = data;
    free(data);
    return str;
}

}
