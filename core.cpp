#include <core.hpp>
#include <iostream>

namespace core
{
    Object::Object()
    {

    }
    Object::~Object()
    {

    }
    bool Object::parentExistance(String name)
    {
        return false;
    }

//------------------------------------------------------------------------------------------------------------------

    String::String()
    {

    }
    String::String(const String& value)
    {
        s = value.s;
    }
    String::String(String& value)
    {
        s = value.s;
    }
    String::String(std::string value)
    {
        s = value;
    }
    String::String(const char *value)
    {
        s = value;
    }
    std::string String::to_str()
    {
        return s;
    }
    char* String::c_str()
    {
        char* ss = (char*)s.c_str();
        return ss;
    }
    String::String(char *value)
    {
        s = value;
    }
    String::String(char value)
    {
        char cs[2];
        cs[0] = value;
        cs[1] = 0;
        s = cs;
    }
    String::String(std::size_t value)
    {
        s = std::to_string(value);
    }
    String::String(long double value)
    {
        s = std::to_string(value);
    }
    String::String(bool value)
    {
        s = (value)?"1":"0";
    }
    String::~String()
    {

    }
    char String::getChar(std::size_t index)
    {
        char ch(s[index]);
        return ch;
    }
    String String::getCharString(std::size_t index)
    {
        String mys = s[index];
        return mys;
    }
    void String::setChar(std::size_t index, char ch)
    {
        s[index] = ch;
    }
    void String::setChar(std::size_t index, String ch)
    {
        s[index] = ch.s.c_str()[0];
    }

    String String::operator+(String value)
    {
        std::string ss = this->s + value.s;
        String str(ss);
        return str;
    }
    String& String::operator=(const String& value)
    {
        this->s = value.s;
        return *this;
    }
    String operator+(const char* value, String stvalue)
    {
        String retString(value);
        retString += stvalue;
        return retString;
    }
    String String::operator+=(String value)
    {
        std::string ss = s += value.s;
        String str(ss);
        return str;
    }
    bool String::operator==(String value)
    {
        return s == value.s;
    }
    bool String::operator!=(String value)
    {
        return s != value.s;
    }
    bool String::operator>(String value)
    {
        return s > value.s;
    }
    bool String::operator>=(String value)
    {
        return s >= value.s;
    }
    bool String::operator<(String value)
    {
        return s < value.s;
    }
    bool String::operator<=(String value)
    {
        return s <= value.s;
    }
    std::size_t String::getLength()
    {
        return s.length();
    }
    String String::subString(std::size_t pos, std::size_t count)
    {
        String sss;
        try
        {
            std::string ss = s.substr(pos, count);
            sss = ss;
        }
        catch(std::exception& e)
        {
            std::cerr<< "Error w/ substring:" << e.what() << "\n";
            return "";
        }
        return sss;
    }
    String String::subString(std::size_t pos)
    {
        String sss;
        try
        {
            std::string ss = s.substr(pos);
            sss = ss;
        }
        catch(std::exception& e)
        {
            std::cerr<< "Error w/ substring:" << e.what() << "\n";
            return "";
        }
        return sss;
    }
    long long String::getPos(String str)
    {
        std::size_t len = str.getLength();
        if (len <= 0) return -1;
        for (std::size_t i = 0; i <= getLength() - len; i++)
        {
            String s = subString(i, len);
            if (s == str) return i;
        }
        return -1;
    }
    long long String::getPosBack(String str)
    {
        long long len = str.getLength();
        if (len <= 0) return -1;
        for (long long i = getLength() - len; i >= 0; i--)
        {
            String s = subString(i, len);
            if (s == str) return i;
        }
        return -1;
    }
    std::size_t String::find(const String& str, std::size_t start)
    {
        return s.find(str.s, start);
    }
    std::size_t String::toInt()
    {
        return std::stoll(s);
    }
    long double String::toFloat()
    {
        if (s == "") return 0;
        return stold(s);
    }

//------------------------------------------------------------------------------------------------------------------

    ParametList::ParametList()
    {

    }
    ParametList::~ParametList()
    {

    }
    void ParametList::addAttr(std::string name, std::string value)
    {
        parameters.insert(std::pair<std::string, std::string>(name, value));
    }
    void ParametList::addAttr(String name, String value)
    {
        parameters.insert(std::pair<std::string, std::string>(name.to_str(), value.to_str()));
    }

    std::size_t ParametList::Count()
    {
        return parameters.size();
    }

    String ParametList::Name(std::size_t i)
    {
        auto it = parameters.begin();
        for (std::size_t j = 0; j < i; ++j) ++it;
        return it->first;
    }

    String ParametList::Value(std::size_t i)
    {
        auto it = parameters.begin();
        for (std::size_t j = 0; j < i; ++j) ++it;
        return it->second;
    }

    String ParametList::Value(String name)
    {
        return parameters[name.to_str()];
    }

//------------------------------------------------------------------------------------------------------------------

    List::List()
        : count(0), cap(0), memory(NULL)
    {

    }
    List::~List()
    {
        memory = NULL;
    }
    void List::setMemory(std::size_t m)
    {
        cap = m;
        try
        {
            memory = (Object**)realloc(memory, sizeof(Object*) * cap);
        }
        catch(std::exception& e)
        {
            std::cerr << "Error w/ reallocation memory:" << e.what() << std::endl;
            memory = NULL;
            cap = 0;
        }

    }
    Object* List::add(Object *node)
    {
        if (memory == NULL || count >= cap)
            setMemory(cap + NODE_MEM_STEP);
        memory[count]=(Object*)node;
        ++count;
        return node;
    }
    void List::insert(std::size_t i, Object* node)
    {
        if (memory == NULL || count >= cap)
            setMemory(cap + NODE_MEM_STEP);
        for (std::size_t j = count-1; j >= i; j--)
            memory[j+1]=memory[j];
        memory[count]=(Object*)node;
        ++count;
    }
    Object* List::getByIndex(std::size_t i)
    {
        if (memory == NULL) return NULL;
        return memory[i];
    }
    std::size_t List::getIndex(Object* node)
    {
        if (memory == NULL) return -1;
        for (std::size_t i = 0; i < count; ++i)
        {
            if (getByIndex(i)==node) return i;
        }
        return -1;
    }
    void List::remove(int i)
    {
        if (memory == NULL) return;
        else if (i < 0) return;
        else if (count == 0) return;
        delete memory[i];
        for (std::size_t j = i; j < count - 1; j++)
                    memory[i] = memory[i + 1];

        --count;
    }
    void List::clear()
    {
        if (memory == NULL) return;
        std::size_t count;
        while ((count = Count()) != 0)
        {
            delet(count-1);
        }
    }
    void List::delet(std::size_t i)
    {
        if (memory == NULL || !count || i >= count) return;
        for (std::size_t j = i; j < count -1; ++j)
            memory[j] = memory[j+1];
        --count;
    }
    std::size_t List::delet(Object* node)
    {
        std::size_t i = getIndex(node);
        delet(i);
        return i;
    }
    std::size_t List::Count()
    {
        return count;
    }
}
