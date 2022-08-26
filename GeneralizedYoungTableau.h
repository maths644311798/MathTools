
#include<vector>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<iostream>
using namespace std;

struct Point
{
    int s;
    int t;

    Point(): s(0), t(0) {}
    Point(int out_s, int out_t)
    {
        s = out_s;
        t = out_t;
    }
};

class GeneralizedYoungTableau
{
public:
	//data[i][0] = 0, data[1][1] is the first element
	vector<vector<unsigned int>> data;

    GeneralizedYoungTableau()
    {
        data.push_back(vector<unsigned int>({0,0}));
        data.push_back(vector<unsigned int>({0}));
    }

    Point Insert(unsigned int x)
    {
        unsigned int i = 1;
        unsigned int j = data[1].size();
        unsigned int next_x = x;

        while( true )
        {
            if ( i >= data.size())
            {
                data.push_back( vector<unsigned int>({0,x}) );
                return Point(i,1);
            }
            while(  x < data[i][j-1] )
                --j;
            if ( j >= data[i].size())
            {
                data[i].push_back(x);
                break;
            }
            else
            {
                next_x =  data[i][j];
                data[i][j] = x;
                ++i;
                x = next_x;
            }
        }
        return Point(i,j);
    }

    unsigned int Delete(Point p)
    {
        unsigned int i = p.s;
        unsigned int j = data[i].size() - 1;
        unsigned int next_x = data[i][j], x = next_x;
        data[i].pop_back();
        --i;
        while( i > 0)
        {
            while( j < data[i].size()-1 &&  data[i][j+1] < x)
                ++j;
            next_x = data[i][j];
            data[i][j] = x;
            x = next_x;
            --i;
        }
        return x;
    }

    void display()
    {
        for(int i=1; i<data.size(); ++i)
        {
            for(int j=1; j<data[i].size(); ++j)
            {
                printf("%u ", data[i][j]);
            }
            printf("\n");
        }
    }
};