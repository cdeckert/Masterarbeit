//
//  Exceptions.h
//

#ifndef RuleBasedOptimizer_Exceptions_h
#define RuleBasedOptimizer_Exceptions_h

struct SyntaxError {
    
    SyntaxError(uint aLine) :
    _line(aLine),
    _token(){}
    
    SyntaxError(uint aLine, const std::string& aToken):
    _line(aLine),
    _token(aToken) {}
    
    uint _line;
    std::string _token;
};


struct FileError {
    
    FileError (const std::string& aFilePath) :
    _filePath(aFilePath) {}
    
    std::string _filePath;
};

struct ProfileException {
    ProfileException(const std::string& aErrorMsg) :
    _errorMsg(aErrorMsg) {}
    
    std::string _errorMsg;
};

#endif
