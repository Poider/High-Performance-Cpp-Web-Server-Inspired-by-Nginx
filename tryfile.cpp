// #include "filesystem.hpp"
#include <iostream>
int main()
{
    std::string path = "./aa";
    char a[6];
    
    a[0] = 'a';
    a[1] = 'b';
    a[2] = 'c';
    a[3] = '\0';
    a[4] = 'd';
    a[5] = '\0';
    std::string str(a,6) ;
    std::string ss = str;
    // ss += str;
    ss = ss.substr(2, str.length());
    std::cout << ss.size()<< std::endl;
    // FileSystem fs =  FileSystem(path,WRITE,".txt");
    // fs.open();
    // fs.Write_chunk(str,6);

    // std::string s1,s2;
    // s1 = "abcd";
    // s2 = s1.substr(2,4);
    // s1 = s1.substr(0,2);

    // std::cout << s1 << std::endl;
    // std::cout << s2 << std::endl;

}