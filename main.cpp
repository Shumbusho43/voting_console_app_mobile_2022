#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;
// saving user functioin.
string saveUser()
{
    string fname, lname, address, email, phone, nationalId, password, role, names, data;
    ofstream myFile;
    int roleCommand;
    cout << "Enter your first name" << endl;
    getline(cin, fname);
    cout << "Enter your last name" << endl;
    getline(cin, lname);
    cout << "Enter your address" << endl;
    getline(cin, address);
    cout << "Enter your email" << endl;
    getline(cin, email);
    cout << "Enter your phone" << endl;
    getline(cin, phone);
    cout << "Enter your nationalId" << endl;
    getline(cin, nationalId);
    cout << "Enter password" << endl;
    getline(cin, password);
    cout << "choose role" << endl;
    cout << "press 1 for admin or 2 for voter" << endl;
    cin >> roleCommand;
    if (roleCommand == 1)
    {
        role = "admin";
    }
    if (roleCommand == 0)
    {
        role = "voter";
    };

    names = fname + lname;
    // opening file in append mode
    myFile.open("users.txt", ios::app);
    if (!myFile)
    {
        cout << "Unable to open the file" << endl;
    }
    else
    {
        // saving user
        data = names + " " + address + " " + email + " " + phone + " " + nationalId + " " + password + " " + role;
        myFile << data << endl;
        cout << "user saved successfully" << endl;
    }
}
// stringer func
string subStringer(const string &str, char delimiter, int position)
{
    vector<string> tokens;
    int start = 0;
    int end = str.find(delimiter);
    while (end != string::npos)
    {
        tokens.push_back(str.substr(start, end - start));
        start = end + 1;
        end = str.find(delimiter, start);
    }
    tokens.push_back(str.substr(start));
    if (position >= 0 && position < tokens.size())
    {
        return tokens[position];
    }
    else
    {
        return "";
    }
}
// login
string login()
{
    string email, password;
    cout << "Enter your email" << endl;
    getline(cin, email);
    cout << "Enter your password" << endl;
    getline(cin, password);
    // checking if there is a user with this email and password
    ifstream myFile("users.txt");
    string line;
    if (!myFile)
    {
        cout << "Unable to open file users.txt" << endl;
    }
    else
    {
        while (getline(myFile, line))
        {
            if (subStringer(line, ' ', 2) == email && subStringer(line, ' ', 5) == password)
            {
                // writting to login file
                ofstream loginFile("login.txt");
                loginFile << "1"
                          << " " << subStringer(line, ' ', 2);
                cout << "Logged in successfully!" << endl;
            }
            else
            {
                cout << "Invalid email or password!" << endl;
            }
        }
    }
}
// register candidate by logged in admin only
string registerCandidates()
{
    string email, names, nationalId, profilePicture, gender, missionStatement;
    cout << "Enter admin email" << endl;
    getline(cin, email);
    // finding if this user exists and is an admin
    string line;
    ifstream userFile("users.txt");
    while (getline(userFile, line))
    {
        if (subStringer(line, ' ', 2) != email)
        {
            // user exists
            cout << "User with email " << email << " does not exits" << endl;
        }
        if (subStringer(line, ' ', 6) != "admin")
        {
            // user exists
            cout << "You are not an admin" << endl;
        }
        else
        {
            // checking if user is logged in
            string myLine;
            ifstream loginFile("login.txt");
            while (getline(loginFile, myLine))
            {
                if (subStringer(myLine, ' ', 1) == email && subStringer(myLine, ' ', 0) == "1")
                {
                    cout << endl;
                    // this means that u are logged in, continue and register candidate
                    cout << "Enter candidate's names" << endl;
                    getline(cin, names);
                    cout << "Enter candidate's national id" << endl;
                    getline(cin, nationalId);
                    cout << "Enter link of profile picture for a candidate" << endl;
                    getline(cin, profilePicture);
                    cout << "Enter candidate's gender" << endl;
                    getline(cin, gender);
                    cout << "Enter candidate's mission statement" << endl;
                    getline(cin, missionStatement);
                    string data = names + " " + nationalId + " " + profilePicture + " " + gender + " " + missionStatement + " 0";
                    // save to the file
                    ofstream candidates("candidates.txt");
                    candidates << data;
                    cout << "Candidate saved successfully." << endl;
                }
            }
        }
    }
}

// listing all candidates
string listCandidates()
{
    string email;
    cout << "Enter your email" << endl;
    getline(cin, email);
    // checking if u re logged in
    string line;
    ifstream loginFile("login.txt");
    while (getline(loginFile, line))
    {
        if (subStringer(line, ' ', 1) != email)
        {
            cout << "You must be logged in to access candidates list." << endl;
        }
        else
        {
            // Print table header
            cout << left<<setw(15) << "Names"
                      << setw(15) << "nationalID"
                      << setw(15) << "profilePic"
                      << setw(15) << "Gender"
                      << setw(25) << "missionStat"
                      << setw(10) << "votes" << endl;
            std::cout << "------------------------------------------------------------------------------------------" << endl;
            // get all candidate
            string myData;
            ifstream candidates("candidates.txt");
            while (getline(candidates, myData))
            {
                cout << left << setw(15) << subStringer(myData, ' ', 0) << setw(15) << subStringer(myData, ' ', 1) << setw(15) << subStringer(myData, ' ', 2) << setw(15) << subStringer(myData, ' ', 3) << setw(25) << subStringer(myData, ' ', 4) << setw(10) << subStringer(myData, ' ', 5) << endl
                     << endl;
            }
        }
    }
}

// voting for a candidate
string voting()
{
    // candidate email,
    string candidateNationalId, voterEmail;
    cout << "Enter your email" << endl;
    getline(cin, voterEmail);
    // checking if voter exists
    string line;
    ifstream users("users.txt");
    while (getline(users, line))
    {
        if (subStringer(line, ' ', 2) != voterEmail)
        {
            cout << "No voter with email this address" << endl;
            break;
        }
        else
        {
            cout << "Enter candidate's national id" << endl;
            getline(cin, candidateNationalId);
            // checking candidate exists

            string myLine;
            ifstream candidates("candidates.txt");
            while (getline(candidates, myLine))
            {
                if (subStringer(myLine, ' ', 1) != candidateNationalId)
                {
                    cout << "No candidate with this nationalid" << endl;
                    break;
                }
                else
                {
                    string prevData = myLine;
                    string votes = subStringer(prevData, ' ', 5);
                    // convert votes into int
                    int votesInt = stoi(votes);
                    // increment votes
                    votesInt++;
                    // convert votes back to string
                    string votesString = to_string(votesInt);
                    // replace votes in prevData
                    string newData = subStringer(prevData, ' ', 0) + " " + subStringer(prevData, ' ', 1) + " " + subStringer(prevData, ' ', 2) + " " + subStringer(prevData, ' ', 3) + " " + subStringer(prevData, ' ', 4) + " " + votesString;
                    // save to file
                    ofstream candidates("candidates.txt");
                    candidates << newData;
                    cout << "You have voted successfully" << endl;
                }
            }
        }
    }
}
// main function
int main()
{
    cout << "=================== Welcome to the voting system  =======================\n";
    cout << "press 1 if you want to register user" << endl;
    cout << "press 2 if you want to login" << endl;
    cout << "press 3 if you want to register a candidate(you must be an admin)" << endl;
    cout << "press 4 to get the list of candidates" << endl;
    cout << "press 5 to vote for a candidate" << endl;
    cout << "press 0 if you want to exit" << endl
         << endl;
    int command;
    while (true)
    {
        ifstream loginFile;
        string line;
        cout << "console>";
        cin >> command;
        cin.ignore(); // Add this line to clear the newline character from the input stream
        switch (command)
        {
        case 0:
            cout << "Thanks for using our system!!!!!!!!!";
            return 0;
        case 1:
            saveUser();
            break;
        case 2:
            // checking if already logged in
            loginFile.open("login.txt");
            bool value;
            if (!loginFile.is_open())
            {
                login();
            }
            else
            {
                while (getline(loginFile, line))
                {
                    if (line.substr(0, 1) == "1")
                    {
                        cout << "You are already logged in" << endl;
                    }
                    else
                    {
                        login();
                    }
                }
            }
            break;
        case 3:
            registerCandidates();
            break;
        case 4:
            listCandidates();
            break;
        case 5:
            voting();
            break;
        default:
            cout << "Invalid command entered" << endl;
            break;
        }
        // voter registration
    }
    return 0;
}