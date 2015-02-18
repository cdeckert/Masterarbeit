//
//  Scanner.h
//

#ifndef RuleBasedOptimizer_Scanner_h
#define RuleBasedOptimizer_Scanner_h

#include <fstream>
#include <sstream>
#include <string>


#include "Exceptions.h"

struct TokenDelimiters
{
    static const char COLON = ':';
    static const char LEFTPAREN = '(';
    static const char RIGHTPAREN = ')';
    static const char LEFTSQUAREBRACK = '[';
    static const char RIGHTSQUAREBRACK = ']';
    static const char BRACELEFT = '{';
    static const char BRACERIGHT = '}';
    static const char WHITESPACE = ' ';
    static const char TAB = '\t';
    static const char COMMA = ',';
    static const char LINEBREAK = '\n';
    static const char HASH = '#';
    static const char SEMICOLON = ';';
    static const char ASTERISK = '*';
    static const char DOT = '.';
};

class Scanner
{
public:
    Scanner(const std::string& aFilename);
    ~Scanner();
    
public:
    bool readNextToken(std::string& aString);
    
    inline bool endOfFile()
    {
        return !_inputFile.good();
    }
    
    uint getCurrentLine() const;
    
private:
    bool nextCharIsDelimiter();
    bool currentCharIsDelimiter();
    
    
private:
    std::ifstream _inputFile;
    char _next;
    char _current;
    uint _currentLine;
};

#endif
