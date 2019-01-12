#pragma once
#ifndef HANDLER_HPP
#define HANDLER_HPP
#include <core.hpp>

namespace core
{
    class TagAttributes : public ParametList
    {
    public:
        TagAttributes();
    };
    class Nodes : public List
    {
    public:
        Nodes();
    };

    class XMLTag : public Object
    {
        public:
        String name;
        String val;
        TagAttributes attr;
        Nodes childNodes;
        XMLTag();
    };

    class XMLProlog : public Object
    {
    public:
        String name;
        TagAttributes attr;
        Nodes nodes;
        XMLProlog();
    };



    class XMLParser : public Object
    {
    public:
        String xml;
        std::size_t position;
        Nodes nodes;
        XMLParser();
        virtual short tagParse(XMLTag *root);
        virtual bool notNull(char ch);
        virtual void skipNulls();
        virtual bool letter(char ch);
        template<typename T>
        int attrParse(T *xmlT);
        virtual bool parse();
        virtual int getChar(char& ch);
        virtual void prologParse();
    };

}
#endif // HANDLER_HPP
