/*
ref: http://blog.sina.com.cn/s/blog_489b92d401000ak7.html

pseudo code:
将m1.txt,m2.txt的数据读入两个50×50的数组
用floyid算法求出所有点对之间的最短路长,和最小费用
声明并初始化一些变量和数据结构
建立一个堆栈,初始化该堆栈
取出栈顶的结点,检查它的相邻结点(从上次考虑的那个结点的下一个结点开始考虑).确定下一个当前最优路径上的结点.被扩展的结点都被加入堆栈中
    在检查的过程中,如果发现超出当前的路长界或超出费用的界,则进行”剪枝” ,然后回溯
    找到一个解后,保存改解.
重复上一步的过程,直到堆栈为空.当前保存的解即为最优解
*/
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <stack>

using namespace std;

const int maxValue = 9999;
int m1[56][56], m2[56][56];
int minDist[56][56], minCost[56][56];
int visited[56];
stack<int> staCity;

void inputFile()
{
    FILE *fp1 = freopen("m1.txt", "r", stdin);
    for(int i = 1; i <= 50; i++)
    {
        for(int j = 1; j <= 50; j++)
        {
            cin >> m1[i][j];
            if(i == j)
            {
                m1[i][i] = 0;
            }
        }
    }
    FILE *fp2 = freopen("m2.txt", "r", stdin);
    for(int i = 1; i <= 50; i++)
    {
        for(int j = 1; j <= 50; j++)
        {
            cin >> m2[i][j];
        }
    }
    return;
}

void floyd()
{
    for(int i = 1; i <= 50; i++)
    {
        for(int j = 1; j <=50; j++)
        {
            minDist[i][j] = m1[i][j];
            minCost[i][j] = m2[i][j];
        }
    }
    for(int k = 1; k <= 50; k++)
    {
        for(int i = 1; i <= 50; i++)
        {
            for(int j =1; j <=50; j++)
            {
                if(minDist[i][k] + minDist[k][j] < minDist[i][j])
                {
                    minDist[i][j] = minDist[i][k] + minDist[k][j];
                }
                if(minCost[i][k] + minCost[k][j] < minCost[i][j])
                {
                    minCost[i][j] = minCost[i][k] + minCost[k][j];
                }
            }
        }
    }
}

int main()
{
    inputFile();

    floyd();

//    for(int i = 1; i <= 50; i++)
//    {
//        for(int j = 1; j <= 50; j++)
//        {
//            cout << minDist[i][j] << "  ";
//        }
//        puts("");
//    }

    memset(visited , 0, sizeof(visited));

    staCity.push(1);
    visited[1] = 1;
    int currentDist = 0;
    int currentCost = 0;
    int distBound = maxValue;
    int costOfMinDistBound = maxValue;
    int path[56];
    int numOfMinDist = -1;
    const int costBound = 1500;
    int next = 0;
    while(!staCity.empty())
    {
        int top = staCity.top();
        int i;
        for(i = next + 1; i <= 50; i++)
        {
            if(visited[i] == 1)
            {
                continue;
            }
            if(m1[top][i] == maxValue)
            {
                continue;
            }
            if(currentCost + m2[top][i] + minCost[i][50] > costBound || currentDist + m1[top][i] + minDist[i][50] > distBound)
            {
                continue;
            }
            break;
        }
        if(i == 51) //当前栈顶节点没有可用后继节点
        {
            int topOld = staCity.top();
            staCity.pop();
            if(!staCity.empty())
            {
                int topNew = staCity.top();
                currentDist -= m1[topNew][topOld];
                currentCost -= m2[topNew][topOld];
                visited[topOld] = 0;
                next = topOld;
            }
        }
        else
        {
            if(i == 50) //到达终点， 更新最优解
            {
                distBound = currentDist + m1[top][i];
                costOfMinDistBound = currentCost + m2[top][i];
                next = i;

                numOfMinDist = 0;
                while(!staCity.empty())
                {
                    path[++numOfMinDist] = staCity.top();
                    staCity.pop();
                }
                for(int k = numOfMinDist; k >= 1; k--)
                {
                    staCity.push(path[k]);
                }
            }
            else
            {
                staCity.push(i);
                next = 0;
                visited[i] = 1;
                currentDist += m1[top][i];
                currentCost += m2[top][i];
            }

        }
    }

    printf("distBound : %d\n", distBound);
    printf("costOfMinDistBound : %d\n", costOfMinDistBound);
    printf("pathLength : %d\n", numOfMinDist+1);
    printf("path is : ");
    for(int i = numOfMinDist; i >= 1; i--)
    {
        printf("%d, ", path[i]);
    }
    puts("50");
    return 0;
}
















