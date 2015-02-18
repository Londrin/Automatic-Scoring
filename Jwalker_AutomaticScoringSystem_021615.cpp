// Jwalker_AutomaticScoringSystem_021615.cpp : Defines the entry point for the console application.
// Jeff Walker
// Automatic Scoring System
// Feb 16th 2015.
// ________________________________________________________________________________________________

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>

using namespace std;

// Function Prototypes.
int Menu();
void Setup(int firstTime, int& numQuestions, vector<char>& quizAnswers, int& numStudents, vector<string>& studentNames);
void Grade(int numQuestions, vector<char> quizAnswers, int numStudents, vector<string> studentNames);
int GetInt(string message);
char GetChar(string message);

int main(int argc, const char * argv[]) {
	// Initial variable setup.
	int numQuestions, numStudents;
	vector<char> quizAnswers;
	vector<string> studentNames;
	int numOfLoops = 0;
	bool exit = false;
	int menuSelection;

	// Calling setup. This is to force the first entry into the program to always go into setup.
	// Future calls use the menu system.
	Setup(numOfLoops, numQuestions, quizAnswers, numStudents, studentNames);

	// I am using numOfLoops to determine an entry message to the user. (To describe the program)
	++numOfLoops;

	// Exit is set to true if the user wants to exit the program.
	while (!exit) {

		// Calling Menu. Retrieving back their value to determine what to do with the program
		menuSelection = Menu();

		// Our if statement chain. Determines how to handle the program. Designed into a loop
		// to allow the user to use the program multiple times.
		if (menuSelection == 3) {
			exit = true;
		}
		else if (menuSelection == 2)
		{
			// Calling setup again. This allows the user to change students, or in the case of a mistake.
			Setup(numOfLoops, numQuestions, quizAnswers, numStudents, studentNames);
		}
		else
		{
			// Calling Grade. This is where the students are finally graded against the stored setup.
			Grade(numQuestions, quizAnswers, numStudents, studentNames);
		}

		++numOfLoops;
	}

	cout << "Thank you for using the Automatic Scoring System!" << endl;
	system("pause");
	return 0;
}

// Menu determines what the user wants to do beyond initial setup of program.
// This will return their selection to drive the program as well.
int Menu()
{
	int selection;
	while (true) {
		cout << "\nPlease select an option below:\n";
		cout << "1) Start grading" << endl;
		cout << "2) Setup and/or change the options of the Automatic Scoring System" << endl;
		cout << "3) Exit Program" << endl;
		cout << ">: ";
		cin >> selection;

		// Input checking.
		if (selection > 0 && selection < 4)
		{
			cin.clear();
			break;
		}
		else
		{
			system("CLS");
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "You entered an incorrect entry - Enter a value between 1 and 3" << endl;
		}
	}
	return selection;
}

// Setup is where the user will decide how many students are graded, as well as the answer to the questions.
void Setup(int firstTime, int& numQuestions, vector<char>& quizAnswers, int& numStudents, vector<string>& studentNames)
{
	// Clearing out quizAnswer and studentNames. This is to make sure that we're working with a clean vector.
	// This corrects some bugs in the program, where the user might enter multiple setups and never get the
	// desired outcome.
	if (quizAnswers.size() > 0)
		quizAnswers.clear();
	if (studentNames.size() > 0)
		studentNames.clear();

	// This is to semi-explain the program so someone can understand what it does.
	if (firstTime == 0) {
		cout << "Welcome to the Automatic Scoring System setup!" << endl;
		cout << "Since this is the first time you have entered setup,\n" <<
			"This system is designed to automatically score multiple\n" <<
			"choice quizzes/tests for you. We will ask you a series \n" <<
			"of questions to get everything setup." << endl;
	}
	else
	{
		cout << "Welcome to the Automatic Scoring System setup!" << endl;
	}

	// Calling GetInt. This has error checking against invalid inputs. It accepts a string as the question.
	// This will insert the number of questions on the test into the variable numQuestions.
	numQuestions = GetInt("\nEnter the total number of questions on the quiz/test: ");
	
	// Initializing variables near to where they are needed - as well as outside the for loop.
	// I have been curious if initializing them in the for loop is bad form or better?
	char answer;
	string question;

	// For loop to retrieve the answers to the previous number of questions.
	// Will be skipped if user inputs 0.
	for (int i = 1; i <= numQuestions; i++)
	{
		// Using a do while to make sure that we always run this atleast once.
		do
		{
			// Assigning question so that we can use it in the call to GetChar - as i is an int.
			question = "Enter the answer for question #" + to_string(i) + " (A-D) : ";

			// Calling GetChar. This function has error checking as well as will retireve
			// the answer to the question.
			answer = GetChar(question);
			// Setting answer equal to the uppercase of the letter entered.
			// This allows correct error checking in the if statement below.
			answer = toupper(answer);

			// Making sure we are getting the correct input.
			if (answer < 65 || answer > 68) {
				cout << "You entered an incorrect value. Please enter an answer from A-D only" << endl;
			}
			// Exiting the while loop if a correct value is input.
		} while (answer < 65 || answer > 68);

		// Using a vector to store the quiz answers. This will expand as necessary to fit the size
		// of questions there are on the quiz. Instead of restricting the user to a specified number
		// I felt this was probably more user friendly. Except for the time when someone decides to
		// put in a rather large quantity of questions.
		quizAnswers.push_back(answer);
	}

	// Calling GetInt to get the number of students.
	numStudents = GetInt("Enter the total number of students to be graded: ");

	// Initializing studenName near the loop, will store the students names.
	string studentName;

	// Capturing the correct quantity of student names that is to be graded.
	for (int i = 1; i <= numStudents; i++)
	{
		cout << "Enter the name of student #" << i << ": ";
		cin >> studentName;
		cin.clear();

		// Storing the students names into a vector. Similar to the previous reasons as quizAnswers.
		studentNames.push_back(studentName);
	}
}

// Grade is designed to grade the quiz/test and allow the user to input the students question answers.
void Grade(int numQuestions, vector<char> quizAnswers, int numStudents, vector<string> studentNames)
{
	// Setup Variables
	vector<char> studentAnswers;
	vector<string>::const_iterator sIter;
	vector<string> finalList;
	double questions = static_cast<double>(numQuestions);
	char answer;
	int count;
	int grade;
	string finalScore;
	string question;

	// Using an iterator to cycle through all the students names since we're using a vector.
	// Could use substring indexing, but felt this was more efficient and something new.
	for (sIter = studentNames.begin() ; sIter != studentNames.end(); ++sIter)
	{
		cout << "We're grading " << *sIter << " now: " << endl;
		
		// Capturing the students question answers similar to the time we get the answers to the quiz/test.
		for (int i = 1; i <= numQuestions; i++)
		{
			do
			{
				question = "what is " + *sIter + "'s answer for question #" + to_string(i) + " (A-D Only): ";
				answer = GetChar(question);
				answer = toupper(answer);

				if (answer < 65 || answer > 68) {
					cout << "\nYou entered an incorrect value. Please enter an answer from A-D only" << endl;
				}
			} while (answer < 65 || answer > 68);
			
			// Storing them into another vector. This is for later grade checking.
			studentAnswers.push_back(answer);
		}

		count = 0;

		// Using subindexing here. This allows me to call both of the same stored values in both of the vectors.
		// evaluate them in the if statement, and increase count if the answer was correct.
		// Using the numQuestions as my evaluation because this should only loop for the number of questions
		// on the test/quiz
		for (int i = 0; i < numQuestions; i++)
		{
			if (studentAnswers[i] == quizAnswers[i])
			{
				count++;
			}
		}

		// Converting the equation into an int. This is to get rid of any unwanted decimal places.
		// The reason I used questions and set it as a double was to allow for the decimal places to be used to get
		// precise grading on tests with large numbers of questions (ex. 98%).
		grade = static_cast<int> ((count / questions) * 100);

		// Telling the user what the student should be graded based on his/her success on the test/quiz.
		cout << *sIter << " scored: " << count << "/" << numQuestions << " correct. " << *sIter << " should receive a " << grade << "% grade." << endl;
		
		// Storing the string into finalScore. This is used to be stored into a vector to later be looped 
		// through at the end of the scoring.
		finalScore = *sIter + " scored: " + to_string(count) + "/" + to_string(numQuestions) + " correct. " + *sIter + " should receive a " + to_string(grade) + "% grade.";

		// Using this to store the students grades.
		finalList.push_back(finalScore);

		// Clearing studentsAnswers to allow it to store the next students answers.
		studentAnswers.clear();

	}

	cout << "\n";

	// Iterating through finalList to display all the students grades, including how many they got correct
	// out of the total number of questions. Gives a grade % as well.
	for (sIter = finalList.begin(); sIter != finalList.end(); ++sIter)
	{
		cout << *sIter << endl;
	}

	// Pausing the system to allow the user time to document the results.
	system("pause");
}

// Will capture an integer, and only an integer.
int GetInt(string message)
{

	int value;
	while (true)
	{
		cout << message;
		cin >> value;
		// I decided to capture the absolute value of the entry here. This is to prevent
		// the user from entering a negative number and causing there to be bugs in the system.
		value = abs(value);

		// Checking to make sure the value is good (int) otherwise telling the user to try again.
		if (cin.good())
		{
			cin.clear();
			// We run another ignore here. This allows us to drop values still stuck in the buffer.
			// Specifically this allowed me to not pass along a 0 when someone entered a float value
			// like (10.0).
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			break;
		}
		else
		{
			// Here we're clearing the input stream
			cin.clear();
			// Here we're telling the stream what values we're ignoring. This is done to prevent users
			// from entering values outside of our numeric limits (Specifically stopping alpha characters).
			cin.ignore(numeric_limits<int>::max(), '\n');
			cout << "Please enter an integer: ";
		}
	}

	return value;
}

// Using GetChar to capture a single letter. Everything about this is the same as
// GetInt except it only accepts character values based on the ascii table.
char GetChar(string message)
{
	char answer;
	while (true)
	{
		cout << message;
		cin >> answer;

		if (cin.good())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			break;
		}
		else
		{
			// Here we're clearing the input stream
			cin.clear();
			// Here we're telling the stream what values we're ignoring. This is done to prevent users
			// from entering values outside of our numeric limits (Specifically stopping alpha characters).
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Please enter a non-numeric character: ";
		}
	}

	return answer;
}