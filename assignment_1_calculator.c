/* Navn: Rune Bohnstedt Email: rbohns18@student.aau.dk Gruppe: a400B Studieretning: Software */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void run_calculator(void);
double scan_data(double *operand, char *operator);
double do_next_up(double *akkumulator, double *operand, char *operator);

/* Main som køre regnemaskinen.*/
int main(void) {
   run_calculator();
   return 0;
}
/* Funktion der samler regnemaskinen samt prompter brugeren.*/
void run_calculator(void) {
   double akkumulator = 0;
   double operand;
   char operator;
   
   while(!(operator == 'q')) {
      printf("Enter operator and an optional operand: ");
      scan_data(&operand, &operator);
      do_next_up(&akkumulator, &operand, &operator);

   if(operator != 'q')
      printf("Result so far is: %f \n", akkumulator);
   }
      printf("Final result is: %f \n", akkumulator);  
}
/* Funktion der scanner for bruger inputs.*/
double scan_data(double *operand, char *operator) {
   scanf(" %c", &*operator);

   if(*operator == '+' || *operator == '-' || *operator == '*' || *operator == '/' || *operator == '^')
      scanf(" %lf", &*operand);
      return 0;
}
/* Funktion der håndtere og beregner binære og unære operationer.*/
double do_next_up(double *akkumulator, double *operand, char *operator) {
   if(*operator == '+')
      *akkumulator = *akkumulator + *operand;

   else if(*operator == '-')
      *akkumulator = *akkumulator - *operand;

   else if(*operator == '*')
      *akkumulator = *akkumulator * *operand;

   else if(*operator == '/' && *operand != 0)
      *akkumulator = *akkumulator / *operand;

   else if(*operator == '^')
      *akkumulator = pow(*akkumulator,*operand);

   else if(*operator == '#' && *akkumulator > 0)
      *akkumulator = sqrt(*akkumulator);

   else if(*operator == '%')
      *akkumulator = -1 * *akkumulator;

   else if(*operator == '!')
      *akkumulator = 1 / *akkumulator;
   return 0;
}