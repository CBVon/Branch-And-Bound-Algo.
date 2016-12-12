/*
ref: http://blog.sina.com.cn/s/blog_489b92d401000ak7.html

pseudo code:
��m1.txt,m2.txt�����ݶ�������50��50������
��floyid�㷨������е��֮������·��,����С����
��������ʼ��һЩ���������ݽṹ
����һ����ջ,��ʼ���ö�ջ
ȡ��ջ���Ľ��,����������ڽ��(���ϴο��ǵ��Ǹ�������һ����㿪ʼ����).ȷ����һ����ǰ����·���ϵĽ��.����չ�Ľ�㶼�������ջ��
    �ڼ��Ĺ�����,������ֳ�����ǰ��·����򳬳����õĽ�,����С���֦�� ,Ȼ�����
    �ҵ�һ�����,����Ľ�.
�ظ���һ���Ĺ���,ֱ����ջΪ��.��ǰ����Ľ⼴Ϊ���Ž�
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
        if(i == 51) //��ǰջ���ڵ�û�п��ú�̽ڵ�
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
            if(i == 50) //�����յ㣬 �������Ž�
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
















