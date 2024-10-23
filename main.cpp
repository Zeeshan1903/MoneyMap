#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
using namespace std;

int totalDebitedAmnt = 0;
int totalCreditedAmnt = 0;
int totalAmnt = 0;
int limit = 150 ; //limit of rs 
vector <string> date;
vector <string> amnt;
vector <string> type;
vector <int> amntInt;

bool startsWith(const string&str, const string& prefix){
    //here prefix.size() is the length to compare
    return str.compare(0,prefix.size(),prefix) == 0;
}

//a fn to find whether a given string contains a particular word or not
bool contains(const std::string& line, const std::string& substring) {
    return line.find(substring) != std::string::npos;
}

string trim(const std::string& str) {
    
    size_t start = str.find_first_not_of(" \t\n\r\f\v");
    
    size_t end = str.find_last_not_of(" \t\n\r\f\v");        


    // If the string is all whitespace, return an empty string
    if (start == std::string::npos || end == std::string::npos) {
        return "";
    }

    // Return the trimmed substring
    return str.substr(start, end - start + 1);
}

void string_int(vector<string> a){
    for(int i = 0; i<a.size(); i++){
        int no = 0;
        int power = 0;
        char zero = '0';
        for(int j = a[i].length(); j>=1; j--){
            if(a[i][j] <= '9' &&  a[i][j] >= '0'){
                int n = a[i][j] - zero;
                
                no+=pow(10,power) * (n);
                power++;
            }

        }
        amntInt.push_back(no);
      
    }
}

void debit(vector<int>a){
    for(int i = 0; i<a.size(); i++){
        if(type[i] == "DEBIT" && a[i] <= limit){
            totalDebitedAmnt += a[i];
        }
    }
    
}
void credit(vector<int>a){
    for(int i = 0; i<a.size(); i++){
        if(type[i] != "DEBIT"){
            totalCreditedAmnt+= a[i];
        }
    }
    
}

int main(){

    
    //Here now first make a program that will write to the file if and only if that line contains the date because the thing is 
    //our line which contains the date contains the price and type also 

    string month ;
    cout << "Enter the month for which you want to see the data "<<endl;
    cin >> month;

    //open a file 
    fstream inputfile;
    inputfile.open("output.txt");

    // fstream outputfile;
    // outputfile.open("cpp_out.txt");

    //check whether the file gets open or not
    if(inputfile.is_open()){
        string line;
        while(getline(inputfile,line)){

            //check if line contains the month or not
            if(startsWith(line,month)){
                // outputfile << line << endl;

                //pushing the type of the trxn
                if(contains(line,"DEBIT")){
                    type.push_back("DEBIT");
                }
                else{
                    type.push_back("CREDIT");
                }

                //fetch amnt here 
                amnt.push_back((line.substr(line.length()-8,8)));

                date.push_back((line.substr(0,13)));
            }
        }
    }
    for(int i = 0; i<amnt.size();i++){
        amnt[i] = trim(amnt[i]);
        type[i] = trim(type[i]);
        amnt[i] = trim(amnt[i]);
    }

    string_int(amnt);
    for(int i =0; i<date.size(); i++){
        amnt[i] = trim(amnt[i]);
        date[i] = trim(date[i]);
        type[i] = trim(type[i]);
        cout << date[i] << "\t" << type[i] <<"\t" << amnt[i] << "\t"<<amntInt[i]<<endl;
    }
    credit(amntInt);
    debit(amntInt);
    cout <<"\nIn "<< month <<" expense under "<<limit<< " is , Debited Amnt:\t"<<totalDebitedAmnt << "\t" << "Credited Amnt:"<<"\t"<<totalCreditedAmnt<<endl;
}