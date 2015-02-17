//
//  Scanner.cpp
//

#include <stdio.h>

#include "Scanner.h"
#include "Types.h"


Scanner::Scanner(const std::string& aFilename) : _inputFile(), _next('\0'), _current('\0'), _currentLine(1)
{
    _inputFile.open(aFilename.c_str());
    if (!_inputFile.is_open())
    {
        throw FileError(aFilename);
    }
}

Scanner::~Scanner()
{
    _inputFile.close();
}

bool Scanner::readNextToken(std::string& aString)
{
    if (_inputFile.good())
    {
        _current = _inputFile.get();
        _next = _inputFile.peek();
        
        // line comment: skip to the next linebreak
        if (_current == TokenDelimiters::HASH)
        {
            while (_current != TokenDelimiters::LINEBREAK ||
                   _next == TokenDelimiters::HASH)
            {
                _current = _inputFile.get();
                _next = _inputFile.peek();
            }
            
            if (_current == TokenDelimiters::LINEBREAK)
            {
                _current = _inputFile.get();
                _next = _inputFile.peek();
            }
        }
        
        while (_current == TokenDelimiters::WHITESPACE ||
               _current == TokenDelimiters::LINEBREAK ||
               _current == TokenDelimiters::TAB)
        {
            
            if (_current == TokenDelimiters::LINEBREAK)
            {
                ++_currentLine;
            }
            
            _current = _inputFile.get();
            _next = _inputFile.peek();
        }
        
        if (currentCharIsDelimiter())
        {
            aString.push_back(_current);
            return true;
        }
        
        while (_inputFile.good())
        {
            if (nextCharIsDelimiter())
            {
                aString.push_back(_current);
                return true;
            }
            aString.push_back(_current);
            _current = _inputFile.get();
            _next = _inputFile.peek();
        }
        
        
        return false;
        
    }
    
    return false;
}

uint Scanner::getCurrentLine() const
{
    return _currentLine;
}

bool Scanner::nextCharIsDelimiter()
{
    return (_next == TokenDelimiters::COLON ||
            _next == TokenDelimiters::COMMA ||
            _next == TokenDelimiters::LEFTPAREN ||
            _next == TokenDelimiters::LEFTSQUAREBRACK ||
            _next == TokenDelimiters::RIGHTSQUAREBRACK ||
            _next == TokenDelimiters::RIGHTPAREN ||
            _next == TokenDelimiters::BRACELEFT ||
            _next == TokenDelimiters::BRACERIGHT ||
            _next == TokenDelimiters::WHITESPACE ||
            _next == TokenDelimiters::LINEBREAK ||
            _next == TokenDelimiters::SEMICOLON ||
            _next == TokenDelimiters::ASTERISK ||
            _next == TokenDelimiters::DOT);
}

bool Scanner::currentCharIsDelimiter() {
    return (_current == TokenDelimiters::COLON ||
            _current == TokenDelimiters::COMMA ||
            _current == TokenDelimiters::LEFTPAREN  ||
            _current == TokenDelimiters::RIGHTPAREN ||
            _current == TokenDelimiters::LEFTSQUAREBRACK ||
            _current == TokenDelimiters::RIGHTSQUAREBRACK ||
            _current == TokenDelimiters::BRACELEFT ||
            _current == TokenDelimiters::BRACERIGHT ||
            _current == TokenDelimiters::WHITESPACE ||
            _current == TokenDelimiters::LINEBREAK ||
            _current == TokenDelimiters::SEMICOLON ||
            _current == TokenDelimiters::ASTERISK ||
            _current == TokenDelimiters::DOT);
}