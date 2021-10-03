
#include <iomanip>
#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <unordered_map>
using namespace std;

//Price of each tickets
const double adultPrice = 10.00;
const double childPrice = 5.00;
const double seniorPrice = 7.50;


//Class for Orders
class Order{
private:
    int adult;
    int child;
    int senior;
    int audNum;
    vector<string> seats;
    
public:
    void printOrder(){
        
        //If there is no orders
        if(seats.size() == 0){
            
            //print out no orders
            cout << "No orders" << endl;
        }
        
        //if there are orders
        else{
            
            //print out auditorium number
            cout << "Auditorium " << audNum;
            
            //for every element in the vector
            for (auto const& seat : seats)
            {
                //print out the element in the vector(seats)
                cout << ", " << seat;
            }
            
            cout << endl; //create another line
            
            //print out the order
            cout << adult << " adult, " << child << " child, " << senior << " senior" << endl;
        }
    }
    Order(){
        adult = 0;
        child = 0;
        senior = 0;
        audNum = 0;
        
    }
    Order(int a, int c, int s, int aNum, vector<string> seat){
        adult = a;
        child = c;
        senior = s;
        audNum = aNum;
        seats = seat;
    }
};


class Customer{
private:
    string username;
    string password;
    vector<Order> orders;
    
public:
    Customer(string u, string p){
        username = u;
        password = p;
    }
    
    Customer(){
        username = "";
        password = "";
    }
    string getUsername(){
        return username;
    }
    string getPassword(){
        return password;
    }
    void addOrder(Order o){
        orders.push_back(o);
    }
};






//This function is to print out the report of auditorium
void report(char auditorium[][26])
{
    /* We will initialize all the values below to zero
     (such as adult and totalSeats) because we have
     not checked the characters in the char array auditorium */

    //initialize sales to 0.0
    double sales = 0.0;
    //initialize number of adult tickets to 0
    int adult = 0;
    //initialize number of child tickets to 0
    int children = 0;
    //initialize number of senior tickets to 0
    int seniors = 0;
    //initialize number of seats to 0
    int totalSeats = 0;
    //initialize number of tickets sold to 0
    int sold = 0;

    //We will check every row of the 2D array
    for(int row=0;row<10;row++)
    {
        //We will check every column of the 2D array
        for(int j=0;j<26;j++)
        {
        //If there is a character in the array that equals A
            if(auditorium[row][j] == 'A')
            {
                //Increase tickets sold by 1
                sold++;
                //Increase total seats by 1
                totalSeats++;
                //Increase number of adult tickets by 1
                adult++;
                //Increase sales by 10.00
                sales+=adultPrice;
            }
            else if(auditorium[row][j] == 'S')
            {
                //Increase tickets sold by 1
                sold++;
                //Increase total seats by 1
                totalSeats++;
                //Increase senior tickets by 1
                seniors++;
                //Increase sales by 7.50
                sales += seniorPrice;
            }
            else if(auditorium[row][j] == 'C')
            {
                //Increase ticket sold by 1
                sold++;
                //Increase total seats by 1
                totalSeats++;
                //Increase children tickets by 1
                children++;
                //Increase sales by 5.00
                sales += childPrice;
            }
            else if(auditorium[row][j] == '.')
            {
                //Increase total seats by 1
                totalSeats++;
            }

            /* If character is a empty character which means
             that it is not part of the auditorium */
            else
            {
                //Break from the inner loop
                break;
            }
        }

        // We will check if it is the end of the auditorium:
        //If row does not equal 9 and if next row is an empty character
        //If both of the above statement is true, then it is the end
        if(row!=9 && auditorium[row+1][0] == ' ')
        {
            //break from the outer loop
            break;
        }
    }
    
        //Printing out the status of the auditorium

        //Print out total seats in the auditorium
        cout << "Open:    " << totalSeats - sold << endl;

        //Print out total tickets sold
        cout << "Total Tickets:  " << sold << endl;

        //print out total adult tickets sold
        cout << "Adult Tickets:  " << adult << endl;

        //print out total child tickets sold
        cout << "Child Tickets:  " << children << endl;

        //print out total senior tickets sold
        cout << "Senior Tickets: " << seniors << endl;

        //Printing out the sales with 2 decimal places only using setprecision(2)
        cout << "Total Sales:    $" << fixed << setprecision(2) << sales << endl;

}






//This function is used to reserve seats in the auditorium
void reserveSeats(char auditorium[][26], int row, int seat, int adultQuan, int seniorQuan, int childQuan)
{
    //We will reserve adult tickets first, followed by children and then senior

    //for each adult tickets
    for(int a=0; a<adultQuan;a++)
    {
        //set a character in the array to A
        auditorium[row][seat+a] = 'A';
    }
    //for each child tickets
    for(int c=0;c<childQuan;c++)
    {
        //set a character in the array to C
        auditorium[row][seat+adultQuan+c] = 'C';
    }
    //for each senior tickets
    for(int s=0;s<seniorQuan;s++)
    {
        //set a character in the array to S
        auditorium[row][seat+adultQuan+childQuan+s] = 'S';
    }

}




//This function is to check if the seats entered are available or not
bool isAvailable(char auditorium[10][26], int row, int seat, int quantity)
{
    //We will check every tickets
    for(int i=0;i<quantity;i++)
    {
        //If the seats are not empty
        if(auditorium[row][seat+i] != '.')
        {
            //return false(not available)
            return false;
        }
        //else if it is a empty character
        else if(auditorium[row][seat+i] == ' ')
        {
            //return false(not available)
            return false;
        }
    }
    //return true(available)
    return true;
}




//This function is to display the current status of auditorium to the user
void displayAuditorium(char auditorium[][26])
{
    //initializing number of columns as zero
    int columns = 0;

    //using a for-loop to determine how many columns are in the theater
    for(int seat=0;seat<26;seat++)
    {
        //If it is not an empty character
        if(auditorium[0][seat] != ' ')
        {
            //Increase number of columns by 1
            columns++;
        }
    }

    //print two spaces so the column letter can line up with its respective columns
    cout << "  ";

    //for each columns in the auditorium
    for(int i=0;i<columns;i++)
    {
        //We will convert the column into alphabets letters
        char column = (char) (65 + i);
        //print out the letter
        cout << column;
    }
    //Create another line
    cout << endl;

    //For every row in the array
    for(int i=0;i<10;i++)
    {
        //print out the row number and a space
        cout << i+1 << " ";

        //for every column in the row
        for(int j=0;j<26;j++)
        {
            //if the character equals period(.)
            if(auditorium[i][j] == '.')
            {
                //prints out perior(.)
                cout<< ".";
            }
            //If it is a empty character
            else if(auditorium[i][j] == ' ')
            {
                //break from the inner loop
                break;
            }
            //if neither of above state are true
            else
            {
                //Print out # to display reserved seats
                cout << "#";
            }
        }
        //create another line
        cout << endl;

        // We will check if it is the end of the auditorium:
        //If row does not equal 9 and if next row is an empty character
        //If both of the above statement is true, then it is the end
        if(i!=9 && auditorium[i+1][0] == ' ')
        {
            //break from the outer loop
            break;
        }
    }
}



void bestAvailable(char auditorium[][26], int &row, int &seats, int quantity)
{
    int columns = 0; //initialize column to zero
    int rows = 0;
    double distance = 0.0; //initialize distance to 0.0
    double shortestDistance = 100000.0; //initialize shortest Distance to 100000.0
    bool empty = true; //initialize empty to true

    //using a for-loop to determine how many columns are in the theater
    for(int seat=0;seat<26;seat++)
    {
        /*some characters in the array might be empty
         and we are going to ignore them because they
         are not part of the auditorium*/

        //If the character is not empty
        if(auditorium[1][seat] != ' ')
        {
            //increase number of columns by 1
            columns++;
        }
    }

    for(int i=0; i<10;i++){
        if(auditorium[i][0] != ' '){
            rows++;
        }
    }
    
    

    //initialize it to -1
    int startSeat = -1;
    int startRow = -1;

    //for each rows in the auditorium
    for(int z=0;z<rows;z++){
    //For each seat in the column
        for(int i=0;i<columns-quantity;i++)
        {
            //initialize empty to true
            empty = true;

            //for every ticket
            for(int j=0;j<quantity;j++)
            {
                //if there is an non-empty seat
                if(auditorium[z][i+j] != '.')
                {
                    //set variable empty to false
                    empty = false;
                    //break from the inner loop
                    break;
                }
            }
            
            //If the seats checked are empty
            if(empty)
            {
                //calculate the distance from center and store in distance variable
                distance = pow(abs(z+1-(rows+1)/2) , 2.0) + pow(abs((i + 1 + (quantity-1)/2.0) - (columns+1)/2.0), 2.0);
                
                //keep the seat that is closest to middle
                if(shortestDistance > distance)
                {
                    //keep the shortest distance
                    shortestDistance = distance;
                    //keep the seat that is closest to the middle
                    startSeat = i;
                    //keep the row that is closest to the middle
                    startRow = z;
                }
                
                //if there is a tie of distance
                else if(shortestDistance == distance && (z) != startRow)
                {
                    //if the current row is closer than middle
                    if(abs(z+1 -(row+1)/2) < abs((startRow+1) - (row+1)/2)){
                        //keep the current row
                        startRow = z;
                        //keep the current seat
                        startSeat = i;
                    }
                    
                    //if the row is tied and current row is smaller than the previous one
                    else if(z<startRow)
                    {
                        //keep the current row
                        startRow = z;
                        
                        //keep the current seat
                        startSeat = i;
                    }
                }
            }
        }
    }
    
    row = startRow+1; //set row to the best available row
    seats = startSeat;  //set seats to the best available seat
    
}



int main() {
    
    //creating three 10x26 arrays to store auditoriums
    char a1[10][26];
    char a2[10][26];
    char a3[10][26];

    //for every row in the arrays
    for(int i=0;i<10;i++)
    {
        //for every column in the array
        for(int j =0;j<26;j++)
        {
            //initialize it as empty character
            a1[i][j] = ' ';
            a2[i][j] = ' ';
            a3[i][j] = ' ';
        }
    }
    
    
    //create 3 files to handle 3 auditoriums
    ifstream file1;
    ifstream file2;
    ifstream file3;
    
    //open up 3 files
    file1.open("A1.txt");
    file2.open("A2.txt");
    file3.open("A3.txt");
    
    
    string rows; //used to store each line of the input
    
    //arrays of 3 elements that stores the number of rows and columns of each auditorium
    int numOfRows[3] = {0,0,0};
    int numOfColumns[3] = {0,0,0};
    

    //convert and store the file to the 10x26 character array
    while(getline(file1, rows) && rows != "")
    {
        numOfColumns[0] = (int)rows.length();
        //for every column in the auditorium
        for(int j=0;j<numOfColumns[0];j++)
        {
            //initializing the first auditorium
            a1[numOfRows[0]][j] = rows[j];
        }
        //Increase numOfRows by 1
        numOfRows[0]++;
    }
    
    
    //convert and store the file to the 10x26 character array
    while(getline(file2, rows) && rows != "")
    {
        numOfColumns[1] = (int)rows.length();
        //for every column in the auditorium
        for(int j=0;j<numOfColumns[1];j++)
        {
            //initializing the 2nd auditorium
            a2[numOfRows[1]][j] = rows[j];
        }
        //Increase numOfRows by 1
        numOfRows[1]++;
    }
    
    
    //convert and store the file to the 10x26 character array
    while(getline(file3, rows) && rows != "")
    {
        numOfColumns[2] = (int)rows.length();
        //for every column in the auditorium
        for(int j=0;j<numOfColumns[2];j++)
        {
            //initializing the 3rd auditorium
            a3[numOfRows[2]][j] = rows[j];
        }
        //Increase numOfRows by 1
        numOfRows[2]++;
    }
    
    
    
    //create and unordered hashmap
    unordered_map<string, Customer> hashT;
    
    //create and open up the file that stores user datas
    ifstream userFile;
    userFile.open("userdb.dat");
    
    string line; //stores each line in the file
    
    //for each line in the file
    while(getline(userFile, line) && line != ""){
        
        //return the index of the space
        int index = (int)line.find(' ');
        
        //return the length of the password
        int rLen = (int)line.length() - index - 1;
        
        //create an customer object
        Customer t(line.substr(0, index), line.substr(index+1, rLen));
        
        //create an pair of username as a key and the customer as the element
        pair<string, Customer> temp (line.substr(0, index), t);
        
        //insert the pair into the tree
        hashT.insert(temp);
        
    }
    
    
    bool on = true;//whether or not the program is still running
    
    bool logout = true; //whether or not the user/admin is logged out
    
    //while the program is still running(admin hasn't exit the program)
    while(on){
        
        //stores username
        string username;
        
        //if it is logged out
        if(logout){
            
        cout << "Enter username: "; //asks the user to enter the username
        
        cin >> username; //get the username
        
            
        bool isAdmin = false; //set isAdmin to false
        bool failed = false; //set failed to false
        bool exist = false; //set exist to false
        
        //for each pair in the hash table
        for (auto& x: hashT){
            
            //if the key is found
            if(x.first == username){
                
                int trys = 3; //initialize tryes to 3
               
                exist = true; //set exist to true
                
                //if it is the admin
                if(username == "admin"){
                    
                    isAdmin = true; //set isAdmin to true
                    
                }
                
                //ask user to enter password
                cout << "Enter password: ";
                string password; //create and password variable
                
                cin >> password; //takes in the input
                
                //while the password does not match
                while(password != x.second.getPassword()){
                    
                    //print out invalid password
                    cout << "Invalid password" << endl;
                    
                    trys--; //decrement trys by 1
                    
                    //if the user entered the password incorrectly 3 times
                    if(trys == 0){
                        
                        //print out returning to main menu
                        cout << "Returning to main menu" << endl << endl;
                        failed = true; //set failed to true
                        
                        //break from loop
                        break;
                    }
                    else{
                        //ask user to re-enter the password
                        cout << "Enter password: ";
                        cin >> password;
                    }
                }
                
                //if the user entered the password wrong 3 times
                if(failed){
                    break; //break from the loop
                }
            }
            
        }
        
        //if the username does not exist
        if(!exist){
            
            continue;//skip the loop
        }
        
        //if the user entered the password wrong 3 times
        if(failed){
            
            continue; //continue(return to starting point)
        }
        
        //store input
        int inputAd;
        
        //if the user is administrator
        if(isAdmin){
            
            //display the menu below
            cout << endl << "1. Print Report" << endl;
            cout << "2. Log Out" << endl;
            cout << "3. Exit" << endl;
            
            cin >> inputAd; //takes in user input
            
            
            //if user chooses to print report
            if(inputAd == 1){
                
                logout = false; //set logout to false
                
                // the user keeps selecting to print report
                while(inputAd == 1){
                    
                    //display the menu options
                    cout << endl << "1. Print Report" << endl;
                    cout << "2. Log Out" << endl;
                    cout << "3. Exit" << endl;
                    
                    cin >> inputAd; //takes in input
                    
                }
                
                logout = true; //set logout to true
                
                //if admin wants to exit the program
                if(inputAd == 3){
                    on = false; //set on to false
                    break; //break from the loop(exit the program)
                }
                
                continue; //skip an iteration of the loop
                
                  
                
                
                
            }
            
            //else if user wants to log out
            else if(inputAd == 2){
                
                logout = true; //set logout to true
                
                continue; //continue(return to starting point)
                
            }
            
            //if admin wants to exit
            else{
                
                on = false; //set on to false
                
                break; //break from the loop(exit the program)
            }
        }
    }
        
        int inputA; //create and variable inputA
        
        
        //display the main menu below
        cout << endl << "1. Reserve Seats" << endl;
        cout << "2. View Order" << endl;
        cout << "3. Update Order" << endl;
        cout << "4. Display Receipt" << endl;
        cout << "5. Log Out" << endl;
        
        
        cin >> inputA; //takes in an input
    
        if(inputA == 1){

            logout = false; //if logout is false

            //prompt user for which auditorium
            cout << "1. Auditorium 1" << endl;
            cout << "2. Auditorium 2" << endl;
            cout << "3. Auditorium 3" << endl;

            //takes in the input
            int inputB;
            cin >> inputB;
            
            //if it is the first auditorium
            if(inputB == 1){
            //display the first auditorium
            displayAuditorium(a1);
            }
            
            //if it is the second auditorium
            else if(inputB == 2){
            //display the second auditorium
            displayAuditorium(a2);
            }
            //if it is the 3rd auditorium
            else{
            //display the 3rd auditorium
            displayAuditorium(a3);
            }


            //creating below variables to store user inputs
            int row = 0;
            char letter = ' ';
            int adultQuan = 0;
            int seniorQuan = 0;
            int childQuan = 0;
            
            
            string input; //used to store user inputs

            //ask for seat location and number of tickets
            cout << "Enter Row: ";

            //get number of rows in the auditorium
            

            //while user is inputting
            while(cin >> input)
            {
                //get the length of the input
                int inputLen = (int)input.length();
                
                //if the length is zero
                if(inputLen ==0)
                {
                    //prompter user to enter valid input
                    cout << "Please enter valid row: ";
                    
                    //continue asking user to input
                    continue;
                }
                
                
                bool isDigit = true; //will be used to check if the input are integer numbers
                
                //stores the length of the input
                int leng = (int)input.length();
                
                //for every character of the input
                for(int i=0;i<leng;i++)
                {
                    //if the character is not a digit
                    if(!isdigit(input[i]))
                    {
                        isDigit = false; //set isDigit to false
                    }
                }
                
                //if the input is not some integer number
                if(!isDigit)
                {
                    //prompt user to re-enter
                    cout << "Please enter valid row: ";
                    
                    //continue asking for inputs
                    continue;
                }
                
                //convert string to integer
                row = stoi(input);

                //if the row number entered is out of bounds
                if(row>numOfRows[inputB -1] || row<1)
                {
                    //prompt user to re-enter
                    cout << "Please enter valid row: ";
                    
                    //continue taking user inputs
                    continue;
                }
                
                //if the input is valid
                else{
                    break; //stop asking for row number
                }
            }



            //Ask user for column letter
            cout << "Enter Column: ";

            //convert letter into a ASCII value and store in variable seat
            int seat = (int)letter;
            
            //getting input for the column
            while(cin >> input)
            {
                letter = input[0]; //get the first character of the input
                
                //if the input is lower case
                if(islower(letter)){
                    //change the input to uppercase
                    letter = (char)toupper(letter);
                    }
                
                seat = (int)letter; //convert the character to integer
                
                //if the character is not an alphabet
                if(!isalpha(letter)){
                    //prompt user to re-enter the seat
                    cout << "Please enter valid seat: ";
                    continue;
                }
                
                //else if the length is 0 or greater than 1
                else if(input.length() == 0 || input.length() > 1){
                    //prompt user to re-enter the seat
                    cout << "Please enter valid seat: ";
                    continue;
                }
                
                //else if the seat is out of bounds
                else if(seat<65 || seat>(64+numOfColumns[inputB-1])){
                    //prompt user to re-enter the seat
                    cout << "Please enter valid seat: ";
                    continue;
                }
                //if the input is valid
                else{
                    break; //break the loop
                }
            }

            //prompt user to enter number of adult tickets
            cout << "Enter adult ticket number: ";
            
            //getting user inputs
            while(cin >> input)
            {
                //get the length of the input
                int inputLen = (int)input.length();
                
                //if the length is zero
                if(inputLen == 0)
                {
                    //prompt user to re-enter
                    cout << "Please enter valid number: ";
                    continue;
                }
                
                //It will be used to check if the input is integer number
                bool isInt = true;
                
                //for every character of the input
                for(int i=0;i<inputLen;i++)
                {
                    //if the character is not an integer number
                    if(!isdigit(input[i]))
                    {
                        isInt = false; //set isInt to false
                    }
                }

                //if the input is not an integer
                if(!isInt)
                {
                    //prompt user to re-enter
                    cout << "Please enter valid number: ";
                    continue;
                }
                
                //set adult ticket quantity to the input
                adultQuan = stoi(input);

                //if the quantity is less than 0
                if(adultQuan<0)
                {
                    //prompt user to re-enter
                    cout << "Please enter valid number: ";
                    continue;
                }

                //if everything is valid
                else{
                    break; //break from the loop
                }
            }

            //prompt user to enter number of child tickets
            cout << "Enter child ticket number: ";
            
            //get user input
            while(cin >> input)
            {
                //get the length of the input
                int inputLen = (int)input.length();
                
                //if the length of the input is zero
                if(inputLen == 0)
                {
                    //prompt the user to re-enter
                    cout << "Please enter valid number: ";
                    continue;
                }

                //this will be used to check if the input is integer
                bool isInt = true;
                
                //for every character in the input
                for(int i=0;i<inputLen;i++)
                {
                    //if it is not an digit
                    if(!isdigit(input[i]))
                    {
                        isInt = false; //set isInt to false
                    }
                }

                //if it is not an integer number
                if(!isInt)
                {
                    //prompt user to re-enter
                    cout << "Please enter valid number: ";
                    continue;
                }
                
                //convert string to int
                childQuan = stoi(input);

                //if the input(childQuan) is less than zero
                if(childQuan<0)
                {
                    //prompt the user to re-enter
                    cout << "Please enter valid number: ";
                    continue;
                }

                //if it is valid
                else{
                    break; //break from the loop
                }
            }

            //ask user to enter number of tickets for seniors
            cout << "Enter senior ticket number: ";
            
            //get user inputs
            while(cin >> input)
            {
                //get the length of the input
                int inputLen = (int)input.length();
                
                //if the length is zero
                if(inputLen == 0)
                {
                    //prompt the user to re-enter
                    cout << "Please enter valid number: ";
                    continue;
                }
                
                //get the length of the input
                int leng = (int)input.length();
                
                //this will be used to determine if the input is an integer number
                bool isInt = true;
                
                //for every character of the input
                for(int i=0;i<leng;i++)
                {
                    //if it is not an digit
                    if(!isdigit(input[i]))
                    {
                        isInt = false; //set isInt to false
                    }
                }

                //if the input is not an integer number
                if(!isInt)
                {
                    //prompt user to re-enter
                    cout << "Please enter valid number: ";
                    continue;
                }

                seniorQuan = stoi(input); //convert string to integer

                //if the number user entered is less than zero
                if(seniorQuan<0)
                {
                    //prompt user to re-enter
                    cout << "Please enter valid number: ";
                    continue;
                }

                //
                else{
                    break; //break from the loop
                }
            }

                    
                    
        //calculate total number of tickets reserved
        int quantity = adultQuan + childQuan + seniorQuan;
        seat -= 65;
            
        //if it is the first auditorium
        if(inputB == 1){
            
            
            //check if the seat the user entered is available
            if(isAvailable(a1, row-1, seat, quantity))
            {
                //reserve seats the user entered
                reserveSeats(a1, row-1, seat, adultQuan, seniorQuan, childQuan);
            }
            else
            {
                    
                    //initialize below two variable to -1 and potentially change them later
                    int bestRow = -1;
                    int bestSeat = -1;
                    
                    //get the best available seats in the auditorium
                    bestAvailable(a1, bestRow, bestSeat, quantity);
                    
                    //if bestRow is -1 (means there is no seats available)
                    if(bestRow == -1){
                        //tell the user that there is no seats available
                        cout << "no seats available" << endl;
                    }
                    
                    //else if there is seats available
                    else{
                        
                        //convert startSeat to character
                        char seatStart = (char)(bestSeat+65);
                        
                        //convert endSeat to character
                        char seatEnd = (char)(seatStart+quantity-1);
                        
                        //display best available seats to the user
                        cout << bestRow << seatStart<< " - " << bestRow << seatEnd << endl;
                        
                        //ask user if they want to reserve it
                        cout << "Y/N:";
                        char reserve = ' '; //stores the user input
                        
                        //get user input
                        while(cin >> input){
                            
                            //get the length of the input
                            int inputLen = (int)input.length();
                            reserve = (char)input[0]; //convert first letter of the input to character
                            
                            //if the length of the input is greater than one or is not an alphabet
                            if(inputLen == 0 || inputLen > 1 || !isalpha(reserve))
                            {
                                //prompt user to re-enter
                                cout << "Please enter valid option: ";
                                continue;
                            }
                            
                            //else if user entered something other than Y or N
                            else if(reserve != 'Y' && reserve != 'N'){
                                
                                //prompt user to re-enter
                                cout << "Please enter valid: ";
                                continue;
                            }
                            
                            //if it is valid
                            else{
                                break; //break from the loop
                            }
                            
                        }
                        
                        //if the user want to reserve the seat
                        if(reserve == 'Y'){
                            
                            //reserve best available seats for the user
                            reserveSeats(a1, bestRow-1, bestSeat, adultQuan, seniorQuan, childQuan);
                        }
                        
                        //else if the user don't want to reserve the best available
                        else{
                            //apologize to the user
                            cout << "I'm sorry that didn't work out." << endl;
                        }
                        
                    }
                
                }
        }

                else if(inputB == 2){
                //check if the seat the user entered is available
                if(isAvailable(a2, row-1, seat, quantity))
                {
                //reserve seats the user entered
                reserveSeats(a2, row-1, seat, adultQuan, seniorQuan, childQuan);
                }
                else{
                    
                    //initialize below two variable to -1 and potentially change them later
                    int bestRow = -1;
                    int bestSeat = -1;
                    
                    //get the best available seats in the auditorium
                    bestAvailable(a2, bestRow, bestSeat, quantity);
                    
                    //if bestRow is -1 (means there is no seats available)
                    if(bestRow == -1){
                        //tell the user that there is no seats available
                        cout << "no seats available" << endl;
                    }
                    
                    //else if there is seats available
                    else{
                        
                        //convert startSeat to character
                        char seatStart = (char)(bestSeat+65);
                        
                        //convert endSeat to character
                        char seatEnd = (char)(seatStart+quantity-1);
                        
                        //display best available seats to the user
                        cout << bestRow << seatStart<< " - " << bestRow << seatEnd << endl;
                        
                        //ask user if they want to reserve it
                        cout << "Y/N:";
                        char reserve = ' '; //stores the user input
                        
                        //get user input
                        while(cin >> input){
                            
                            //get the length of the input
                            int inputLen = (int)input.length();
                            reserve = (char)input[0]; //convert first letter of the input to character
                            
                            //if the length of the input is greater than one or is not an alphabet
                            if(inputLen == 0 || inputLen > 1 || !isalpha(reserve))
                            {
                                //prompt user to re-enter
                                cout << "Please enter valid option: ";
                                continue;
                            }
                            
                            //else if user entered something other than Y or N
                            else if(reserve != 'Y' && reserve != 'N'){
                                
                                //prompt user to re-enter
                                cout << "Please enter valid: ";
                                continue;
                            }
                            
                            //if it is valid
                            else{
                                break; //break from the loop
                            }
                            
                        }
                        
                        //if the user want to reserve the seat
                        if(reserve == 'Y'){
                            
                            //reserve best available seats for the user
                            reserveSeats(a2, bestRow-1, bestSeat, adultQuan, seniorQuan, childQuan);
                            
                            vector<string> o;
                            for(int i=0;i<quantity;i++){
                                string s = to_string(bestRow);
                                char seeat = (char)(bestSeat+65+1);
                                s += seeat;
                                
                                
                                o.push_back(s);
                                
                                
                            }
                            Order ord(adultQuan, childQuan, seniorQuan, 2, o);
                            hashT[username].addOrder(ord);
                        }
                        
                        //else if the user don't want to reserve the best available
                        else{
                            //apologize to the user
                            cout << "I'm sorry that didn't work out." << endl;
                        }
                        
                    }

                }


                }

                else{

                //check if the seat the user entered is available
                if(isAvailable(a3, row-1, seat, quantity))
                {
                //reserve seats the user entered
                reserveSeats(a3, row-1, seat, adultQuan, seniorQuan, childQuan);
                }
                else
                {
                    
                    //initialize below two variable to -1 and potentially change them later
                    int bestRow = -1;
                    int bestSeat = -1;
                    
                    //get the best available seats in the auditorium
                    bestAvailable(a3, bestRow, bestSeat, quantity);
                    
                    //if bestRow is -1 (means there is no seats available)
                    if(bestRow == -1){
                        //tell the user that there is no seats available
                        cout << "no seats available" << endl;
                    }
                    
                    //else if there is seats available
                    else{
                        
                        //convert startSeat to character
                        char seatStart = (char)(bestSeat+65);
                        
                        //convert endSeat to character
                        char seatEnd = (char)(seatStart+quantity-1);
                        
                        //display best available seats to the user
                        cout << bestRow + 1 << seatStart<< " - " << bestRow + 1 << seatEnd << endl;
                        
                        //ask user if they want to reserve it
                        cout << "Y/N:";
                        char reserve = ' '; //stores the user input
                        
                        //get user input
                        while(cin >> input){
                            
                            //get the length of the input
                            int inputLen = (int)input.length();
                            reserve = (char)input[0]; //convert first letter of the input to character
                            
                            //if the length of the input is greater than one or is not an alphabet
                            if(inputLen == 0 || inputLen > 1 || !isalpha(reserve))
                            {
                                //prompt user to re-enter
                                cout << "Please enter valid option: ";
                                continue;
                            }
                            
                            //else if user entered something other than Y or N
                            else if(reserve != 'Y' && reserve != 'N'){
                                
                                //prompt user to re-enter
                                cout << "Please enter valid: ";
                                continue;
                            }
                            
                            //if it is valid
                            else{
                                break; //break from the loop
                            }
                            
                        }
                        
                        //if the user want to reserve the seat
                        if(reserve == 'Y'){
                            
                            //reserve best available seats for the user
                            reserveSeats(a3, bestRow-1, bestSeat, adultQuan, seniorQuan, childQuan);
                        }
                        
                        //else if the user don't want to reserve the best available
                        else{
                            //apologize to the user
                            cout << "I'm sorry that didn't work out." << endl;
                        }
                        
                    }

                }
            }
        }
            
        
        
        else if(inputA == 2){
            
            //cout << endl << "User selected 2" << endl << endl;
            
            logout = false;
            
            //view orders
            
        }
        
        else if(inputA == 3){
            
            //cout << endl << "User selected 3" << endl << endl;
            
            logout = false;
            
            //update order
            
            int inputBA;
            
            //display the options for user
            cout << "1. Add tickets to order" << endl;
            cout << "2. Delete tickets from order" << endl;
            cout << "3. Cancel order" << endl;
            
            cin >> inputBA;
            
                                if(inputBA == 1){
                                    cout << "Auditorium 1, 3J,5S,5T" << endl;
                                    cout << "1 adult, 1 child, 1 senior" << endl;
                                    cout << "Order Total: $22.50" << endl << endl;

                                    cout << "Customer Total: $22.50" << endl;
                                }
            
        }
        
        //if the user wants to see receipt
        else if (inputA == 4){
            
            logout = false; //set logout to false
            
            
            
        }
        
        
        else{
            
            logout = true; //set logout to true 
            
            //Log out
            
        }
        }
    
    
    return 0;
}
