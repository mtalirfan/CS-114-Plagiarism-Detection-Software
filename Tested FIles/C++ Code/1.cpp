#include <iostream> // input/output stream, contains basic statements e.g. cin, cout as part of the "std" (standard) namespace 
#include <string> // string library to manipulate strings
#include <fstream> // file stream to manipulate files for data handling


using namespace std; // standard namespace is used so if any scope used in main() isn't available elsewhere, the compiler checks standard library "std" for availability. helps with minimising repetition e.g. cout instead of std::cout

// create a word plagiarism check function
// create pool file streams via a loop, then check for plagiarism
// check plagiarism by taking a word, check if that word isn't already checked from the report file (loop), if not append its count from the pool of files, another loop
// make a report with plagiarism index arithmetic calculation, append to the test file

void word_transform(std::ifstream& infile)
{
    // read something from infile
}



// create a phrase plagiarism check function



int main() { // main function, with int type that needs an integer to be returned at the end of the function, either by putting "return 0;" or your compiler does that for you anyways

    int i; // size_t i; // (UNSIGNED integer and so good for indexing) (there's a high chance it can cost marks for no reason, you have to go with what you studied in course) // a simple integer named i is initialised, will be used for various loops (LITERALLY ALL OF THEM LMAO) 
    string file_names[1][6]; // AH YES, an array of strings (not characters) to store file names, typical jugaar (trick). the first index, [1] WITHOUT the second index [6] would otherwise make an array of characters, which is a single string itself.
    ifstream file[6]; // DAMN you can do THAT too, made stuff SO MUCH EASIER, praying that an array of (input) ifstreams is not out of the scope of the FOP course lmao
    // input file names, create streams (1 test file, 5 source files). tried many loop methods that failed, apparently you can use: idk what that even is anymore?
    for (i = 0; i <= 5; i++) { // for loop where i starts with a value of 0, increments each time the loop finishes a cycle. the loop terminates when i exceeds 5, so the loop runs 6 times
        string text = (i == 0)? "test" : "source"; // pretty sure we did the shorthand if-else in class, YES IT WAS IN AIKMAN SERIES IF STATEMENTS NOTES
        do { // Just Do It. Seriously, a do-while loop will make sure it executes statements in it at least once, until...
            cout << "enter file name of the " << text << " file, file " << i << ": "; // cout prints the given text in console. integer i being used for numbering, as text.
            getline(cin, file_names[0][i]); // similar to cin input, getline allows taking in a string WITH spaces as input instead of buffering inputs delimited by spaces. here, integer i is being used for indexing, and the loop means each index stores a different string.
            file[i].open(file_names[0][i]); // tries to open the file name you input, in an input stream
            if (!file[i].is_open()) cout << "failed to open \"" << file_names[0][i] << "\".\nPlease try again, making sure the file is in the same directory as this code.\n\n"; // if file does not open, cout these statements
            else { cout << text << " file \"" << file_names[0][i] << "\" opened successfully!\n\n"; continue; } // ELSE, this file has its stream correctly opened, continue to next loop for next file
        } while (!file[i].is_open()); } // ...until the file stream is successful / WHILE the file is NOT open to input stream













    for (i = 0; i <= 5; i++) {
        cout << endl << file_names[0][i];
    }

    ofstream test_file(file_names[0][0], ios::app);

    test_file << "hi" << endl;

    // call both plagiarism check functions
    
    // word check, get 



















    // close streams
    for (i = 0; i <= 5; i++) { file[i].close(); } // a for loop closes all ifstreams
    test_file.close(); // close the ofstream

    return 0; } // terminates the main function by returning code 0 to system; program ends after successful execution