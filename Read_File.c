// --------------------------------------------------------------------------------
// Name: Derrick Warren
// Class: SET-151 C Programming 1
// Abstract: Census Bureau Final Project - Data Read Application
// 
// This application will read data and print it from a text file for a census bureau survey.  
// --------------------------------------------------------------------------------

// --------------------------------------------------------------------------------
// Includes
// --------------------------------------------------------------------------------
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include <conio.h>
#include <string.h>

// --------------------------------------------------------------------------------
// Constants
// --------------------------------------------------------------------------------
const int intSTRUCTURE_ARRAY_SIZE = 100;
#define true 1
#define false 0
#define MIN_INCOME_1 12000
#define MIN_INCOME_2 18000
#define MIN_INCOME_3 25000
#define MIN_INCOME_4 30000
#define MIN_INCOME_5 40000

// --------------------------------------------------------------------------------
// User Defined Types (UDTs)
// --------------------------------------------------------------------------------
typedef int boolean;

typedef struct
{
	char dtmDate[25];
	char strState[50];
	char strCounty[50];
	char strRace[50];
	int intHouseholdNumber;
	float sngIncome;
} udtSurveyType;

// --------------------------------------------------------------------------------
// Prototypes
// --------------------------------------------------------------------------------
// functions to handle reading and formatting the text file
void InitializeSurveyList(udtSurveyType audtSurveyList[]);
void InitializeSurvey(udtSurveyType* pudtSurvey);

int PopulateSurveyList(udtSurveyType audtSurveyList[], udtSurveyType* pudtSurvey);
int OpenInputFile(char strFileName[], FILE** ppfilInput);
int ReadNextLineFromFile(char strBuffer[], FILE* pfilInput);
void AddSurveyToArray(char strAddress[], udtSurveyType* pudtSurvey);
void GetNextField(char strNextField[], char strSource[], char chrDelimiter);

void PrintSurveyList(udtSurveyType audtSurveyList[], size_t sizeArray);
void PrintSurvey(int intIndex, udtSurveyType udtSurvey);

// User Menu Functions 
char UserMenu(char chrSelection);
int TotalHouseholdsSurveyed(udtSurveyType audtSurveyList[], size_t sizeArray, int intTotalHousesSurveyed);
int TotalHouseholdsSurveyedOhio(udtSurveyType audtSurveyList[], size_t sizeArray, int intHousesSurveyedOhio);
int TotalHouseholdsSurveyedHamilton(udtSurveyType audtSurveyList[], size_t sizeArray, int intHousesSurveyedHamilton);
int TotalHouseholdsSurveyedButler(udtSurveyType audtSurveyList[], size_t sizeArray, int intHousesSurveyedButler);
int TotalHouseholdsSurveyedKentucky(udtSurveyType audtSurveyList[], size_t sizeArray, int intHousesSurveyedKentucky);
int TotalHouseholdsSurveyedBoone(udtSurveyType audtSurveyList[], size_t sizeArray, int intHousesSurveyedBoone);
int TotalHouseholdsSurveyedKenton(udtSurveyType audtSurveyList[], size_t sizeArray, int intHousesSurveyedKenton);
int TotalHouseholdsSurveyedCaucasian(udtSurveyType audtSurveyList[], size_t sizeArray, int intHousesSurveyedCaucasian);
int TotalHouseholdsSurveyedAfricanAmerican(udtSurveyType audtSurveyList[], size_t sizeArray, int intHousesSurveyedAfricanAmerican);
int TotalHouseholdsSurveyedHispanic(udtSurveyType audtSurveyList[], size_t sizeArray, int intHousesSurveyedHispanic);
int TotalHouseholdsSurveyedAsian(udtSurveyType audtSurveyList[], size_t sizeArray, int intHousesSurveyedAsian);
int TotalHouseholdsSurveyedOther(udtSurveyType audtSurveyList[], size_t sizeArray, int intHousesSurveyedOther);

float TotalAverageIncome(udtSurveyType audtSurveyList[], size_t sizeArray, float sngTotalAverageIncome, int intTotalHousesSurveyed, float sngTotalIncome);
float AverageIncomeOhio(udtSurveyType audtSurveyList[], size_t sizeArray, float sngAverageIncomeOhio, int intTotalHousesSurveyedOhio, float sngTotalIncomeOhio);
float AverageIncomeHamilton(udtSurveyType audtSurveyList[], size_t sizeArray, float sngAverageIncomeHamilton, int intHousesSurveyedHamilton, float sngTotalIncomeHamilton);
float AverageIncomeButler(udtSurveyType audtSurveyList[], size_t sizeArray, float sngAverageIncomeButler, int intHousesSurveyedButler, float sngTotalIncomeButler);
float AverageIncomeKentucky(udtSurveyType audtSurveyList[], size_t sizeArray, float sngAverageIncomeKentucky, int intHousesSurveyedKentucky, float sngTotalIncomeKentucky);
float AverageIncomeBoone(udtSurveyType audtSurveyList[], size_t sizeArray, float sngAverageIncomeBoone, int intHousesSurveyedBoone, float sngTotalIncomeBoone);
float AverageIncomeKenton(udtSurveyType audtSurveyList[], size_t sizeArray, float sngAverageIncomeKenton, int intHousesSurveyedKenton, float sngTotalIncomeKenton);
float AverageIncomeCaucasian(udtSurveyType audtSurveyList[], size_t sizeArray, float sngAverageIncomeCaucasian, int intHousesSurveyedCaucasian, float sngTotalIncomeCaucasian);
float AverageIncomeAfricanAmerican(udtSurveyType audtSurveyList[], size_t sizeArray, float sngAverageIncomeAfricanAmerican, int intHousesSurveyedAfricanAmerican, float sngTotalIncomeAfricanAmerican);
float AverageIncomeHispanic(udtSurveyType audtSurveyList[], size_t sizeArray, float sngAverageIncomeHispanic, int intHousesSurveyedHispanic, float sngTotalIncomeHispanic);
float AverageIncomeAsian(udtSurveyType audtSurveyList[], size_t sizeArray, float sngAverageIncomeAsian, int intHousesSurveyedAsian, float sngTotalIncomeAsian);
float AverageIncomeOther(udtSurveyType audtSurveyList[], size_t sizeArray, float sngAverageIncomeOther, int intHousesSurveyedOther, float sngTotalIncomeOther);

float TotalHouseholdsPoverty(udtSurveyType audtSurveyList[], size_t sizeArray, int intTotalHousesSurveyed, int intTotalHouseholdsPoverty, float sngPercentageHouseholdsPoverty);
float HouseholdsPovertyOhio(udtSurveyType audtSurveyList[], size_t sizeArray, int intHousesSurveyedOhio, int intHouseholdsPovertyOhio, float sngPercentageHouseholdsPovertyOhio);
float HouseholdsPovertyHamilton(udtSurveyType audtSurveyList[], size_t sizeArray, int intHousesSurveyedHamilton, int intHouseholdsPovertyHamilton, float sngPercentageHouseholdsPovertyHamilton);
float HouseholdsPovertyButler(udtSurveyType audtSurveyList[], size_t sizeArray, int intHousesSurveyedButler, int intHouseholdsPovertyButler, float sngPercentageHouseholdsPovertyButler);
float HouseholdsPovertyKentucky(udtSurveyType audtSurveyList[], size_t sizeArray, int intHousesSurveyedKentucky, int intHouseholdsPovertyKentucky, float sngPercentageHouseholdsPovertyKentucky);
float HouseholdsPovertyBoone(udtSurveyType audtSurveyList[], size_t sizeArray, int intHousesSurveyedBoone, int intHouseholdsPovertyBoone, float sngPercentageHouseholdsPovertyBoone);
float HouseholdsPovertyKenton(udtSurveyType audtSurveyList[], size_t sizeArray, int intHousesSurveyedKenton, int intHouseholdsPovertyKenton, float sngPercentageHouseholdsPovertyKenton);
float HouseholdsPovertyCaucasian(udtSurveyType audtSurveyList[], size_t sizeArray, int intHousesSurveyedCaucasian, int intHouseholdsPovertyCaucasian, float sngPercentageHouseholdsPovertyCaucasian);
float HouseholdsPovertyAfricanAmerican(udtSurveyType audtSurveyList[], size_t sizeArray, int intHousesSurveyedAfricanAmerican, int intHouseholdsPovertyAfricanAmerican, float sngPercentageHouseholdsPovertyAfricanAmerican);
float HouseholdsPovertyHispanic(udtSurveyType audtSurveyList[], size_t sizeArray, int intHousesSurveyedHispanic, int intHouseholdsPovertyHispanic, float sngPercentageHouseholdsPovertyHispanic);
float HouseholdsPovertyAsian(udtSurveyType audtSurveyList[], size_t sizeArray, int intHousesSurveyedAsian, int intHouseholdsPovertyAsian, float sngPercentageHouseholdsPovertyAsian);
float HouseholdsPovertyOther(udtSurveyType audtSurveyList[], size_t sizeArray, int intHousesSurveyedOther, int intHouseholdsPovertyOther, float sngPercentageHouseholdsPovertyOther);

// String Functions
int StringLength(char strSource[]);
int FindLetterIndex(char strSource[], char chrLetterToFind);
void Trim(char strSource[]);
boolean IsWhiteSpace(char chrLetterToCheck);
int CountWords(char strSource[]);

// --------------------------------------------------------------------------------
// Name: main
// Abstract: This is where the program starts.
// --------------------------------------------------------------------------------
void main()
{
	udtSurveyType audtSurveyList[100];
	udtSurveyType* pudtSurvey = NULL;
	size_t sizeArray = 0;

	InitializeSurveyList(audtSurveyList);

	sizeArray = PopulateSurveyList(audtSurveyList, pudtSurvey);

	PrintSurveyList(audtSurveyList, sizeArray);


	// variables for user menu
	char chrSelection = ' ';
	char chrAnswer = ' ';

	//variables for houses surveyed
	int intTotalHousesSurveyed = 0;
	int intHousesSurveyedOhio = 0;
	int intHousesSurveyedHamilton = 0;
	int intHousesSurveyedButler = 0;
	int intHousesSurveyedKentucky = 0;
	int intHousesSurveyedBoone = 0;
	int intHousesSurveyedKenton = 0;
	int intHousesSurveyedCaucasian = 0;
	int intHousesSurveyedAfricanAmerican = 0;
	int intHousesSurveyedHispanic = 0;
	int intHousesSurveyedAsian = 0;
	int intHousesSurveyedOther = 0;

	// variables for income
	float sngTotalIncome = 0;
	float sngTotalAverageIncome = 0;
	float sngAverageIncomeOhio = 0;
	float sngTotalIncomeOhio = 0;
	float sngAverageIncomeHamilton = 0;
	float sngTotalIncomeHamilton = 0;
	float sngAverageIncomeButler = 0;
	float sngTotalIncomeButler = 0;
	float sngAverageIncomeKentucky = 0;
	float sngTotalIncomeKentucky = 0;
	float sngAverageIncomeBoone = 0;
	float sngTotalIncomeBoone = 0;
	float sngAverageIncomeKenton = 0;
	float  sngTotalIncomeKenton = 0;
	float sngAverageIncomeCaucasian = 0;
	float sngTotalIncomeCaucasian = 0;
	float sngAverageIncomeAfricanAmerican = 0;
	float sngTotalIncomeAfricanAmerican = 0;
	float sngAverageIncomeHispanic = 0;
	float sngTotalIncomeHispanic = 0;
	float sngAverageIncomeAsian = 0;
	float sngTotalIncomeAsian = 0;
	float sngAverageIncomeOther = 0;
	float sngTotalIncomeOther = 0;

	// variables for households in poverty
	int intTotalHouseholdsPoverty = 0;
	float sngPercentageHouseholdsPoverty = 0;
	int intHouseholdsPovertyOhio = 0;
	float sngPercentageHouseholdsPovertyOhio = 0;
	int intHouseholdsPovertyHamilton = 0;
	float sngPercentageHouseholdsPovertyHamilton = 0;
	int intHouseholdsPovertyButler = 0;
	float sngPercentageHouseholdsPovertyButler = 0;
	int intHouseholdsPovertyKentucky = 0;
	float sngPercentageHouseholdsPovertyKentucky = 0;
	int intHouseholdsPovertyBoone = 0;
	float sngPercentageHouseholdsPovertyBoone = 0;
	int intHouseholdsPovertyKenton = 0;
	float sngPercentageHouseholdsPovertyKenton = 0;
	int intHouseholdsPovertyCaucasian = 0;
	float sngPercentageHouseholdsPovertyCaucasian = 0;
	int intHouseholdsPovertyAfricanAmerican = 0;
	float sngPercentageHouseholdsPovertyAfricanAmerican = 0;
	int intHouseholdsPovertyHispanic = 0;
	float sngPercentageHouseholdsPovertyHispanic = 0;
	int intHouseholdsPovertyAsian = 0;
	float sngPercentageHouseholdsPovertyAsian = 0;
	int intHouseholdsPovertyOther = 0;
	float sngPercentageHouseholdsPovertyOther = 0;

	do
	{
		// User menu for user to select desired task
		chrSelection = UserMenu(chrSelection);

		// functions for user menu selections 
		if (chrSelection == 'A' || chrSelection == 'a')
		{
			// calculate and print total houses surveyed
			intTotalHousesSurveyed = TotalHouseholdsSurveyed(audtSurveyList, sizeArray, intTotalHousesSurveyed);
			printf("Total houses surveyed: %d\n\n", intTotalHousesSurveyed);
		}
		else if (chrSelection == 'B' || chrSelection == 'b')
		{
			// calculate and print total households surveyed by county and state
			intHousesSurveyedOhio = TotalHouseholdsSurveyedOhio(audtSurveyList, sizeArray, intHousesSurveyedOhio);
			intHousesSurveyedHamilton = TotalHouseholdsSurveyedHamilton(audtSurveyList, sizeArray, intHousesSurveyedHamilton);
			intHousesSurveyedButler = TotalHouseholdsSurveyedButler(audtSurveyList, sizeArray, intHousesSurveyedButler);
			intHousesSurveyedKentucky = TotalHouseholdsSurveyedKentucky(audtSurveyList, sizeArray, intHousesSurveyedKentucky);
			intHousesSurveyedBoone = TotalHouseholdsSurveyedBoone(audtSurveyList, sizeArray, intHousesSurveyedBoone);
			intHousesSurveyedKenton = TotalHouseholdsSurveyedKenton(audtSurveyList, sizeArray, intHousesSurveyedKenton);

			printf("Total houses surveyed per county and state\n\n");
			printf("Ohio:			%d\n", intHousesSurveyedOhio);
			printf("\tHamilton:	%d\n", intHousesSurveyedHamilton);
			printf("\tButler:		%d\n\n", intHousesSurveyedButler);
			printf("Kentucky:		%d\n", intHousesSurveyedKentucky);
			printf("\tBoone:		%d\n", intHousesSurveyedBoone);
			printf("\tKenton:		%d\n\n", intHousesSurveyedKenton);
		}
		else if (chrSelection == 'C' || chrSelection == 'c')
		{
			// calculate and print total households surveyed by race
			intHousesSurveyedCaucasian = TotalHouseholdsSurveyedCaucasian(audtSurveyList, sizeArray, intHousesSurveyedCaucasian);
			intHousesSurveyedAfricanAmerican = TotalHouseholdsSurveyedAfricanAmerican(audtSurveyList, sizeArray, intHousesSurveyedAfricanAmerican);
			intHousesSurveyedHispanic = TotalHouseholdsSurveyedHispanic(audtSurveyList, sizeArray, intHousesSurveyedHispanic);
			intHousesSurveyedAsian = TotalHouseholdsSurveyedAsian(audtSurveyList, sizeArray, intHousesSurveyedAsian);
			intHousesSurveyedOther = TotalHouseholdsSurveyedOther(audtSurveyList, sizeArray, intHousesSurveyedOther);

			printf("Total houses surveyed by race\n\n");
			printf("Caucasian:				%d\n", intHousesSurveyedCaucasian);
			printf("African American:		\t%d\n", intHousesSurveyedAfricanAmerican);
			printf("Hispanic:				%d\n", intHousesSurveyedHispanic);
			printf("Asian:					%d\n", intHousesSurveyedAsian);
			printf("Other:					%d\n\n", intHousesSurveyedOther);

		}
		else if (chrSelection == 'D' || chrSelection == 'd')
		{
			// calculate and print average household income for all households surveyed
			sngTotalAverageIncome = TotalAverageIncome(audtSurveyList, sizeArray, sngTotalAverageIncome, intTotalHousesSurveyed, sngTotalIncome);

			printf("Average household income: $%.2f\n\n", sngTotalAverageIncome);

		}
		else if (chrSelection == 'E' || chrSelection == 'e')
		{
			// calculate and print average household income per county and state
			sngAverageIncomeOhio = AverageIncomeOhio(audtSurveyList, sizeArray, sngAverageIncomeOhio, intHousesSurveyedOhio, sngTotalIncomeOhio);
			sngAverageIncomeHamilton = AverageIncomeHamilton(audtSurveyList, sizeArray, sngAverageIncomeHamilton, intHousesSurveyedHamilton, sngTotalIncomeHamilton);
			sngAverageIncomeButler = AverageIncomeButler(audtSurveyList, sizeArray, sngAverageIncomeButler, intHousesSurveyedButler, sngTotalIncomeButler);
			sngAverageIncomeKentucky = AverageIncomeKentucky(audtSurveyList, sizeArray, sngAverageIncomeKentucky, intHousesSurveyedKentucky, sngTotalIncomeKentucky);
			sngAverageIncomeBoone = AverageIncomeBoone(audtSurveyList, sizeArray, sngAverageIncomeBoone, intHousesSurveyedBoone, sngTotalIncomeBoone);
			sngAverageIncomeKenton = AverageIncomeKenton(audtSurveyList, sizeArray, sngAverageIncomeKenton, intHousesSurveyedKenton, sngTotalIncomeKenton);

			printf("Average household income per county and state\n\n");
			printf("Ohio:			$%.2f\n", sngAverageIncomeOhio);
			printf("\tHamilton:	$%.2f\n", sngAverageIncomeHamilton);
			printf("\tButler:		$%.2f\n\n", sngAverageIncomeButler);
			printf("Kentucky:		$%.2f\n", sngAverageIncomeKentucky);
			printf("\tBoone:		$%.2f\n", sngAverageIncomeBoone);
			printf("\tKenton:		$%.2f\n\n", sngAverageIncomeKenton);

		}
		else if (chrSelection == 'F' || chrSelection == 'f')
		{
			// calculate and print average household income per race
			sngAverageIncomeCaucasian = AverageIncomeCaucasian(audtSurveyList, sizeArray, sngAverageIncomeCaucasian, intHousesSurveyedCaucasian, sngTotalIncomeCaucasian);
			sngAverageIncomeAfricanAmerican = AverageIncomeAfricanAmerican(audtSurveyList, sizeArray, sngAverageIncomeAfricanAmerican, intHousesSurveyedAfricanAmerican, sngTotalIncomeAfricanAmerican);
			sngAverageIncomeHispanic = AverageIncomeHispanic(audtSurveyList, sizeArray, sngAverageIncomeHispanic, intHousesSurveyedHispanic, sngTotalIncomeHispanic);
			sngAverageIncomeAsian = AverageIncomeAsian(audtSurveyList, sizeArray, sngAverageIncomeAsian, intHousesSurveyedAsian, sngTotalIncomeAsian);
			sngAverageIncomeOther = AverageIncomeOther(audtSurveyList, sizeArray, sngAverageIncomeOther, intHousesSurveyedOther, sngTotalIncomeOther);

			printf("Average household income per race\n\n");
			printf("Caucasian:				$%.2f\n", sngAverageIncomeCaucasian);
			printf("African American:		\t$%.2f\n", sngAverageIncomeAfricanAmerican);
			printf("Hispanic:				$%.2f\n", sngAverageIncomeHispanic);
			printf("Asian:					$%.2f\n", sngAverageIncomeAsian);
			printf("Other:					$%.2f\n\n", sngAverageIncomeOther);

		}
		else if (chrSelection == 'G' || chrSelection == 'g')
		{
			// calculate and print total households below poverty line
			sngPercentageHouseholdsPoverty = TotalHouseholdsPoverty(audtSurveyList, sizeArray, intTotalHousesSurveyed, intTotalHouseholdsPoverty, sngPercentageHouseholdsPoverty);

			printf("Percentage of total households below poverty: %.2f %%\n\n", sngPercentageHouseholdsPoverty);

		}
		else if (chrSelection == 'H' || chrSelection == 'h')
		{
			// calculate and print households below poverty per county and state
			sngPercentageHouseholdsPovertyOhio = HouseholdsPovertyOhio(audtSurveyList, sizeArray, intHousesSurveyedOhio, intHouseholdsPovertyOhio, sngPercentageHouseholdsPovertyOhio);
			sngPercentageHouseholdsPovertyHamilton = HouseholdsPovertyHamilton(audtSurveyList, sizeArray, intHousesSurveyedHamilton, intHouseholdsPovertyHamilton, sngPercentageHouseholdsPovertyHamilton);
			sngPercentageHouseholdsPovertyButler = HouseholdsPovertyButler(audtSurveyList, sizeArray, intHousesSurveyedButler, intHouseholdsPovertyButler, sngPercentageHouseholdsPovertyButler);
			sngPercentageHouseholdsPovertyKentucky = HouseholdsPovertyKentucky(audtSurveyList, sizeArray, intHousesSurveyedKentucky, intHouseholdsPovertyKentucky, sngPercentageHouseholdsPovertyKentucky);
			sngPercentageHouseholdsPovertyBoone = HouseholdsPovertyBoone(audtSurveyList, sizeArray, intHousesSurveyedBoone, intHouseholdsPovertyBoone, sngPercentageHouseholdsPovertyBoone);
			sngPercentageHouseholdsPovertyKenton = HouseholdsPovertyKenton(audtSurveyList, sizeArray, intHousesSurveyedKenton, intHouseholdsPovertyKenton, sngPercentageHouseholdsPovertyKenton);

			printf("Percentage of households below poverty per county and state\n\n");
			printf("Ohio:			%.2f %%\n", sngPercentageHouseholdsPovertyOhio);
			printf("\tHamilton:	%.2f %%\n", sngPercentageHouseholdsPovertyHamilton);
			printf("\tButler:		%.2f %%\n\n", sngPercentageHouseholdsPovertyButler);
			printf("Kentucky:		%.2f %%\n", sngPercentageHouseholdsPovertyKentucky);
			printf("\tBoone:		%.2f %%\n", sngPercentageHouseholdsPovertyBoone);
			printf("\tKenton:		%.2f %%\n\n", sngPercentageHouseholdsPovertyKenton);

		}
		else if (chrSelection == 'I' || chrSelection == 'i')
		{
			// calculate and print households below poverty per race
			sngPercentageHouseholdsPovertyCaucasian = HouseholdsPovertyCaucasian(audtSurveyList, sizeArray, intHousesSurveyedCaucasian, intHouseholdsPovertyCaucasian, sngPercentageHouseholdsPovertyCaucasian);
			sngPercentageHouseholdsPovertyAfricanAmerican = HouseholdsPovertyAfricanAmerican(audtSurveyList, sizeArray, intHousesSurveyedAfricanAmerican, intHouseholdsPovertyAfricanAmerican, sngPercentageHouseholdsPovertyAfricanAmerican);
			sngPercentageHouseholdsPovertyHispanic = HouseholdsPovertyHispanic(audtSurveyList, sizeArray, intHousesSurveyedHispanic, intHouseholdsPovertyHispanic, sngPercentageHouseholdsPovertyHispanic);
			sngPercentageHouseholdsPovertyAsian = HouseholdsPovertyAsian(audtSurveyList, sizeArray, intHousesSurveyedAsian, intHouseholdsPovertyAsian, sngPercentageHouseholdsPovertyAsian);
			sngPercentageHouseholdsPovertyOther = HouseholdsPovertyOther(audtSurveyList, sizeArray, intHousesSurveyedOther, intHouseholdsPovertyOther, sngPercentageHouseholdsPovertyOther);

			printf("Households below poverty per race\n\n");
			printf("Caucasian:				%.2f %%\n", sngPercentageHouseholdsPovertyCaucasian);
			printf("African American:		\t%.2f %%\n", sngPercentageHouseholdsPovertyAfricanAmerican);
			printf("Hispanic:				%.2f %%\n", sngPercentageHouseholdsPovertyHispanic);
			printf("Asian:					%.2f %%\n", sngPercentageHouseholdsPovertyAsian);
			printf("Other:					%.2f %%\n\n", sngPercentageHouseholdsPovertyOther);

		}
		else if (chrSelection == 'X' || chrSelection == 'x')
		{
			// Nice parting message for user 	
			printf("*** You have chosen to exit the program ***\n");
			printf("**********  Thanks for using!    **********\n\n");
			// exit program
			exit(1);
		}

		// Ask user if they would like to choose additional options
		printf("Would you like to choose additional options (Y/N)?");
		scanf(" %c", &chrAnswer);
		printf("\n");


		if (chrAnswer == 'N' || chrAnswer == 'n')
		{
			// Nice parting message for user
			printf("*** You have chosen to exit the program ***\n");
			printf("**********  Thanks for using!    **********\n\n");
		}

		// if user types 'Y' then program will loop
	} while (chrAnswer == 'Y' || chrAnswer == 'y');

	system("pause");
}


// --------------------------------------------------------------------------------
// Name: TotalHouseholdsSurveyed
// Abstract: Calculates total households surveyed
// --------------------------------------------------------------------------------
int TotalHouseholdsSurveyed(udtSurveyType audtSurveyList[], size_t sizeArray, int intTotalHousesSurveyed)
{
	int intIndex = 0;
	int intSurveyIndex = 0;

	for (intIndex = 0; intIndex < sizeArray - 1; intIndex += 1)
	{
		// if household number is greater than 0 count house
		while (audtSurveyList[intSurveyIndex].intHouseholdNumber > 0)
		{
			// add to houses surveyed
			intTotalHousesSurveyed += 1;

			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}


	}
	return intTotalHousesSurveyed;
}


// --------------------------------------------------------------------------------
// Name: TotalHouseholdsSurveyedOhio
// Abstract: Calculates total households surveyed for ohio
// --------------------------------------------------------------------------------
int TotalHouseholdsSurveyedOhio(udtSurveyType audtSurveyList[], size_t sizeArray, int intHousesSurveyedOhio)
{
	int intIndex = 0;
	int intSurveyIndex = 0;

	for (intIndex = 0; intIndex < sizeArray - 1; intIndex += 1)
	{
		while (strcmp(audtSurveyList[intSurveyIndex].strState, "Ohio") == 0)
		{
			// count Ohio
			intHousesSurveyedOhio += 1;

			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}

		// move forward in Survey List
		audtSurveyList += 1;
		audtSurveyList[intSurveyIndex + 1];
	}
	return intHousesSurveyedOhio;
}


// --------------------------------------------------------------------------------
// Name: TotalHouseholdsSurveyedHamilton
// Abstract: Calculates total households surveyed for hamilton
// --------------------------------------------------------------------------------
int TotalHouseholdsSurveyedHamilton(udtSurveyType audtSurveyList[], size_t sizeArray, int intHousesSurveyedHamilton)
{
	int intIndex = 0;
	int intSurveyIndex = 0;

	for (intIndex = 0; intIndex < sizeArray - 1; intIndex += 1)
	{
		while (strcmp(audtSurveyList[intSurveyIndex].strCounty, "Hamilton") == 0)
		{
			// count Hamilton
			intHousesSurveyedHamilton += 1;

			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}

		// move forward in Survey List
		audtSurveyList += 1;
		audtSurveyList[intSurveyIndex + 1];
	}
	return intHousesSurveyedHamilton;
}


// --------------------------------------------------------------------------------
// Name: TotalHouseholdsSurveyedButler
// Abstract: Calculates total households surveyed for butler
// --------------------------------------------------------------------------------
int TotalHouseholdsSurveyedButler(udtSurveyType audtSurveyList[], size_t sizeArray, int intHousesSurveyedButler)
{
	int intIndex = 0;
	int intSurveyIndex = 0;

	for (intIndex = 0; intIndex < sizeArray - 1; intIndex += 1)
	{
		while (strcmp(audtSurveyList[intSurveyIndex].strCounty, "Butler") == 0)
		{
			// count butler
			intHousesSurveyedButler += 1;

			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}

		// move forward in Survey List
		audtSurveyList += 1;
		audtSurveyList[intSurveyIndex + 1];
	}
	return intHousesSurveyedButler;
}


// --------------------------------------------------------------------------------
// Name: TotalHouseholdsSurveyedKentucky
// Abstract: Calculates total households surveyed for kentucky
// --------------------------------------------------------------------------------
int TotalHouseholdsSurveyedKentucky(udtSurveyType audtSurveyList[], size_t sizeArray, int intHousesSurveyedKentucky)
{
	int intIndex = 0;
	int intSurveyIndex = 0;

	for (intIndex = 0; intIndex < sizeArray - 1; intIndex += 1)
	{
		while (strcmp(audtSurveyList[intSurveyIndex].strState, "Kentucky") == 0)
		{
			// count Kentucky
			intHousesSurveyedKentucky += 1;

			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}

		// move forward in Survey List
		audtSurveyList += 1;
		audtSurveyList[intSurveyIndex + 1];
	}
	return intHousesSurveyedKentucky;
}


// --------------------------------------------------------------------------------
// Name: TotalHouseholdsSurveyedBoone
// Abstract: Calculates total households surveyed for boone
// --------------------------------------------------------------------------------
int TotalHouseholdsSurveyedBoone(udtSurveyType audtSurveyList[], size_t sizeArray, int intHousesSurveyedBoone)
{
	int intIndex = 0;
	int intSurveyIndex = 0;

	for (intIndex = 0; intIndex < sizeArray - 1; intIndex += 1)
	{
		while (strcmp(audtSurveyList[intSurveyIndex].strCounty, "Boone") == 0)
		{
			// count Boone
			intHousesSurveyedBoone += 1;

			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}

		// move forward in Survey List
		audtSurveyList += 1;
		audtSurveyList[intSurveyIndex + 1];
	}
	return intHousesSurveyedBoone;
}


// --------------------------------------------------------------------------------
// Name: TotalHouseholdsSurveyedKenton
// Abstract: Calculates total households surveyed for boone
// --------------------------------------------------------------------------------
int TotalHouseholdsSurveyedKenton(udtSurveyType audtSurveyList[], size_t sizeArray, int intHousesSurveyedKenton)
{
	int intIndex = 0;
	int intSurveyIndex = 0;

	for (intIndex = 0; intIndex < sizeArray - 1; intIndex += 1)
	{
		while (strcmp(audtSurveyList[intSurveyIndex].strCounty, "Kenton") == 0)
		{
			// count Kenton
			intHousesSurveyedKenton += 1;

			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}

		// move forward in Survey List
		audtSurveyList += 1;
		audtSurveyList[intSurveyIndex + 1];
	}
	return intHousesSurveyedKenton;
}


// --------------------------------------------------------------------------------
// Name: TotalHouseholdsSurveyedCaucasian
// Abstract: Calculates total households surveyed for caucasian
// --------------------------------------------------------------------------------
int TotalHouseholdsSurveyedCaucasian(udtSurveyType audtSurveyList[], size_t sizeArray, int intHousesSurveyedCaucasian)
{
	int intIndex = 0;
	int intSurveyIndex = 0;

	for (intIndex = 0; intIndex < sizeArray - 1; intIndex += 1)
	{
		while (strcmp(audtSurveyList[intSurveyIndex].strRace, "Caucasian") == 0)
		{
			// count Caucasian
			intHousesSurveyedCaucasian += 1;

			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}

		// move forward in Survey List
		audtSurveyList += 1;
		audtSurveyList[intSurveyIndex + 1];
	}
	return intHousesSurveyedCaucasian;
}


// --------------------------------------------------------------------------------
// Name: TotalHouseholdsSurveyedAfricanAmerican
// Abstract: Calculates total households surveyed for african american
// --------------------------------------------------------------------------------
int TotalHouseholdsSurveyedAfricanAmerican(udtSurveyType audtSurveyList[], size_t sizeArray, int intHousesSurveyedAfricanAmerican)
{
	int intIndex = 0;
	int intSurveyIndex = 0;

	for (intIndex = 0; intIndex < sizeArray - 1; intIndex += 1)
	{
		while (strcmp(audtSurveyList[intSurveyIndex].strRace, "African American") == 0)
		{
			// count African American
			intHousesSurveyedAfricanAmerican += 1;

			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}

		// move forward in Survey List
		audtSurveyList += 1;
		audtSurveyList[intSurveyIndex + 1];
	}
	return intHousesSurveyedAfricanAmerican;
}


// --------------------------------------------------------------------------------
// Name: TotalHouseholdsSurveyedHispanic
// Abstract: Calculates total households surveyed for hispanic
// --------------------------------------------------------------------------------
int TotalHouseholdsSurveyedHispanic(udtSurveyType audtSurveyList[], size_t sizeArray, int intHousesSurveyedHispanic)
{
	int intIndex = 0;
	int intSurveyIndex = 0;

	for (intIndex = 0; intIndex < sizeArray - 1; intIndex += 1)
	{
		while (strcmp(audtSurveyList[intSurveyIndex].strRace, "Hispanic") == 0)
		{
			// count Hispanic
			intHousesSurveyedHispanic += 1;

			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}

		// move forward in Survey List
		audtSurveyList += 1;
		audtSurveyList[intSurveyIndex + 1];
	}
	return intHousesSurveyedHispanic;
}


// --------------------------------------------------------------------------------
// Name: TotalHouseholdsSurveyedAsian
// Abstract: Calculates total households surveyed for asian
// --------------------------------------------------------------------------------
int TotalHouseholdsSurveyedAsian(udtSurveyType audtSurveyList[], size_t sizeArray, int intHousesSurveyedAsian)
{
	int intIndex = 0;
	int intSurveyIndex = 0;

	for (intIndex = 0; intIndex < sizeArray - 1; intIndex += 1)
	{
		while (strcmp(audtSurveyList[intSurveyIndex].strRace, "Asian") == 0)
		{
			// count Asian
			intHousesSurveyedAsian += 1;

			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}

		// move forward in Survey List
		audtSurveyList += 1;
		audtSurveyList[intSurveyIndex + 1];
	}
	return intHousesSurveyedAsian;
}


// --------------------------------------------------------------------------------
// Name: TotalHouseholdsSurveyedOther
// Abstract: Calculates total households surveyed for other
// --------------------------------------------------------------------------------
int TotalHouseholdsSurveyedOther(udtSurveyType audtSurveyList[], size_t sizeArray, int intHousesSurveyedOther)
{
	int intIndex = 0;
	int intSurveyIndex = 0;

	for (intIndex = 0; intIndex < sizeArray - 1; intIndex += 1)
	{
		while (strcmp(audtSurveyList[intSurveyIndex].strRace, "Other") == 0)
		{
			// count Other
			intHousesSurveyedOther += 1;

			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}

		// move forward in Survey List
		audtSurveyList += 1;
		audtSurveyList[intSurveyIndex + 1];
	}
	return intHousesSurveyedOther;
}


// --------------------------------------------------------------------------------
// Name: TotalAverageIncome
// Abstract: Calculates average income for all households surveyed 
// --------------------------------------------------------------------------------
float TotalAverageIncome(udtSurveyType audtSurveyList[], size_t sizeArray, float sngTotalAverageIncome, int intTotalHousesSurveyed, float sngTotalIncome)
{
	int intIndex = 0;
	int intSurveyIndex = 0;

	intTotalHousesSurveyed = TotalHouseholdsSurveyed(audtSurveyList, sizeArray, intTotalHousesSurveyed);

	for (intIndex = 0; intIndex < sizeArray - 1; intIndex += 1)
	{
		while (audtSurveyList[intSurveyIndex].sngIncome > 0)
		{
			sngTotalIncome += audtSurveyList[intIndex].sngIncome;

			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}

		// move forward in Survey List
		audtSurveyList += 1;
		audtSurveyList[intSurveyIndex + 1];
	}

	// make sure program doesn't crash by dividing by 0
	if (sngTotalIncome != 0)
	{
		sngTotalAverageIncome = sngTotalIncome / intTotalHousesSurveyed;
	}
	else
	{
		sngTotalAverageIncome = 0;
	}

	return sngTotalAverageIncome;
}


// --------------------------------------------------------------------------------
// Name: AverageIncomeOhio
// Abstract: Calculates average income for ohio households
// --------------------------------------------------------------------------------
float AverageIncomeOhio(udtSurveyType audtSurveyList[], size_t sizeArray, float sngAverageIncomeOhio, int intHousesSurveyedOhio, float sngTotalIncomeOhio)
{
	int intIndex = 0;
	int intSurveyIndex = 0;

	intHousesSurveyedOhio = TotalHouseholdsSurveyedOhio(audtSurveyList, sizeArray, intHousesSurveyedOhio);

	for (intIndex = 0; intIndex < sizeArray - 1; intIndex += 1)
	{
		while (audtSurveyList[intSurveyIndex].sngIncome > 0 && strcmp(audtSurveyList[intSurveyIndex].strState, "Ohio") == 0)
		{
			sngTotalIncomeOhio += audtSurveyList[intSurveyIndex].sngIncome;

			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}

		// move forward in Survey List
		audtSurveyList += 1;
		audtSurveyList[intSurveyIndex + 1];
	}

	// make sure program doesn't crash by dividing by 0
	if (sngTotalIncomeOhio != 0)
	{
		sngAverageIncomeOhio = sngTotalIncomeOhio / intHousesSurveyedOhio;
	}
	else
	{
		sngAverageIncomeOhio = 0;
	}

	return sngAverageIncomeOhio;
}


// --------------------------------------------------------------------------------
// Name: AverageIncomeHamilton
// Abstract: Calculates average income for hamilton households
// --------------------------------------------------------------------------------
float AverageIncomeHamilton(udtSurveyType audtSurveyList[], size_t sizeArray, float sngAverageIncomeHamilton, int intHousesSurveyedHamilton, float sngTotalIncomeHamilton)
{
	int intIndex = 0;
	int intSurveyIndex = 0;

	intHousesSurveyedHamilton = TotalHouseholdsSurveyedHamilton(audtSurveyList, sizeArray, intHousesSurveyedHamilton);

	for (intIndex = 0; intIndex < sizeArray - 1; intIndex += 1)
	{
		while (audtSurveyList[intSurveyIndex].sngIncome > 0 && strcmp(audtSurveyList[intSurveyIndex].strCounty, "Hamilton") == 0)
		{
			sngTotalIncomeHamilton += audtSurveyList[intSurveyIndex].sngIncome;

			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}

		// move forward in Survey List
		audtSurveyList += 1;
		audtSurveyList[intSurveyIndex + 1];
	}

	// make sure program doesn't crash by dividing by 0
	if (sngTotalIncomeHamilton != 0)
	{
		sngAverageIncomeHamilton = sngTotalIncomeHamilton / intHousesSurveyedHamilton;
	}
	else
	{
		sngAverageIncomeHamilton = 0;
	}

	return sngAverageIncomeHamilton;
}


// --------------------------------------------------------------------------------
// Name: AverageIncomeButler
// Abstract: Calculates average income for butler households
// --------------------------------------------------------------------------------
float AverageIncomeButler(udtSurveyType audtSurveyList[], size_t sizeArray, float sngAverageIncomeButler, int intHousesSurveyedButler, float sngTotalIncomeButler)
{
	int intIndex = 0;
	int intSurveyIndex = 0;

	intHousesSurveyedButler = TotalHouseholdsSurveyedButler(audtSurveyList, sizeArray, intHousesSurveyedButler);

	for (intIndex = 0; intIndex < sizeArray - 1; intIndex += 1)
	{
		while (audtSurveyList[intSurveyIndex].sngIncome > 0 && strcmp(audtSurveyList[intSurveyIndex].strCounty, "Butler") == 0)
		{
			sngTotalIncomeButler += audtSurveyList[intSurveyIndex].sngIncome;

			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}

		// move forward in Survey List
		audtSurveyList += 1;
		audtSurveyList[intSurveyIndex + 1];
	}

	// make sure program doesn't crash by dividing by 0
	if (sngTotalIncomeButler != 0)
	{
		sngAverageIncomeButler = sngTotalIncomeButler / intHousesSurveyedButler;
	}
	else
	{
		sngAverageIncomeButler = 0;
	}

	return sngAverageIncomeButler;
}


// --------------------------------------------------------------------------------
// Name: AverageIncomeKentucky
// Abstract: Calculates average income for kentucky households
// --------------------------------------------------------------------------------
float AverageIncomeKentucky(udtSurveyType audtSurveyList[], size_t sizeArray, float sngAverageIncomeKentucky, int intHousesSurveyedKentucky, float sngTotalIncomeKentucky)
{
	int intIndex = 0;
	int intSurveyIndex = 0;

	intHousesSurveyedKentucky = TotalHouseholdsSurveyedKentucky(audtSurveyList, sizeArray, intHousesSurveyedKentucky);

	for (intIndex = 0; intIndex < sizeArray - 1; intIndex += 1)
	{
		while (audtSurveyList[intSurveyIndex].sngIncome > 0 && strcmp(audtSurveyList[intSurveyIndex].strState, "Kentucky") == 0)
		{
			sngTotalIncomeKentucky += audtSurveyList[intSurveyIndex].sngIncome;

			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}

		// move forward in Survey List
		audtSurveyList += 1;
		audtSurveyList[intSurveyIndex + 1];
	}

	// make sure program doesn't crash by dividing by 0
	if (sngTotalIncomeKentucky != 0)
	{
		sngAverageIncomeKentucky = sngTotalIncomeKentucky / intHousesSurveyedKentucky;
	}
	else
	{
		sngAverageIncomeKentucky = 0;
	}

	return sngAverageIncomeKentucky;
}


// --------------------------------------------------------------------------------
// Name: AverageIncomeBoone
// Abstract: Calculates average income for boone households
// --------------------------------------------------------------------------------
float AverageIncomeBoone(udtSurveyType audtSurveyList[], size_t sizeArray, float sngAverageIncomeBoone, int intHousesSurveyedBoone, float sngTotalIncomeBoone)
{
	int intIndex = 0;
	int intSurveyIndex = 0;

	intHousesSurveyedBoone = TotalHouseholdsSurveyedBoone(audtSurveyList, sizeArray, intHousesSurveyedBoone);

	for (intIndex = 0; intIndex < sizeArray - 1; intIndex += 1)
	{
		while (audtSurveyList[intSurveyIndex].sngIncome > 0 && strcmp(audtSurveyList[intSurveyIndex].strCounty, "Boone") == 0)
		{
			sngTotalIncomeBoone += audtSurveyList[intSurveyIndex].sngIncome;

			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}

		// move forward in Survey List
		audtSurveyList += 1;
		audtSurveyList[intSurveyIndex + 1];
	}

	// make sure program doesn't crash by dividing by 0
	if (sngTotalIncomeBoone != 0)
	{
		sngAverageIncomeBoone = sngTotalIncomeBoone / intHousesSurveyedBoone;
	}
	else
	{
		sngAverageIncomeBoone = 0;
	}

	return sngAverageIncomeBoone;
}


// --------------------------------------------------------------------------------
// Name: AverageIncomeKenton
// Abstract: Calculates average income for kenton households
// --------------------------------------------------------------------------------
float AverageIncomeKenton(udtSurveyType audtSurveyList[], size_t sizeArray, float sngAverageIncomeKenton, int intHousesSurveyedKenton, float sngTotalIncomeKenton)
{
	int intIndex = 0;
	int intSurveyIndex = 0;

	intHousesSurveyedKenton = TotalHouseholdsSurveyedKenton(audtSurveyList, sizeArray, intHousesSurveyedKenton);

	for (intIndex = 0; intIndex < sizeArray - 1; intIndex += 1)
	{
		while (audtSurveyList[intSurveyIndex].sngIncome > 0 && strcmp(audtSurveyList[intSurveyIndex].strCounty, "Kenton") == 0)
		{
			sngTotalIncomeKenton += audtSurveyList[intSurveyIndex].sngIncome;

			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}

		// move forward in Survey List
		audtSurveyList += 1;
		audtSurveyList[intSurveyIndex + 1];
	}
	// make sure program doesn't crash by dividing by 0
	if (sngTotalIncomeKenton != 0)
	{
		sngAverageIncomeKenton = sngTotalIncomeKenton / intHousesSurveyedKenton;
	}
	else
	{
		sngAverageIncomeKenton = 0;
	}

	return sngAverageIncomeKenton;
}


// --------------------------------------------------------------------------------
// Name: AverageIncomeCaucasian
// Abstract: Calculates average income for caucasian households
// --------------------------------------------------------------------------------
float AverageIncomeCaucasian(udtSurveyType audtSurveyList[], size_t sizeArray, float sngAverageIncomeCaucasian, int intHousesSurveyedCaucasian, float sngTotalIncomeCaucasian)
{
	int intIndex = 0;
	int intSurveyIndex = 0;

	intHousesSurveyedCaucasian = TotalHouseholdsSurveyedCaucasian(audtSurveyList, sizeArray, intHousesSurveyedCaucasian);

	for (intIndex = 0; intIndex < sizeArray - 1; intIndex += 1)
	{
		while (audtSurveyList[intSurveyIndex].sngIncome > 0 && strcmp(audtSurveyList[intSurveyIndex].strRace, "Caucasian") == 0)
		{
			sngTotalIncomeCaucasian += audtSurveyList[intSurveyIndex].sngIncome;

			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}

		// move forward in Survey List
		audtSurveyList += 1;
		audtSurveyList[intSurveyIndex + 1];
	}
	// make sure program doesn't crash by dividing by 0
	if (sngTotalIncomeCaucasian != 0)
	{
		sngAverageIncomeCaucasian = sngTotalIncomeCaucasian / intHousesSurveyedCaucasian;
	}
	else
	{
		sngAverageIncomeCaucasian = 0;
	}

	return sngAverageIncomeCaucasian;
}


// --------------------------------------------------------------------------------
// Name: AverageIncomeAfricanAmerican
// Abstract: Calculates average income for african american households
// --------------------------------------------------------------------------------
float AverageIncomeAfricanAmerican(udtSurveyType audtSurveyList[], size_t sizeArray, float sngAverageIncomeAfricanAmerican, int intHousesSurveyedAfricanAmerican, float sngTotalIncomeAfricanAmerican)
{
	int intIndex = 0;
	int intSurveyIndex = 0;

	intHousesSurveyedAfricanAmerican = TotalHouseholdsSurveyedAfricanAmerican(audtSurveyList, sizeArray, intHousesSurveyedAfricanAmerican);

	for (intIndex = 0; intIndex < sizeArray - 1; intIndex += 1)
	{
		while (audtSurveyList[intSurveyIndex].sngIncome > 0 && strcmp(audtSurveyList[intSurveyIndex].strRace, "African American") == 0)
		{
			sngTotalIncomeAfricanAmerican += audtSurveyList[intSurveyIndex].sngIncome;

			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}

		// move forward in Survey List
		audtSurveyList += 1;
		audtSurveyList[intSurveyIndex + 1];
	}

	// make sure program doesn't crash by dividing by 0
	if (sngTotalIncomeAfricanAmerican != 0)
	{
		sngAverageIncomeAfricanAmerican = sngTotalIncomeAfricanAmerican / intHousesSurveyedAfricanAmerican;
	}
	else
	{
		sngAverageIncomeAfricanAmerican = 0;
	}

	return sngAverageIncomeAfricanAmerican;
}


// --------------------------------------------------------------------------------
// Name: AverageIncomeHispanic
// Abstract: Calculates average income for hispanic households
// --------------------------------------------------------------------------------
float AverageIncomeHispanic(udtSurveyType audtSurveyList[], size_t sizeArray, float sngAverageIncomeHispanic, int intHousesSurveyedHispanic, float sngTotalIncomeHispanic)
{
	int intIndex = 0;
	int intSurveyIndex = 0;

	intHousesSurveyedHispanic = TotalHouseholdsSurveyedHispanic(audtSurveyList, sizeArray, intHousesSurveyedHispanic);

	for (intIndex = 0; intIndex < sizeArray - 1; intIndex += 1)
	{
		while (audtSurveyList[intSurveyIndex].sngIncome > 0 && strcmp(audtSurveyList[intSurveyIndex].strRace, "Hispanic") == 0)
		{
			sngTotalIncomeHispanic += audtSurveyList[intSurveyIndex].sngIncome;

			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}

		// move forward in Survey List
		audtSurveyList += 1;
		audtSurveyList[intSurveyIndex + 1];
	}

	// make sure program doesn't crash by dividing by 0
	if (sngTotalIncomeHispanic != 0)
	{
		sngAverageIncomeHispanic = sngTotalIncomeHispanic / intHousesSurveyedHispanic;
	}
	else
	{
		sngAverageIncomeHispanic = 0;
	}

	return sngAverageIncomeHispanic;
}



// --------------------------------------------------------------------------------
// Name: AverageIncomeAsian
// Abstract: Calculates average income for asian households
// --------------------------------------------------------------------------------
float AverageIncomeAsian(udtSurveyType audtSurveyList[], size_t sizeArray, float sngAverageIncomeAsian, int intHousesSurveyedAsian, float sngTotalIncomeAsian)
{
	int intIndex = 0;
	int intSurveyIndex = 0;

	intHousesSurveyedAsian = TotalHouseholdsSurveyedAsian(audtSurveyList, sizeArray, intHousesSurveyedAsian);

	for (intIndex = 0; intIndex < sizeArray - 1; intIndex += 1)
	{
		while (audtSurveyList[intSurveyIndex].sngIncome > 0 && strcmp(audtSurveyList[intSurveyIndex].strRace, "Asian") == 0)
		{
			sngTotalIncomeAsian += audtSurveyList[intSurveyIndex].sngIncome;

			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}

		// move forward in Survey List
		audtSurveyList += 1;
		audtSurveyList[intSurveyIndex + 1];
	}

	// make sure program doesn't crash by dividing by 0
	if (sngTotalIncomeAsian != 0)
	{
		sngAverageIncomeAsian = sngTotalIncomeAsian / intHousesSurveyedAsian;
	}
	else
	{
		sngAverageIncomeAsian = 0;
	}

	return sngAverageIncomeAsian;
}


// --------------------------------------------------------------------------------
// Name: AverageIncomeOther
// Abstract: Calculates average income for other households
// --------------------------------------------------------------------------------
float AverageIncomeOther(udtSurveyType audtSurveyList[], size_t sizeArray, float sngAverageIncomeOther, int intHousesSurveyedOther, float sngTotalIncomeOther)
{
	int intIndex = 0;
	int intSurveyIndex = 0;

	intHousesSurveyedOther = TotalHouseholdsSurveyedOther(audtSurveyList, sizeArray, intHousesSurveyedOther);

	for (intIndex = 0; intIndex < sizeArray - 1; intIndex += 1)
	{
		while (audtSurveyList[intSurveyIndex].sngIncome > 0 && strcmp(audtSurveyList[intSurveyIndex].strRace, "Other") == 0)
		{
			sngTotalIncomeOther += audtSurveyList[intSurveyIndex].sngIncome;

			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}

		// move forward in Survey List
		audtSurveyList += 1;
		audtSurveyList[intSurveyIndex + 1];
	}

	// make sure program doesn't crash by dividing by 0
	if (sngTotalIncomeOther != 0)
	{
		sngAverageIncomeOther = sngTotalIncomeOther / intHousesSurveyedOther;
	}
	else
	{
		sngAverageIncomeOther = 0;
	}

	return sngAverageIncomeOther;
}


// --------------------------------------------------------------------------------
// Name: TotalHouseholdsPoverty
// Abstract: Calculates percentage of total households surveyed in poverty
// --------------------------------------------------------------------------------
float TotalHouseholdsPoverty(udtSurveyType audtSurveyList[], size_t sizeArray, int intTotalHousesSurveyed, int intTotalHouseholdsPoverty, float sngPercentageHouseholdsPoverty)
{
	int intIndex = 0;
	int intSurveyIndex = 0;

	intTotalHousesSurveyed = TotalHouseholdsSurveyed(audtSurveyList, sizeArray, intTotalHousesSurveyed);

	for (intIndex = 0; intIndex < sizeArray - 1; intIndex += 1)
	{
		while (audtSurveyList[intSurveyIndex].intHouseholdNumber == 1 && audtSurveyList[intSurveyIndex].sngIncome < MIN_INCOME_1)
		{
			intTotalHouseholdsPoverty += 1;

			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}
		while (audtSurveyList[intSurveyIndex].intHouseholdNumber == 2 && audtSurveyList[intSurveyIndex].sngIncome < MIN_INCOME_2)
		{
			intTotalHouseholdsPoverty += 1;
			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}
		while (audtSurveyList[intSurveyIndex].intHouseholdNumber == 3 && audtSurveyList[intSurveyIndex].sngIncome < MIN_INCOME_3)
		{
			intTotalHouseholdsPoverty += 1;
			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}
		while (audtSurveyList[intSurveyIndex].intHouseholdNumber == 4 && audtSurveyList[intSurveyIndex].sngIncome < MIN_INCOME_4)
		{
			intTotalHouseholdsPoverty += 1;
			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}
		while (audtSurveyList[intSurveyIndex].intHouseholdNumber >= 5 && audtSurveyList[intSurveyIndex].sngIncome < MIN_INCOME_5)
		{
			intTotalHouseholdsPoverty += 1;
			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}

		// move forward in Survey List
		audtSurveyList += 1;
		audtSurveyList[intSurveyIndex + 1];
	}

	// percentage of households in poverty
	// make sure program doesn't crash by dividing by 0
	if (intTotalHouseholdsPoverty != 0)
	{
		sngPercentageHouseholdsPoverty = ((float)intTotalHouseholdsPoverty / intTotalHousesSurveyed) * 100;
	}
	else
	{
		sngPercentageHouseholdsPoverty = 0;
	}

	return sngPercentageHouseholdsPoverty;
}

// --------------------------------------------------------------------------------
// Name: HouseholdsPovertyOhio
// Abstract: Calculates percentage of ohio households surveyed in poverty
// --------------------------------------------------------------------------------
float HouseholdsPovertyOhio(udtSurveyType audtSurveyList[], size_t sizeArray, int intHousesSurveyedOhio, int intHouseholdsPovertyOhio, float sngPercentageHouseholdsPovertyOhio)
{
	int intIndex = 0;
	int intSurveyIndex = 0;

	intHousesSurveyedOhio = TotalHouseholdsSurveyedOhio(audtSurveyList, sizeArray, intHousesSurveyedOhio);

	for (intIndex = 0; intIndex < sizeArray - 1; intIndex += 1)
	{
		while (audtSurveyList[intSurveyIndex].intHouseholdNumber == 1 && audtSurveyList[intSurveyIndex].sngIncome < MIN_INCOME_1
			&& strcmp(audtSurveyList[intSurveyIndex].strState, "Ohio") == 0)
		{
			intHouseholdsPovertyOhio += 1;

			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}
		while (audtSurveyList[intSurveyIndex].intHouseholdNumber == 2 && audtSurveyList[intSurveyIndex].sngIncome < MIN_INCOME_2
			&& strcmp(audtSurveyList[intSurveyIndex].strState, "Ohio") == 0)
		{
			intHouseholdsPovertyOhio += 1;
			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}
		while (audtSurveyList[intSurveyIndex].intHouseholdNumber == 3 && audtSurveyList[intSurveyIndex].sngIncome < MIN_INCOME_3
			&& strcmp(audtSurveyList[intSurveyIndex].strState, "Ohio") == 0)
		{
			intHouseholdsPovertyOhio += 1;
			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}
		while (audtSurveyList[intSurveyIndex].intHouseholdNumber == 4 && audtSurveyList[intSurveyIndex].sngIncome < MIN_INCOME_4
			&& strcmp(audtSurveyList[intSurveyIndex].strState, "Ohio") == 0)
		{
			intHouseholdsPovertyOhio += 1;
			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}
		while (audtSurveyList[intSurveyIndex].intHouseholdNumber >= 5 && audtSurveyList[intSurveyIndex].sngIncome < MIN_INCOME_5
			&& strcmp(audtSurveyList[intSurveyIndex].strState, "Ohio") == 0)
		{
			intHouseholdsPovertyOhio += 1;
			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}

		// move forward in Survey List
		audtSurveyList += 1;
		audtSurveyList[intSurveyIndex + 1];
	}

	// make sure program doesn't crash by dividing by 0
	if (intHouseholdsPovertyOhio != 0)
	{
		sngPercentageHouseholdsPovertyOhio = ((float)intHouseholdsPovertyOhio / intHousesSurveyedOhio) * 100;
	}
	else
	{
		sngPercentageHouseholdsPovertyOhio = 0;
	}

	return sngPercentageHouseholdsPovertyOhio;
}


// --------------------------------------------------------------------------------
// Name: HouseholdsPovertyHamilton
// Abstract: Calculates percentage of hamilton households surveyed in poverty
// --------------------------------------------------------------------------------
float HouseholdsPovertyHamilton(udtSurveyType audtSurveyList[], size_t sizeArray, int intHousesSurveyedHamilton, int intHouseholdsPovertyHamilton, float sngPercentageHouseholdsPovertyHamilton)
{
	int intIndex = 0;
	int intSurveyIndex = 0;

	intHousesSurveyedHamilton = TotalHouseholdsSurveyedHamilton(audtSurveyList, sizeArray, intHousesSurveyedHamilton);

	for (intIndex = 0; intIndex < sizeArray - 1; intIndex += 1)
	{
		while (audtSurveyList[intSurveyIndex].intHouseholdNumber == 1 && audtSurveyList[intSurveyIndex].sngIncome < MIN_INCOME_1
			&& strcmp(audtSurveyList[intSurveyIndex].strCounty, "Hamilton") == 0)
		{
			intHouseholdsPovertyHamilton += 1;

			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}
		while (audtSurveyList[intSurveyIndex].intHouseholdNumber == 2 && audtSurveyList[intSurveyIndex].sngIncome < MIN_INCOME_2
			&& strcmp(audtSurveyList[intSurveyIndex].strCounty, "Hamilton") == 0)
		{
			intHouseholdsPovertyHamilton += 1;
			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}
		while (audtSurveyList[intSurveyIndex].intHouseholdNumber == 3 && audtSurveyList[intSurveyIndex].sngIncome < MIN_INCOME_3
			&& strcmp(audtSurveyList[intSurveyIndex].strCounty, "Hamilton") == 0)
		{
			intHouseholdsPovertyHamilton += 1;
			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}
		while (audtSurveyList[intSurveyIndex].intHouseholdNumber == 4 && audtSurveyList[intSurveyIndex].sngIncome < MIN_INCOME_4
			&& strcmp(audtSurveyList[intSurveyIndex].strCounty, "Hamilton") == 0)
		{
			intHouseholdsPovertyHamilton += 1;
			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}
		while (audtSurveyList[intSurveyIndex].intHouseholdNumber >= 5 && audtSurveyList[intSurveyIndex].sngIncome < MIN_INCOME_5
			&& strcmp(audtSurveyList[intSurveyIndex].strCounty, "Hamilton") == 0)
		{
			intHouseholdsPovertyHamilton += 1;
			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}

		// move forward in Survey List
		audtSurveyList += 1;
		audtSurveyList[intSurveyIndex + 1];
	}

	// make sure program doesn't crash by dividing by 0
	if (intHouseholdsPovertyHamilton != 0)
	{
		sngPercentageHouseholdsPovertyHamilton = ((float)intHouseholdsPovertyHamilton / intHousesSurveyedHamilton) * 100;
	}
	else
	{
		sngPercentageHouseholdsPovertyHamilton = 0;
	}

	return sngPercentageHouseholdsPovertyHamilton;
}


// --------------------------------------------------------------------------------
// Name: HouseholdsPovertyButler
// Abstract: Calculates percentage of butler households surveyed in poverty
// --------------------------------------------------------------------------------
float HouseholdsPovertyButler(udtSurveyType audtSurveyList[], size_t sizeArray, int intHousesSurveyedButler, int intHouseholdsPovertyButler, float sngPercentageHouseholdsPovertyButler)
{
	int intIndex = 0;
	int intSurveyIndex = 0;

	intHousesSurveyedButler = TotalHouseholdsSurveyedButler(audtSurveyList, sizeArray, intHousesSurveyedButler);

	for (intIndex = 0; intIndex < sizeArray - 1; intIndex += 1)
	{
		while (audtSurveyList[intSurveyIndex].intHouseholdNumber == 1 && audtSurveyList[intSurveyIndex].sngIncome < MIN_INCOME_1
			&& strcmp(audtSurveyList[intSurveyIndex].strCounty, "Butler") == 0)
		{
			intHouseholdsPovertyButler += 1;

			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}
		while (audtSurveyList[intSurveyIndex].intHouseholdNumber == 2 && audtSurveyList[intSurveyIndex].sngIncome < MIN_INCOME_2
			&& strcmp(audtSurveyList[intSurveyIndex].strCounty, "Butler") == 0)
		{
			intHouseholdsPovertyButler += 1;
			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}
		while (audtSurveyList[intSurveyIndex].intHouseholdNumber == 3 && audtSurveyList[intSurveyIndex].sngIncome < MIN_INCOME_3
			&& strcmp(audtSurveyList[intSurveyIndex].strCounty, "Butler") == 0)
		{
			intHouseholdsPovertyButler += 1;
			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}
		while (audtSurveyList[intSurveyIndex].intHouseholdNumber == 4 && audtSurveyList[intSurveyIndex].sngIncome < MIN_INCOME_4
			&& strcmp(audtSurveyList[intSurveyIndex].strCounty, "Butler") == 0)
		{
			intHouseholdsPovertyButler += 1;
			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}
		while (audtSurveyList[intSurveyIndex].intHouseholdNumber >= 5 && audtSurveyList[intSurveyIndex].sngIncome < MIN_INCOME_5
			&& strcmp(audtSurveyList[intSurveyIndex].strCounty, "Butler") == 0)
		{
			intHouseholdsPovertyButler += 1;
			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}

		// move forward in Survey List
		audtSurveyList += 1;
		audtSurveyList[intSurveyIndex + 1];
	}

	// make sure program doesn't crash by dividing by 0
	if (intHouseholdsPovertyButler != 0)
	{
		sngPercentageHouseholdsPovertyButler = ((float)intHouseholdsPovertyButler / intHousesSurveyedButler) * 100;
	}
	else
	{
		sngPercentageHouseholdsPovertyButler = 0;
	}

	return sngPercentageHouseholdsPovertyButler;
}


// --------------------------------------------------------------------------------
// Name: HouseholdsPovertyKentucky
// Abstract: Calculates percentage of kentucky households surveyed in poverty
// --------------------------------------------------------------------------------
float HouseholdsPovertyKentucky(udtSurveyType audtSurveyList[], size_t sizeArray, int intHousesSurveyedKentucky, int intHouseholdsPovertyKentucky, float sngPercentageHouseholdsPovertyKentucky)
{
	int intIndex = 0;
	int intSurveyIndex = 0;

	intHousesSurveyedKentucky = TotalHouseholdsSurveyedKentucky(audtSurveyList, sizeArray, intHousesSurveyedKentucky);

	for (intIndex = 0; intIndex < sizeArray - 1; intIndex += 1)
	{
		while (audtSurveyList[intSurveyIndex].intHouseholdNumber == 1 && audtSurveyList[intSurveyIndex].sngIncome < MIN_INCOME_1
			&& strcmp(audtSurveyList[intSurveyIndex].strState, "Kentucky") == 0)
		{
			intHouseholdsPovertyKentucky += 1;

			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}
		while (audtSurveyList[intSurveyIndex].intHouseholdNumber == 2 && audtSurveyList[intSurveyIndex].sngIncome < MIN_INCOME_2
			&& strcmp(audtSurveyList[intSurveyIndex].strState, "Kentucky") == 0)
		{
			intHouseholdsPovertyKentucky += 1;
			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}
		while (audtSurveyList[intSurveyIndex].intHouseholdNumber == 3 && audtSurveyList[intSurveyIndex].sngIncome < MIN_INCOME_3
			&& strcmp(audtSurveyList[intSurveyIndex].strState, "Kentucky") == 0)
		{
			intHouseholdsPovertyKentucky += 1;
			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}
		while (audtSurveyList[intSurveyIndex].intHouseholdNumber == 4 && audtSurveyList[intSurveyIndex].sngIncome < MIN_INCOME_4
			&& strcmp(audtSurveyList[intSurveyIndex].strState, "Kentucky") == 0)
		{
			intHouseholdsPovertyKentucky += 1;
			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}
		while (audtSurveyList[intSurveyIndex].intHouseholdNumber >= 5 && audtSurveyList[intSurveyIndex].sngIncome < MIN_INCOME_5
			&& strcmp(audtSurveyList[intSurveyIndex].strState, "Kentucky") == 0)
		{
			intHouseholdsPovertyKentucky += 1;
			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}

		// move forward in Survey List
		audtSurveyList += 1;
		audtSurveyList[intSurveyIndex + 1];
	}

	// make sure program doesn't crash by dividing by 0
	if (intHouseholdsPovertyKentucky != 0)
	{
		sngPercentageHouseholdsPovertyKentucky = ((float)intHouseholdsPovertyKentucky / intHousesSurveyedKentucky) * 100;
	}
	else
	{
		sngPercentageHouseholdsPovertyKentucky = 0;
	}

	return sngPercentageHouseholdsPovertyKentucky;
}


// --------------------------------------------------------------------------------
// Name: HouseholdsPovertyBoone
// Abstract: Calculates percentage of boone households surveyed in poverty
// --------------------------------------------------------------------------------
float HouseholdsPovertyBoone(udtSurveyType audtSurveyList[], size_t sizeArray, int intHousesSurveyedBoone, int intHouseholdsPovertyBoone, float sngPercentageHouseholdsPovertyBoone)
{
	int intIndex = 0;
	int intSurveyIndex = 0;

	intHousesSurveyedBoone = TotalHouseholdsSurveyedBoone(audtSurveyList, sizeArray, intHousesSurveyedBoone);

	for (intIndex = 0; intIndex < sizeArray - 1; intIndex += 1)
	{
		while (audtSurveyList[intSurveyIndex].intHouseholdNumber == 1 && audtSurveyList[intSurveyIndex].sngIncome < MIN_INCOME_1
			&& strcmp(audtSurveyList[intSurveyIndex].strCounty, "Boone") == 0)
		{
			intHouseholdsPovertyBoone += 1;

			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}
		while (audtSurveyList[intSurveyIndex].intHouseholdNumber == 2 && audtSurveyList[intSurveyIndex].sngIncome < MIN_INCOME_2
			&& strcmp(audtSurveyList[intSurveyIndex].strCounty, "Boone") == 0)
		{
			intHouseholdsPovertyBoone += 1;
			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}
		while (audtSurveyList[intSurveyIndex].intHouseholdNumber == 3 && audtSurveyList[intSurveyIndex].sngIncome < MIN_INCOME_3
			&& strcmp(audtSurveyList[intSurveyIndex].strCounty, "Boone") == 0)
		{
			intHouseholdsPovertyBoone += 1;
			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}
		while (audtSurveyList[intSurveyIndex].intHouseholdNumber == 4 && audtSurveyList[intSurveyIndex].sngIncome < MIN_INCOME_4
			&& strcmp(audtSurveyList[intSurveyIndex].strCounty, "Boone") == 0)
		{
			intHouseholdsPovertyBoone += 1;
			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}
		while (audtSurveyList[intSurveyIndex].intHouseholdNumber >= 5 && audtSurveyList[intSurveyIndex].sngIncome < MIN_INCOME_5
			&& strcmp(audtSurveyList[intSurveyIndex].strCounty, "Boone") == 0)
		{
			intHouseholdsPovertyBoone += 1;
			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}

		// move forward in Survey List
		audtSurveyList += 1;
		audtSurveyList[intSurveyIndex + 1];
	}

	// make sure program doesn't crash by dividing by 0
	if (intHouseholdsPovertyBoone != 0)
	{
		sngPercentageHouseholdsPovertyBoone = ((float)intHouseholdsPovertyBoone / intHousesSurveyedBoone) * 100;
	}
	else
	{
		sngPercentageHouseholdsPovertyBoone = 0;
	}

	return sngPercentageHouseholdsPovertyBoone;
}


// --------------------------------------------------------------------------------
// Name: HouseholdsPovertyKenton
// Abstract: Calculates percentage of kenton households surveyed in poverty
// --------------------------------------------------------------------------------
float HouseholdsPovertyKenton(udtSurveyType audtSurveyList[], size_t sizeArray, int intHousesSurveyedKenton, int intHouseholdsPovertyKenton, float sngPercentageHouseholdsPovertyKenton)
{
	int intIndex = 0;
	int intSurveyIndex = 0;

	intHousesSurveyedKenton = TotalHouseholdsSurveyedKenton(audtSurveyList, sizeArray, intHousesSurveyedKenton);

	for (intIndex = 0; intIndex < sizeArray - 1; intIndex += 1)
	{
		while (audtSurveyList[intSurveyIndex].intHouseholdNumber == 1 && audtSurveyList[intSurveyIndex].sngIncome < MIN_INCOME_1
			&& strcmp(audtSurveyList[intSurveyIndex].strCounty, "Kenton") == 0)
		{
			intHouseholdsPovertyKenton += 1;

			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}
		while (audtSurveyList[intSurveyIndex].intHouseholdNumber == 2 && audtSurveyList[intSurveyIndex].sngIncome < MIN_INCOME_2
			&& strcmp(audtSurveyList[intSurveyIndex].strCounty, "Kenton") == 0)
		{
			intHouseholdsPovertyKenton += 1;
			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}
		while (audtSurveyList[intSurveyIndex].intHouseholdNumber == 3 && audtSurveyList[intSurveyIndex].sngIncome < MIN_INCOME_3
			&& strcmp(audtSurveyList[intSurveyIndex].strCounty, "Kenton") == 0)
		{
			intHouseholdsPovertyKenton += 1;
			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}
		while (audtSurveyList[intSurveyIndex].intHouseholdNumber == 4 && audtSurveyList[intSurveyIndex].sngIncome < MIN_INCOME_4
			&& strcmp(audtSurveyList[intSurveyIndex].strCounty, "Kenton") == 0)
		{
			intHouseholdsPovertyKenton += 1;
			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}
		while (audtSurveyList[intSurveyIndex].intHouseholdNumber >= 5 && audtSurveyList[intSurveyIndex].sngIncome < MIN_INCOME_5
			&& strcmp(audtSurveyList[intSurveyIndex].strCounty, "Kenton") == 0)
		{
			intHouseholdsPovertyKenton += 1;
			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}

		// move forward in Survey List
		audtSurveyList += 1;
		audtSurveyList[intSurveyIndex + 1];
	}

	// make sure program doesn't crash by dividing by 0
	if (intHouseholdsPovertyKenton != 0)
	{
		sngPercentageHouseholdsPovertyKenton = ((float)intHouseholdsPovertyKenton / intHousesSurveyedKenton) * 100;
	}
	else
	{
		sngPercentageHouseholdsPovertyKenton = 0;
	}

	return sngPercentageHouseholdsPovertyKenton;
}


// --------------------------------------------------------------------------------
// Name: HouseholdsPovertyCaucasian
// Abstract: Calculates percentage of caucasian households surveyed in poverty
// --------------------------------------------------------------------------------
float HouseholdsPovertyCaucasian(udtSurveyType audtSurveyList[], size_t sizeArray, int intHousesSurveyedCaucasian, int intHouseholdsPovertyCaucasian, float sngPercentageHouseholdsPovertyCaucasian)
{
	int intIndex = 0;
	int intSurveyIndex = 0;

	intHousesSurveyedCaucasian = TotalHouseholdsSurveyedCaucasian(audtSurveyList, sizeArray, intHousesSurveyedCaucasian);

	for (intIndex = 0; intIndex < sizeArray - 1; intIndex += 1)
	{
		while (audtSurveyList[intSurveyIndex].intHouseholdNumber == 1 && audtSurveyList[intSurveyIndex].sngIncome < MIN_INCOME_1
			&& strcmp(audtSurveyList[intSurveyIndex].strRace, "Caucasian") == 0)
		{
			intHouseholdsPovertyCaucasian += 1;

			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}
		while (audtSurveyList[intSurveyIndex].intHouseholdNumber == 2 && audtSurveyList[intSurveyIndex].sngIncome < MIN_INCOME_2
			&& strcmp(audtSurveyList[intSurveyIndex].strRace, "Caucasian") == 0)
		{
			intHouseholdsPovertyCaucasian += 1;
			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}
		while (audtSurveyList[intSurveyIndex].intHouseholdNumber == 3 && audtSurveyList[intSurveyIndex].sngIncome < MIN_INCOME_3
			&& strcmp(audtSurveyList[intSurveyIndex].strRace, "Caucasian") == 0)
		{
			intHouseholdsPovertyCaucasian += 1;
			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}
		while (audtSurveyList[intSurveyIndex].intHouseholdNumber == 4 && audtSurveyList[intSurveyIndex].sngIncome < MIN_INCOME_4
			&& strcmp(audtSurveyList[intSurveyIndex].strRace, "Caucasian") == 0)
		{
			intHouseholdsPovertyCaucasian += 1;
			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}
		while (audtSurveyList[intSurveyIndex].intHouseholdNumber >= 5 && audtSurveyList[intSurveyIndex].sngIncome < MIN_INCOME_5
			&& strcmp(audtSurveyList[intSurveyIndex].strRace, "Caucasian") == 0)
		{
			intHouseholdsPovertyCaucasian += 1;
			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}

		// move forward in Survey List
		audtSurveyList += 1;
		audtSurveyList[intSurveyIndex + 1];
	}
	// make sure program doesn't crash by dividing by 0
	if (intHouseholdsPovertyCaucasian != 0)
	{
		sngPercentageHouseholdsPovertyCaucasian = ((float)intHouseholdsPovertyCaucasian / intHousesSurveyedCaucasian) * 100;
	}
	else
	{
		sngPercentageHouseholdsPovertyCaucasian = 0;
	}

	return sngPercentageHouseholdsPovertyCaucasian;
}


// --------------------------------------------------------------------------------
// Name: HouseholdsPovertyAfricanAmerican
// Abstract: Calculates percentage of african american households surveyed in poverty
// --------------------------------------------------------------------------------
float HouseholdsPovertyAfricanAmerican(udtSurveyType audtSurveyList[], size_t sizeArray, int intHousesSurveyedAfricanAmerican, int intHouseholdsPovertyAfricanAmerican, float sngPercentageHouseholdsPovertyAfricanAmerican)
{
	int intIndex = 0;
	int intSurveyIndex = 0;

	intHousesSurveyedAfricanAmerican = TotalHouseholdsSurveyedAfricanAmerican(audtSurveyList, sizeArray, intHousesSurveyedAfricanAmerican);

	for (intIndex = 0; intIndex < sizeArray - 1; intIndex += 1)
	{
		while (audtSurveyList[intSurveyIndex].intHouseholdNumber == 1 && audtSurveyList[intSurveyIndex].sngIncome < MIN_INCOME_1
			&& strcmp(audtSurveyList[intSurveyIndex].strRace, "African American") == 0)
		{
			intHouseholdsPovertyAfricanAmerican += 1;

			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}
		while (audtSurveyList[intSurveyIndex].intHouseholdNumber == 2 && audtSurveyList[intSurveyIndex].sngIncome < MIN_INCOME_2
			&& strcmp(audtSurveyList[intSurveyIndex].strRace, "African American") == 0)
		{
			intHouseholdsPovertyAfricanAmerican += 1;
			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}
		while (audtSurveyList[intSurveyIndex].intHouseholdNumber == 3 && audtSurveyList[intSurveyIndex].sngIncome < MIN_INCOME_3
			&& strcmp(audtSurveyList[intSurveyIndex].strRace, "African American") == 0)
		{
			intHouseholdsPovertyAfricanAmerican += 1;
			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}
		while (audtSurveyList[intSurveyIndex].intHouseholdNumber == 4 && audtSurveyList[intSurveyIndex].sngIncome < MIN_INCOME_4
			&& strcmp(audtSurveyList[intSurveyIndex].strRace, "African American") == 0)
		{
			intHouseholdsPovertyAfricanAmerican += 1;
			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}
		while (audtSurveyList[intSurveyIndex].intHouseholdNumber >= 5 && audtSurveyList[intSurveyIndex].sngIncome < MIN_INCOME_5
			&& strcmp(audtSurveyList[intSurveyIndex].strRace, "African American") == 0)
		{
			intHouseholdsPovertyAfricanAmerican += 1;
			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}

		// move forward in Survey List
		audtSurveyList += 1;
		audtSurveyList[intSurveyIndex + 1];
	}

	// make sure program doesn't crash by dividing by 0
	if (intHouseholdsPovertyAfricanAmerican != 0)
	{
		sngPercentageHouseholdsPovertyAfricanAmerican = ((float)intHouseholdsPovertyAfricanAmerican / intHousesSurveyedAfricanAmerican) * 100;
	}
	else
	{
		sngPercentageHouseholdsPovertyAfricanAmerican = 0;
	}

	return sngPercentageHouseholdsPovertyAfricanAmerican;
}


// --------------------------------------------------------------------------------
// Name: HouseholdsPovertyHispanic
// Abstract: Calculates percentage of hispanic households surveyed in poverty
// --------------------------------------------------------------------------------
float HouseholdsPovertyHispanic(udtSurveyType audtSurveyList[], size_t sizeArray, int intHousesSurveyedHispanic, int intHouseholdsPovertyHispanic, float sngPercentageHouseholdsPovertyHispanic)
{
	int intIndex = 0;
	int intSurveyIndex = 0;

	intHousesSurveyedHispanic = TotalHouseholdsSurveyedHispanic(audtSurveyList, sizeArray, intHousesSurveyedHispanic);

	for (intIndex = 0; intIndex < sizeArray - 1; intIndex += 1)
	{
		while (audtSurveyList[intSurveyIndex].intHouseholdNumber == 1 && audtSurveyList[intSurveyIndex].sngIncome < MIN_INCOME_1
			&& strcmp(audtSurveyList[intSurveyIndex].strRace, "Hispanic") == 0)
		{
			intHouseholdsPovertyHispanic += 1;

			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}
		while (audtSurveyList[intSurveyIndex].intHouseholdNumber == 2 && audtSurveyList[intSurveyIndex].sngIncome < MIN_INCOME_2
			&& strcmp(audtSurveyList[intSurveyIndex].strRace, "Hispanic") == 0)
		{
			intHouseholdsPovertyHispanic += 1;
			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}
		while (audtSurveyList[intSurveyIndex].intHouseholdNumber == 3 && audtSurveyList[intSurveyIndex].sngIncome < MIN_INCOME_3
			&& strcmp(audtSurveyList[intSurveyIndex].strRace, "Hispanic") == 0)
		{
			intHouseholdsPovertyHispanic += 1;
			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}
		while (audtSurveyList[intSurveyIndex].intHouseholdNumber == 4 && audtSurveyList[intSurveyIndex].sngIncome < MIN_INCOME_4
			&& strcmp(audtSurveyList[intSurveyIndex].strRace, "Hispanic") == 0)
		{
			intHouseholdsPovertyHispanic += 1;
			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}
		while (audtSurveyList[intSurveyIndex].intHouseholdNumber >= 5 && audtSurveyList[intSurveyIndex].sngIncome < MIN_INCOME_5
			&& strcmp(audtSurveyList[intSurveyIndex].strRace, "Hispanic") == 0)
		{
			intHouseholdsPovertyHispanic += 1;
			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}

		// move forward in Survey List
		audtSurveyList += 1;
		audtSurveyList[intSurveyIndex + 1];
	}

	// make sure program doesn't crash by dividing by 0
	if (intHouseholdsPovertyHispanic != 0)
	{
		sngPercentageHouseholdsPovertyHispanic = ((float)intHouseholdsPovertyHispanic / intHousesSurveyedHispanic) * 100;
	}
	else
	{
		sngPercentageHouseholdsPovertyHispanic = 0;
	}

	return sngPercentageHouseholdsPovertyHispanic;
}


// --------------------------------------------------------------------------------
// Name: HouseholdsPovertyAsian
// Abstract: Calculates percentage of asian households surveyed in poverty
// --------------------------------------------------------------------------------
float HouseholdsPovertyAsian(udtSurveyType audtSurveyList[], size_t sizeArray, int intHousesSurveyedAsian, int intHouseholdsPovertyAsian, float sngPercentageHouseholdsPovertyAsian)
{
	int intIndex = 0;
	int intSurveyIndex = 0;

	intHousesSurveyedAsian = TotalHouseholdsSurveyedAsian(audtSurveyList, sizeArray, intHousesSurveyedAsian);

	for (intIndex = 0; intIndex < sizeArray - 1; intIndex += 1)
	{
		while (audtSurveyList[intSurveyIndex].intHouseholdNumber == 1 && audtSurveyList[intSurveyIndex].sngIncome < MIN_INCOME_1
			&& strcmp(audtSurveyList[intSurveyIndex].strRace, "Asian") == 0)
		{
			intHouseholdsPovertyAsian += 1;

			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}
		while (audtSurveyList[intSurveyIndex].intHouseholdNumber == 2 && audtSurveyList[intSurveyIndex].sngIncome < MIN_INCOME_2
			&& strcmp(audtSurveyList[intSurveyIndex].strRace, "Asian") == 0)
		{
			intHouseholdsPovertyAsian += 1;
			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}
		while (audtSurveyList[intSurveyIndex].intHouseholdNumber == 3 && audtSurveyList[intSurveyIndex].sngIncome < MIN_INCOME_3
			&& strcmp(audtSurveyList[intSurveyIndex].strRace, "Asian") == 0)
		{
			intHouseholdsPovertyAsian += 1;
			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}
		while (audtSurveyList[intSurveyIndex].intHouseholdNumber == 4 && audtSurveyList[intSurveyIndex].sngIncome < MIN_INCOME_4
			&& strcmp(audtSurveyList[intSurveyIndex].strRace, "Asian") == 0)
		{
			intHouseholdsPovertyAsian += 1;
			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}
		while (audtSurveyList[intSurveyIndex].intHouseholdNumber >= 5 && audtSurveyList[intSurveyIndex].sngIncome < MIN_INCOME_5
			&& strcmp(audtSurveyList[intSurveyIndex].strRace, "Asian") == 0)
		{
			intHouseholdsPovertyAsian += 1;
			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}

		// move forward in Survey List
		audtSurveyList += 1;
		audtSurveyList[intSurveyIndex + 1];
	}

	// make sure program doesn't crash by dividing by 0
	if (intHouseholdsPovertyAsian != 0)
	{
		sngPercentageHouseholdsPovertyAsian = ((float)intHouseholdsPovertyAsian / intHousesSurveyedAsian) * 100;
	}
	else
	{
		sngPercentageHouseholdsPovertyAsian = 0;
	}

	return sngPercentageHouseholdsPovertyAsian;
}


// --------------------------------------------------------------------------------
// Name: HouseholdsPovertyOther
// Abstract: Calculates percentage of other households surveyed in poverty
// --------------------------------------------------------------------------------
float HouseholdsPovertyOther(udtSurveyType audtSurveyList[], size_t sizeArray, int intHousesSurveyedOther, int intHouseholdsPovertyOther, float sngPercentageHouseholdsPovertyOther)
{
	int intIndex = 0;
	int intSurveyIndex = 0;

	intHousesSurveyedOther = TotalHouseholdsSurveyedOther(audtSurveyList, sizeArray, intHousesSurveyedOther);

	for (intIndex = 0; intIndex < sizeArray - 1; intIndex += 1)
	{
		while (audtSurveyList[intSurveyIndex].intHouseholdNumber == 1 && audtSurveyList[intSurveyIndex].sngIncome < MIN_INCOME_1
			&& strcmp(audtSurveyList[intSurveyIndex].strRace, "Other") == 0)
		{
			intHouseholdsPovertyOther += 1;

			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}
		while (audtSurveyList[intSurveyIndex].intHouseholdNumber == 2 && audtSurveyList[intSurveyIndex].sngIncome < MIN_INCOME_2
			&& strcmp(audtSurveyList[intSurveyIndex].strRace, "Other") == 0)
		{
			intHouseholdsPovertyOther += 1;
			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}
		while (audtSurveyList[intSurveyIndex].intHouseholdNumber == 3 && audtSurveyList[intSurveyIndex].sngIncome < MIN_INCOME_3
			&& strcmp(audtSurveyList[intSurveyIndex].strRace, "Other") == 0)
		{
			intHouseholdsPovertyOther += 1;
			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}
		while (audtSurveyList[intSurveyIndex].intHouseholdNumber == 4 && audtSurveyList[intSurveyIndex].sngIncome < MIN_INCOME_4
			&& strcmp(audtSurveyList[intSurveyIndex].strRace, "Other") == 0)
		{
			intHouseholdsPovertyOther += 1;
			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}
		while (audtSurveyList[intSurveyIndex].intHouseholdNumber >= 5 && audtSurveyList[intSurveyIndex].sngIncome < MIN_INCOME_5
			&& strcmp(audtSurveyList[intSurveyIndex].strRace, "Other") == 0)
		{
			intHouseholdsPovertyOther += 1;
			// move forward in Survey List
			audtSurveyList += 1;
			audtSurveyList[intSurveyIndex + 1];
		}

		// move forward in Survey List
		audtSurveyList += 1;
		audtSurveyList[intSurveyIndex + 1];
	}

	// make sure program doesn't crash by dividing by 0
	if (intHouseholdsPovertyOther != 0)
	{
		sngPercentageHouseholdsPovertyOther = ((float)intHouseholdsPovertyOther / intHousesSurveyedOther) * 100;
	}
	else
	{
		sngPercentageHouseholdsPovertyOther = 0;
	}

	return sngPercentageHouseholdsPovertyOther;
}



// --------------------------------------------------------------------------------
// Name: UserMenu
// Abstract: Main menu user selects task from
// --------------------------------------------------------------------------------
char UserMenu(char chrSelection)
{
	// User Menu
	printf("\n*** CENSUS BUREAU USER MENU ***\n\n");
	printf("*** MAKE A SELECTION ***\n\n");
	printf("A. Total Households Surveyed\n");
	printf("B. Total Households Surveyed per County and State\n");
	printf("C. Total Households Surveyed per Race\n");
	printf("D. Average Household Income\n");
	printf("E. Average Household Income per county and state\n");
	printf("F. Average Household Income per race\n");
	printf("G. Percentage below Poverty\n");
	printf("H. Percentage below Poverty per county and state\n");
	printf("I. Percentage below Poverty per race\n");
	printf("X. Exit\n\n");
	printf("User Selection: ");
	scanf(" %c", &chrSelection);
	printf("\n");

	return chrSelection;

}


// --------------------------------------------------------------------------------
// Name: InitializeSurveyList
// Abstract: Intialize all the households in the list
// --------------------------------------------------------------------------------
void InitializeSurveyList(udtSurveyType audtSurveyList[])
{
	int intIndex = 0;

	for (intIndex = 0; intIndex < sizeof(audtSurveyList) + 1; intIndex += 1)
	{
		// Pass a single array element by pointer
		InitializeSurvey(&audtSurveyList[intIndex]);
	}
}


// --------------------------------------------------------------------------------
// Name: InitializeSurvey
// Abstract: Set all the values to 0 or empty strings.
// --------------------------------------------------------------------------------
void InitializeSurvey(udtSurveyType* pudtSurvey)
{
	// Use -> or *( ). syntax.  Both are functionally equivalent
	strcpy(pudtSurvey->dtmDate, "");
	strcpy(pudtSurvey->strState, "");
	strcpy(pudtSurvey->strCounty, "");
	strcpy(pudtSurvey->strRace, "");
	pudtSurvey->intHouseholdNumber = 0;
	pudtSurvey->sngIncome = 0;
}


// --------------------------------------------------------------------------------
// Name: PopulateSurveyList
// Abstract: Load the surveys from a file into the array.
// --------------------------------------------------------------------------------
int PopulateSurveyList(udtSurveyType audtSurveyList[], udtSurveyType* pudtSurvey)
{
	// Declare a file pointer
	FILE* pfilInput = 0;
	int intResultFlag = 0;
	char strBuffer[100] = "";
	char chrLetter = 0;
	int intIndex = 0;
	size_t sizeArray = 0;

	// pudtSurvey = (udtSurveyType*) calloc(1, sizeof(udtSurveyType));


	// Try to open the file for reading (notice you have to double up the backslashes)
	intResultFlag = OpenInputFile("/temp/test.txt", &pfilInput);

	// Was the file opened?
	if (intResultFlag == 1)
	{

		// Yes, read in records until end of file( EOF )
		while (feof(pfilInput) == 0)
		{
			// Grow array
			sizeArray += 1;

			ReadNextLineFromFile(strBuffer, pfilInput);

			// Dynamically allocate memory 
			pudtSurvey = realloc(pudtSurvey, sizeArray * sizeof(udtSurveyType));

			// Add to array
			AddSurveyToArray(strBuffer, &audtSurveyList[intIndex]);

			// Next record
			intIndex += 1;
		}

		audtSurveyList = pudtSurvey;

		// Delete memory 
		free(audtSurveyList);

		

		// Clean up
		fclose(pfilInput);
	}

	// Return the size of the array after reading in the whole text file
	return sizeArray;
}


// --------------------------------------------------------------------------------
// Name: OpenInputFile
// Abstract: Open the file for reading.  Return true if successful.
// --------------------------------------------------------------------------------
int OpenInputFile(char strFileName[], FILE** ppfilInput)
{

	int intResultFlag = 0;

	// Open the file for reading
	*ppfilInput = fopen(strFileName, "rb");

	// Success?
	if (*ppfilInput != 0)
	{
		// Yes
		intResultFlag = 1;
	}
	else
	{
		// No
		printf("Error opening %s for reading!!!\n", strFileName);
	}

	return intResultFlag;

}


// --------------------------------------------------------------------------------
// Name: ReadNextLineFromFile
// Abstract: Read until the end of the line or the end of the file.
// --------------------------------------------------------------------------------
int ReadNextLineFromFile(char strBuffer[], FILE* pfilInput)
{
	char chrLetter = 0;
	int intIndex = 0;

	// Any data left in file?
	while (feof(pfilInput) == 0)
	{
		// Yes, get the next letter
		chrLetter = fgetc(pfilInput);

		// Add to string
		strBuffer[intIndex] = chrLetter;

		// Count it
		intIndex += 1;

		// End of the line?
		if (chrLetter == '\n')
		{
			// Yes, stop reading
			break;
		}
	}

	// Terminate
	strBuffer[intIndex] = 0;

}


// --------------------------------------------------------------------------------
// Name: AddSurveyToArray
// Abstract: Add survey to the array
// --------------------------------------------------------------------------------
void AddSurveyToArray(char strSurvey[], udtSurveyType* pudtSurvey)
{
	char strNextField[50] = "";
	int intNextField = 0;
	float sngNextField = 0;

	// Append a comma so parsing last field is just like all the others
	// AppendString(strSurvey, ",");
	strcat(strSurvey, ",");

	// Date
	GetNextField(strNextField, strSurvey, ',');
	strcpy(pudtSurvey->dtmDate, strNextField);

	// State
	GetNextField(strNextField, strSurvey, ',');
	strcpy(pudtSurvey->strState, strNextField);

	// County
	GetNextField(strNextField, strSurvey, ',');
	strcpy(pudtSurvey->strCounty, strNextField);

	// Race
	GetNextField(strNextField, strSurvey, ',');
	strcpy(pudtSurvey->strRace, strNextField);

	// Household number
	GetNextField(strNextField, strSurvey, ',');
	pudtSurvey->intHouseholdNumber = atoi(strNextField);

	// Income
	GetNextField(strNextField, strSurvey, ',');
	pudtSurvey->sngIncome = atof(strNextField);

	pudtSurvey += 1;

}



// --------------------------------------------------------------------------------
// Name: GetNextField
// Abstract: Get and remove everything up to the next delimiter.
// --------------------------------------------------------------------------------
void GetNextField(char strNextField[], char strSource[], char chrDelimiter)
{
	int intDelimiterIndex = 0;
	int intIndex = 0;

	// Finds first comma
	intDelimiterIndex = FindLetterIndex(strSource, chrDelimiter);

	// Did we find it?
	if (intDelimiterIndex >= 0)
	{
		// copies everything up to comma into next field
		for (intIndex = 0; intIndex < intDelimiterIndex; intIndex += 1)
		{
			strNextField[intIndex] = strSource[intIndex];
		}

		// Terminate
		strNextField[intIndex] = 0;

		// Copy everything after the comma (+1) up to the end of the string
		intIndex = 0;
		while (strSource[intDelimiterIndex + 1 + intIndex] != 0)
		{
			strSource[intIndex] = strSource[intDelimiterIndex + 1 + intIndex];

			intIndex += 1;
		}

		// Terminate
		strSource[intIndex] = 0;

		Trim(strSource);

		Trim(strNextField);

	}

}


// --------------------------------------------------------------------------------
// Name: PrintSurveyList
// Abstract: Print all the surveys
// --------------------------------------------------------------------------------
void PrintSurveyList(udtSurveyType audtSurveyList[], size_t sizeArray)
{
	int intIndex = 0;

	for (intIndex = 0; intIndex < sizeArray - 1; intIndex += 1)
	{
		// Don't print blank records
		if (audtSurveyList[intIndex].dtmDate >= 1)
		{
			// Pass a single array element 
			PrintSurvey(intIndex, audtSurveyList[intIndex]);
		}
	}
}



// --------------------------------------------------------------------------------
// Name: PrintSurvey
// Abstract: Print all the structure field values
// --------------------------------------------------------------------------------
void PrintSurvey(int intIndex, udtSurveyType udtSurvey)
{
	printf("\n");
	printf("Survey #%2d ----------------------------------------\n", intIndex + 1);
	printf("\tDate				: %s\n", udtSurvey.dtmDate);
	printf("\tState				: %s\n", udtSurvey.strState);
	printf("\tCounty			\t: %s\n", udtSurvey.strCounty);
	printf("\tRace				: %s\n", udtSurvey.strRace);
	printf("\tHousehold Number  \t\t: %d\n", udtSurvey.intHouseholdNumber);
	printf("\tIncome			\t: $%.2f\n", udtSurvey.sngIncome);
}




// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
// String Functions
// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------



// --------------------------------------------------------------------------------
// Name: StringLength
// Abstract: Return the string length
// --------------------------------------------------------------------------------
int StringLength(char strSource[])
{
	int intIndex = 0;
	int intLength = 0;

	// Pre-test because string may be empty
	while (strSource[intIndex] != 0)
	{
		intIndex += 1;
	}

	intLength = intIndex;

	return intLength;
}


// --------------------------------------------------------------------------------
// Name: FindLetterIndex
// Abstract: Find first occurence of letter (case-sensitive) from left to right.
// --------------------------------------------------------------------------------
int FindLetterIndex(char strSource[], char chrLetterToFind)
{
	int intLetterToFindIndex = -1;
	int intIndex = 0;

	// Check character
	while (strSource[intIndex] != 0)
	{
		// Is this the character for which we are looking
		if (strSource[intIndex] == chrLetterToFind)
		{
			// Yes, save the index
			intLetterToFindIndex = intIndex;

			// Stop searching
			break;
		}
		intIndex += 1;
	}

	return intLetterToFindIndex;
}



// --------------------------------------------------------------------------------
// Name: Trim
// Abstract: Remove leading and trailing whitespace (space, tab or newline)
// --------------------------------------------------------------------------------
void Trim(char strSource[])
{

	int intIndex = 0;
	int intFirstNonWhitespaceIndex = -1;
	int intLastNonWhitespaceIndex = 0;
	int intSourceIndex = 0;
	int intDestinationIndex = 0;

	// Default first non-whitespace character index to end of string in case string is all whitespace
	// Bug fix.  Not in video.
	intFirstNonWhitespaceIndex = StringLength(strSource);

	// Find first non-whitespace character
	while (strSource[intIndex] != 0)
	{
		// Non-whitespace character?
		if (IsWhiteSpace(strSource[intIndex]) == false)
		{
			// Yes, save the index
			intFirstNonWhitespaceIndex = intIndex;

			// Stop searching!
			break;
		}

		// Next character
		intIndex += 1;
	}

	// Find the last non-whitespace character
	while (strSource[intIndex] != 0)
	{
		// Non-whitespace character?
		if (IsWhiteSpace(strSource[intIndex]) == false)
		{
			// Yes, save the index
			intLastNonWhitespaceIndex = intIndex;
		}

		// Next character
		intIndex += 1;
	}

	// Any non-whitepsace characters?
	if (intFirstNonWhitespaceIndex >= 0)
	{
		// Yes, copy everything in between
		for (intSourceIndex = intFirstNonWhitespaceIndex; intSourceIndex <= intLastNonWhitespaceIndex; intSourceIndex += 1)
		{
			// Copy next character
			strSource[intDestinationIndex] = strSource[intSourceIndex];

			intDestinationIndex += 1;
		}
	}

	// Terminate 
	strSource[intDestinationIndex] = 0;
}



// --------------------------------------------------------------------------------
// Name: IsWhiteSpace
// Abstract: Return true if letter is a space, tab, newline or carriage return
// --------------------------------------------------------------------------------
boolean IsWhiteSpace(char chrLetterToCheck)
{
	boolean blnIsWhiteSpace = false;

	// Space
	if (chrLetterToCheck == ' ') blnIsWhiteSpace = true;

	// Tab
	if (chrLetterToCheck == '\t') blnIsWhiteSpace = true;

	// Carriarge return
	if (chrLetterToCheck == '\r') blnIsWhiteSpace = true;

	// Line feed
	if (chrLetterToCheck == '\n') blnIsWhiteSpace = true;

	return blnIsWhiteSpace;
}


// --------------------------------------------------------------------------------
// Name: CountWords
// Abstract: Count the words in a string
// --------------------------------------------------------------------------------
int CountWords(char strSource[])
{
	int intWordCount = 0;
	int intIndex = 0;
	char chrCurrentLetter = 0;
	char chrPreviousLetter = ' ';

	// Copy each character
	while (strSource[intIndex] != 0)
	{
		chrCurrentLetter = strSource[intIndex];

		// Word boundary (space followed by non-space)?
		if (chrPreviousLetter == ' ' && chrCurrentLetter != ' ')
		{
			// Yes, count it
			intWordCount += 1;
		}

		// Save current character
		chrPreviousLetter = chrCurrentLetter;

		// Next
		intIndex += 1;
	}

	return intWordCount;
}