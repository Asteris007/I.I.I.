#ifndef __URLPARSER_H__
#define __URLPARSER_H__

#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

typedef unordered_map<string, string> KeyValueMap_t;
typedef vector<string> Folder_t;

class urlParser {
private:
    KeyValueMap_t m_keysvalues;
    Folder_t m_folders;
public:
    urlParser(){};
    urlParser(const char* url);
    bool parse(const char* url);
    Folder_t& paths() { return m_folders; };
    KeyValueMap_t& params() { return m_keysvalues; };
    string path();
    void print(char splitter = '\n');
};

#endif 
