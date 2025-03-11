#ifndef IF_PARSER_HPP_
#define IF_PARSER_HPP_

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

    static void printNodeInfo(const pugi::xml_node& node, XMLNode* parent = nullptr, int level = 0);

private:
    static void processAttributes(const pugi::xml_node& node, XMLNode& xmlNode, int level);
    static void debugPrint(const std::string& message, int level);
    void populateXMLnode(const pugi::xml_node& node, int level = 0);

};

#endif  // IF_PARSER_HPP_   