// #include "filesystem.hpp"
#include <iostream>

size_t findSubstring(const std::string& str, const std::string& substr)
{
    const char* strData = str.data();
    const char* substrData = substr.data();
    size_t strLength = str.length();
    size_t substrLength = substr.length();

    for (size_t i = 0; i <= strLength - substrLength; i++)
    {
        size_t len = std::min(substrLength, strLength - i);
        if (memcmp(strData + i, substrData, len) == 0)
        {
            return i;
        }
    }

    return std::string::npos;
}
int main()
{
    std::string path = "./aa";
    char *a = "abcdefghi\0jklmno\0pqrstu\0vwxyz";
    std::string str(a,29) ;
    std::cout << str.size() << std::endl;
    std::cout << str << std::endl;
    std:: string s= "yzz";
    std::cout << findSubstring(str,s) << std::endl;
    // FileSystem fs =  FileSystem(path,WRITE,".txt");
    // fs.open();
    // fs.Write_chunk(str,6);
}