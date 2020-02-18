//
// Created by light on 20-2-18.
//
#include <iostream>
#include <vector>
using namespace std;
class Solution {
private:
    vector<vector<bool>> isVisited;
    int direct[4][2] = {
            {1,0},
            {-1,0},
            {0,1},
            {0,-1}
    };
public:
    int movingCount(int m, int n, int k) {

        isVisited = vector<vector<bool>>(m,vector<bool>(n,false));

        return dfs(0,0,k,m,n);
    }
    int dfs(int x,int y,int k,int m, int n) {

        int tmp = rowColSum(x)+rowColSum(y);
        int res=0;
        if(!inArea(m,n,x,y) || isVisited[x][y] || tmp>k)
            return res;

        isVisited[x][y] = true;

        res++;

        for(int i=0;i<4;i++) {
            int newX = x+direct[i][0];
            int newY = y+direct[i][1];
            res += dfs(newX,newY,k,m,n);
        }

        return res;
    }
    // 机器人在格子中
    bool inArea(int m,int n,int x,int y) {
        return x>=0 && x<m && y>=0 && y <n;
    }

    int rowColSum(int number) {
        int s=0;
        while(number!=0) {
            s+= number%10;
            number=number/10;
        }

        return s;
    }
};