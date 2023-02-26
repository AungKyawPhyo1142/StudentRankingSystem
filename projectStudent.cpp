#include <iostream>
#include <iomanip>
#include <sys/ioctl.h>
#include <unistd.h>
#include <chrono>
#include <fstream>
#include <cmath>
#include <sstream>
#include <thread>

using namespace std;

class Student
{
private:
    // for marks
    string name;
    int myan, eng, math;
    int total;
    float avg;

public:
    string status;

    // inititalized the variables
    Student() : name(""), myan(0), eng(0), math(0), total(0), avg(0.0), status("") {}

    // input data
    void InputDetails()
    {
        cout << "\nEnter Name: ";
        cin>>name;
        cout << "\nEnter Myanmar Marks: ";
        cin >> myan;
        cout << "\nEnter English Marks: ";
        cin >> eng;
        cout << "\nEnter Math Marks: ";
        cin >> math;
    }
    string getName()
    {
        return name;
    }
    int getMyanmarMarks()
    {
        return myan;
    }
    int getEnglishMarks()
    {
        return eng;
    }
    int getMathMarks()
    {
        return math;
    }
    void calTotal()
    {
        total = myan + eng + math;
    }
    int getTotal()
    {
        return total;
    }
    void calAvg()
    {
        avg = (myan + eng + math) / 3;
    }
    float getAvg()
    {
        return avg;
    }
};
/*------------------------------------- Utility Functions -------------------------------------*/

int getTerminalWidth(){
    // Get the width of the terminal
    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    int width = size.ws_col;
    return width;
}

int getTerminalHeight(){
    // Get the height of the terminal
    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    int height = size.ws_row;
    return height;
}

// make the string to reach the mid of the terminal using midX
string addMidToText(string text,int midX){
	return string(midX, ' ') + text;
}

// print the line from start to end of the terminal
void printFullLine(int width){
    for (int i = 0; i < width; i++) {
        cout << "-";
    }
}

// print the text to the center of the terminal (center of both width and height)
void printTextInCenter(string text){	
	int width = getTerminalWidth();
    int height = getTerminalHeight();
    int num_lines = count(text.begin(), text.end(), '\n') + 1;
    int midX = (width-text.length())/2;
    int midY = (height-num_lines)/2;
    for (int i = 0; i < midY; i++)
    {
        cout<<endl;
    }
    for (int i = 0; i < midX; i++)
    {
        cout<<" ";
    }
	cout<<text;
}

// print text to the middle of the terminal (width only)
void printTextInMiddle(string title,string color){

	if(color=="red"){
		color = "\033[1;31m";
	}
	else if(color=="green"){
		color = "\033[1;32m";
	}
	else if(color=="yellow"){
		color = "\033[1;33m";
	}
	else if(color=="blue"){
		color = "\033[1;34m";
	}
	else{
		color = "\033[0m";
	}

    int width = getTerminalWidth();
    printFullLine(width);
    int middle = (width/2) - title.length()/2;
    string paddedText = string(middle, ' ') + title + string(middle, ' ');
    cout<<color<<paddedText<<"\033[0;37m\n";
    printFullLine(width);

}

// get the current date
string getCurrentDate(){

    // Get the current timepoint
    auto now = std::chrono::system_clock::now();

    // Convert the timepoint to a time_t object
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);

    // Convert the time_t object to a tm struct
    std::tm* now_tm = std::localtime(&now_time);

    // Extract the year, month, and day from the tm struct
    int year = now_tm->tm_year + 1900;
    int month = now_tm->tm_mon + 1;
    int day = now_tm->tm_mday;

    string date;

    date = to_string(day) +"/"+to_string(month) +"/"+ to_string(year);

    return date;

}

// print a dotted line at the middle of the terminal (width only)
void printLineInMiddle(){
    string line = "------------------------------------------------------------------------";
    int width = getTerminalWidth();
    int middle = (width-line.length())/2;
    string paddedline = string(middle, ' ') + line + string(middle, ' ');
}

// make the floating point to 2 decimal places
string toTwoDecimal(float x){
    stringstream sstream;
    sstream << fixed << setprecision(2) << x;
    return sstream.str();
}

// get the midX
int getMidX(string text){
	int width = getTerminalWidth();
	return (width - text.length())/2;
}

// get the midY
int getMidY(string text){
	int height = getTerminalHeight();
    int num_lines = count(text.begin(), text.end(), '\n') + 1;
	return (height-num_lines)/2;
}

// convert the string to lower case
string toLowercase(string text){
    for (int i = 0; i < text.length(); i++)
    {
        if(text[i]==' ' || text[i]=='_' || text[i]=='-'){
            continue;
        }
        else{
            text[i] = 'a' + text[i] - 'A';
        }
    }
    return text;
}

void animateText(string text){

    int width = getTerminalWidth();
    int height = getTerminalHeight();

    int num_lines = count(text.begin(), text.end(), '\n') + 1;

    int midX = (width-text.length())/2;
    int midY = (height-num_lines)/2;

    for (int i = 0; i < midY; i++)
    {
        cout<<endl;
    }

    for (int i = 0; i < midX; i++)
    {
        cout<<" ";
    }

    for(char c : text){
        cout<<c<<flush;
        usleep(100000);
    }

    usleep(500000);
    system("clear");
    
}

/*---------------------------------------------------------------------------------------------*/


/*--------------------------- Functions related to Students & Processing ---------------------------*/

Student checkPass(Student student)
{
    if (student.getMyanmarMarks() < 40 || student.getEnglishMarks() < 40 || student.getMathMarks() < 40)
    {
        student.status = "fail";
    }
    else
    {
        if ((student.getMyanmarMarks() >= 80 && student.getMyanmarMarks() <= 100) || (student.getEnglishMarks() >= 80 && student.getEnglishMarks() <= 100) || (student.getMathMarks() >= 80 && student.getMathMarks() <= 100))
        {
            student.status = "dist";
        }
        else
        {
            student.status = "pass";
        }
    }
    return student;
}




Student getPassStudents(Student student)
{
    if (student.status != "fail")
    {
        return student;
    }
}



void printRanks(Student students[], int num)
{

    int rank_count = 0;
    char ch;

    cout << "\n\n\t\t------------------------------------------------------------------------";
    cout << "\n\t\t\t\tStudents Marks Table (Pass & Distinctions)\n";
    cout << "\t\t------------------------------------------------------------------------\n";
    cout << "\t\t\033[1mRank\tName\t\tMyan\tEng\tMath\tTotal\tAvg\tStatus\033[0m\n";
    cout << "\t\t------------------------------------------------------------------------\n";

    for (int i = 0; i < num; i++)
    {
        if (students[i].getName() == "")
        {
            continue;
        }
        else
        {
            cout << "\t\t" << (++rank_count);
            cout << "\t" << students[i].getName();
            cout << "\t\t" << students[i].getMyanmarMarks();
            cout << "\t" << students[i].getEnglishMarks();
            cout << "\t" << students[i].getMathMarks();
            cout << "\t" << students[i].getTotal();
            cout << "\t" << students[i].getAvg();

            if (students[i].status == "pass")
            {
                cout << "\t\033[1;33m" << students[i].status << "\033[0m";
            }
            else
            {
                cout << "\t\033[1;32m" << students[i].status << "\033[0m";
            }
            cout << "\n";
        }
    }
    
    cout << "\t\t------------------------------------------------------------------------\n";


}

void sortPassStudents(Student students[], int num)
{

    for (int i = 0; i < num - 1; i++)
    {
        for (int j = i + 1; j < num; j++)
        {
            if (students[i].getTotal() < students[j].getTotal())
            {
                Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }

    printRanks(students, num);
}

void printFailStudents(Student students[], int num)
{

    cout << "\n\n\n\t\t------------------------------------------------------------------------";
    cout << "\n\t\t\t\t\tStudents Marks Table (Fail)\n";
    cout << "\t\t------------------------------------------------------------------------\n";
    cout << "\t\tName\t\tMyan\tEng\tMath\tTotal\tAvg\tStatus\n";
    cout << "\t\t------------------------------------------------------------------------\n";

    for (int i = 0; i < num; i++)
    {
        if (students[i].getName() == "")
        {
            continue;
        }
        else
        {
            cout << "\t\t" << students[i].getName();
            cout << "\t\t" << students[i].getMyanmarMarks();
            cout << "\t" << students[i].getEnglishMarks();
            cout << "\t" << students[i].getMathMarks();
            cout << "\t" << students[i].getTotal();
            cout << "\t" << students[i].getAvg();
            cout << "\t\033[1;31m" << students[i].status << "\033[0m";
            cout << "\n";
        }
    }
}


string sortStudents(Student students[],int len){
    
    string data;

    for (int i = 0; i < len - 1; i++)
    {
        for (int j = i + 1; j < len; j++)
        {
            if (students[i].getTotal() < students[j].getTotal())
            {
                Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }            
        }
        
    }

    // assign to data
    int rank_count=0;
    for (int i = 0; i < len; i++)
    {
        if (students[i].getName() == "")
        {
            continue;
        }
        else {
            if(students[i].status!="fail"){

                data += to_string((++rank_count))+","+
                        students[i].getName()+","+
                        to_string(students[i].getMyanmarMarks())+","+
                        to_string(students[i].getEnglishMarks())+","+
                        to_string(students[i].getMathMarks())+","+
                        to_string(students[i].getTotal())+","+
                        toTwoDecimal(students[i].getAvg())+","+
                        students[i].status+",\n";
            }
            else {
                
                data += "-,"+
                        students[i].getName()+","+
                        to_string(students[i].getMyanmarMarks())+","+
                        to_string(students[i].getEnglishMarks())+","+
                        to_string(students[i].getMathMarks())+","+
                        to_string(students[i].getTotal())+","+
                        toTwoDecimal(students[i].getAvg())+","+
                        students[i].status+",\n";
            }
        }

    }
    
    return data;
    
}


void saveData(Student passStudents[],int passLength,Student failStudents[],int failLength,string className,string date){

    ofstream outfile;    
    string data;

    for (int i = 0; i < date.length(); i++) {
        if (date[i] == '/') {
        date[i] = '_';
        }
    }

    for (int i = 0; i < className.length(); i++)
    {
        if(className[i]=='-' ){
            className[i] = '_';
        }
    }

    className = toLowercase(className);    

    string fileName = "./save_data/"+className+"_"+date+".csv";

    outfile.open(fileName, std::ios::out | std::ios::trunc);
    
    if(outfile.is_open()){

        // get the field names
        outfile<<"Ranks,Name,Myanmar,English,Math,Total,Avg,Status\n";
        
        data = sortStudents(passStudents,passLength);
        
        data += sortStudents(failStudents,failLength);

        outfile<<data<<"\n";
        outfile.close();

        cout<<"\nAll the data has been saved to \033[0;32m"<<fileName<<"\033[0;37m\n";

    }
    else{
        cout<<"Unable to save this file!";
    }

}

void StudentRankingSystem()
{
    int m;
    string date;
    int num = 0;
    string className;
    char ch;

	int midX;
	int midY;
	string tempText;

	printTextInCenter("Class Name: ");
	cin>>className;

	system("clear");

	printTextInMiddle("SELECT AN OPTION","");
	cout<<"\n\n";

	tempText = "(1) Current Date";
	midX = getMidX(tempText);
	tempText = addMidToText(tempText,midX);
	cout<<setw(midX)<<tempText<<endl<<endl;

	tempText = "(2) Custom Date";
	midX = getMidX(tempText);
	tempText = addMidToText(tempText,midX);
	cout<<setw(midX)<<tempText<<endl<<endl;

	printFullLine(getTerminalWidth());
	cout<<endl;

	tempText = "ENTER AN OPTION: ";
	midX = getMidX(tempText);
	tempText = addMidToText(tempText,midX);
	cout<<tempText;
	cin>>m;

	system("clear");

    if(m==1){
        date = getCurrentDate();
    }
    else{
        cout<<"\nEnter Date in the following format(D/M/Y): ";
        cin>>date;
    }

    cout << "\nHow many student(s)?: ";
    cin >> num;


    Student students[num];

    int pass = 0;
    int fail = 0;

    for (int i = 0; i < num; i++)
    {
        cout << "\nStudent (" << (i + 1) << ")";
        students[i].InputDetails();
        students[i].calTotal();
        students[i].calAvg();
        students[i] = checkPass(students[i]);
        if (students[i].status != "fail")
        {
            pass++;
        }
        else
        {
            fail++;
        }
    }

    system("clear");

    string title =  className+" ("+date+")";

    printTextInMiddle(title,"green");
    cout<<"\n";
    cout << "\nTotal Pass Students: " << pass;
    cout << "\nTotal Failed Students: " << fail;
    cout << "\nTotal Students: " << num;

    Student passStudents[num];
    Student failStudents[num];

    for (int i = 0; i < num; i++)
    {
        if (students[i].status != "fail")
        {
            passStudents[i] = students[i];
        }
    }

    int passLength = sizeof(passStudents) / sizeof(passStudents[0]);
    int failLength = sizeof(failStudents) / sizeof(failStudents[0]);

    for (int i = 0; i < num; i++)
    {
        if (students[i].status == "fail")
        {
            failStudents[i] = students[i];
        }
    }

    if(pass!=0){
        // sorting and Printing out all the Pass & Distinction Students
        sortPassStudents(passStudents, passLength);
    }
    else{
        cout<<"\n\n";
        string text = "\033[0m No students from \033[31m"+className+"\033[0m have pass the exam";
        printTextInMiddle(text,"");
        cout<<"\n";
    }

    if(fail!=0){
        // printing out all the fail students
        printFailStudents(failStudents, failLength);
    }
    else{
        cout<<"\n\n";
        string text = "\033[0m All the students from \033[35m"+className+"\033[0m have pass the exam";
        printTextInMiddle(text,"");
        cout<<"\n";
    }


    // saving data
    cout<<"\nDo you want to save this data as CSV?\n(y/n): ";
    cin>>ch;

    if(ch=='y'){
       saveData(passStudents,passLength,failStudents,failLength,className,date);
    }

}

/*--------------------------------------------------------------------------------------------------*/

int main()
{
    char choice;

    system("clear");

    animateText("Welcome from student ranking system!");

    do
    {
        system("clear");

        StudentRankingSystem();

        cout<<"\n";

        printFullLine(getTerminalWidth());

        cout<<"\nWanna do it again?\n(y/n): ";
        cin>>choice;

    } while (choice=='y');

    system("clear");

    animateText("Thank you & Goodbye...");

    cout<<"\n\n";
    return 0;
}
