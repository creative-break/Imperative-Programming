/* Navn: Rune Bohnstedt Email: rbohns18@student.aau.dk Gruppe: a400B Studieretning: Software */ 

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define DIE_MAX_EYES 6
#define TABLE_SIZE 6
#define SCOREBOARD_SIZE 16

void roll_dies(int _table[], int _n);
void play_yatzy();
void table_clear(int _table[]);
void score_clear(int _scoreboard[]);
void one_too_six(int _table[], int _scoreboard[], int _n);
void bonus(int _scoreboard[]);
void one_pair(int _table[], int _scoreboard[], int _n);
void two_pairs(int _table[], int _scoreboard[], int _n);
void three_of_a_kind(int _table[], int _scoreboard[], int _n);
void four_of_a_kind(int _table[], int _scoreboard[], int _n);
void low_straight(int _table[], int _scoreboard[], int _n);
void high_straight(int _table[], int _scoreboard[], int _n);
void full_house(int _table[], int _scoreboard[], int _n);
void chance(int _table[], int _scoreboard[], int _n);
void yatzy(int _table[], int _scoreboard[], int _n);
void score_board(int _scoreboard[]);

int main(void) {
    srand(time(NULL));
    play_yatzy();
    return 0;
}

/* Funktion der samler alle funktioner, samt prompter og printer */
void play_yatzy() {
    int table[TABLE_SIZE] = {0};
    int scoreboard[SCOREBOARD_SIZE] = {0};
    int n = 0;
    
    do {
    printf("Enter the numbers of dices you want to play with below 5 terminates: ");
    scanf("%d", &n);

    if (n < 5) {
        printf("Bye \n");
        exit(0);
    }
    
    /* Funktions kald der køre igennem funktionerne for yatzy */
    one_too_six(table, scoreboard, n);
    bonus(scoreboard);
    one_pair(table, scoreboard, n);
    two_pairs(table, scoreboard, n);
    three_of_a_kind(table, scoreboard, n);
    four_of_a_kind(table, scoreboard, n);
    low_straight(table, scoreboard, n);
    high_straight(table, scoreboard, n);
    full_house(table, scoreboard, n);
    chance(table, scoreboard, n);
    yatzy(table, scoreboard, n);
    
    /* Print statements der printer de forskellige scores */
    printf("\nCATEGORY\t POINTS\t\n");
    printf("SUM OF 1s:\t %d\n", scoreboard[0]);
    printf("SUM OF 2s:\t %d\n", scoreboard[1]);
    printf("SUM OF 3s:\t %d\n", scoreboard[2]);
    printf("SUM OF 4s:\t %d\n", scoreboard[3]);
    printf("SUM OF 5s:\t %d\n", scoreboard[4]);
    printf("SUM OF 6s:\t %d\n", scoreboard[5]);

    printf("\nBONUS:\t\t %d\n", scoreboard[6]);
    printf("\nONE PAIR:\t %d\n", scoreboard[7]);
    printf("TWO PAIRS:\t %d\n", scoreboard[8]);
    printf("THREE OF A KIND: %d\n", scoreboard[9]);
    printf("FOUR OF A KIND:\t %d\n", scoreboard[10]);
    printf("LOW STRAIGHT:\t %d\n", scoreboard[11]);
    printf("HIGH STRAIGHT:\t %d\n", scoreboard[12]);
    printf("FULL HOUSE:\t %d\n", scoreboard[13]);
    printf("CHANCE:\t\t %d \n", scoreboard[14]);
    printf("YATZY:\t\t %d\n", scoreboard[15]);

    /*Funktion der holder styr på den totale score */
    score_board(scoreboard);
    printf("TOTAL SCORE:\t %d\n", scoreboard[16]);
    }
    while(n > 4);
}
/* Herfra funktioner der bliver brugt i play_yatzy
   Funktion der simulere et terningekast vha rand funktion samt table_clear der rydder table før hvert kast */
void roll_dies(int _table[], int _n) {
    int i = 0;

    table_clear(_table);

    for (i = 0; i < _n; i++) {
        int roll = (rand() % DIE_MAX_EYES) + 1;
         
        _table[roll -1]++;
    }
}
/* Funktion der tæller samlet score, samt rydder efter hvert spil */
void score_board(int _scoreboard[]) {
    int i = 0, sum = 0;

    for (i = 0; i <= 15; i++) {
        sum = sum + _scoreboard[i];
        _scoreboard[16] = sum;
    }
    score_clear(_scoreboard);
}

/* Funktion der anvendes til at rydde terningekast */
void table_clear(int _table[]) {
    int i = 0;

    for (i = 0; i < 6; i++)
        _table[i] = 0;
}

/* Funktion der anvendes til at rydde score */
void score_clear(int _scoreboard[]) {
    int i = 0;

    for (i = 0; i < SCOREBOARD_SIZE; i++)
        _scoreboard[i] = 0;
}

/* Funktion der udregner fra 1 til 6 */
void one_too_six(int _table[], int _scoreboard[], int _n) {
    int i = 0;

    for (i = 0; i < 6; i++) {

        roll_dies(_table, _n);

        if(_table[i] > 5) {
           _scoreboard[i] = (i + 1) * 5;
        }
        else {
            _scoreboard[i] = (_table[i] * (i + 1));
        }
    }
}

/* Funktion der bestemmer om der er opnået bonus */
void bonus(int _scoreboard[]) {
    int i = 0, sum = 0, bonus = 50;

    for(i = 0; i < 6; i ++) {
        sum = sum + _scoreboard[i];
    }
    if(sum >= 64) {
    _scoreboard[6] = bonus;
    }
}

/* Funktion der afgør om der er et par og finder det højest mulige */ 
void one_pair(int _table[], int _scoreboard[], int _n) {
    int i = 0;

    roll_dies(_table, _n);

    for(i = 5; i >= 0; i--) {
        if(_table[i] >= 2) {
        _scoreboard[7] = (i + 1) * 2;
        }
        if(_scoreboard[7] == (i + 1) * 2) {
        break;
        }
    }
}
/* Funktion der finder to par ved først at lede efter det højeste par, og dernæst lede efter det næsthøjeste par */
void two_pairs(int _table[], int _scoreboard[], int _n) {
int i = 0, j = 0, sum1 = 0, sum2 = 0, tablei = 0;

    roll_dies(_table, _n);

    for(i = 5; i >= 0; i--) {
        if(_table[i] >= 2) {
            sum1 = (i + 1) * 2;
            tablei = i;
        }
        if(sum1 == ((i + 1) * 2))
        break;
        }
    for(j = 5; j >= 0; j--) {
        if(_table[j] >= 2 && j != tablei) {
        sum2 = (j + 1) * 2;
        _scoreboard[8] = sum1 + sum2;
        }
        if(sum2 == ((j + 1) * 2)) {
        break;
        }
    }   
}
/* Funktion der afgør om der er 3 ens og finder den højeste mulige score */
void three_of_a_kind(int _table[], int _scoreboard[], int _n) {
    int i = 0;

    roll_dies(_table, _n);

    for(i = 5; i >= 0; i--) {
        if(_table[i] >= 3) {
        _scoreboard[9] = (i + 1) * 3;
        }
        if(_scoreboard[9] == (i + 1) * 3) {
        break;
        }
    }
}
/* Funktion der afgør om der er 4 ens og finder den højeste mulige score */
void four_of_a_kind(int _table[], int _scoreboard[], int _n) {
    int i = 0;

    roll_dies(_table, _n);

    for(i = 5; i >= 0; i--) {
        if(_table[i] >= 3) {
        _scoreboard[10] = (i + 1) * 4;
        }
        if(_scoreboard[10] == (i + 1) * 4) {
        break;
        }
    }
}
/* Funktion der afgør om der er en small straight, og giver point */
void low_straight(int _table[], int _scoreboard[], int _n) {
    int low = 15;

    roll_dies(_table, _n);

    if (_table[0] >= 1 && _table[1] >= 1 && _table[2] >= 1 && _table[3] >= 1 && _table[4] >= 1) {
        _scoreboard[11] = low;
    }
}
/* Funktion der afgør om der er en high straight og giver point */
void high_straight(int _table[], int _scoreboard[], int _n) {
    int high = 20;

    roll_dies(_table, _n);

    if (_table[1] >= 1 && _table[2] >= 1 && _table[3] >= 1 && _table[4] >= 1 && _table[5] >= 1) {
        _scoreboard[12] = high;
    }
}
/* Funktion der finder fuldt hus ved først at lede efter 3 ens
og dernæst lede efter 2 ens og undlader at lede på den plads der holder 3 ens */
void full_house(int _table[], int _scoreboard[], int _n) {
    int i = 0, j = 0, sum1 = 0, sum2 = 0, tablei = 0;

    roll_dies(_table, _n);

    for(i = 5; i >= 0; i--) {
        if(_table[i] >= 3) {
            sum1 = (i + 1) * 3;
            tablei = i;
        }
            if(sum1 == ((i + 1) * 3))
            break;
    }
    for(j = 5; j >= 0; j--) {
        if(_table[j] >= 2 && j != tablei) {
        sum2 = (j + 1) * 2;
        _scoreboard[13] = sum1 + sum2;
        }
        if(sum2 == ((j + 1) * 2)) {
        break;
        }
    }
}
/* Funktion der tæller 5 terninger op, ved at starte fra 6ere ned mod 1ere */ 
void chance(int _table[], int _scoreboard[], int _n) {
    int i = 0, sum = 0, cnt = 0, a = 0;

    roll_dies(_table, _n);

    for(i = 5; i >= 0; i--) {
        a = _table[i] + cnt;
        
        if(a >= 5)
            a = 5 - cnt;
        else
            a = _table[i];
        cnt += a;
        sum += (i + 1 ) * a;
        
        if(cnt >= 5)
        break;
    }
        _scoreboard[14] = sum;
}   
/* Funktion der finder yatzy ved at søge efter 5 ens terninger */
void yatzy(int _table[], int _scoreboard[], int _n) {
    int i = 0;

    roll_dies(_table, _n);

    for(i = 5; i >= 0; i--) {
        if(_table[i] >= 5) {
            _scoreboard[15] = (i + 1) * 5;  
        }
        if(_scoreboard[15] == (i + 1) * 5) {
        break;
        }
    }
}