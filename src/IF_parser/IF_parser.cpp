#include "IF_parser.hpp"
#include <cstring>

IFParser::IFParser(const std::string& filename)
{
    // as first step, open the file
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(filename.c_str());

    // check if the file is opened
    std::cout << "Load result: " << result.description() << std::endl;

    // Initialize the root node and build the tree
    xml_root.name = "root";
    xml_root.path = "/";
    printNodeInfo(doc, &xml_root);

    //check if the root element is present and is named "UPF"
    // if (!doc.root().name().compare("UPF")) {
    //     std::cout << "Root element is not named 'UPF'" << std::endl;
    //     return;
    // }
}

IFParser::~IFParser() = default;

void IFParser::debugPrint(const std::string& message, int level) {
    if (DBG::debug_level > 0) {
        std::string indent(level * 2, ' ');
        std::string prefix = (DBG::debug_level == 2) ? "[" + std::to_string(level) + "]: " : "";
        std::cout << prefix << indent << message << std::endl;
    }
}

void IFParser::processAttributes(const pugi::xml_node& node, XMLNode& xmlNode, int level) {
    std::string indent(level * 2, ' ');
    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        XMLAttribute xmlAttr;
        xmlAttr.name = attr.name();
        xmlAttr.value = attr.value();
        xmlNode.attributes.push_back(xmlAttr);
        xmlNode.has_attributes = true;

        debugPrint("  Attribute: " + xmlAttr.name + " = " + xmlAttr.value, level);
    }
}

void IFParser::printNodeInfo(const pugi::xml_node& node, XMLNode* parent, int level) {
    // Skip empty text nodes
    if (node.type() == pugi::node_pcdata && strlen(node.value()) == 0) {
        return;
    }

    // Ensure we have enough levels in our container
    while (xml_levels.size() <= level) {
        LevelNodes newLevel;
        newLevel.level = xml_levels.size();
        xml_levels.push_back(newLevel);
    }

    // Create a new XMLNode for this node
    XMLNode xmlNode;
    xmlNode.name = node.name();
    xmlNode.path = std::string(node.path().data());
    xmlNode.value = node.child_value();

    // Only process element nodes or non-empty text nodes
    if (node.type() == pugi::node_element || (node.type() == pugi::node_pcdata && strlen(node.value()) > 0)) {
        std::string nodeInfo = "Node: " + xmlNode.name;
        if (node.type() == pugi::node_pcdata) {
            nodeInfo += " (text: " + std::string(node.value()) + ")";
        }
        debugPrint(nodeInfo, level);

        // Process attributes
        processAttributes(node, xmlNode, level);

        // Add this node to its level
        xml_levels[level].nodes.push_back(xmlNode);

        // Add this node to parent's children if parent exists
        if (parent != nullptr) {
            parent->children.push_back(xmlNode);
        }
        
        // Recursively process child nodes
        for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
            printNodeInfo(child, &xmlNode, level + 1);
        }
    }
}

