#include "test_bus_lines.h"
#include <stdio.h>
#include  <stdlib.h>

int is_sorted_by_distance (const BusLine *start, const BusLine *end)
{
    for (const BusLine *cur=start; cur < end - 1; cur++)
    {
        if (cur->distance > (cur+1)->distance)
        {
            return 0;
        }
    }
    return 1;
}


int is_sorted_by_duration (const BusLine *start, const BusLine *end)
{
    for (const BusLine *cur=start; cur < end - 1; cur++)
    {
        if (cur->duration > (cur+1)->duration)
        {
            return 0;
        }
    }
    return 1;
}


int is_sorted_by_stops (const BusLine *start, const BusLine *end)
{
    for (const BusLine *cur=start; cur < end - 1; cur++)
    {
        if (cur->stops > (cur+1)->stops)
        {
            return 0;
        }
    }
    return 1;
}


int is_sorted_by_name (const BusLine *start, const BusLine *end)
{
    for (const BusLine *cur=start; cur < end - 1; cur++)
    {
        if (strcmp(cur->name,(cur+1)->name) > 0)
        {
            return 0;
        }
    }
    return 1;
}


/*int is_equal (const BusLine *start_sorted,
              const BusLine *end_sorted,
              const BusLine *start_original,
              const BusLine *end_original)
{
    const BusLine *temp_original = start_original;
    const BusLine *temp_sorted = start_sorted;

    while (temp_sorted <= end_sorted && temp_original <= end_original)
    {
        if (strcmp(temp_sorted->name, temp_original->name) != 0 ||
            temp_sorted->distance != temp_original->distance ||
            temp_sorted->duration != temp_original->duration)
        {
            return 0;
        }

        temp_original++;
        temp_sorted++;
    }
    return 1;
}*/

int is_equal (const BusLine *start_sorted,
              const BusLine *end_sorted,
              const BusLine *start_original,
              const BusLine *end_original)
{
    int n_sorted   = (int)(end_sorted   - start_sorted   + 1);
    int n_original = (int)(end_original - start_original + 1);

    // different number of elements?
    if (n_sorted != n_original)
    {
        return 0;
    }

    //for each line in the sorted array, check that there exists a line with the same in original
    for (const BusLine *cur_sorted = start_sorted;
         cur_sorted <= end_sorted;
         cur_sorted++)
    {
        int found = 0;
        for (const BusLine *cur_orig = start_original;
             cur_orig <= end_original;
             cur_orig++)
        {
            if (strcmp(cur_sorted->name, cur_orig->name) == 0)
            {
                found = 1;
                break;
            }
        }
        if (!found)
        {
            return 0;
        }
    }
    return 1;
}


int run_tests(BusLine *lines, int num_lines)
{
    int all_passed = 1;
    int test_id = 1;

    BusLine *base = malloc(num_lines * sizeof(BusLine));
    BusLine *test = malloc(num_lines * sizeof(BusLine));

    if (!base || !test)
    {
        free(base);
        free(test);
        printf("TEST %d FAILED: Memory allocation error\n", test_id);
        return 0;
    }

    memcpy(base, lines, num_lines * sizeof(BusLine));

    //TEST 1: SORT BY DISTANCE
    memcpy(test, base, num_lines * sizeof(BusLine));
    quick_sort(test, test + num_lines - 1, DISTANCE);

    if (!is_sorted_by_distance(test, test + num_lines - 1))
    {
        printf("TEST %d FAILED: Not sorted by distance\n", test_id);
        all_passed = 0;
    }
    else
    {
        printf("TEST %d PASSED: Sorted by distance\n", test_id);
    }
    test_id++;

    //TEST 2: SAME CONTENT AFTER DISTANCE SORT
    if (!is_equal(test, test + num_lines - 1, base, base + num_lines - 1))
    {
        printf("TEST %d FAILED: Lines changed after distance sort\n", test_id);
        all_passed = 0;
    }
    else
    {
        printf("TEST %d PASSED: Same lines after distance sort\n", test_id);
    }
    test_id++;

    //TEST 3: SORT BY DURATION
    memcpy(test, base, num_lines* sizeof(BusLine));
    quick_sort(test, test + num_lines - 1, DURATION);

    if (!is_sorted_by_duration(test, test + num_lines - 1))
    {
        printf("TEST %d FAILED: Not sorted by duration\n", test_id);
        all_passed = 0;
    }
    else
    {
        printf("TEST %d PASSED: Sorted by duration\n", test_id);
    }
    test_id++;

    //TEST 4: SAME CONTENT AFTER DURATION SORT
    if (!is_equal(test, test + num_lines - 1, base, base + num_lines - 1))
    {
        printf("TEST %d FAILED: Lines changed after duration sort\n", test_id);
        all_passed = 0;
    }
    else
    {
        printf("TEST %d PASSED: Same lines after duration sort\n", test_id);
    }
    test_id++;

    //TEST 5: SORT BY STOPS
    memcpy(test, base, num_lines*sizeof(BusLine));
    quick_sort(test, test + num_lines - 1, STOPS);

    if (!is_sorted_by_stops(test, test + num_lines - 1))
    {
        printf("TEST %d FAILED: Not sorted by stops\n", test_id);
        all_passed = 0;
    }
    else
    {
        printf("TEST %d PASSED: Sorted by stops\n", test_id);
    }
    test_id++;

    //TEST 6: SAME CONTENT AFTER STOPS SORT
    if (!is_equal(test, test + num_lines - 1, base, base + num_lines - 1))
    {
        printf("TEST %d FAILED: Lines changed after stops sort\n", test_id);
        all_passed = 0;
    }
    else
    {
        printf("TEST %d PASSED: Same lines after stops sort\n", test_id);
    }
    test_id++;

    //TEST 7: SORT BY NAME (BUBBLE SORT)
    memcpy(test, base, num_lines*sizeof(BusLine));
    bubble_sort(test, test + num_lines - 1);

    if (!is_sorted_by_name(test, test + num_lines - 1))
    {
        printf("TEST %d FAILED: Not sorted by name\n", test_id);
        all_passed = 0;
    }
    else
    {
        printf("TEST %d PASSED: Sorted by name\n", test_id);
    }
    test_id++;

    //TEST 8: SAME CONTENT AFTER NAME SORT
    if (!is_equal(test, test + num_lines - 1, base, base + num_lines - 1))
    {
        printf("TEST %d FAILED: Lines changed after name sort\n", test_id);
        all_passed = 0;
    }
    else
    {
        printf("TEST %d PASSED: Same lines after name sort\n", test_id);
    }

    free(base);
    free(test);
    return all_passed;
}