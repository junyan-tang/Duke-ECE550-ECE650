#include "exerciser.h"

void exercise(connection *C)
{
    query1(C,1,35,40,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
    query1(C,1,15,35,1,14,19,0,0,0,0,0,0,0,0,0,0,0,0);

    query2(C,"DarkBlue");
    query2(C,"Green");

    query3(C,"Duke");
    query3(C,"UNC");

    query4(C,"NC","DarkBlue");
    query4(C,"GA","Orange");

    query5(C,11);
    query5(C,20);
}
