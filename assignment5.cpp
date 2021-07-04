#include <iostream> 
#include <sqlite3.h> 
#include <string> 
#include <stdio.h>
  
using namespace std; 
  
/************************************************************************************************* 	
 The callback() function is invoked for each result row coming out of the evaluated SQL statement
 1st argument - the 4th argument provided by sqlite3_exec() and is typically not used
 2nd argument - number of columns in the result
 3rd argument - an array of strings containing the fields in that row
 4th argument - an array of strings containing the names of the columns
*************************************************************************************************/
static int callback(void* data, int argc, char** argv, char** azColName) 
{ 				
	int i; 
   
    	for (i = 0; i < argc; i++) 
		{ 
        	printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL"); 
    	} 
  
    	printf("\n"); 
    	
		return 0; 
}
class User
{
protected:
    string firstName;
    string lastName;
    string idNumber; //attributes for user class

public:
    virtual void print()
    {
        cout << firstName + lastName << "has ID number " << idNumber << ".\n";  //virtual function to print all info about user
    }
    User(string name1, string name2, string ID) //constructor for base class when user is created
    {
        firstName = name1;
        lastName = name2;
        idNumber = ID;
        sqlite3* DB; 
    }
    ~User() {} // destructor for base class
    
        void setFirst(string f) {firstName = f;}  //set functions
        void setLast(string l) {lastName = l;}
        void setID(string i) {idNumber = i;}
    
        void login()
        {
            
        }
        
        void menu()
        {
            cout << endl;
            selection = 0;
            cout << " Please choose from the following options - \n";
            cout << " 1. Login. \n";
            cout << " 2. Exit.\n""
            cin >> selection;
        
            if (selection == 1)
            {
                  login();
            }
            else if (selection == 2)
            {
                  exit ();
            }
        }
           

    string getFirst() { return firstName; }  //get functions
    string getLast() { return lastName; }
    string getID() { return idNumber; }
};

class Student : public User
{
    protected:

    public:
        Student(string name1, string name2, string ID) :User(name1, name2, ID) {} //constructor for student class
        sqlite3* DB; 
        ~Student(){} //destructor for student class
        
        void searchCourse()
        {
             string StudentSearch = "SELECT * FROM COURSES;"; 
   
             cout << endl << StudentSearch << endl;		//print the                         string to screen

             //you need the callback function this time since there               could be multiple rows in the table
	           sqlite3_exec(DB, StudentSearch.c_str(), callback, NULL, NULL);
        }
        void addDrop()
        {
            cout << "Add Dropping courses.\n"; 
        }
        void printSchedule()
        {
            cout << "Printing Schedule.\n";
        }
};
class Instructor : public User
{
    protected:

    public:
        Instructor(string name1, string name2, string ID) :User(name1, name2, ID) {} //constructor for instructor class
        ~Instructor(){} //destructor for instructor class
        
        void printScheduleInstruct()
        {
            cout << "Printing Schedule.\n";
        }
        void printRoster()
        {
            cout << "Printing Class List.\n";
        }
        void classSearch()
        {
            string InstructorSearch = "SELECT * FROM COURSES;"; 
   
             cout << endl << InstructorSearch << endl;		//print the                         string to screen

             //you need the callback function this time since there               could be multiple rows in the table
	           sqlite3_exec(DB, StudentSearch.c_str(), callback, NULL, NULL);
        }
};        

class Admin : public User
{
    protected:

    public:
        Admin(string name1, string name2, string ID) :User(name1, name2, ID) {} //constructor for admin class
        ~Admin(){} //desctructor for admin class
        
        void addCourse()
        {
            cout << "Adding Course.\n";
        }
        void removeCourse()
        {
           
            cout << "Removing Course.\n";
        }
        void addRemoveUser()
        {
          
            cout << "Adding/Removing user.\n"; 
        }
        void addRemoveStudent()
        {
            cout << "Adding/Removing Student from Course.\n";
        }
        void SearchPrint()
        {
            cout << "Searching and Printing.\n";
        }
};
int main(int argc, char** argv) 
{ 
    sqlite3* DB; 
    	
	/*******************************************************************	
	 Creating a table
	 Create a string then pass the string into the sqlite3_exec function
	********************************************************************/
    string table = "CREATE TABLE COURSES("
                   "CRN INTEGER PRIMARY KEY, "
                   "TITLE TEXT NOT NULL, "
                   "DEPT TEXT NOT NULL, "
                   "TIME TEXT NOT NULL, "
                   "DAYS TEXT NOT NULL, " 
                   "SEMESTER TEXT NOT NULL, "
                   "YEAR INTEGER NOT NULL, " 
                   "CREDITS TEXT NOT NULL); "; 
    	
	int exit = 0;
		
    exit = sqlite3_open("assignment3.db", &DB);			//open the database
		
	char* messageError; 
	
	// execute the create table command
	// sqlite3_exec( pointer to database file, string for sql command, callback function (used to respond to queries, not used here), input to callback, error message address)
    exit = sqlite3_exec(DB, table.c_str(), NULL, 0, &messageError); 
  
   	if (exit != SQLITE_OK) 
	{ 
        std::cerr << "Error Create Table" << std::endl; 
       	sqlite3_free(messageError); 
    } 
    else
        cout << "Table created Successfully" << std::endl; 
        
        /*******************************************************************
	 Inserting values into a table.
	 Create a string then pass the string into the sqlite3_exec function
	********************************************************************/
	// hard-code (push) a few values into the database - NOTE you can create a single string with multiple INSERT commands
	string sql("INSERT INTO COURSES VALUES(32222, 'Computer Networks For Engineers', 'BCOS', '8:00am-9:20am', 'WF', 'Summer', 2021, '4');"
		"INSERT INTO COURSES VALUES(32276, 'Network Theory II', 'BSAS', '5:00pm-6:50pm', 'M', 'Summer', 2021, '4');"
		"INSERT INTO COURSES VALUES(32315, 'Advanced Digital Circuit Design', 'BSEE', '12:30pm-1:50pm', 'WF', 'Summer', 2021, '4');"
		"INSERT INTO COURSES VALUES(32536, 'Applied Programming Concepts', 'BSCO', '8:00am-8:50am', 'M', 'Summer', 2021, '4');"
		"INSERT INTO COURSES VALUES(32726, 'Internet Of Things', 'BSME', '12:00pm-1:50pm', 'M', 'Summer', 2021, '4');"
	);

	// execute the command for inserting courses
	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);

	if (exit != SQLITE_OK) 
	{
		std::cerr << "Error Insert" << std::endl;
		sqlite3_free(messageError);
	}
	else
		std::cout << "Records Created Successfully!" << std::endl;
   
   string test = "SELECT TITLE, TIME, DAYS, SEMESTER, YEAR, CREDITS FROM COURSES;"; 
   
   cout << endl << test << endl;		//print the string to screen

	// you need the callback function this time since there could be multiple rows in the table
	sqlite3_exec(DB, test.c_str(), callback, NULL, NULL);
   
   string query = "SELECT c.CRN, c.TITLE, c.DEPT, i.SURNAME AS 'Professor' FROM COURSES c LEFT JOIN INSTRUCTOR i ON c.DEPT = i.DEPT;";
   
	 cout << endl << query << endl;		//print the string to screen

	// you need the callback function this time since there could be multiple rows in the table
	sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);
 
 // hard-code (push) a few values into the database - NOTE you can create a single string with multiple INSERT commands
	string student("INSERT INTO STUDENT VALUES(10000, 'Hamza', 'Khalid', '2022', 'BSCO', 'khalidh');"
		"INSERT INTO STUDENT VALUES(10011, 'Hiba', 'Shamim', '2021', 'ISOM', 'shamimh');");
		

	// execute the command for inserting new students
	exit = sqlite3_exec(DB, student.c_str(), NULL, 0, &messageError);

	if (exit != SQLITE_OK) 
	{
		std::cerr << "Error Insert" << std::endl;
		sqlite3_free(messageError);
	}
	else
		std::cout << "Records Inserted Successfully!" << std::endl;
   
   string instructor("DELETE FROM INSTRUCTOR WHERE ID = 20004;");
   
   	// execute the command for removing instructors
	exit = sqlite3_exec(DB, instructor.c_str(), NULL, 0, &messageError);

	if (exit != SQLITE_OK) 
	{
		std::cerr << "Error Delete" << std::endl;
		sqlite3_free(messageError);
	}
	else
		std::cout << "Record Deleted Successfully!" << std::endl;


  string admin("UPDATE ADMIN SET TITLE = 'Vice-President' WHERE ID = 30002;");
   
   	// execute the command for updating admins
	exit = sqlite3_exec(DB, admin.c_str(), NULL, 0, &messageError);

	if (exit != SQLITE_OK) 
	{
		std::cerr << "Error Update" << std::endl;
		sqlite3_free(messageError);
	}
	else
		std::cout << "Record Updated Successfully!" << std::endl;
   
   string classes("ALTER TABLE STUDENT ADD CLASS1 INTEGER(5);" "ALTER TABLE STUDENT ADD CLASS2 INTEGER(5);" "ALTER TABLE STUDENT ADD CLASS3 INTEGER(5);" "ALTER TABLE STUDENT ADD CLASS4 INTEGER(5);" "ALTER TABLE STUDENT ADD CLASS5 INTEGER(5);");
   
   	// execute the command for altering Student table to hold class info
	exit = sqlite3_exec(DB, classes.c_str(), NULL, 0, &messageError);

	if (exit != SQLITE_OK) 
	{
		std::cerr << "Error Alter" << std::endl;
		sqlite3_free(messageError);
	}
	else
		std::cout << "Record Altered Successfully!" << std::endl;
   
   sqlite3_close(DB); 
   	return 0; 
}