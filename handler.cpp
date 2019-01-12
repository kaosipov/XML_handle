#include <handler.hpp>

namespace core
{
    TagAttributes::TagAttributes()
    {

    }

    Nodes::Nodes()
        : List()
    {

    }

//----------------------------------------------------------------------------------------------------

    XMLTag::XMLTag()
    {

    }

    XMLParser::XMLParser()
    {

    }

    XMLProlog::XMLProlog()
    {

    }

    void XMLParser::prologParse()
    {
        while (xml.find("<?", position) != std::string::npos)
        {
            position = xml.find("<?", position);
            position += 2;
            //tag's name detecting
            String name = "";
            skipNulls();
            for (;;)
            {
                char ch = xml.getChar(position);
                if (!letter(ch)) break;
                String sch(ch);
                name += sch;
                ++position;
            }
            XMLProlog* prolog = new XMLProlog();
            prolog->name = name;
            this->nodes.add(prolog);
            skipNulls();
            attrParse(prolog);
            skipNulls();
            if (xml.getChar(position) == '?' && xml.getChar(position+1) == '>')
            {
                position +=2;
            }
        }
    }

    short XMLParser::tagParse(XMLTag *root)
    {
        // "<"-search
        skipNulls();
        if (xml.getChar(position) != '<') return -1;
        ++position;
        // "/"-search
        skipNulls();
        if (xml.getChar(position) == '/' && root != NULL)
        {
            ++position;
            return 2;
        }        
        // tag's name detecting
        String name = "";
        skipNulls();
        for (;;)
        {
            char ch = xml.getChar(position);
            if (!letter(ch)) break;
            String sch(ch);
            name += sch;
            ++position;
        }
        if (name == "") return -1;
        XMLTag *xmlTag = new XMLTag();
        xmlTag->name = name;
        if (root == NULL) nodes.add(xmlTag);
        else root->childNodes.add(xmlTag);

        skipNulls();

        int result = attrParse(xmlTag);
        if (result < 1) return result;

        skipNulls();

        // ">"-, "/>"-search
        char ch = xml.getChar(position);
        if (ch == '/')
        {
                ++position;
                ch = xml.getChar(position);
                if (ch == '>')
                {
                    ++position;
                    return 1;
                }
        }
        if (ch != '>') return -1;
        ++position;

        skipNulls();

        //find sub Tags
        for (;;)
        {
            result = tagParse(xmlTag);
            if (result != 1) break;
        }

        if (result != 2)
        {
            xmlTag->val = "";
            for (;;)
            {
                ch = xml.getChar(position);
                ++position;
                if (ch == '<')
                {
                    skipNulls();
                    ch = xml.getChar(position);
                    if (ch == '/')
                    {
                        ++position;
                        break;
                    }
                    else return -1;
                }
                String sch(ch);
                xmlTag->val = xmlTag->val + sch;
                }
        }

            skipNulls();
            String name2 = "";
            for (;;)
            {
                char ch = xml.getChar(position);
                if (!letter(ch)) break;
                String sch(ch);
                name2 = name2 + sch;
                ++position;
            }

            if (name2 == "" || name != name2) return -1;

            //find >
            skipNulls();
            if (xml.getChar(position) != '>') return -1;
            ++position;
            return 1;
        }

template <typename T>
int XMLParser::attrParse(T *xmlT)
{
        for (;;)
        {
            skipNulls();
            String name = "";
            while (true) {
                if (!letter(xml.getChar(position))) break;
                String sch(xml.getChar(position));
                name += sch;
                ++position;
            }

            if (name == "") return 1;

            skipNulls();

            char ch;
            int result = getChar(ch);
            if (result < 1) return result;
            if (ch != '=') return -1;
            ++position;

            skipNulls();

            result = getChar(ch);
            if (result < 1) return result;
            if (ch != '\"') return -1;
            ++position;

            String value = "";
            for (;;)
            {
                char ch;
                int result = getChar(ch);
                if (result < 1) return result;
                if (ch == '\"') {
                    position++;
                    break;
                }
                String sch(ch);
                value += sch;
                position++;
            }

            xmlT->attr.addAttr(name, value);
        }

        return 1;
    }

bool XMLParser::parse()
{
        nodes.clear();
        position = 0;
        prologParse();
        int result = tagParse(NULL);
        return result == 1;
}

int XMLParser::getChar(char &ch)
{
    ch = xml.getChar(position);
    return 1;
}

bool XMLParser::notNull(char ch)
{
    return (ch < 33) ? 0:1;
}

void XMLParser::skipNulls()
{
    for (;;)
    {
        char ch = xml.getChar(position);
        if (notNull(ch)) return;
        ++position;
    }

}

bool XMLParser::letter(char ch)
{
    return ((ch >= 'a' && ch <='z') || (ch >= 'A' && ch <= 'Z') || ch == '-' || ch =='_' || ch == ':') ?1:0;
}

}
