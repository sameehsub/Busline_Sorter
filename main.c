#include "sort_bus_lines.h"
#include "test_bus_lines.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define ARG_LEN 2
#define MAX_LEN_ARG 60
#define MAX_LEN_NAME 21
#define MIN_DISTANCE 0
#define MAX_DISTANCE 1000
#define MIN_DURATION 10
#define MAX_DURATION 100
#define MIN_STOPS 1
#define MAX_STOPS 50



int get_n()
{
    int num_lines;
    while (true)
    {
        fprintf(stdout, "Enter number of lines. Then enter\n");
        char input[MAX_LEN_ARG];
        fgets(input, MAX_LEN_ARG, stdin);

        if (sscanf(input, "%d", &num_lines) == 1 && num_lines > 0)
        {
            return num_lines;
        }
        fprintf(stdout, "Error: Number of lines should be a positive integer\n");

    }

}


void get_bus_lines(BusLine* lines, int num_lines)
{
    for (int i=0; i<num_lines; i++)
    {
        while (true)
        {
            fprintf(stdout, "Enter line info. Then enter\n");

            char input[MAX_LEN_ARG];

            // Case: fgets failed to read line
            if (!fgets(input, MAX_LEN_ARG, stdin))
            {
                fprintf(stdout, "Error: failed to read line info\n");
                continue;
            }

            //STRING INITIALIZATION
            char name[NAME_LEN];
            char distance_str[10];
            char duration_str[10];
            char stops_str[10];

            //SCANNING INPUT
            if (sscanf(input, "%20[^,],%9[^,],%9[^,],%9[^,\n]", name, distance_str, duration_str, stops_str) != 4)
            {
                fprintf(stdout, "Error: invalid input\n");
                continue;
            }


            //STRING VALIDATION

            //name
            size_t name_len = strlen(name);
            if (name_len == 0 || name_len > MAX_LEN_NAME - 1)
            {
                fprintf(stdout,
                        "Error: bus name should contains only digits and small chars\n");
                continue;
            }

            int name_ok = 1;
            for (size_t j = 0; j < name_len; j++)
            {
                char c = name[j];
                if (!((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z')))
                {
                    name_ok = 0;
                    break;
                }
            }

            if (!name_ok)
            {
                fprintf(stdout, "Error: bus name should contains only digits and small chars\n");
                continue;
            }
            //name


            char *end_ptr = NULL; //pointer for strtol

            //distance
            long distance_val = strtol(distance_str, &end_ptr, 10);
            if (*end_ptr != '\0' || distance_val < MIN_DISTANCE || distance_val > MAX_DISTANCE)
            {
                fprintf(stdout,"Error: distance should be an integer between %d and %d (includes)\n", MIN_DISTANCE, MAX_DISTANCE);
                continue;
            }
            //distance


            //duration
            end_ptr = NULL;
            long duration_val = strtol(duration_str, &end_ptr, 10);
            if (*end_ptr != '\0' || duration_val < MIN_DURATION || duration_val > MAX_DURATION)
            {
                fprintf(stdout,"Error: duration should be an integer between %d and %d (includes)\n", MIN_DURATION, MAX_DURATION);
                continue;
            }
            //duration


            //stops
            end_ptr = NULL;
            long stops_val = strtol(stops_str, &end_ptr, 10);
            if (*end_ptr != '\0' || stops_val < MIN_STOPS || stops_val > MAX_STOPS)
            {
                fprintf(stdout,"Error: stops should be an integer between %d and %d (includes)\n", MIN_STOPS, MAX_STOPS);
                continue;
            }
            //stops

            //assigning array
            strncpy(lines[i].name, name, MAX_LEN_NAME - 1);
            lines[i].name[MAX_LEN_NAME - 1] = '\0';
            lines[i].distance = (int)distance_val;
            lines[i].duration = (int)duration_val;
            lines[i].stops    = (int)stops_val;


            break;
        }
    }
}


int main (int argc, char *argv[])
{
    if (argc != ARG_LEN)
    {
        fprintf(stdout, "Usage: ./<compiled_file> <by_duration|by_distance|by_name|by_stops|test> \n");
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "test") == 0)
    {
        const int num_lines = get_n();
        BusLine *lines = malloc(num_lines * sizeof(BusLine));
        if (!lines)
        {
            free(lines);
            return EXIT_FAILURE;
        }
        get_bus_lines(lines, num_lines);
        int ok = run_tests(lines, num_lines);

        free(lines);

        if (ok)
        {
            return EXIT_SUCCESS;
        }
        return EXIT_FAILURE;
    }

    SortType sort_type;
    if (strcmp(argv[1], "by_duration") == 0) {
        sort_type = DURATION;
    } else if (strcmp(argv[1], "by_distance") == 0) {
        sort_type = DISTANCE;
    } else if (strcmp(argv[1], "by_stops") == 0) {
        sort_type = STOPS;
    } else if (strcmp(argv[1], "by_name") == 0)
    {
        sort_type = NAME;
    }


    else {
        fprintf(stdout, "Usage: ./<compiled_file> <by_duration|by_distance|by_name|by_stops|test>\n");
        return EXIT_FAILURE;
    }

    // get n & validate
    const int num_lines = get_n();

    // allocate array of struct BusLines
    BusLine * lines = malloc(num_lines*sizeof(BusLine));
    if (!lines)
    {
        free(lines);
        return EXIT_FAILURE;
    }


    // get bus lines
    get_bus_lines(lines, num_lines);


    // sort the array
    if (sort_type == NAME) {
        bubble_sort(lines, lines + num_lines - 1);
    } else {
        quick_sort(lines, lines + num_lines - 1, sort_type);
    }


    // print the array
    for (int i = 0; i < num_lines; i++) {
        fprintf(stdout, "%s,%d,%d,%d\n", lines[i].name, lines[i].distance, lines[i].duration, lines[i].stops);
    }


    // free allocated memory
    free(lines);

    return EXIT_SUCCESS;
}
