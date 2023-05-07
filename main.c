#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define limit 10

  struct room {
    int occupancy;
    int age;
    int id;

    char first[40];
    char last[40];

    bool executive;
    bool business;
    bool economy;
    bool occupied;
  };

//function prototype for converting commands to uppercase
void convert(char input[50]);

int main() {

  char command[50];

  //for scanning in floor
  int floor;

  //keeping track of current index per each floor
  int current_index1 = 11;
  int current_index2 = 0;
  int current_index3 = 11;

  //for scanning in occupancy of a room booked
  int occupancy;

  //counting specific room occupancy
  int thirdOccupied = 0;
  int firstOccupied = 0;
  int secondOccupied = 0;

  //counting rooms per floor for calculating rate
  int economy = 0;
  int business = 0; 
  int executive = 0;
  
  //for name input
  char first[40];
  char last[40];

  char ch;
  char read;

  //create array of structs
  struct room floor1[limit];
  struct room floor2[limit];
  struct room floor3[limit];
  
  //init the rooms based on their type
  for (int i = 0; i < limit; ++i) {
    floor1[i].economy = true;
    floor2[i].business = true;
    floor3[i].executive = true;
  }

  for (int i = 0; i < limit; ++i) {
    floor1[i].occupancy = 0;
    floor2[i].occupancy = 0;
    floor3[i].occupancy = 0;
  }

  for (int i = 0; i < limit; ++i) {
    floor1[i].occupied = false;
    floor2[i].occupied = false;
    floor3[i].occupied = false;
  }

  for (;;) {

    printf("What would you like to do?\n"); 
    printf("COMMANDS: BOOK, LEAVE, LIST, INCOME, COUNT, READ, WRITE, QUIT, \n");
    printf(">> ");
    scanf("%49s", command);
    convert(command);

    if (strcmp(command, "BOOK") == 0) {
      printf("Which floor would you like?\n");
      printf(">> ");

      if (scanf("%d", &floor) != 1 || floor > 3 || floor < 1) {
        printf("Input a number from 1 to 3; there are 3 floors\n");
        printf("\n");
      }

      else {
        switch (floor) {
          case 1:

            printf("Enter your first name: ");
            scanf("%39s", first);
            fflush(stdin);
            printf("\n");

            printf("Enter your last name: "); 
            scanf("%39s", last);
            fflush(stdin);
            printf("\n");

            printf("Enter the number of occupancies: ");
            if (scanf("%d", &occupancy) != 1 || occupancy > 4 || occupancy < 0) {
              printf("\n");
              printf("Invalid Input. Enter an occupancy number between 0 and 4 inclusive.\n\n");
              fflush(stdin);
              break;
            }
            else if (current_index1 <= 10) {
              strcpy(floor1[current_index1].first, first);
              strcpy(floor1[current_index1].last, last);
              floor1[current_index1].occupancy = occupancy;
              floor1[current_index1].occupied = true;
              ++current_index1;
            }

            else {
              //moving to floor2 logic but with economy rate pricing
              if (current_index2 <= 10) {
                printf("The rooms on this floor is full!\n");
                printf("Moving you to Floor 2...\n\n");

                strcpy(floor2[current_index2].first, first);
                strcpy(floor2[current_index2].last, last);

                floor2[current_index2].occupancy = occupancy;
                floor2[current_index2].occupied = true;
                floor2[current_index2].economy = true;
                floor2[current_index2].business = false;
                ++current_index2;
              }
              //moving to floor3 logic but with economy pricing
              else if (current_index2 > 10 && current_index3 <= 10) {
                printf("Initially moved to floor 2\n");
                printf("Turns out Floor 2 is also full!\n");
                printf("Moving you to floor 3...\n\n"); 

                strcpy(floor3[current_index3].first, first);
                strcpy(floor3[current_index3].last, last);

                floor3[current_index3].occupancy = occupancy;
                floor3[current_index3].occupied = true;
                floor3[current_index3].executive = false;
                floor3[current_index3].business = false;
                floor3[current_index3].economy = true;
                ++current_index3;
              }

              else if (current_index3 > 10) {
                printf("\x1b[31m THE HOTEL IS FULL. \x1b[0m  \n");
                printf("You cannot book any more rooms :(\n\n");
              }
            }
            break;

          case 2:
            printf("Enter your first name: ");
            scanf("%39s", first);
            printf("\n");

            printf("Enter your last name: "); 
            scanf("%39s", last);
            printf("\n");

            printf("Enter the number of occupancies: "); 
            if (scanf("%d", &occupancy) != 1 || occupancy > 4 || occupancy < 0) {
              printf("\n");
              printf("Invalid Input. Enter an occupancy number between 0 and 4 inclusive.\n\n");
              fflush(stdin);
              break;
            }

            else if (current_index2 <= 10){
              strcpy(floor2[current_index2].first, first);
              strcpy(floor2[current_index2].last, last);
              floor2[current_index2].occupancy = occupancy;
              floor2[current_index2].occupied = true;
              ++current_index2;
            }
            else {
              //moving to floor3 logic but with business rate pricing
              if (current_index3 <= 10) {

                printf("The rooms on this floor is full!\n");
                printf("Moving you to Floor 3...\n\n");

                strcpy(floor3[current_index3].first, first);
                strcpy(floor3[current_index3].last, last);

                floor3[current_index3].occupancy = occupancy;
                floor3[current_index3].occupied = true;
                floor3[current_index3].executive = false;
                floor3[current_index3].business = true;
                ++current_index3;
              }
              //moving to floor1 logic but with business rate pricing
              else if (current_index3 > 10 && current_index1 <= 10) {
                printf("Initially moved to floor 3\n");
                printf("Turns out Floor 3 is also full!\n");
                printf("Moving you to floor 1...\n\n"); 

                strcpy(floor1[current_index1].first, first);
                strcpy(floor1[current_index1].last, last);

                floor1[current_index1].occupancy = occupancy;
                floor1[current_index1].occupied = true;
                floor1[current_index1].executive = false;
                floor1[current_index1].business = true;
                floor1[current_index1].economy = false;
                ++current_index1;
              }
              else {
                printf("\x1b[31m THE HOTEL IS FULL. \x1b[0m  \n");
                printf("You cannot book any more rooms :(\n\n");
              }
            }
            break;

          case 3:
            printf("Enter your first name: ");
            scanf("%39s", first);
            printf("\n");

            printf("Enter your last name: "); 
            scanf("%39s", last);
            printf("\n");

            printf("Enter the number of occupancies: ");
            if (scanf("%d", &occupancy) != 1 || occupancy > 4 || occupancy < 0) {
              printf("\n");
              printf("Invalid Input. Enter an occupancy number between 0 and 4 inclusive.\n\n");
              fflush(stdin);
              break;
            }

            else if (current_index3 <= 10) {
              strcpy(floor3[current_index3].first, first);
              strcpy(floor3[current_index3].last, last);
              floor3[current_index3].occupancy = occupancy;
              floor3[current_index3].occupied = true;
              ++current_index3;
            }
            else {
              printf("The rooms on this floor is full!\n");

              if (current_index1 <= 10 && current_index3 > 10) {
                printf("Moving you to floor 1...\n\n");
                strcpy(floor1[current_index1].first, first);
                strcpy(floor1[current_index1].last, last);
                floor1[current_index1].occupancy = occupancy;
                floor1[current_index1].occupied = true;
                floor1[current_index1].economy = false;
                floor1[current_index1].business = false;
                floor1[current_index1].executive = true;
                ++current_index1;
              }

              else if (current_index1 > 10 && current_index2 <= 10) {
                //floor 1 is full but floor 2 is open
                printf("Initially moved to floor1...\n");
                printf("Turns out floor 1 is also full!\n\n");
                printf("Moving to floor 2 instead...\n");

                strcpy(floor2[current_index2].first, first);
                strcpy(floor2[current_index2].last, last);
                floor2[current_index2].occupancy = occupancy;
                floor2[current_index2].occupied = true;
                floor2[current_index2].economy = false;
                floor2[current_index2].business = false;
                floor2[current_index2].executive = true;
                ++current_index2;
              }
              else {
                printf("\x1b[31m THE HOTEL IS FULL. \x1b[0m  \n");
                printf("You cannot book any more rooms :(\n\n");
              }
            }
          break;
        }
      }
    }

    else if (strcmp(command, "LIST") == 0) {
      printf("Which floor would you like to list the occupied rooms?\n");
      printf("Enter floor number: ");

      if (scanf("%d", &floor) != 1 || floor > 3 || floor < 1) {
        printf("Please input a valid floor number\n");
      }

      else if (floor == 1) {
        printf("\n");
        int check = 0; 
        for (int i = 0; i < 10; ++i) {
          if (floor1[i].occupied == true) {
            ++check;
            printf("FIRST NAME: %s", floor1[i].first);
            printf("\n");
            printf("LAST NAME: %s", floor1[i].last);
            printf("\n");
            printf("# OF OCCUPANTS: %d", floor1[i].occupancy);
            printf("\n");
            printf("\n");
          }
          else {
            continue;
          }
        }
        if (check == 0)
          printf("The floor is empty!\n\n");
          
      }
      else if (floor == 2) {
        printf("\n");
        int check2 = 0;
        for (int i = 0; i < 10; ++i) {
          if (floor2[i].occupied == true) {
            ++check2;
            printf("FIRST NAME: %s", floor2[i].first);
            printf("\n");
            printf("LAST NAME: %s", floor2[i].last);
            printf("\n");
            printf("# OF OCCUPANTS: %d", floor2[i].occupancy);
            printf("\n");
            printf("\n");
          }
          else {
            continue;
          }
      }
      if (check2 == 0)
        printf("The floor is empty!\n\n");
    }
      else if (floor == 3) {
        printf("\n");
        int check3 = 0;
        for (int i = 0; i < 10; ++i) {
          if (floor3[i].occupied == true) {
            ++check3;
            printf("FIRST NAME: %s", floor3[i].first);
            printf("\n");
            printf("LAST NAME: %s", floor3[i].last);
            printf("\n");
            printf("# OF OCCUPANTS: %d", floor3[i].occupancy);
            printf("\n");
            printf("\n");
          }
          else {
            continue;
          }
      }
      if (check3 == 0)
        printf("The floor is empty!\n\n");
      }
    }

    else if (strcmp(command, "COUNT") == 0) {

        for (int i = 0; i < 10; ++i) {
          if (floor1[i].occupied == true) {
            firstOccupied += floor1[i].occupancy;
          }
          else 
            continue;
        }
        for (int i = 0; i < 10; ++i) {
          if (floor2[i].occupied == true) {
            secondOccupied += floor2[i].occupancy;
          }
          else 
            continue;
        }

        for (int i = 0; i < 10; ++i) {
          if (floor3[i].occupied == true) {
              thirdOccupied += floor3[i].occupancy;
          }
          else 
            continue;
        }
        printf("Occupants in First floor: %d\n", firstOccupied);
        printf("Occupants in Second floor: %d\n", secondOccupied);
        printf("Occupants in Third floor: %d\n", thirdOccupied);

        int totalOccupants = firstOccupied + secondOccupied + thirdOccupied;
        printf("The total occupants in this hotel is: %d\n", totalOccupants);
        printf("\n");

        //set counter back so it can be ready to count again when command is called
        totalOccupants = 0;
        firstOccupied = 0;
        secondOccupied = 0;
        thirdOccupied = 0;
    }

    else if (strcmp(command, "INCOME") == 0) {
      for (int i = 0; i < 10; ++i) {
        if(floor1[i].occupied == true && floor1[i].economy == true) {
          ++economy;
        }
        else if(floor1[i].occupied == true && floor1[i].business == true) {
          ++business;
        }
        else if(floor1[i].occupied == true && floor1[i].executive == true) {
          ++executive;
        }
        else
          continue;
      }
      for (int i = 0; i < 10; ++i) {
        if(floor2[i].occupied == true && floor2[i].business == true) {
          ++business;
        }
        else if(floor2[i].occupied == true && floor2[i].economy == true) {
          ++economy; 
        }
        else if(floor2[i].occupied == true && floor2[i].executive == true) {
          ++executive; 
        }
        else 
          continue;
      }
      for (int i = 0; i < 10; ++i) {
        if(floor3[i].occupied == true && floor3[i].executive == true) {
          ++executive;
        }
        else if(floor3[i].occupied == true && floor3[i].business == true) {
          ++business;
        }
        else if(floor3[i].occupied == true && floor3[i].economy == true) {
          ++economy;
        }
        else 
          continue;
      }

      int floor1Rate = (economy * 80);
      int floor2Rate = (business * 90);
      int floor3Rate = (executive * 100);

      printf("Floor 1 rate: %d\n", floor1Rate);
      printf("Floor 2 rate: %d\n", floor2Rate);
      printf("Floor 3 rate: %d\n", floor3Rate);

      int total_income = (floor1Rate + floor2Rate + floor3Rate);
      
      printf("The Total Gross Income for tonight is: %d\n\n", total_income);
      
      //reset the count so we dont duplicatate counts
      total_income = 0;
      economy = 0;
      business = 0; 
      executive = 0;

    }

    else if (strcmp(command, "WRITE") == 0) {

        //FILE
        FILE *fptr;
        fptr = fopen("output.txt","w");

        if(fptr == NULL) {
          printf("Error!"); 
          exit(1); 
        }

        do {
          ch = getc(fptr);
          for (int i = 0; i < 10; ++i) {
            if (floor1[i].occupied == true) {
              fprintf(fptr, "FIRST NAME: %s", floor1[i].first);
              fprintf(fptr, "\n");
              fprintf(fptr, "LAST NAME: %s", floor1[i].last);
              fprintf(fptr, "\n");
              fprintf(fptr, "# OF OCCUPANTS: %d", floor1[i].occupancy);
              fprintf(fptr, "\n");
              fprintf(fptr, "\n");
            }
            else {
              continue;
            }
          }
          for (int i = 0; i < 10; ++i) {
            if (floor2[i].occupied == true) {
              fprintf(fptr, "FIRST NAME: %s", floor2[i].first);
              fprintf(fptr, "\n");
              fprintf(fptr, "LAST NAME: %s", floor2[i].last);
              fprintf(fptr, "\n");
              fprintf(fptr, "# OF OCCUPANTS: %d", floor2[i].occupancy);
              fprintf(fptr, "\n");
              fprintf(fptr, "\n");
            }
            else {
              continue;
            }
          }
          for (int i = 0; i < 10; ++i) {
            if (floor3[i].occupied == true) {
              fprintf(fptr, "FIRST NAME: %s", floor3[i].first);
              fprintf(fptr, "\n");
              fprintf(fptr, "LAST NAME: %s", floor3[i].last);
              fprintf(fptr, "\n");
              fprintf(fptr, "# OF OCCUPANTS: %d", floor3[i].occupancy);
              fprintf(fptr, "\n");
              fprintf(fptr, "\n");
            }
            else {
              continue;
            }
          }
        } while (ch != EOF);
        printf("Written to file!\n\n");
        fclose(fptr);
    }

    else if (strcmp(command, "READ") == 0) {
        FILE *fptr;
        fptr = fopen("output.txt","r");

        if(fptr == NULL) {
          printf("Error!"); 
          exit(1); 
        }
          
        printf("Outputted Save File: \n\n");

        do {
          
          read = getc(fptr);
          printf("%c", read);
                
        } while (read != EOF);

        fclose(fptr);
    }

    else if (strcmp(command, "QUIT") == 0) {
      printf("Thank you for your time.\n");

      //this break essentally breaks out of the for(;;)
      //stops the program as a result
      break;
    }

    else {
      printf("Invalid input.\n");
      printf("\n");
    }
  }

  return 0;
}

void convert(char input[50]) {
//converts input in all uppercase
  for (int i = 0; i <= strlen(input); ++i) {
      input[i] = toupper(input[i]);
    }
}
