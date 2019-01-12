#include <iostream>
#include <fstream>
#include<handler.hpp>

using namespace core;

void childInspection(Nodes& childNodes, std::size_t d = 1);

std::string readFile(const std::string& fileName) {
    std::ifstream f(fileName);
    f.seekg(0, std::ios::end);
    size_t size = f.tellg();
    std::string s(size, ' ');
    f.seekg(0);
    f.read(&s[0], size); // по стандарту можно в C++11, по факту работает и на старых компиляторах
    return s;
}

int main()
{
    std::cout << "==============================XML-Handler===============================\n\n\n\n  Input file path: ";
    std::string filepath, input;
    std::cin >> filepath;
    XMLParser *xmlparse = new XMLParser();
//    String xmltext;
    input = readFile(filepath);
    std::cout << input <<"\n\n";
    xmlparse->xml = input;
    xmlparse->parse();

    //prolog output
    std::size_t count = xmlparse->nodes.Count();
    if (count > 1) std::cout << "================================Prolog==================================\n\n\n";
    for (std::size_t i = 0; i < count-1; ++i)
    {
        XMLProlog *prolog = (XMLProlog*)xmlparse->nodes.getByIndex(i);
        std::cout << "name = " << prolog->name.to_str() << "\n";
        std::size_t coun = prolog->attr.Count();
        for (std::size_t k = 0; k < coun; ++k)
        {
            String name = prolog->attr.Name(k);
            String value = prolog->attr.Value(k);
            std::cout << "  (name = " << name.to_str() << ", value = " << value.to_str() << ")\n";
        }
    }
    //tag output
        std::cout << "\n==================================Tags==================================\n\n\n";
        XMLTag *tag = (XMLTag*)xmlparse->nodes.getByIndex(xmlparse->nodes.Count()-1);
        std::cout << "name = " << tag->name.to_str();
        if (tag->val.to_str() != "") std::cout << ", value = " << tag->val.to_str();
        std::cout << std::endl;

        std::size_t coun = tag->attr.Count();
        for (std::size_t k = 0; k < coun; ++k)
        {
            String name = tag->attr.Name(k);
            String value = tag->attr.Value(k);
            std::cout << " attributes:\n";
            std::cout << "  (name = " << name.to_str() << ", value = " << value.to_str() << ")\n";
        }
      std::cout << std::endl;
      childInspection(tag->childNodes);
    return 0;
}

inline void print_stars(std::size_t d)
{
    for (std::size_t i = 0; i < d; ++i) std::cout << "*****";
}

void childInspection(Nodes &childNodes, std::size_t d)
{
    std::size_t count = childNodes.Count();
    if (count)
    {
        for (std::size_t i = 0; i < count; ++i)
        {
            print_stars(d);
            XMLTag* tag = (XMLTag*)childNodes.getByIndex(i);
            std::cout << " name = " << tag->name.to_str();
            if (tag->val.to_str() != "") std::cout << ", value = " << tag->val.to_str();
            std::cout << std::endl;
            std::size_t count2 = tag->attr.Count();
            for (std::size_t j = 0; j < count2; ++j)
            {
                String name = tag->attr.Name(j);
                String value = tag->attr.Value(j);
                print_stars(d);
                std::cout << " attributes:\n";
                print_stars(d);
                std::cout << "  (name = " << name.to_str() << ", value = " << value.to_str() << ")\n";
            }
            std::cout << std::endl;
            childInspection(tag->childNodes, d+1);
        }
    }
}
