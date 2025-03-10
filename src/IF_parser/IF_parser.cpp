#include "IF_parser.hpp"

IFParser::IFParser(std::string filename)
{
    // as first step, open the file
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(filename.c_str());

    // check if the file is opened
    std::cout << "Load result: " << result.description() << std::endl;

    // print the tree
    printNodeInfo(doc);

    //check if the root element is present and is named "UPF"
    // if (!doc.root().name().compare("UPF")) {
    //     std::cout << "Root element is not named 'UPF'" << std::endl;
    //     return;
    // }
}

IFParser::~IFParser()
{
}

void IFParser::printNodeInfo(const pugi::xml_node& node, int level)
{
    // Print indentation
    std::string indent(level * 2, ' ');

    // Ensure we have enough levels in our container
    // We store level 0 at index 0, so we need (level + 1) slots
    while (xml_levels.size() <= level) {
        LevelNodes newLevel;
        newLevel.level = xml_levels.size();
        xml_levels.push_back(newLevel);
    }

    // Create a new XMLNode for this node
    XMLNode xmlNode;
    xmlNode.name = node.name();
    xmlNode.path = std::string(node.path().data());  // Convert pugi::xpath_node to string
    xmlNode.value = node.child_value(); // Get text content if any

    if(DBG::debug_level == 2) {
        std::cout << "[" << level << "]: " << indent << "Node: " << xmlNode.name << std::endl;
    } else if (DBG::debug_level == 1) {
        std::cout << indent << "Node: " << xmlNode.name << std::endl;
    }
    
    // Process all attributes of this node
    for (pugi::xml_attribute attr = node.first_attribute(); 
         attr; 
         attr = attr.next_attribute()) {
        XMLAttribute xmlAttr;
        xmlAttr.name = attr.name();
        xmlAttr.value = attr.value();
        xmlNode.attributes.push_back(xmlAttr);

        if (DBG::debug_level == 2) {
            std::cout<< "[" << level << "]: " << indent << "  Attribute: " << xmlAttr.name 
                     << " = " << xmlAttr.value << std::endl;
        } else if (DBG::debug_level == 1) {
            std::cout << indent << "  Attribute: " << xmlAttr.name 
                     << " = " << xmlAttr.value << std::endl;
        }
    }

    // Add this node to its level (level 0 stored at index 0)
    xml_levels[level].nodes.push_back(xmlNode);
    
    // Recursively print child nodes
    for (pugi::xml_node child = node.first_child(); 
         child; 
         child = child.next_sibling()) {
        printNodeInfo(child, level + 1);
    }
}
