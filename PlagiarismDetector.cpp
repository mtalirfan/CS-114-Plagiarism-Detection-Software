#include <iostream> // input/output stream, contains basic statements e.g. cin, cout as part of the "std" (standard) namespace 
#include <string> // string library to use and manipulate strings
#include <fstream> // (both input and output) file stream to manipulate files for data handling
#include <iomanip> // contains manipulators for plagiarism report formatting (in output statements)
#include <stdlib.h> // standard library contains system("PAUSE") and system("CLS") for presentation of executable
#include "SimilarityReporter.h" // a custom header file (that contains a custom class) that will contain code to store numerical data and prepare a similarity report using arithmetic functions and data from word check and phrase check functions
using namespace std; // standard namespace is used so if any scope used in main() isn't available elsewhere, the compiler checks standard library "std" for availability. helps with minimising repetition e.g. cout instead of std::cout

// GLOBAL VARIABLES TO USE IN ALL FUNCTIONS, CLASSES AND STUFF
int i; // size_t i; // (UNSIGNED integer and so good for indexing) (there's a high chance it can cost marks for no reason, you have to go with what you studied in course) // a simple integer named i is initialised, will be used for various loops (LITERALLY ALL OF THEM LMAO) 
string file_names[1][6]; // AH YES, an array of strings (not characters) to store file names, typical jugaar (trick). the first index, [1] WITHOUT the second index [6] would otherwise make an array of characters, which is a single string itself.
ifstream file[6]; // DAMN you can do THAT too, made stuff SO MUCH EASIER, praying that an array of (input) ifstreams is not out of the scope of the FOP course lmao
SimilarityReporter data_of_file; // the indices [6] are in the class file itself // SimilarityReporter custom class to manipulate numerical data
string similar_phrase_data[2][10000]; // stores phrases data. DON'T DECREASE FIRST INDEX: index [0] for source file number, index [1] for phrase string, CAN CHANGE SECOND INDEX: this 2d string array can store [1000] phrase strings and their file numbers

// WORD SIMILARITY CHECK KNOBS (idk what to call them, you change them according to plagiarism need?)
const string letters_numbers = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"; // a constant (that cannot be modified) string of letters and numbers, used in counting words if they contain at least one of these
int min_word_substring_len = 4; // 4 WORKS BEST FOR MOST CASES, AND 1 FOR EXACT; minimum length of substrings to calculate similarity of
int substring_len_diff_tolerance = 2; // 2 WORKS BEST FOR MOST CASES, AND 0 FOR EXACT; difference tolerance between test substring and source substring lengths: length adjustment, for punctuation, "too small vs too large" substring exclusion and similar words

// PHRASE SIMILARITY CHECK KNOBS
const string letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"; // alphabet for phrases report listing
int min_phrase_len = 2; // 2 IS REQUIRED IN PROBLEM SET: the minimum number of words to take for checking similarity of the phrase, don't worry, the code will ALWAYS take 1 word

void word_check() { // function of type void that does not return any value to main function, takes in an output stream parameter
    string word, test_word, source_word; // declare (but not initialise) strings with appropriate names
    int test_substring_position, source_substring_position; // declare integers for substring positions for searches

    // COUNT TOTAL WORDS OF EACH FILE
    for (i = 0; i <= 5; i++) { // loop for file 0-5
            data_of_file.word_count[i] = 0; // initialise word count for file i in the data_of_file of type SimilarityReporter Class
        while(file[i] >> word) { // take a word from file i and store in the word variable, the WHILE loop indicates this will run until ALL words are taken, after that the file ends and error is raised so loop ends
            if ( word.find_first_of(letters_numbers) != string::npos ) { // we haven't studied find_first_of in lectures, so... anyways, if there is at least a single letter or number in a string, helps reduce word count of non-word symbols in code plagiarism
                data_of_file.word_count[i]++; // count the word for the file i, nice and simple
                }
    }}

    // ACTUAL WORD PLAGIARISM CHECK
    for (i = 1; i <= 5; i++) { // for source files 1-5
            file[0].clear(); // clear stream state of test file to goodbit
            file[0].seekg(ios::beg); // seek to beginning for test file, for iteration in the next source file i
        while( file[0] >> test_word ) { // iterate through test file, take one word then loop through whole file i beacuse of the nested WHILE loop 
                file[i].clear(); // clear stream state for source file i to goodbit
                file[i].seekg(ios::beg); // seek file i to beginning for next word in test file to iterate through source file
            while ( file[i] >> source_word ) { // iterate through source file i, word by word
                    test_substring_position = source_word.find(test_word); // search for the test word substring in source word string, return the position of first character if substring is found, otherwise return -1
                    source_substring_position = test_word.find(source_word); // search for the source word substring in test word string, return the position of first character if substring is found, otherwise return -1
                if(test_substring_position != string::npos || source_substring_position != string::npos) { // cross check if substring is found in either of the two; if either of the positions are not -1 as the substring is found
                    // some conditions to meet: must contain at least a letter or number, and length adjustment, for punctuation, "too small vs too large" substring exclusion and similar words (SEE KNOBS ABOVE)
                    if ( test_word.find_first_of(letters_numbers) != string::npos && source_word.find_first_of(letters_numbers) != string::npos ) { // check if both substrings contain at least a letter/number (the constant string in knobs)
                        if ( test_word.length() >= min_word_substring_len && source_word.length() >= min_word_substring_len ) { // both the substrings should be greater than the minimum length, to filter out small words
                            if ( test_word.length() <= source_word.length() + substring_len_diff_tolerance && test_word.length() >= source_word.length() - substring_len_diff_tolerance ) { // length adjustment, for punctuation, "too small vs too large" substring exclusion and similar words. works for length differences in any order: e.g. "work": "worked" or "work." can be similar through this
                                data_of_file.similar_words[i]++; // increment similar word count for file i. the main thing. POWER
                                break; // terminates the source word while loop, so that the next word in test file can be taken.
    }}}}}}}
}

void phrase_check() { // function of type void that does not return any value to main function, takes in an output stream parameter
    string test_word, test_phrase, source_line, temp_phrase; // declare (but not initialise) strings with appropriate names
    int test_substring_position, j, test_words_done; // declare integers for various uses

    for (i = 1; i <= 5; i++) { // for source files 1-5
        file[0].clear();
        file[0].seekg(0); // clear stream state to goodbit and seek to position 0 (beginning of file) for test file
        file[i].clear();
        file[i].seekg(0); // clear stream state to goodbit and seek to position 0 (beginning of file) for source file i
        test_words_done = 0; // initialise integer that skips words already done in test file

        while ( file[0].good() ) { // as long as test file has no errors failbit, eof the loop runs
            for ( j = 1; j <= test_words_done; j++ ) { file[0] >> test_word; } // skip words that are checked already
            if ( file[0].eof() ) break; // if test file literally ends here move to next source file
            else { // otherwise take the first word for phrase check
                file[0] >> test_word;
                test_phrase = test_word;
                if ( file[0].eof() ) break; } // if test file literally ends here (eof bugfix lmao), move to next source file

            for ( j = 1; j <= min_phrase_len - 1; j++ ) { // if no issues, take more words as specified by min phrase length...
                if ( !file[0].eof() ) { // ... as long as the file doesn't end. if it ends, it does not take in more words
                    file[0] >> test_word;
                    test_phrase = test_phrase + " " + test_word; }}

            // ACTUAL PHRASE PLAGIARISM CHECK
            while ( !file[i].eof() ) {  // while source file does not end
                    getline(file[i], source_line); // take each line from source file
                    test_substring_position = source_line.find(test_phrase); // check if our test phrase is in any line
                if ( test_substring_position != string::npos ) { // if the phrase was found (the position is not -1)
                    test_words_done = test_words_done + min_phrase_len; // add the number of words in phrase to the words done, to skip them in next loop 
                    file[i].clear();
                    file[i].seekg(0); // clear stream state to goodbit and seek to start for source file i            
                    break; }} // exit the loop if phrase was found

            if ( test_substring_position == string::npos ) { // if the phrase was not found
                test_words_done++; // add just one to test words done, so the next loop takes in the second word from the current phrase, NOT THE FIRST WORD AGAIN AS IT WILL REPEAT THE SAME THING
                file[0].clear();
                file[0].seekg(0); // clear stream state to goodbit and seek to position 0 (beginning of file) for test file
                file[i].clear();
                file[i].seekg(0); // clear stream state to goodbit and seek to position 0 (beginning of file) for source file i
                continue; } // run the next iteration of phrase check loop, trust me it will skip your previous, including the first word in current phrase for word by word progression

            while ( test_substring_position != string::npos ) { // while the string is found, in a loop
                if ( file[0].eof() ) break; // if test file ends, that's the end, WE GOT A SIMILAR PHRASE
                else { // else take a test word and add it to a TEMPORARY PHRASE, WE WANT TO CONFIRM THE PHRASE IS STILL SIMILAR
                    file[0] >> test_word;
                    temp_phrase = test_phrase + " " + test_word; }
                while ( !file[i].eof() ) { // another loop for source file, had to make a repeated code for this
                        getline(file[i], source_line); // get each line from source file
                        test_substring_position = source_line.find(temp_phrase); // check if temp phrase exists in any line           
                    if ( test_substring_position != string::npos ) { // if phrase is found...
                        test_words_done++; // add a count for test words done, because it's done.
                        test_phrase = temp_phrase; // NOW WE HAVE CONFIRMED THE PHRASE WAS SIMILAR
                        file[i].clear();
                        file[i].seekg(0); // clear stream state to goodbit and seek to start for source file i
                        break; // RUN THE WORD ADDING LOOP AGAIN SINCE THE SUBSTRING WAS FOUND, keep on doing until it's not found in which case TEMP PHRASE DOESN'T BECOME TEST PHRASE and we HAVE OUR PHRASE
            }}}

            // if the dumpload of conditions above are passed without the code any break; or continue; or getting stuck in an infinite loop, preventing code execution reaching this stage, we HAVE A SIMILAR PHRASE
            data_of_file.similar_phrase_count++; // increment similar phrase count because WE HAVE A SIMILAR PHRASE FOR THIS ITERATION
            similar_phrase_data[0][data_of_file.similar_phrase_count] = to_string(i); // convert the integer to string, store the source file number in the 2d data array at the unique index equal to current similar phrase count
            similar_phrase_data[1][data_of_file.similar_phrase_count] = test_phrase; // store the actual phrase in the 2d data array at the unique index equal to current similar phrase count
            file[0].clear();
            file[0].seekg(0); // clear stream state to goodbit and seek to position 0 (beginning of file) for test file
            file[i].clear();
            file[i].seekg(0); // clear stream state to goodbit and seek to position 0 (beginning of file) for source file i
    }}
}

void similarity_report(ofstream& test_file) { // Similarity Report Function with an ofstream parameter passed by reference

    cout << "Results:"; // some text

    // Similarity Report for Similar Words, format as REQUIRED using setw manipulators, taking data and using function from the class in header file
    cout << endl << endl << setw(0) << "Total number of similar words found = " << data_of_file.sum_similar_words() << endl; // print to console
    // test_file << endl << endl << setw(0) << "Total number of similar words found = " << data_of_file.sum_similar_words() << endl; // print the same to test file, NOT REQUIRED IN PROBLEM SET
    for (i = 1; i <= 5; i++) { // for source files 1-5
        cout << setw(15) << data_of_file.similar_words[i] << " from file " << i << endl; // print to console
        // test_file << setw(15) << data_of_file.similar_words[i] << " from file " << i << endl; // print the same to test file, NOT REQUIRED IN PROBLEM SET
    }

    // Similarity Report for Similarity Index Percentage, format as REQUIRED using setprecision, \t manipulators, taking data and using function from the class in header file
    data_of_file.calculate_similarity_index(); // call a void function in the class that just performs arithmetic and returns nothing
    cout << endl << endl << setprecision(3) << "\t\tSimilarity Index = " << data_of_file.similarity_percentage[0] << "%" << endl; // print to console
    test_file << endl << endl << setprecision(3) << "\t\tSimilarity Index = " << data_of_file.similarity_percentage[0] << "%" << endl; // print the same to test file
    for (i = 1; i <= 5; i ++) { // for source files 1-5
        cout << setprecision(3) << "Source " << i << "\t= " << data_of_file.similarity_percentage[i] << "%" << endl; // print to console
        test_file << setprecision(3) << "Source " << i << "\t= " << data_of_file.similarity_percentage[i] << "%" << endl; // print the same to test file
    }

    // Similarity Report for Similar Phrases, using manipulators setw and std::left, and data stored in the class and the 2d string array
    // cout << endl << endl << "Total Number of Similar Phrases = " << data_of_file.similar_phrase_count << endl << "    Similar Phrases/Clauses       Source File" << endl << "    \"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\""; // NOT REQUIRED IN PROBLEM SET
    test_file << endl << endl << "Total Number of Similar Phrases = " << data_of_file.similar_phrase_count << endl << "    Similar Phrases/Clauses       Source File" << endl << "    \"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"";
    for (i = 1; i <= data_of_file.similar_phrase_count; i++) { // for loop runs for the number of phrases stored: until all phrases stored in the 2d array are iterated
        // cout << endl << "    " << letters.at( (i - 1) % letters.size() ) << ")  "; // NOT REQUIRED IN PROBLEM SET, the .at() gives the character at the specified position in the letters string, the position is given by the remainder of (i - 1/52) : a-z is 0-25, A-Z is 26-51. i - 1 because we started i from 1, not 0 so we don't start from "b"
        // cout << setw(30) << std::left << similar_phrase_data[1][i]; // NOT REQUIRED IN PROBLEM SET, print the phrase, using formatting
        // cout << " " << similar_phrase_data[0][i]; // NOT REQUIRED IN PROBLEM SET, print the file number for the phrase
        // PRINT THE SAME TO TEST FILE
        test_file << endl << "    " << letters.at( (i - 1) % letters.size() ) << ")  "; // the .at() gives the character at the specified position in the letters string, the position is given by the remainder of (i - 1/52) : a-z is 0-25, A-Z is 26-51. i - 1 because we started i from 1, not 0 so we don't start from "b"
        test_file << setw(30) << std::left << similar_phrase_data[1][i]; // print the phrase, using formatting
        test_file << " " << similar_phrase_data[0][i]; // print the file number for the phrase
    }
}

int main() { // main function, with int type that needs an integer to be returned at the end of the function, either by putting "return 0;" or your compiler does that for you anyways

    cout << "Welcome to our Plagiarism Detection Software." << endl << endl; // some text

    // input file names, create streams (1 test file, 5 source files). tried many loop methods that failed, apparently you can use: idk what that even is anymore?
    for (i = 0; i <= 5; i++) { // for loop where i starts with a value of 0, increments each time the loop finishes a cycle. the loop terminates when i exceeds 5, so the loop runs 6 times
        string text = (i == 0)? "test" : "source"; // pretty sure we did the shorthand if-else in class, YES IT WAS IN AIKMAN SERIES IF STATEMENTS NOTES
        do { // Just Do It. Seriously, a do-while loop will make sure it executes statements in it at least once, until...
            cout << "Enter name of the " << text << " file, file " << i << ": "; // cout prints the given text in console. integer i being used for numbering, as text.
            getline(cin, file_names[0][i]); // similar to cin input, getline allows taking in a string WITH spaces as input instead of buffering inputs delimited by spaces. here, integer i is being used for indexing, and the loop means each index stores a different string.
            file[i].open(file_names[0][i]); // tries to open the file name you input, in an input stream
            if (!file[i].is_open()) cout << "Failed to open \"" << file_names[0][i] << "\".\nPlease try again, making sure the file is in the same directory as this software.\n\n"; // if file does not open, cout these statements
            else { cout << "The " << text << " file \"" << file_names[0][i] << "\" opened successfully!\n\n"; } // ELSE, this file has its stream correctly opened, continue to next loop for next file
        } while (!file[i].is_open()); } // ...until the file stream is successful / WHILE the file is NOT open to input stream
    
    ofstream test_file(file_names[0][0], ios::app); // call a solitary output stream for test file, ios::app flag appends text to the end of file

    cout << "All files opened successfully, proceeding to Plagiarism Detection." << endl; // some text
    system("PAUSE"); // pauses the execution
    system("CLS"); // clears the screen for Plagiarism detection results to show

    // call both plagiarism check functions
    word_check(); // if filestreams are global, you don't need to pass so many arguments for everything (actually I was unable to pass an array of filestreams lmao (i am scared if we were being tested for pointer usage here)), bad on security/code practice but we aren't being judged for a secure code
    phrase_check(); // similarly, a phrase_check function is called after the word_check function successfully executes and control returns to the main function

    //call similarity report function
    similarity_report(test_file); // a function that contains required and formatted similarity reports, an argument ofstream of name test_file is given

    cout << endl << endl << "Thank you for using our Plagiarism Detection Software!" << endl; // some text
    system("PAUSE"); // pauses the program execution to display the results, and not immediately close

    // close filestreams after both functions have executed and terminated
    for (i = 0; i <= 5; i++) { file[i].close(); } // for loop closes all ifstreams
    test_file.close(); // close the ofstream separately

    return 0; } // terminates the main function by returning code 0 to system; program ends after successful execution