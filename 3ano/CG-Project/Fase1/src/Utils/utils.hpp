#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>


#include <stdio.h>
#include <stdlib.h>
#include <cstring>

namespace utils
{
    struct point 
    {
        float x;
        float y;
        float z;
    };

    class figure 
    {

    public:
        std::vector<point> pontos;
        void addPoint(float, float, float);
    };
}