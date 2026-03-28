#include "sort_bus_lines.h"
#include <stdio.h>


void bubble_sort (BusLine *start, BusLine *end)
{
    //CHECK
    int n = (int)(end - start + 1);

    for (int i=0; i<n-1; i++)
    {
        for (int j=0; j< n-i-1; j++)
        {
            BusLine *a = start + j;
            BusLine *b = start + j + 1;

            if (strcmp(a->name, b->name) > 0)
            {
                BusLine temp = *a;
                *a = *b;
                *b = temp;
            }
        }
    }
}


void quick_sort (BusLine *start, BusLine *end, SortType sort_type)
{
    if (start < end)
    {
        BusLine *pivot = partition(start, end, sort_type);

        quick_sort(start, pivot-1, sort_type);
        quick_sort(pivot+1, end, sort_type);
    }

}

BusLine *partition (BusLine *start, BusLine *end, SortType sort_type)
{
    BusLine pivot = *end;
    BusLine *i = start - 1;

    for (BusLine *j = start; j <= end - 1; j++)
    {
        int condition;
        if (sort_type == DISTANCE)
        {
            condition = (j->distance < pivot.distance);
        }
        else if (sort_type == DURATION)
        {
            condition = (j->duration < pivot.duration);
        }
        else
        {
            condition = (j->stops < pivot.stops);
        }

        if (condition)
        {
            i++;
            BusLine temp = *i;
            *i = *j;
            *j = temp;
        }
    }

    BusLine temp = *(i+1);
    *(i+1) = *end;
    *end = temp;

    return i+1;
}