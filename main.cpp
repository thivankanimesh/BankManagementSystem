#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <stdlib.h>
#include <cstdio>

using namespace std;

class Log{

    private :
        string logName;
        string description;
        string date;
        string dir;

    public :
        void createLog(string logName, string description, string dir){

            this->logName=logName;
            this->description=description;
            this->dir=dir;

            this->date=getCurrentDate();

            ofstream file;
            file.open(this->dir,ios::app);
            file << logName << "," << description << "," << date << endl;
            file.close();

        }

    private :
        string getCurrentDate(){

                time_t rawtime;
                struct tm * timeinfo;
                char buffer[80];

                time (&rawtime);
                timeinfo = localtime(&rawtime);

                strftime(buffer,sizeof(buffer),"%d-%m-%Y %H:%M:%S",timeinfo);
                string str(buffer);

                return str;

        }
};

class Account{

    protected :
        int accountNo;
        float balance=0;
        string createdDate;
        const char* ACCOUNT_FILE = "accounts.csv";
        const char* TEMP_ACCOUNT_FILE = "temp_accounts.csv";
        const char* LOG_FILE="logs.csv";

    public :

        void openAccount(){

            string fname;
            string lname;
            int age;
            string address;
            string NIC;

            system("cls");

                do{
                    cout << "Enter First Name :";
                    cin >> fname;
                    cin.clear();
                    cin.ignore();

                    bool contains_non_alpha = fname.find_first_not_of("qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM") != std::string::npos;

                    if(contains_non_alpha==true){
                        cout << "Please enter characters only" << endl;
                        fname.erase();
                    }
                }while(fname.empty());

               do{
                    cout << "Enter Last Name :";
                    cin >> lname;
                    cin.clear();
                    cin.ignore();

                    bool contains_non_alpha = lname.find_first_not_of("qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM") != std::string::npos;

                    if(contains_non_alpha==true){
                        cout << "Please enter characters only" << endl;
                        lname.erase();
                    }
               }while(lname.empty());

                do{
                    cout << "Enter Age :";
                    cin >> age;
                    cin.clear();
                    cin.ignore();
                    if(age==NULL){
                        cout << "Please enter integers only" << endl;
                        age=NULL;
                    }else if(age<=0||age>=120){
                        cout << "Age need to be between 0 - 120" << endl;
                        age=NULL;
                    }
                }while(age==NULL);

                do{
                    cout << "Enter Address :";
                    getline(cin,address,'\n');

                    bool contains_non_expected_values = address.find_first_not_of("qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM1234567890-/ ") != std::string::npos;

                    if(contains_non_expected_values==true){
                        cout << "You cannot use ,(comma) or any other symbols but instead of you can use dash(-) and slash(/)" << endl;
                        address.erase();
                    }

                }while(address.empty());

                do{
                    cout << "Enter NIC :";
                    cin >> NIC;
                    cin.clear();
                    cin.ignore();

                    bool contains_non_expected_values = NIC.find_first_not_of("1234567890v") != std::string::npos;

                    if(contains_non_expected_values==true){
                        cout << "Please use 1,2,3,4,5,6,7,8,9,0,v only" << endl;
                        NIC.erase();
                    }

                }while(NIC.empty());

                do{
                    
                    cout << "Enter Initial Deposite :";
                    cin >> this->balance;
                    cin.clear();
                    cin.ignore();

                    if(balance==0||balance<0){
                        cout << "Initial balance cannot be 0 or minu" << endl;
                        balance=NULL;
                    }

                }while(balance==NULL);    

                // Generating account number
                this->accountNo=generateNewAccountNumber();

                // Getting current date and time
                this->createdDate=getCurrentDate();

                ofstream oAccountFile;
                oAccountFile.open(ACCOUNT_FILE,ios::app);
                oAccountFile << accountNo <<","<<fname<<","<<lname<<","<<age<<","<<address<<","<<NIC<< "," << balance << "," << createdDate <<endl;
                oAccountFile.close();

                // Making a log
                Log log;
                log.createLog("Success",""+to_string(accountNo)+" account created",LOG_FILE);

                // Success message
                system("cls");
                cout << "Account creation successful" << endl;

                // press button to continue
                system("pause");
                system("cls");

        };
        void modifyAccount(){

            string accountDetails[8];
            string line;
            string search;
            string temp;

            do{
                system("cls");
                cout << "Enter Account Number :";
                cin >> search;
                cin.clear();
                cin.ignore();

                bool contains_non_integer = search.find_first_not_of("1234567890") != std::string::npos;

                if(contains_non_integer){
                    cout << "Please enter integers only" << endl;
                    search=" ";
                    system("pause");
                }else if(search.length()<5){
                    cout << "Account number need to be 5 digits long" << endl;
                    search=" ";
                    system("pause");
                }
            }while(search==" ");


            ifstream iAccountsFile1;
            iAccountsFile1.open(ACCOUNT_FILE);

            // search the line upto specific line
            while(getline(iAccountsFile1,temp,'\n')){

                string::size_type pos=temp.find(search);

                if(pos!=string::npos){
                    line=temp;
                    break;
                }
            }

            iAccountsFile1.close();

            // make 'line' as a stream
            int i=0;
            stringstream accountDetailsStream(line);
            while(accountDetailsStream.good()){
                getline(accountDetailsStream,accountDetails[i],',');
                i++;
            }

            system("cls");
            cout << "---------------------Current Details-----------------" << endl << endl;

            cout << "Account Number :"<< accountDetails[0] << endl << endl;
            cout << "1 - First Name :" << accountDetails[1] << endl;
            cout << "2 - Last Name :" << accountDetails[2] << endl;
            cout << "3 - Age :" << accountDetails[3] << endl;
            cout << "4 - Address :" << accountDetails[4] << endl;
            cout << "5 - NIC :" << accountDetails[5] << endl << endl;

            bool needToEditAgain=true;
            int op;

            while (needToEditAgain)
            {
                do{
                    cout << "Press number to change :" ;
                    cin >> op;
                    cin.clear();
                    cin.ignore();
                    if(op<0||op>5||op==NULL){
                        cout << "Wrong Input" << endl;
                    }
                }while(op==NULL);

                string userInput;
                switch(op){
                    case 1:

                        do{
                            cout << "Enter new first name :";
                            cin >> userInput;
                            cin.clear();
                            cin.ignore();

                            bool contains_non_alpha = userInput.find_first_not_of("qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM") != std::string::npos;

                            if(contains_non_alpha==true){
                                cout << "Please enter characters only"<<endl;
                                userInput=" ";
                            }
                            accountDetails[1]=userInput;

                        }while(userInput==" ");
                        break;
                    case 2:

                        do{
                            cout << "Enter new last name :";
                            cin >> userInput;
                            cin.clear();
                            cin.ignore();

                            bool contains_non_alpha = userInput.find_first_not_of("qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM") != std::string::npos;

                             if(contains_non_alpha==true){
                                cout << "Please enter characters only"<<endl;
                                userInput=" ";
                            }
                            accountDetails[2]=userInput;
                        }while(userInput==" ");
                        break;
                    case 3:

                        do{
                            cout << "Enter new age :";
                            cin >> userInput;
                            cin.clear();
                            cin.ignore();

                            bool contains_non_integer = userInput.find_first_not_of("1234567890") != std::string::npos;

                            if(contains_non_integer==true){
                                cout << "Please enter digits only" << endl;
                                userInput=" ";
                            }
                            accountDetails[3]=userInput;
                        }while(userInput==" ");
                        break;
                    case 4:

                        do{
                            cout << "Enter new address :";
                            getline(cin,userInput,'\n');
                           
                            bool contains_non_expected_values = userInput.find_first_not_of("qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM1234567890-/ ") != std::string::npos;

                            if(contains_non_expected_values==true){
                                cout << "You cannot use , or any other symbols but you can use dash(-) and slash(/)" << endl;
                                userInput.clear();
                            }else{
                                 accountDetails[4]=userInput;
                            }

                        }while(userInput.empty());
                        break;
                    case 5:
                        do{
                            cout << "Enter new NIC :";
                            cin >> userInput;
                            cout << userInput << endl;
                            cin.clear();
                            cin.ignore();
                            accountDetails[5]=userInput;
                        }while(userInput==" ");
                        break;
                    default :
                        cout << "Wrong input"<<endl;
                }

                system("cls");
                cout << "---------------------Editted Details-----------------" << endl << endl;

                cout << "Account Number :"<< accountDetails[0] << endl << endl;
                cout << "1 - First Name :" << accountDetails[1] << endl;
                cout << "2 - Last Name :" << accountDetails[2] << endl;
                cout << "3 - Age :" << accountDetails[3] << endl;
                cout << "4 - Address :" << accountDetails[4] << endl;
                cout << "5 - NIC :" << accountDetails[5] << endl << endl;

                char edit;

                do{
                     cout << "Do you need to edit more : (y/n) :";
                     cin >> edit;

                      if(edit=='y'||edit=='Y'){
                         needToEditAgain=true;
                        }else if(edit=='n'||edit=='N'){
                            needToEditAgain=false;
                        }else{
                            cout << "Wrong input" << endl;
                            edit=' ';
                        }
                     cin.clear();
                     cin.ignore();
                }while(edit==' ');

            }

             // Create a new file without that specific line
            ofstream newFile;
            ifstream iAccountsFile2;
            iAccountsFile2.open(ACCOUNT_FILE);
            newFile.open(TEMP_ACCOUNT_FILE,ios::app);

            while (getline(iAccountsFile2,temp,'\n'))
            {
                if(temp!=line){
                     newFile<<temp<<endl;
                }
            }

            newFile.close();
            iAccountsFile2.close();

            // This is the modified line
            line = accountDetails[0]+","+accountDetails[1]+","+accountDetails[2]+","+accountDetails[3]+","+accountDetails[4]+","+accountDetails[5]+","+accountDetails[6]+","+accountDetails[7];

            // append eddited line to new file
            ofstream oAccountFile;
            oAccountFile.open(TEMP_ACCOUNT_FILE,ios::app);
            oAccountFile << line << endl;
            oAccountFile.close();

            // remove existing file
            remove(ACCOUNT_FILE);

            // rename file
            rename(TEMP_ACCOUNT_FILE,ACCOUNT_FILE);

            // Making a log
            Log log;
            log.createLog("Success","Account "+search+" modified",LOG_FILE);

            // Success message
            system("cls");
            cout << "Account successfully modified" << endl;

            // press button to continue
            system("pause");
            system("cls");

        }
        void closeAccount(){

            string accountDetails[8];
            string line;
            string search;
            string temp;

            do{
                system("cls");
                cout << "Enter Account Number :";
                cin >> search;
                cin.clear();
                cin.ignore();

                bool contains_non_alpha = search.find_first_not_of("1234567890") != std::string::npos;

                if(contains_non_alpha){
                    cout << "Please enter digis only" << endl;
                    search=" ";
                }else if(search.length()<5){
                    cout << "Account number need to be 5 digits long" << endl;
                    search=" ";
                    system("pause");
                }
            }while(search==" ");

            ifstream iAccountsFile1;
            iAccountsFile1.open(ACCOUNT_FILE);

            // search the line upto specific line
            while(getline(iAccountsFile1,temp,'\n')){

                string::size_type pos=temp.find(search);

                if(pos!=string::npos){
                    line=temp;
                    break;
                }
            }

            iAccountsFile1.close();

            // make 'line' as a stream
            int i=0;
            stringstream accountDetailsStream(line);
            while(getline(accountDetailsStream,accountDetails[i],',')){
                i++;
            }

            // Create a new file without that specific line
            ofstream newFile;
            ifstream iAccountsFile2;
            iAccountsFile2.open(ACCOUNT_FILE);
            newFile.open(TEMP_ACCOUNT_FILE,ios::app);

            while (getline(iAccountsFile2,temp,'\n'))
            {

                if(temp!=line){
                     newFile<<temp<<endl;
                }
            }

            iAccountsFile2.close();
            newFile.close();

            // remove existing file
            remove(ACCOUNT_FILE);

            // rename file
            rename(TEMP_ACCOUNT_FILE,ACCOUNT_FILE);

            // Making a log
            Log log;
            log.createLog("Success","Account "+search+" closed",LOG_FILE);

            // Success message
            system("cls");
            cout << "Account successfully deleted" << endl;

            // press button to continue
            system("pause");
            system("cls");
        }
        void listAllAccounts(){
            system("cls");
            string line;
            ifstream file;
            string accountDetails[8];

            file.open(ACCOUNT_FILE);

             cout << "Account Num" << "\t\t" << "Name" << "\t\t" << "Age" << "\t\t" << "Address" << "\t\t" << "NIC" << "\t\t" << "Balance" << "\t\t" << "Created Date" << endl << endl;

            while(getline(file,line,'\n')){
                stringstream ss(line);
               // cout << line << endl;

                int i=0;
                while(getline(ss,accountDetails[i],',')){
                      i++;
                }
               
                cout << accountDetails[0] << "\t" << accountDetails[1] << " " <<accountDetails[2] << "\t\t" << accountDetails[3] <<"\t\t" <<accountDetails[4] << "\t\t" <<accountDetails[5] << "\t\t" << accountDetails[6] <<"\t\t" << accountDetails[7] << endl;
            }
            file.close();
            // press button to continue
            system("pause");
            system("cls");
        }

        void virtual deposite(){

            float ammount;

            string accountDetails[8];
            string line;
            string search;
            string temp;

            do{
                cout << "Enter Account Number :";
                cin >> search;
                cin.clear();
                cin.ignore();

                bool contains_non_integer = search.find_first_not_of("1234567890") != std::string::npos;

                if(contains_non_integer){
                    cout << "Please enter digis only" << endl;
                    search=" ";
                }else if(search.length()<5){
                    cout << "Account number need to be 5 digits long" << endl;
                    search=" ";
                    system("pause");
                }
            }while(search==" ");

            ifstream iAccountsFile1;
            iAccountsFile1.open(ACCOUNT_FILE);

            // search the line upto specific line
            while(getline(iAccountsFile1,temp,'\n')){

                string::size_type pos=temp.find(search);

                if(pos!=string::npos){
                    line=temp;
                    break;
                }
            }

            iAccountsFile1.close();

            // make 'line' as a stream
            int i=0;
            stringstream accountDetailsStream(line);
            while(getline(accountDetailsStream,accountDetails[i],',')){
                i++;
            }

            // Create a new file and write lines without that specific line
            ofstream newFile;
            ifstream iAccountsFile2;
            iAccountsFile2.open(ACCOUNT_FILE);
            newFile.open(TEMP_ACCOUNT_FILE,ios::app);

            while (getline(iAccountsFile2,temp,'\n'))
            {

                if(temp!=line){
                     newFile<<temp<<endl;
                }
            }

            iAccountsFile2.close();
            newFile.close();

            // get input from user

             do{
                cout << "Enter ammount :";
                cin >> ammount;
                cin.clear();
                cin.ignore();

                if(ammount==NULL){
                    cout << "Please enter integers only" << endl;
                }

            }while(ammount==NULL);

            // modify the array index [6]
            accountDetails[6] = to_string(std::stof(accountDetails[6])+ammount);

            //modified line
            line = accountDetails[0]+","+accountDetails[1]+","+accountDetails[2]+","+accountDetails[3]+","+accountDetails[4]+","+accountDetails[5]+","+accountDetails[6]+","+accountDetails[7];

            // append new line to the file
            ofstream oAccountFile;
            oAccountFile.open(TEMP_ACCOUNT_FILE,ios::app);
            oAccountFile << line << endl;
            oAccountFile.close();

            // remove existing file
            remove(ACCOUNT_FILE);

            // rename file
            rename(TEMP_ACCOUNT_FILE,ACCOUNT_FILE);


            // Success message
            system("cls");
            cout << "Your diposite successful" << endl;

            // press button to continue
            system("pause");
            system("cls");

        }
        void withdraw(){

            float ammount;

            string accountDetails[8];
            string line;
            string search;
            string temp;

             do{
                cout << "Enter Account Number :";
                cin >> search;
                cin.clear();
                cin.ignore();

                bool contains_non_integer = search.find_first_not_of("1234567890") != std::string::npos;

                if(contains_non_integer){
                    cout << "Please enter digis only" << endl;
                    search=" ";
                }else if(search.length()<5){
                    cout << "Account number need to be 5 digits long" << endl;
                    search=" ";
                    system("pause");
                }
            }while(search==" ");

            ifstream iAccountsFile1;
            iAccountsFile1.open(ACCOUNT_FILE);

            // search the line upto specific line
            while(getline(iAccountsFile1,temp,'\n')){

                string::size_type pos=temp.find(search);

                if(pos!=string::npos){
                    line=temp;
                    break;
                }
            }

            iAccountsFile1.close();

            // make 'line' as a stream
            int i=0;
            stringstream accountDetailsStream(line);
            while(getline(accountDetailsStream,accountDetails[i],',')){
                i++;
            }

            // get input from user
            do{
                cout << "Enter Ammount ";
                cin >> ammount;
                cin.clear();
                cin.ignore();

                if(ammount==NULL){
                    cout << "Please enter integers only" << endl;
                }

            }while(ammount==NULL);


            // checking balance
            if(ammount<=std::stof(accountDetails[6])){

                // Create a new file and write lines without that specific line
                ofstream newFile;
                ifstream iAccountsFile2;
                iAccountsFile2.open(ACCOUNT_FILE);
                newFile.open(TEMP_ACCOUNT_FILE,ios::app);

                while (getline(iAccountsFile2,temp,'\n'))
                {

                    if(temp!=line){
                        newFile<<temp<<endl;
                    }
                }

                iAccountsFile2.close();
                newFile.close();

                 // modify the array index [6]
                accountDetails[6] = to_string(std::stof(accountDetails[6])-ammount);

                //modified line
                line = accountDetails[0]+","+accountDetails[1]+","+accountDetails[2]+","+accountDetails[3]+","+accountDetails[4]+","+accountDetails[5]+","+accountDetails[6]+","+accountDetails[7];

                // append new line to the file
                ofstream oAccountFile;
                oAccountFile.open(TEMP_ACCOUNT_FILE,ios::app);
                oAccountFile << line << endl;
                oAccountFile.close();

                // remove existing file
                remove(ACCOUNT_FILE);

                // rename file
                rename(TEMP_ACCOUNT_FILE,ACCOUNT_FILE);

                // Success message
                system("cls");
                cout << "Your withdrawal successful" << endl;

                // press button to continue
                system("pause");
                system("cls");

            }else{
                system("cls");
                cout << "Insufficient Balance" << endl;
                // press button to continue
                system("pause");
                system("cls");
            }

        }
        void checkBalance(){

            system("cls");
            string accountDetails[8];
            string line;
            string search;
            string temp;

             do{
                cout << "Enter Account Number :";
                cin >> search;
                cin.clear();
                cin.ignore();

                bool contains_non_integer = search.find_first_not_of("1234567890") != std::string::npos;

                if(contains_non_integer){
                    cout << "Please enter integers only" << endl;
                    search=" ";
                }else if(search.length()<5){
                    cout << "Account number need to be 5 digits long" << endl;
                    search=" ";
                    system("pause");
                }
            }while(search==" ");

            ifstream iAccountsFile1;
            iAccountsFile1.open(ACCOUNT_FILE);

            // search the line upto specific line
            while(getline(iAccountsFile1,temp,'\n')){

                string::size_type pos=temp.find(search);

                if(pos!=string::npos){
                    line=temp;
                    break;
                }
            }

            iAccountsFile1.close();

            // make 'line' as a stream
            int i=0;
            stringstream accountDetailsStream(line);
            while(getline(accountDetailsStream,accountDetails[i],',')){
                i++;
            }
            system("cls");
            cout << "Account balance : "+accountDetails[6] << endl;
            // press button to continue
            system("pause");
            system("cls");
        }

    protected :
        string getCurrentDate(){

                time_t rawtime;
                struct tm * timeinfo;
                char buffer[80];

                time (&rawtime);
                timeinfo = localtime(&rawtime);

                strftime(buffer,sizeof(buffer),"%d-%m-%Y %H:%M:%S",timeinfo);
                string str(buffer);

                return str;
        }

        int generateNewAccountNumber(){

            int preNum;
            int newNum;
            const char* LATEST_ACCOUNT_NUMBER_FILE="latestAccountNumber.txt";

            ifstream ifile;
            ifile.open(LATEST_ACCOUNT_NUMBER_FILE);
            ifile>>preNum;

            ofstream ofile;
            ofile.open(LATEST_ACCOUNT_NUMBER_FILE);

            newNum =preNum +1;
            ofile << newNum;

            return newNum;

            ifile.close();
            ofile.close();
        }
};

class SavingsAccount : public Account{

};

class CheckingAccount : public Account{
    private :
        int checkNo;
        float ammount;

    public:
        void deposite() override {
  
            string accountDetails[8];
            string line;
            string search;
            string temp;

            do{
                cout << "Enter Account Number :";
                cin >> search;
                cin.clear();
                cin.ignore();

                bool contains_non_integer = search.find_first_not_of("1234567890") != std::string::npos;

                if(contains_non_integer){
                    cout << "Please enter digis only" << endl;
                    search=" ";
                }else if(search.length()<5){
                    cout << "Account number need to be 5 digits long" << endl;
                    search=" ";
                    system("pause");
                }
            }while(search==" ");

            ifstream iAccountsFile1;
            iAccountsFile1.open(ACCOUNT_FILE);

            // search the line upto specific line
            while(getline(iAccountsFile1,temp,'\n')){

                string::size_type pos=temp.find(search);

                if(pos!=string::npos){
                    line=temp;
                    break;
                }
            }

            iAccountsFile1.close();

            // make 'line' as a stream
            int i=0;
            stringstream accountDetailsStream(line);
            while(getline(accountDetailsStream,accountDetails[i],',')){
                i++;
            }

            // Create a new file and write lines without that specific line
            ofstream newFile;
            ifstream iAccountsFile2;
            iAccountsFile2.open(ACCOUNT_FILE);
            newFile.open(TEMP_ACCOUNT_FILE,ios::app);

            while (getline(iAccountsFile2,temp,'\n'))
            {

                if(temp!=line){
                     newFile<<temp<<endl;
                }
            }

            iAccountsFile2.close();
            newFile.close();

            // get input from user

            do{
                cout << "Please enter cheque number :" ;
                cin >> checkNo;
                cin.clear();
                cin.ignore();

                if(checkNo==NULL){
                    cout << "Please enter integers only" << endl;
                }

            }while(checkNo==NULL);

             do{
                cout << "Enter cheque ammount :";
                cin >> ammount;
                cin.clear();
                cin.ignore();

                if(ammount==NULL){
                    cout << "Please enter integers only" << endl;
                }

            }while(ammount==NULL);

            // modify the array index [6]
            accountDetails[6] = to_string(std::stof(accountDetails[6])+ammount);

            //modified line
            line = accountDetails[0]+","+accountDetails[1]+","+accountDetails[2]+","+accountDetails[3]+","+accountDetails[4]+","+accountDetails[5]+","+accountDetails[6]+","+accountDetails[7];

            // append new line to the file
            ofstream oAccountFile;
            oAccountFile.open(TEMP_ACCOUNT_FILE,ios::app);
            oAccountFile << line << endl;
            oAccountFile.close();

            // remove existing file
            remove(ACCOUNT_FILE);

            // rename file
            rename(TEMP_ACCOUNT_FILE,ACCOUNT_FILE);


            // Success message
            system("cls");
            cout << "Your cheque diposite successful" << endl;

            // press button to continue
            system("pause");
            system("cls");
        }    
};

class System{

    private :
       SavingsAccount sAcc;
       CheckingAccount cAcc;
       int op;

    public :

        void start(){

            while(op!=8){
                cout << "1 - Open An Account" << endl;
                cout << "2 - Modify An Account" << endl;
                cout << "3 - List All Accounts" << endl;
                cout << "4 - Close An Account" <<endl;
                cout << "5 - Deposit" <<endl;
                cout << "6 - Withdraw" <<endl;
                cout << "7 - Check Balance" << endl;
                cout << "8 - Exit" << endl;

                do{
                cout << "Enter Operation :";
                cin >> op;
                cin.clear();
                cin.ignore();

                if(op==NULL){
                    cout << "Please enter integers only" << endl;
                }

            }while(op==NULL);

                switch (op)
                {
                case 1:
                    sAcc.openAccount();
                    break;

                case 2:
                    sAcc.modifyAccount();
                    break;

                case 3:
                    sAcc.listAllAccounts();
                    break;

                case 4:
                    sAcc.closeAccount();
                    break;

                case 5:
                    int option;
                    option=NULL;
                    while(option==NULL){
                        system("cls");
                        cout << "1 - Savings Account" << endl;
                        cout << "2 - Checking Account" << endl << endl;
                        do{
                            cout << "Enter account type :";
                            cin >> option;
                            cin.clear();
                            cin.ignore();

                            if(option==NULL){
                                cout << "Please enter integers only" << endl;
                            }
                        }while(option==NULL);

                        switch(option){
                            case 1 :
                                sAcc.deposite();
                                break;
                            case 2 :
                                cAcc.deposite();
                                break;
                            default :
                                option=NULL;
                                system("cls");
                                cout << "Wrong input" << endl;    
                                system("pause");
                                break;    
                        }
                    }
                    break;

                case 6:
                    sAcc.withdraw();
                    break;

                case 7:
                    sAcc.checkBalance();
                    break;

                case 8:
                    cout << "Please Double enter to close"<<endl;
                    std::cin.get();
                    break;

                default:
                    cout << "Wrong Operation"<<endl;
                    break;
                }

            }

        }
};

int main(){

    System sys;

    sys.start();

    return 0;

}
