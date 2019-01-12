#pragma once
#ifndef CORE_HPP
#define CORE_HPP
#define NODE_MEM_STEP 1024
#define LL long long
#include <string>
#include <map>

namespace core
{
    class String;
    class Object
    {
    public:
        Object();
        virtual ~Object();
        virtual bool parentExistance(String name);
    };

    class String : public Object
    {
    protected:
        std::string s;
    public:
        String();
        String(const String& value);
        String(String& value);
        String(std::string value);
        String(const char *value);
        String(char *value);
        String(char value);
        String(std::size_t value);
        String(long double value);
        String(bool value);
        virtual ~String();
        virtual char getChar(std::size_t index);
        virtual String getCharString(std::size_t index);
        virtual void setChar(std::size_t index, char ch);
        virtual void setChar(std::size_t index, String ch);

        virtual String& operator=(const String& value);
        virtual String operator+(String value);
        friend String operator+(const char* value, String stvalue);
        virtual String operator+=(String value);
        virtual bool operator==(String value);
        virtual bool operator!=(String value);
        virtual bool operator>(String value);
        virtual bool operator>=(String value);
        virtual bool operator<(String value);
        virtual bool operator<=(String value);
        virtual std::size_t getLength();
        virtual String subString(std::size_t pos, std::size_t count);
        virtual String subString(std::size_t pos);

        virtual long long getPos(String str);
        virtual long long getPosBack(String str);
        virtual size_t find(const String& str, size_t start = 0);

        virtual std::string to_str();
        virtual char* c_str();
        virtual std::size_t toInt();
        virtual long double toFloat();
};

    class ParametList : public Object
    {
    public:
        std::map<std::string, std::string> parameters;
        ParametList();
        virtual ~ParametList();
        virtual void addAttr(std::string name, std::string value);
        virtual void addAttr(String name, String value);
        virtual std::size_t Count();
        virtual String Name(std::size_t i);
        virtual String Value(String name);
        virtual String Value(std::size_t i);
    };

    class List : public Object
    {
    protected:
        std::size_t count, cap;
        Object **memory;
    public:
        List();
        virtual ~List();
        virtual std::size_t Count();
        virtual void setMemory(std::size_t m);
        virtual Object* add(Object* node);
        virtual void insert(std::size_t i, Object* node);
        virtual Object* getByIndex(std::size_t i);
        virtual std::size_t getIndex(Object* node);
        virtual void remove(int i);
        virtual void clear();
        virtual std::size_t delet(Object* node);
        virtual void delet(std::size_t i);
    };
}

#endif // CORE_HPP
