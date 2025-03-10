#ifndef __GLOBALS_HPP__
#define __GLOBALS_HPP__

#include <string>
#include <vector>

enum RV_Global {
    ALL_OK = 0,
    GLOBAL_ERROR = -1,
    NO_INPUT_FILE = -2,
    BAD_FILE_FORMAT = -3,
    CANNOT_PARSE_FILE = -4
};

// input file globals
// Forward declarations
struct XMLNode;
struct XMLAttribute;

// Structure for XML attribute data
struct XMLAttribute {
    std::string name;
    std::string value;
    std::string node_path;  // to track which node this attribute belongs to
};

struct InputFile {
    bool is_open = false;
    bool is_parsed = false;
    std::string filename;
    std::string UPF_version;

    // Vector of attribute structures - more organized than parallel vectors
    std::vector<XMLAttribute> attributes;

    // Legacy fields - can be removed if not needed
    std::vector<std::string> UPF_fields;
    std::vector<std::string> UPF_values;
};

struct OutputFile {
    bool is_open = false;
    bool is_written = false;
    std::string filename;
};

// global variables
namespace DBG {
    extern int debug_level;
}

// Structure for XML node and its attributes
struct XMLNode {
    std::string name;
    std::string path;
    std::string value;        // Field value if this node represents a field
    bool is_field = false;    // Flag to indicate if this node is a field
    bool has_attributes = false; // Flag to indicate if this node has attributes
    std::vector<XMLAttribute> attributes;
    std::vector<XMLNode> siblings;  // Nodes at the same level
    std::vector<XMLNode> children;  // Child nodes (next level)
};

// Structure for nodes at each level
struct LevelNodes {
    std::vector<XMLNode> nodes;  // All nodes at this level
    int level = 0;              // Level number (root = 1)
};

// Vector to store nodes by level
extern std::vector<LevelNodes> xml_levels;

// Root node for the entire XML document
extern XMLNode xml_root;
#endif // __GLOBALS_HPP__   
