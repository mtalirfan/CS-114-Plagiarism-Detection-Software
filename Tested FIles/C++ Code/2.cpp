#include <iostream> // input/output stream, contains basic statements e.g. cin, cout as part of the "std" (standard) namespace 
#include <string> // string library to manipulate strings
#include <fstream> // (both input and output) file stream to manipulate files for data handling

#include "SimilarityReporter.h" // a custom class that will contain code to store numerical data and prepare a similarity report using data from word check and phrase check functions

using namespace std; // standard namespace is used so if any scope used in main() isn't available elsewhere, the compiler checks standard library "std" for availability. helps with minimising repetition e.g. cout instead of std::cout

// GLOBAL VARIABLES TO USE IN ALL FUNCTIONS, CLASSES AND STUFF
int i; // size_t i; // (UNSIGNED integer and so good for indexing) (there's a high chance it can cost marks for no reason, you have to go with what you studied in course) // a simple integer named i is initialised, will be used for various loops (LITERALLY ALL OF THEM LMAO) 
string file_names[1][6]; // AH YES, an array of strings (not characters) to store file names, typical jugaar (trick). the first index, [1] WITHOUT the second index [6] would otherwise make an array of characters, which is a single string itself.
ifstream file[6]; // DAMN you can do THAT too, made stuff SO MUCH EASIER, praying that an array of (input) ifstreams is not out of the scope of the FOP course lmao
SimilarityReporter data_of_file[6]; // Similarity Report custom class to manipulate numerical data, will try string data too

// create a word plagiarism check function
// create pool file streams via a loop, then check for plagiarism
// check plagiarism by taking a word, check if that word isn't already checked from the report file (loop), if not append its count from the pool of files, another loop
// make a report with plagiarism index arithmetic calculation, append to the test file


void word_check() { // function of type void that does not return any value to main function

    string word, test_word, source_word; // initialise 
    int word_count;

    // COUNT TOTAL WORDS IN EACH FILE AND STORE AS A CLASS DATA
    for (i = 0; i <= 5; i++) {
        word_count = 0;
        while(file[i] >> word) { // cout << word << endl;
            word_count++; } 
        data_of_file[i].word_count = word_count; }

    // for (i = 0; i <= 5; i++) { cout << data_of_file[i].word_count << endl; } 

    cout << endl;


    // ACTUAL WORD PLAGIARISM CHECK

    int j, pos_word; // had to initialise for nested for loop

    for (i = 1; i <= 5; i++) {

        for (j = 0; j <= 5; j++) {
        file[j].clear();
        file[j].seekg(0);
        }

        while( file[0] >> test_word ) { // loop through test file

            // cout << endl << test_word << endl;

            file[i].clear();
            file[i].seekg(0);

        while ( file[i] >> source_word ) { // loop through source files
            // cout << source_word << endl;

            pos_word = source_word.find(test_word); // search for word

            // if (pos_word != string::npos) // if word is found as a substring in a string

            if(test_word == source_word) { // string::npos is returned if word is not found
                data_of_file[i].similar_words++;
                file[i].clear();
                file[i].seekg(0);
                break;
            }
            else if (file[i].eof()) {
                file[i].clear();
                file[i].seekg(0);
                break;
            }
        // cout << data_of_file[i].similar_words << " from file " << i << endl; }

        }}}


    // Similarity Report for Similar Words
//     cout << "Total number of similar words found = " << data_of_file[5].sum_words() << endl;

//     for (i = 1; i <= 5; i++) {
//         cout << data_of_file[i].similar_words << " from file " << i << endl; }


//     data_of_file[0].calculate_similarity_index(); 

}

// create a phrase plagiarism check function
void phrase_check() {

}






int main() { // main function, with int type that needs an integer to be returned at the end of the function, either by putting "return 0;" or your compiler does that for you anyways


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



    // ofstream test_file(file_names[0][0], ios::app);

    // test_file << "hi" << endl;

    // call both plagiarism check functions


    // word check: loop for all 6 files in function above
    word_check(); // if filestreams are global, you don't need to pass its argument, bad on security/code practice but we aren't being judged for a secure code

    // close streams
    for (i = 0; i <= 5; i++) { file[i].close(); } // a for loop closes all ifstreams
    // test_file.close(); // close the ofstream

    return 0; } // terminates the main function by returning code 0 to system; program ends after successful execution