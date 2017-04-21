#include <iostream>
#include <algorithm>
#include <string.h>
#include <vector>
#include <stack>
#include <cmath>
#include<bitset>
#include<cstdio>
using namespace std;
#define MAX_SIZE 100

typedef struct op
{
  char operation;
  int trans_no;
  int record_no;
}op;

//global variables
vector<op>data;
vector<int>adjlist[MAX_SIZE];
vector<op>transaction[MAX_SIZE];
int V = 0;

void print(vector<int> data)
{
  int i;
  for(i=0;i<data.size();i++)
    cout << data[i] << " ";
  cout << "\n";
}

bool isCyclicUtil(int v,bool visited[],bool recStack[])
{
  int i;
  if(visited[v] == false)
  {
      visited[v] = true;
      recStack[v] = true;
      vector<int>::iterator i;
      for(i = adjlist[v].begin(); i != adjlist[v].end(); ++i)
      {
          if ( !visited[*i] && isCyclicUtil(*i, visited, recStack) )
              return true;
          else if (recStack[*i])
              return true;
      }
  }
  recStack[v] = false;
  return false;
}

bool isCyclic()
{
  bool *visited = new bool[V];
  bool *recStack = new bool[V];
  for(int i = 1; i <= V ; i++)
  {
      visited[i] = false;
      recStack[i] = false;
  }
  for(int i = 1; i <= V ; i++)
      if (isCyclicUtil(i, visited, recStack))
          return true;
  return false;
}

void topologicalSortUtil(int v,bool visited[],stack<int> &Stack)
{
  visited[v] = true;
  vector<int>::iterator i;
  for (i = adjlist[v].begin(); i != adjlist[v].end(); ++i)
      if (!visited[*i])
          topologicalSortUtil(*i, visited, Stack);
  Stack.push(v);
}

void  topologicalsort()
{
  stack<int> Stack;
  bool *visited = new bool[V];
  for (int i = 1; i <= V; i++)
      visited[i] = false;
  for (int i = 1; i <= V; i++)
    if (visited[i] == false)
      topologicalSortUtil(i, visited, Stack);
  while (Stack.empty() == false)
  {
      cout << Stack.top() << " ";
      Stack.pop();
  }
  cout << "\n";
}

int main(int argc,char* argv[])
{
    char operation;
    int trans_no;
    int record_no;
    int i,j;
    FILE *fp;
    fp = fopen(argv[1],"r");
    op temp;
    while(!feof(fp))
    {
      fscanf(fp,"%c %d %d",&operation,&trans_no,&record_no);
      if(feof(fp))
        break;
      if(operation == 'R')
      {
        //cout << operation << "\t" << trans_no << "\t" << record_no << "\n";
        temp.operation = operation;
        temp.record_no = record_no;
        temp.trans_no = trans_no;
        if(trans_no > V)
          V = trans_no;
        transaction[record_no].push_back(temp);
        data.push_back(temp);
      }
      else if(operation == 'W')
      {
        //cout << operation << "\t" << trans_no << "\t" << record_no << "\n";
        temp.operation = operation;
        temp.record_no = record_no;
        temp.trans_no = trans_no;
        if(trans_no > V)
          V = trans_no;
        transaction[record_no].push_back(temp);
        data.push_back(temp);
      }
    }
    fclose(fp);
    
    for(i=0;i<data.size();i++)
    {
      cout << data[i].operation << "\t" << data[i].trans_no << "\t" << data[i].record_no << "\n";
      if(data[i].operation == 'W')
      {
        for(j = i+1;j < data.size();j++)
        {
          if(data[i].trans_no != data[j].trans_no && data[i].record_no == data[j].record_no)
          {
            adjlist[data[i].trans_no].push_back(data[j].trans_no);
          }
        }
      }
      else if(data[i].operation == 'R')
      {
        for(j = i+1;j<data.size();j++)
        {
          if(data[i].trans_no != data[j].trans_no && data[i].record_no == data[j].record_no && data[j].operation == 'W')
          {
            adjlist[data[i].trans_no].push_back(data[j].trans_no);
          }
        }
      }
    }
    cout << "\nAdjacency List \n";
    for(i=1;i <= V;i++)
    {
      //if(!adjlist[i].empty())
      //{
        cout << i << "->";
        print(adjlist[i]);
      //}
    }

    if(isCyclic())
      cout << "\nNot Serializable \n";
    else
    {
      cout <<  "\nSerializable\n";
      topologicalsort();
    }

}
