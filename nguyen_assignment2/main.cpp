//  Author: Khanh Nguyen
//  Date: 10/06/2022
//

#include <iostream>
#include <vector>
#include <stdio.h>
#include <ctype.h>

using namespace std;

struct Robot{
    string name;
    int x = 0;
    int y = 0;
    char lastCommand = ' ';
    int currentSpeed = 1;
    int distance = 0;
};

//This findRobot function is designed to help
//the user look for a specific robot in the list/array.
int findRobot(Robot* robolist[], string name, int SIZE){
    for(int i = 0; i < SIZE; i++){
        if(robolist[i]->name == name){
            return i;
        }
    }
    return -1;
}

//This moveRobot function is designed to give the user
//the choice to move a robot U,D,L,R.
void moveRobot(Robot* r, char d){

    if(d=='U') {
        r->y+=r->currentSpeed;

    }
    else if(d=='D'){
        r->y-=r->currentSpeed;

    }
    else if(d=='R'){
        r->x+=r->currentSpeed;

    }
    else if(d=='L'){
        r->x-=r->currentSpeed;

    }
    r->distance+=r->currentSpeed;
    
    return;
}

//This gets the user choice from
//the menu function
char getMenuChoice() {
    string d;
    cin >> d;
    if (d.length() > 1){
        return 'k';
    }
    char c = d[0];
    return c;
}

//This menu function is designed to give the user the
//choices of what they would like the program to do.
void menu(){
    cout<<"Please select:\n";
    cout<<" M - Move\n";
    cout<<" D - Distance\n";
    cout<<" Q - quit\n";

    return;
}

Robot** makeRoboList(int numRobos){
    Robot** robolist = new Robot*[numRobos];
    for (int i = 0; i < numRobos; i++){
        robolist[i] = new Robot;
    }
    
    return robolist;
    
}

//The main function is asking for how many robots
//the user wants and the names of the robots.
//It also contains loops that will run through the userChoice
//and output what they would like to do.
int main(){
    int numOfRobo;
    cout <<"Welcome to MultiRobo Guidance." << endl;
    cout << "How many robots would you like to track?: ";
    cin >> numOfRobo;
    /*
    Robot** robolist;
    robolist = (Robot**)malloc(sizeof(Robot*)*numOfRobo);
    for (int i = 0; i < numOfRobo; i++){
        robolist[i] = (Robot*)malloc(sizeof(Robot));
    }
     */
    
    Robot** robolist = makeRoboList(numOfRobo);
    
    for(int i = 0; i < numOfRobo; i++)
    {
        cout << "Please give each robot a name: ";
        cin >> robolist[i]->name;
    }
                                          

    

    menu();
    //Gets the user input on what they want to do M - move, Q - quit, etc.
    char userChoice = getMenuChoice();
    while(userChoice != 'Q' && userChoice != 'q'){
        if(userChoice == 'M' || userChoice == 'm') {
            string userSearch;
            cin >> userSearch;
            int robotFoundAt = findRobot(robolist, userSearch, numOfRobo);
            if(robotFoundAt == -1){
                cout << "Robot not in list." <<endl;
            }
            else{
                char userMoveChoice = getMenuChoice();
                userMoveChoice = toupper(userMoveChoice);
                
                //Depending on the user choice of directions,
                //the while loop adds to the current speed of the robots.
                
            
                if(userMoveChoice != 'U' && userMoveChoice != 'D'
                   && userMoveChoice != 'L' && userMoveChoice != 'R'){
                    cout << "Invalid Direction" << endl;
                    userChoice = getMenuChoice();
                    continue;
                }
                else{
                    if(robolist[robotFoundAt]->lastCommand == userMoveChoice
                        && robolist[robotFoundAt]->currentSpeed <= 4) {
                        robolist[robotFoundAt]->currentSpeed++;
                    }
                    else if(robolist[robotFoundAt]->lastCommand != userMoveChoice) {
                        robolist[robotFoundAt]->lastCommand = userMoveChoice;
                        robolist[robotFoundAt]->currentSpeed = 1;
                    }
                    
                    moveRobot(robolist[robotFoundAt], userMoveChoice);
                    //userMoveChoice = getMenuChoice();
                    //userMoveChoice = toupper(userMoveChoice);
                }
              
                //prints out the current position of the robot.
                cout << robolist[robotFoundAt]->name <<" position is "
                <<robolist[robotFoundAt]->x<<", "<< robolist[robotFoundAt]->y <<endl;
            }
        }
        //gives the final distance of a specific robot.
        else if(userChoice == 'D' || userChoice == 'd') {
            for (int i = (numOfRobo - 1); i >= 0; i--){
                cout << robolist[i]->name << "\t" << robolist[i]->distance << "\n" << endl;
            }
        }
        else{
            cout << "Invalid Choice" << endl;
        }
        userChoice = getMenuChoice();
    }
    cout << "Goodbye!"<<endl;
    delete robolist;
    
    return 0;
}
