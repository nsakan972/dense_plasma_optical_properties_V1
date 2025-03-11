#ifndef __IF_PARSER_HPP__
#define __IF_PARSER_HPP__

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <cmath>
#include <map>
#include <set>

// Parsing should be done with PugiXML
#include <pugixml.hpp>

#include "globals.hpp"

class IFParser {
public:
    explicit IFParser(const std::string& filename);
    ~IFParser();

    void printNodeInfo(const pugi::xml_node& node, int level = 0);
    void populateXMLnode(const pugi::xml_node& node, int level = 0);

private:

};

#endif // __IF_PARSER_HPP__   