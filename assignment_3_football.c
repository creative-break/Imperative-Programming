/* Navn: Rune Bohnstedt Email: rbohns18@student.aau.dk Gruppe: a400B Studieretning: Software */ 

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define WEEK_DAY 4
#define TEAM_SIZE 4
#define NUMBER_OF_GAMES 182
#define NUMBER_OF_TEAMS 14

struct games {
        char weekday[WEEK_DAY];
        int day;
        int month; 
        int hour; 
        int minute; 
        char team_one[TEAM_SIZE];
        char team_two[TEAM_SIZE];
        int team_one_goals;
        int team_two_goals;
        int spectaters;
};
typedef struct games games;

struct results {
        char team[NUMBER_OF_TEAMS];
        int points;
        int goals_scored;
        int goals_scored_against;
};
typedef struct results results;

void scan_file(games list[]);
void get_teams(results data[], games list[]);
void get_goals(results data[], games list[]);
void get_goals_against(results data[], games list[]);
void get_points(results data[], games list[]);
int cmp_function (const void *a, const void *b);
void sort_teams(results data[]);

/* Main funktioner, samler anvendte funktioner samt printer til prompt */
int main(void) {
    int i = 0;

    games list[NUMBER_OF_GAMES];
    results data[NUMBER_OF_TEAMS];

    /* Funktions kald */ 
    scan_file(list);
    get_teams(data, list);
    get_goals(data,list);
    get_goals_against(data, list);
    get_points(data,list);
    sort_teams(data);

    printf("\n Team\t Points\t Goals\t Goals against");

    for(i = 0; i < NUMBER_OF_TEAMS; i++) {
    printf("\n %s\t %d\t %d\t %d", data[i].team, data[i].points, data[i].goals_scored, 
                                    data[i].goals_scored_against);
    }
    return 0;
}
/* Funktion der anvender fopen, fgets og sscanf til at åbne txt fil, indlæse data og ligge dem i games array */
void scan_file(games list[]) {
    FILE *input_file;
    char line[100];
    int i = 0;

    input_file = fopen("kampe-2018-2019.txt", "r");

    if(input_file == NULL) {
        printf("Error retrieving file\n");
    }

    for(i = 0; i < NUMBER_OF_GAMES; i++) {
        fgets(line, sizeof(line), input_file);

        sscanf(line, "%s %d/%d %d.%d %s - %s %d - %d %d",
                    list[i].weekday,
                    &list[i].day,
                    &list[i].month,
                    &list[i].hour,
                    &list[i].minute,
                    list[i].team_one,
                    list[i].team_two,
                    &list[i].team_one_goals,
                    &list[i].team_two_goals,
                    &list[i].spectaters);
    }
    fclose(input_file);
}
/* Funktion der anvender strcpy til at kopiere holdnavnene fra games til results struct */
void get_teams(results data[], games list[]) {
    int i = 0;

    for(i = 0; i < 7; i++){
       strcpy(data[i].team, list[i].team_one);
    }
    for(i = 0; i < 7; i++){
       strcpy(data[i+7].team, list[i].team_two);
    }
}
/* Funktion der anvender strcomp til at finde antallet af mål holdet har scoret */ 
void get_goals(results data[], games list[]) {
    int i = 0, j = 0, ret = 0, ret2 = 0;

    for(j = 0; j < NUMBER_OF_TEAMS; j++) {
        int sum = 0, sum2 = 0;

        for(i = 0; i < NUMBER_OF_GAMES; i++) {
            ret = strcmp(list[i].team_one, data[j].team);
            ret2 = strcmp(list[i].team_two, data[j].team);
            
            if(ret == 0) {
                sum += list[i].team_one_goals;
            }
            if(ret2 == 0) {
               sum2 += list[i].team_two_goals;              
            }
             data[j].goals_scored = sum2 + sum;
        }
    }
}
/* Funktion der anvender strcomp til at finde antallet af mål scoret imod holdet */
void get_goals_against(results data[], games list[]) {
    int i = 0, j = 0, ret = 0, ret2 = 0;

    for(j = 0; j < NUMBER_OF_TEAMS; j++) {
        int sum = 0, sum2 = 0;

        for(i = 0; i < NUMBER_OF_GAMES; i++) {
            ret = strcmp(list[i].team_one, data[j].team);
            ret2 = strcmp(list[i].team_two, data[j].team);

            if(ret == 0) {
                sum += list[i].team_two_goals;
                }
            if(ret2 == 0) {
                sum2 += list[i].team_one_goals;
            }
            data[j].goals_scored_against = sum + sum2;
        }
    }
}
/* Funktion der der anvender strcmp til at dele points ud til de 14 hold baseret på mål i de enkelte kampe*/
void get_points(results data[], games list[]) {
    int i = 0, j = 0, ret = 0, ret2 = 0;

    for(j = 0; j < NUMBER_OF_TEAMS; j++) {
        int sum = 0, sum2 = 0;

        for(i = 0; i < NUMBER_OF_GAMES; i++) {
            ret = strcmp(list[i].team_one, data[j].team);
            ret2 = strcmp(list[i].team_two, data[j].team);

            if(ret == 0) {
               
                if(list[i].team_one_goals > list[i].team_two_goals) {
                    sum += 3;
                }
                else if(list[i].team_one_goals == list[i].team_two_goals) {
                    sum += 1;
                }
            }
            if(ret2 == 0) {
            
                if(list[i].team_two_goals > list[i].team_one_goals) {
                    sum2 += 3;
                }
                else if(list[i].team_two_goals == list[i].team_one_goals) {
                    sum2 += 1;
                }
            }    
                data[j].points = sum + sum2;
        } 
    }
}
/* Funktion der sammenligner points, og ved tilfælde af lige points sammenligner målforskel */
int cmp_function (const void *a, const void *b) {
    int goal_difference, goal_difference2;

    int cmp1 = ((struct results *)a)->points;
    int cmp2 = ((struct results *)b)->points;

    if(cmp1 == cmp2) {
        int cmp3 = ((struct results *)a)->goals_scored;
        int cmp4 = ((struct results *)b)->goals_scored;

        int cmp5 = ((struct results *)a)->goals_scored_against;
        int cmp6 = ((struct results *)b)->goals_scored_against;

        goal_difference = cmp3 - cmp5;
        goal_difference2 = cmp4 - cmp6;

        return (goal_difference2 - goal_difference);
    }
    return (cmp2 - cmp1);
}
/* qsort funktion der anvender cmpfunc, til at sortere results struct */
void sort_teams(results data[]) {

     qsort(data, NUMBER_OF_TEAMS, sizeof(results), cmp_function);
}