// --------------------------------------------------------------------------------
// Name: Derrick Warren
// Class: SET-151 C Programming 1
// Abstract: Census Bureau Final Project - Data Collection Application
// 
// This application will collect data from the user for a census bureau survey.  
// --------------------------------------------------------------------------------

// --------------------------------------------------------------------------------
// Includes – built-in libraries of functions
// --------------------------------------------------------------------------------
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <string.h>

// --------------------------------------------------------------------------------
// Constants
// --------------------------------------------------------------------------------
const long lngARRAY_SIZE = 100;
#define MAX_SELECTION 2
#define MAX_OCCUPANTS_DIGITS 4
#define MIN_OCCUPANTS_DIGITS 1

// --------------------------------------------------------------------------------
// User Defined Types (UDT)
// --------------------------------------------------------------------------------
typedef int boolean;

// tm is a built in struct related to time() library funtion 
typedef struct tm dtmDate;

// --------------------------------------------------------------------------------
// Prototypes
// --------------------------------------------------------------------------------
int GetDate(struct tm* dtmDate, int intDay, int intMonth, int intYear);
char GetState(char strUserInput[], char strState[]);
char GetCounty(char strUserInput[], char strState[], char strCounty[]);
char GetRace(char strUserInput[], char strRace[]);
int GetHouseholdNumber(int intUserInput, int intHouseholdNumber);
float GetIncome(float sngUserInput, float sngIncome);

void AppendInputToFile(struct tm* dtmDate, char strState[], char strCounty[], char strRace[],
    int intHouseholdNumber, float sngIncome);

int AddMoreHouseholds(int intRunProgram, char chrYesOrNo);

// --------------------------------------------------------------------------------
// Name: main
// Abstract: This is where the program starts
// --------------------------------------------------------------------------------
void main()
{
    // built in struct from time() library function
    struct tm* dtmDate;

    // variables used to keep program running to add additional households
    char chrYesOrNo = ' ';
    int intRunProgram = 0;

    // variables to store date 
    int intDay = 0;
    int intMonth = 0;
    int intYear = 0;

    // variables for "Get" Functions
    char strState[25] = "";
    char strCounty[25] = "";
    char strRace[25] = "";
    int intHouseholdNumber = 0;
    float sngIncome = 0;

    // variables for User Input
    char strUserInput[2] = "";
    int intUserInput = 0;
    float sngUserInput = 0;

    // Header
    printf("########################################\n");
    printf("#### Census Bureau Survey ##############\n");
    printf("########################################\n");

    // loop used to run program until user chooses to exit
    do
    {
        // --------------------------------------------------------------------------------
        // Name: Call Functions
        // --------------------------------------------------------------------------------
        dtmDate = GetDate(&dtmDate, intDay, intMonth, intYear);

        GetState(strUserInput, strState);

        GetCounty(strUserInput, strState, strCounty);

        GetRace(strUserInput, strRace);

        intHouseholdNumber = GetHouseholdNumber(intUserInput, intHouseholdNumber);

        sngIncome = GetIncome(sngUserInput, sngIncome);

        AppendInputToFile(dtmDate, strState, strCounty, strRace, intHouseholdNumber, sngIncome);

        intRunProgram = AddMoreHouseholds(intRunProgram, chrYesOrNo);

    } while (intRunProgram != 0);

    // Goodbye message
    printf("****** Exiting Program ******\n");
    printf("********   Goodbye   ********\n\n");

    system("pause");
}


// --------------------------------------------------------------------------------
// Name: GetDate
// Abstract: This will calculate the current date
// --------------------------------------------------------------------------------
int GetDate(struct tm* dtmDate, int intDay, int intMonth, int intYear)
{
    // variable using time_t data type
    // this is a part of the time() library function
    // it will allow for calculating the current date
    time_t dtmCurrentDate;

    // the time() function in this case returns the time 
    // since 00:00:00 UTC, January 1, 1970 (Unix timestamp) in seconds.
    // it calculates the seconds in order to get the current date
    time(&dtmCurrentDate);

    // dtmDate argument stores the current date
    dtmDate = localtime(&dtmCurrentDate);

    intDay = dtmDate->tm_mday;            // get day of month (1 to 31)
    intMonth = dtmDate->tm_mon + 1;       // get month of year (0 to 11)
    intYear = dtmDate->tm_year + 1900;    // get year since 1900

    // print current date to console
    printf("%02d/%02d/%d\n\n", intMonth, intDay, intYear);

    return dtmDate;

}


// --------------------------------------------------------------------------------
// Name: GetState
// Abstract: This will get the state from user input
// --------------------------------------------------------------------------------
char GetState(char strUserInput[], char strState[])
{
    // variable for converting to user selection string value
    char astrState[2][9] = { "Ohio", "Kentucky" };

    int intResultFlag = 0;

    // loop until user input is valid
    do
    {
        // ask user for input for state
        printf("**Select State**\n");
        printf("A = Ohio\n");
        printf("B = Kentucky\n");
        printf("Selection: ");

        // flushes the standard input 
       // (clears the input buffer) 
       // while ( ( getchar() ) != '\n' );

        // receive input for state
        fgets(strUserInput, MAX_SELECTION, stdin);

        if (strUserInput[0] == 'A' || strUserInput[0] == 'a')
        {
            // copy string literal from array into strState 
            strcpy(strState, astrState[0]);
            intResultFlag = 1;
        }
        else if (strUserInput[0] == 'B' || strUserInput[0] == 'b')
        {
            strcpy(strState, astrState[1]);
            intResultFlag = 1;
        }
        else
        {
            // alert user if input is invalid
            printf("Error! Answer must be 'A' or 'B'.\n\n");
            intResultFlag = 0;
        }
    } while (intResultFlag == 0);

    // print to console for sample output
    printf("%s\n\n", strState);

    return strState;
}


// --------------------------------------------------------------------------------
// Name: GetCounty
// Abstract: This will get the state from user input
// --------------------------------------------------------------------------------
char GetCounty(char strUserInput[], char strState[], char strCounty[])
{
    // variable for converting to user selection string value
    char astrCounty[4][9] = { "Hamilton", "Butler", "Boone", "Kenton" };

    int intResultFlag = 0;

    // loop until user input is valid
    do
    {
        // ask user for input for county
        printf("**Select County**\n");
        printf("1 = Hamilton\n");
        printf("2 = Butler\n");
        printf("3 = Boone\n");
        printf("4 = Kenton\n");
        printf("Selection: ");

        // flushes the standard input 
        // (clears the input buffer) 
        while ((getchar()) != '\n');

        // receive input for county
        fgets(strUserInput, MAX_SELECTION, stdin);

        if (strState[0] == 'O' && strUserInput[0] == '1')
        {
            // copy string literal from array into strCounty 
            strcpy(strCounty, astrCounty[0]);
            intResultFlag = 1;
        }
        else if (strState[0] == 'O' && strUserInput[0] == '2')
        {
            strcpy(strCounty, astrCounty[1]);
            intResultFlag = 1;
        }
        else if (strState[0] == 'K' && strUserInput[0] == '3')
        {
            strcpy(strCounty, astrCounty[2]);
            intResultFlag = 1;
        }
        else if (strState[0] == 'K' && strUserInput[0] == '4')
        {
            strcpy(strCounty, astrCounty[3]);
            intResultFlag = 1;
        }
        else
        {
            // alert user that input is invalid
            printf("Error! Selection must be valid county for state.\n");
            printf("1 or 2 = Ohio, 3 or 4 = Kentucky\n\n");
            intResultFlag = 0;
        }
    } while (intResultFlag == 0);

    // print to console for sample output
    printf("%s\n\n", strCounty);

    return strCounty;
}


// --------------------------------------------------------------------------------
// Name: GetRace
// Abstract: This will get the race from user input
// --------------------------------------------------------------------------------
char GetRace(char strUserInput[], char strRace[])
{
    // variable for converting to user selection string value
    char astrRace[5][17] = { "Caucasian", "African American", "Hispanic", "Asian", "Other" };

    int intResultFlag = 0;

    // loop until user input is valid
    do
    {
        // ask user for input for race
        printf("**Select Race**\n");
        printf("1 = Caucasian\n");
        printf("2 = African American\n");
        printf("3 = Hispanic\n");
        printf("4 = Asian\n");
        printf("5 = Other\n");
        printf("Selection: ");

        // flushes the standard input 
        // (clears the input buffer) 
        while ((getchar()) != '\n');

        // receive input for race
        fgets(strUserInput, MAX_SELECTION, stdin);

        if (strUserInput[0] == '1')
        {
            // copy string literal from array into strRace 
            strcpy(strRace, astrRace[0]);
            intResultFlag = 1;
        }
        else if (strUserInput[0] == '2')
        {
            strcpy(strRace, astrRace[1]);
            intResultFlag = 1;
        }
        else if (strUserInput[0] == '3')
        {
            strcpy(strRace, astrRace[2]);
            intResultFlag = 1;
        }
        else if (strUserInput[0] == '4')
        {
            strcpy(strRace, astrRace[3]);
            intResultFlag = 1;
        }
        else if (strUserInput[0] == '5')
        {
            strcpy(strRace, astrRace[4]);
            intResultFlag = 1;
        }
        else
        {
            // alert user that input is invalid
            printf("Error! Selection must be '1', '2', '3', '4', or '5'.\n\n");
            intResultFlag = 0;
        }
    } while (intResultFlag == 0);

    // print to console for sample output
    printf("%s\n\n", strRace);

    return strRace;
}


// --------------------------------------------------------------------------------
// Name: GetHouseholdNumber
// Abstract: This will get the number of household members from user input
// --------------------------------------------------------------------------------
int GetHouseholdNumber(int intUserInput, int intHouseholdNumber)
{
    int intResultFlag = 0;

    // loop until user input is valid
    do
    {
        // ask user for input for number of household occupants
        printf("**Enter Number of Household Occupants**\n");
        printf("Number of Household Occupants: ");

        // flushes the standard input 
        // (clears the input buffer) 
        while ((getchar()) != '\n');

        scanf(" %d", &intUserInput);

        // if no input was entered or invalid input then alert user
        if (intUserInput < 1 || intUserInput > 100)
        {
            printf("Error! Enter a valid number of household occupants (1-100).\n\n");
            intResultFlag = 0;
        }
        else
        {
            // set Household Number to value input from user
            intHouseholdNumber = intUserInput;
            intResultFlag = 1;
        }

    } while (intResultFlag == 0);

    // print to console for sample output
    printf("%d\n\n", intHouseholdNumber);

    return intHouseholdNumber;

}

// --------------------------------------------------------------------------------
// Name: GetIncome
// Abstract: This will get the income of the household from user input
//  --------------------------------------------------------------------------------
float GetIncome(float sngUserInput, float sngIncome)
{
    int intResultFlag = 0;

    // loop until user input is valid
    do
    {
        // ask user for input for household income
        printf("**Enter Income for Household**\n");
        printf("Income for Household: ");

        // flushes the standard input 
        // (clears the input buffer) 
        while ((getchar()) != '\n');

        scanf(" %f", &sngUserInput);

        // if no input was entered or invalid input then alert user
        if (sngUserInput <= 0)
        {
            printf("Error! Enter a valid value for household income (i.e. XXXXX.XX).\n\n");
            intResultFlag = 0;
        }
        else
        {
            // set Household Income to value input from user
            sngIncome = sngUserInput;
            intResultFlag = 1;
        }
    } while (intResultFlag == 0);

    // print to console for sample output
    printf("$%.2f\n\n", sngIncome);

    return sngIncome;
}


// --------------------------------------------------------------------------------
// Name: AppendInputToFile
// Abstract: Copy the input to a text file
// --------------------------------------------------------------------------------
void AppendInputToFile(struct tm* dtmDate, char strState[], char strCounty[], char strRace[],
    int intHouseholdNumber, float sngIncome)
{
    // Declare a file pointer
    FILE* pfilFilePointer;

    // Open file
    pfilFilePointer = fopen("/temp/test.txt", "a+");

    // Alert user if file wasn't opened
    if (pfilFilePointer == NULL)
    {
        printf("Error! ");
        exit(1);
    }

    // Append to text file
    fprintf(pfilFilePointer, "%02d/%02d/%d, ", dtmDate->tm_mon + 1, dtmDate->tm_mday, dtmDate->tm_year + 1900);
    fprintf(pfilFilePointer, "%s, ", strState);
    fprintf(pfilFilePointer, "%s, ", strCounty);
    fprintf(pfilFilePointer, "%s, ", strRace);
    fprintf(pfilFilePointer, "%d, ", intHouseholdNumber);
    fprintf(pfilFilePointer, "%.2f\n", sngIncome);

    // Clean up
    fclose(pfilFilePointer);

}


// --------------------------------------------------------------------------------
// Name: AddMoreHouseholds
// Abstract: See if user wants to add more households
// --------------------------------------------------------------------------------
int AddMoreHouseholds(int intRunProgram, char chrYesOrNo)
{
    printf("Would you like to enter data for another household? (Y/N) ");
    scanf(" %c", &chrYesOrNo);
    printf("\n");

    // flushes the standard input 
    // (clears the input buffer) 
    while ((getchar()) != '\n');

    if (chrYesOrNo == 'Y' || chrYesOrNo == 'y')
    {
        intRunProgram = 1;
    }
    else
    {
        intRunProgram = 0;
    }

    return intRunProgram;
}