//
// Created by light on 20-2-14.
//

#include <iostream>
#include <string.h>

using namespace std;

#include <iostream>
#include <string.h>

using namespace std;

// 牛客提交方案
class Solution {
public:
    void replaceSpace(char *str,int length) {
        int spaceNum=0;
        int originLen=0;
        for(int i=0;str[i]!='\0';i++){
            if(str[i]==' ')
                spaceNum++;
            originLen++;
        }
        int newL = originLen+2*spaceNum;
        int j=newL-1;
        str[newL]='\0';
        while(j>=0) {
            if(str[originLen-1]==' ') {
                str[j--]='0';
                str[j--]='2';
                str[j--]='%';
            } else {
                str[j--]=str[originLen-1];
            }
            originLen--;
        }
    }

    void replaceSpace1(char *str,int length) {
        string s;
        for (int i=0;str[i]!='\0';i++) {
            if(str[i]!=' ')
                s+=str[i];
            else
                s+="%20";
        }
        strcpy(str,s.c_str());
    }
};

class Solution1 {
public:
    string replaceSpace(string s) {
        string t;
        for (int i=0;i<s.length();i++) {
            if(s[i]!=' ')
                t+=s[i];
            else
                t+="%20";
        }
        return t;
    }
};


