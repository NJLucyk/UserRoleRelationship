//Author: Nathan Lucyk
//Date: 10/4/2012
//Version: 1.0
//Overview: Takes in an input file from the command line filled with user
//and role data (1 to 5 and A to E respectively) and runs the data in three
//propositions to check if they're true.
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;
//constants
const int NUM_OF_USERS_AND_ROLES = 5;
//structs for storing the input from the file
//To increase readability there are two different structs.
struct User
{
  bool assignedRoles[NUM_OF_USERS_AND_ROLES];
  int roleCount;
};
struct Role
{
  bool assignedToUser[NUM_OF_USERS_AND_ROLES];
  int userCount;
};
//function prototypes
void propositions(User users[],Role roles[]);

//Handles the checks to make sure the input is valid
//and then calls the propositions function.
int main(int argc, char *argv[])
{
    const int NUM_OF_FILES = 2;
    const int TEXT_FILE_INDEX = 1;
    if(argc != NUM_OF_FILES)
    {//there should only be 2 files, the executable and the input file.
        cout<<"error";
        cin.ignore();
        return 0;
    }
    User users[NUM_OF_USERS_AND_ROLES];
    Role roles[NUM_OF_USERS_AND_ROLES];
    //initialize all the counts of the structs to zero (there is nothing in them yet).
    for(int i=0; i < NUM_OF_USERS_AND_ROLES;i++)
    {
        users[i].roleCount = 0;
        roles[i].userCount = 0;
    }
    //open the file
    ifstream input;
    input.open(argv[TEXT_FILE_INDEX]);
    if(!input)
    {//check if the file is valid
        cout<<"Error opening file."<<endl;
        cin.ignore();
        return -1;//error
    }

    //read the info in the file and put it into the struct arrays.
    int xUser;
    char yRole;
    int roleIndex;
    const int ASCII_A_VALUE = 65;//used to set A = 0, B = 1 ...
    while(input>>xUser>>yRole)
    {
        //file in the format "x y" per line
        roleIndex = ((int)yRole)-ASCII_A_VALUE;
        xUser--;//makes it an index
        if(users[xUser].assignedRoles[roleIndex] != true)
        {
            users[xUser].assignedRoles[roleIndex] = true;
            roles[roleIndex].assignedToUser[xUser] = true;
            users[xUser].roleCount++;
            roles[roleIndex].userCount++;
        }
    }
    propositions(users, roles);
    cout<<endl<<"Press Enter to Exit"<<endl;
    cin.ignore();
    return 0;
}
//Tests the data against the three propositions. Prints the conclusion to the user.
void propositions(User users[],Role roles[])
{
    const int A_ROLE_ASSIGNED = 1;
    const int TWO_USERS_ASSIGNED = 2;
    const int ALL_ROLES_ASSIGNED = 5;
    //The three propositions
    bool atLeastOneRole = true;
    bool twoUsersPerRole = true;
    bool allRolesNotAssignedToOneUser = true;

    for(int i=0;i < NUM_OF_USERS_AND_ROLES;i++)
    {
        if(users[i].roleCount < A_ROLE_ASSIGNED)//if a user doesn't have a role
            atLeastOneRole = false;
        if(roles[i].userCount < TWO_USERS_ASSIGNED)//if a role only has 1 or less user
            twoUsersPerRole = false;
        if(users[i].roleCount >= ALL_ROLES_ASSIGNED)//if a user has all of the roles assigned
            allRolesNotAssignedToOneUser = false;
    }
    //used for all of the output for letting the user know what propositions are true.
    string booleanToString;
    if(atLeastOneRole)
        booleanToString = "True";
    else
        booleanToString = "False";
    cout<<"There is at least one role assigned per user: "<<booleanToString<<endl;
    if(twoUsersPerRole)
        booleanToString = "True";
    else
        booleanToString = "False";
    cout<<"At least two users per role: "<<booleanToString<<endl;
    if(allRolesNotAssignedToOneUser)
        booleanToString = "True";
    else
        booleanToString = "False";
    cout<<"There is not a user with all of the roles assigned: "<<booleanToString<<endl;
}
