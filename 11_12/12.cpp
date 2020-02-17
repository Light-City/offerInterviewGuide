//
// Created by light on 20-2-17.
//
#include <vector>
#include <iostream>
#include <string>
using namespace std;
class Solution {
private:
    vector<vector<bool>> isVisited;
    int n,m;
    int direct[4][2] = {
            {1,0},
            {-1,0},
            {0,1},
            {0,-1}
    };
public:
    bool exist(vector<vector<char>>& board, string word) {
        n = board.size();
        if (n==0) return false;
        m = board[0].size();
        isVisited = vector<vector<bool>>(n,vector<bool>(m,false));

        for(int i=0;i<n;i++) {
            for(int j=0;j<m;j++) {
                // 找到单词的第一个字符
                if(board[i][j]==word[0] && !isVisited[i][j]) {
                    isVisited[i][j] = true;
                    if(dfs(board,word,1,word.length(),i,j))
                        return true;
                    isVisited[i][j] = false;
                }
            }
        }
        return false;
    }

    bool inBoard(int x,int y) {
        return x>=0&&x<n&&y>=0&&y<m;
    }
    bool dfs(vector<vector<char>>& board, string word,int start,int end,int x,int y) {

        if(start==end) return true;

        for(int i=0;i<4;i++) {
            int newX = x + direct[i][0];
            int newY = y + direct[i][1];
            if (inBoard(newX,newY) && !isVisited[newX][newY]&&board[newX][newY]==word[start]) {
                isVisited[newX][newY]=true;
                if(dfs(board,word,start+1,end,newX,newY))
                    return true;
                isVisited[newX][newY]=false;
            }
        }
        return false;
    }
};