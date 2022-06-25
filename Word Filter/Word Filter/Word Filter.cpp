// Word Filter.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/*
 * Inlcude Headers Files from the C Library
 */

#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

const int bannedSize = 16; // banned word array size = 16 (16 banned words)

typedef pair<string, int> mapPair;

/*
 * Reads the main string and looks for the substring, prints out the position of the substring
 */
void substrPosition(string stringX, string subString)
{
    int j = 0;
    bool flag = false;
    for (int i = 0; i < stringX.length(); i++)
    { // if i is under the string's length, i++
        if (stringX.substr(i, subString.length()) == subString)
        { // if - string's substring position (i) of the substring's length is equal to substring
            cout << i << " ";
            flag = true; // bool flag is true
            j++;         // counting the amount of times the sub string appears in the string
        }
    }
    cout << endl
        << "\n";
    cout << "--------Occurences-------- \n";
    cout << "Keyword " << subString << " Appears " << j << " Times \n"; // Prints Occurences of Keyword
    if (flag == false)                                                  // if flag is false cout NONE, safety check
        cout << "NONE";
}

/*
 * While &line finds subString, with no specific position to start from.
 * line.replace function, line finds position of subString, with the length of subString, "***" replaces the SubString
 */
void censorText(string& line, string subString)
{
    string asterisk(subString.length(), '*'); // asterisk is length of subString multiplied by '*'
    while (line.find(subString) != string::npos)
    {
        line.replace(line.find(subString), subString.length(), asterisk);
    }
}

/*
 * For loop which runs 8 times, size of banned list is 8 lines.
 * 'Find Function' finds each string in the lineBanned array which appear in the line1 string
 * If strings in lineBanned array found in lineX string print out "found"
 * If the strings are not found in the lineX string print out "not found"
 */
void findBannedWords(string lineX, string lineBanned[bannedSize])
{
    for (int i = 0; i < bannedSize; i++)
    {
        if (lineX.find(lineBanned[i]) != std::string::npos)
        { //! std::string:: npos meaning NOT EQUAL to if string has noposition (so has position)
            cout << "banned word in text - " << lineBanned[i] << '\n';
        }
        else
        {
            cout << "not banned in text " << lineBanned[i] << '\n';
        }
    }
}

/*
 * If outfile variable is not open display error, if there is an outfile, line (the string variable holding text) wrties into the outfile.
 * The function then tells the user the out file has been written to then the otufile closes
 */
void outfilePrint(ofstream& outfile, string line)
{
    if (!outfile)
    {
        cout << "Error \n Can't open output file \n";
    }
    else
    {
        outfile << line;
        cout << "Textfile written into " << endl
            << "\n";
        outfile.close();
    }
}

/*
 * Writes into the file so that there is a way for people to create something in which
 */
void writeInfile(ifstream& text, string& line)
{
    int i = 0;

    if (!text)
    {
        cout << "Error\n"
            << "Can't open output file \n";
    }
    // Text no skip whitespace, double check if 'text' variable NOT end of file
    text >> noskipws;
    while (!text.eof())
    {
        if (!text.eof())
        {
            getline(text, line); // Getline from text variable and puts it into the 'line 4' variable
            cout << line << endl;
            i++; // counter
        }
    }

    cout << "text has " << i << " lines of text " << endl
        << "\n";
}

void outfilePrintAllCensorText(ofstream& outfile, string lineOne, string lineTwo, string lineThree, string lineFour)
{
    if (!outfile)
    {
        cout << "Error \n Can't open output file \n";
    }
    else
    {
        outfile << lineOne << endl;
        outfile << lineTwo << endl;
        outfile << lineThree << endl;
        outfile << lineFour;
        cout << "Textfile written censored text from all text files into all text files" << endl
            << "\n";
        outfile.close();
    }
}

string stringToLower(string s)
{
    string stringCopy = s;

    transform(stringCopy.begin(), stringCopy.end(), stringCopy.begin(),
        [](unsigned char c) { return std::tolower(c); });

    return stringCopy;
}

void tenMostCommonWords(string filler) // Filler MEANS nothing it just means that we will have something to work on
{
    istringstream input(filler); // This part of the code is the part which will be read //istringstream is for input ONLY //stromgstrea, is for pretty much everything
    map<string, int> count;      // map means that it stores a combinatoion of a key value and a mapped value
    string word;                 // simple string
    while (input >> word)
    {
        word = stringToLower(word);
        if (count.find(word) == count.end()) // Check if the map already contains the current word as a key
        {
            count[word] = 1; // If not, initialise it with 1
        }
        else
        {
            count[word] += 1; // If so, increment
        }
    }

    // Now we convert the map to a vector so we can sort it
    // https://www.techiedelight.com/sort-map-values-cpp/
    vector<mapPair> vec;
    copy(count.begin(), count.end(), back_inserter<vector<mapPair>>(vec));

    sort(vec.begin(), vec.end(),
        [](const mapPair& l, const mapPair& r)
        {
            if (l.second != r.second) {
                return l.second > r.second;
            }

            return l.first < r.first;
        });

    // Set how many we want to print, checking that the vector is large enough
    int vecSize = vec.size() < 10 ? vec.size() : 10;

    vec.resize(vecSize);

    // Re-sort again, alphabetically this time
    sort(vec.begin(), vec.end(),
        [](const mapPair& l, const mapPair& r)
        {
            return l.first < r.first;
        });

    cout << "Most frequent words:" << endl;

    for (int i = 0; i < vecSize; i++) {
        cout << vec[i].first << ": " << vec[i].second << endl;
    }
}

/*
 * Function counts how many words are in given string parameter
 * function allows for a string to be copied into stringstream then ss stringstream reads into wordCollect string,
 * while ss stringstream is read into wordCollect string int wordCount increases
 */
void stringStream(string lineX)
{
    string wordCollect;
    int wordCount = 0;
    stringstream ss(lineX);
    while (ss >> wordCollect)
    {

        ++wordCount; // counter while string streaming
    }
    cout << "text has " << wordCount << " words" << endl
        << endl; // Shows word count
}

int main()
{
    string totalText; // Used for checking most common words overall

    /*
     * Reads the text variable into the line one variable then COUTs the line one variable, then states how many lines of text there is inside the line one variable
     */
    cout << "--------text1.txt--------\n";
    ifstream textFileOne("text1.txt"); // Creates ifstream variable which holds 'text1.txt'
    string lineOne;                    // string lineOne is written into
    writeInfile(textFileOne, lineOne); // Writes ifstream textFileOne into string lineOne
    stringStream(lineOne);             // Counts the amount of words in string lineOne
    tenMostCommonWords(lineOne);
    totalText += lineOne;

    /*
     * Reads the text variable into the line two array variable then COUTs the line two array variable index, then states how many lines of text there is inside
     * when all the strings are added together
     */
    ifstream bannedText("banned.txt"); // Creates ifstream variable which holds 'banned.txt'
    string lineBanned[bannedSize];
    int j = 0;

    // writeInfile(bannedText, lineBanned[sizeSixteen]);
    if (!bannedText)
    {
        cout << "Error\n"
            << "Can't open output file \n";
    }
    cout << "--------banned.txt-------- \n";
    // Text no skip whitespace, double check if 'text' variable NOT end of file
    bannedText >> noskipws;
    while (!bannedText.eof())
    {
        if (!bannedText.eof())
        {
            getline(bannedText, lineBanned[j]);
            cout << lineBanned[j] << endl;
            j++; // counter for both increasing the arrays position and counting each line
        }
    }

    cout << endl
        << "banned.txt has " << j << " lines and " << j << " words " << endl
        << "\n"; // One word for each line

    cout << "--------Finding Banned Words in text1.txt-------- \n";

    findBannedWords(lineOne, lineBanned); // Finds banned words in lineOne by comparing lineOne string with lineBanned string

    cout << "\n";

    cout << "--------Banned Word text1.txt Positions---------" << endl
        << "\n";
    string subStringCat = "cat"; // keyword cat to search for in function
    cout << "--------Keyword Cat Position in text1.txt:-------- \n";
    substrPosition(lineOne, subStringCat);

    cout << endl;

    string subStringDog = "dog"; // keyword dog to search for in function
    cout << "--------Keyword Dog Position in text1.txt:------- \n";
    substrPosition(lineOne, subStringDog);

    cout << endl;

    string subStringAim = "aim"; // keyword aim to search for in function
    cout << "--------Keyword Aim Position in text1.txt:----------\n";
    substrPosition(lineOne, subStringAim);

    cout << endl;

    cout << "---------Replacing bad words in text1.txt---------- \n";
    /*
     * While line one finds "example", with no specific position to start from.
     * line1.replace function, line one finds position of cat/dog/aim, with the length of cat, "***" replaces the length of cat/dog/aim
     */
    censorText(lineOne, subStringCat);
    censorText(lineOne, subStringDog);
    censorText(lineOne, subStringAim);

    cout << lineOne << endl
        << endl; // Prints out the now filtered text

    cout << "--------Writing filtered text to text1Filtered file-------- \n";

    /*
     *Declaring ofstream outfile then opening the text file does not work directly in a function, even with call by reference
     */
    ofstream outfileOne("text1Filtered.txt"); // Writes string lineTwo into ofstream outfileOne's File
    outfilePrint(outfileOne, lineOne);        // Writes ofstream outfileOne into string lineOne

    cout << "--------text2.txt--------\n";

    ifstream textFileTwo("text2.txt"); // Creates ifstream variable which holds 'text1.txt'
    string lineTwo;                    // string linetTwo is given ifstream textfileTwo "text2.txt" file text.
    writeInfile(textFileTwo, lineTwo); // Writes ifstream textFileTwo into string lineTwo
    stringStream(lineTwo);             // Counts the amount of words in string lineTwo
    tenMostCommonWords(lineTwo);
    totalText += lineTwo;

    cout << "--------Finding Banned Words in text2.txt-------- \n";
    findBannedWords(lineTwo, lineBanned); // Finds banned words in lineTwo by comparing lineTwo string with lineBanned string

    // Banned Words found in line two Uppercase Versions
    string subStringUpEar = "Ear";
    string subStringUpBack = "Back";
    string subStringUpPunk = "Punk";
    string subStringUpAble = "Able";

    // Banned Words found in line two Uppercase Versions
    string subStringEar = "ear";
    string subStringBack = "back";
    string subStringPunk = "punk";
    string subStringAble = "able";

    cout << "--------Banned Word text2.txt Positions---------" << endl
        << "\n";
    cout << "--------Keyword Ear Position in text2.txt-------- \n";
    substrPosition(lineTwo, subStringEar);

    cout << endl;

    cout << "--------Keyword Back Position in text2.txt-------- \n";
    substrPosition(lineTwo, subStringBack);

    cout << endl;
    cout << "--------Keyword Punk Position in text2.txt-------- \n";
    substrPosition(lineTwo, subStringPunk);

    cout << endl;

    cout << "--------Keyword Able Position in text2.txt-------- \n";
    substrPosition(lineTwo, subStringAble);

    cout << endl
        << "\n";

    cout << "---------Replacing bad words in text2.txt---------- \n";
    /*
     * While line one finds "example", with no specific position to start from.
     * line3.replace function, line one finds position of cat/dog/aim, with the length of cat, "***" replaces the length of cat/dog/aim
     */
    censorText(lineTwo, subStringEar);  // Finds the position(s) of subStringEar in the lineFour variable text
    censorText(lineTwo, subStringBack); // Finds the position(s) of subStringBack in the lineFour variable text
    censorText(lineTwo, subStringPunk); // Finds the position(s) of subStringPunk in the lineFour variable text
    censorText(lineTwo, subStringAble); // Finds the position(s) of subStringAble in the lineFour variable text

    cout << lineTwo; // Prints out censored line 3

    cout << endl;
    cout << "--------Writing filtered text to text2Filtered file-------- \n";

    /*
     *Declaring ofstream outfile then opening the text file does not work directly in a function, even with call by reference
     */
    ofstream outfile2("text2Filtered.txt"); // Outfile outfileTwo holds "text2Filtered.txt" to be written into
    outfilePrint(outfile2, lineTwo);        // Writes string lineTwo into ofstream outfileTwo's File

    cout << "--------text3.txt--------\n";
    ifstream textFileThree("text3.txt");   // Creates ifstream variable which holds 'text3.txt'
    string lineThree;                      // string lineThree is given ifstream textfileThree "text3.txt" text.
    writeInfile(textFileThree, lineThree); // Writse ifstream textFileThree into string lineThree
    stringStream(lineThree);               // Counts the amount of words in string lineThree
    tenMostCommonWords(lineThree);
    totalText += lineThree;

    cout << "--------Finding Banned Words in text3.txt-------- \n";
    findBannedWords(lineThree, lineBanned); // Finds banned words in lineThree by comparing lineThree string with lineBanned string
    cout << endl;

    // Banned Words in Line Three Uppercase
    string subStringUpAdd = "Add";
    // Banned Words in Line Three Lowercase
    string subStringAdd = "add";

    cout << "--------Banned Word text3.txt Positions---------" << endl
        << "\n";
    cout << "--------Keyword Add Position in text4.txt-------- \n";
    substrPosition(lineThree, subStringAdd); // Finds the position(s) of subStringAdd in the lineFour variable text
    cout << "\n";

    cout << "---------Replacing bad words in text3.txt---------- \n";
    /*
     * While line one finds "example", with no specific position to start from.
     * line4.replace function, line one finds position of cat/dog/aim, with the length of cat, "***" replaces the length of cat/dog/aim
     */
    censorText(lineThree, subStringAdd); // Finds the position(s) of subStringAdd in the lineFour variable text

    cout << lineThree; // Prints out censored line 4

    cout << endl
        << "\n";
    cout << "--------Writing filtered text to text3Filtered file-------- \n";

    /*
     *Declaring ofstream outfile then opening the text file does not work directly in a function, even with call by reference
     */
    ofstream outfileThree("text3Filtered.txt"); // Outfile outfileThree holds "text3Filtered.txt" to be written into
    outfilePrint(outfileThree, lineThree);      // Writes string lineThree into ofstream outfileThree's File

    cout << "--------text4.txt--------\n";
    ifstream textFileFour("text4.txt");  // Creates ifstream variable which holds 'text4.txt'
    string lineFour;                     // string lineFour is given ifstream textfileFour "text4.txt" text.
    writeInfile(textFileFour, lineFour); // Writes ifstream textFileFour into string lineFour
    stringStream(lineFour);              // Counts the amount of words in string lineFour
    tenMostCommonWords(lineFour);
    totalText += lineFour;

    cout << endl;

    cout << "--------Finding Banned Words in text4.txt-------- \n";
    findBannedWords(lineFour, lineBanned); // Finds banned words in line Four by comparing lineFour string with lineBanned string
    cout << endl;

    cout << "--------Banned Word text4.txt Positions---------" << endl
        << "\n";
    cout << "--------Keyword Ear Position in text4.txt-------- \n";
    substrPosition(lineFour, subStringEar); // Finds the position(s) of subStringEar in the lineFour variable text

    cout << endl;

    cout << "---------Replacing bad words in text4.txt---------- \n";
    /*
     * While line one finds "example", with no specific position to start from.
     * line4.replace function, line one finds position of cat/dog/aim, with the length of cat, "***" replaces the length of cat/dog/aim
     */
    censorText(lineFour, subStringEar);

    cout << lineFour << endl
        << "\n"; // Prints out censored line 5

    cout << "--------Writing filtered text to text4Filtered file-------- \n";

    /*
     *Declaring ofstream outfile then opening the text file does not work directly in a function, even with call by reference
     */
    ofstream outfileFour("text4Filtered.txt"); // Writes string lineFour into ofstream outfileFour's File
    outfilePrint(outfileFour, lineFour);       // Writes ofstream outfileFour into string lineFour

    cout << "--------Most Frequent Words--------\n";

    tenMostCommonWords(totalText);

    /*
     * Writes all text file data into one text file
     */
    cout << "--------Writing all filtered text to textAllFiltered file-------- \n";
    /*
     *Declaring ofstream outfile then opening the text file does not work directly in a function, even with call by reference
     */
    ofstream outfileAll("sorted.txt");
    outfilePrintAllCensorText(outfileAll, lineOne, lineTwo, lineThree, lineFour);

    // Pauses system once completed
    system("pause");
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
