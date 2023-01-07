#include <iostream> // input/output stream, contains basic statements e.g. cin, cout as part of the "std" (standard) namespace 
#include <string> // string library to manipulate strings
#include <fstream> // (both input and output) file stream to manipulate files for data handling
#include <iomanip> // std::setw, std::setprecision, report formatting

#include "SimilarityReporter.h" // a custom class that will contain code to store numerical data and prepare a similarity report using data from word check and phrase check functions

using namespace std; // standard namespace is used so if any scope used in main() isn't available elsewhere, the compiler checks standard library "std" for availability. helps with minimising repetition e.g. cout instead of std::cout

// GLOBAL VARIABLES TO USE IN ALL FUNCTIONS, CLASSES AND STUFF
int i; // size_t i; // (UNSIGNED integer and so good for indexing) (there's a high chance it can cost marks for no reason, you have to go with what you studied in course) // a simple integer named i is initialised, will be used for various loops (LITERALLY ALL OF THEM LMAO) 
string file_names[1][6]; // AH YES, an array of strings (not characters) to store file names, typical jugaar (trick). the first index, [1] WITHOUT the second index [6] would otherwise make an array of characters, which is a single string itself.
ifstream file[6]; // DAMN you can do THAT too, made stuff SO MUCH EASIER, praying that an array of (input) ifstreams is not out of the scope of the FOP course lmao
SimilarityReporter data_of_file; // the index [6] is in the class file itself // Similarity Report custom class to manipulate numerical data

// WORD SIMILARITY CHECK KNOBS (idk what to call them, you change them according to plagiarism need?)
const string letters_numbers = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"; // a constant (that cannot be modified) string of letters and numbers
// const string similar_word_filter = {"I", "i", "We", "we", "They"}; // not willing to add hundreds of combinations lol
int min_substring_len = 4; // minimum length of substrings to calculate similarity of; 4 works best for most cases, and 1 for exact
int substring_len_diff_tolerance = 2; // difference tolerance between test substring and source substring lengths: length adjustment, for punctuation, "too small vs too large" substring exclusion and similar words; 2 works best for most cases, and 0 for exact

// PHRASE SIMILARITY CHECK KNOBS
const string letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

void word_check(ofstream& test_file) { // function of type void that does not return any value to main function, takes in an output stream parameter

    string word, test_word, source_word; // initialise strings
    int test_substring_position, source_substring_position; // substring positions for searches

    // COUNT TOTAL WORDS
    for (i = 0; i <= 5; i++) {
        data_of_file.word_count[i] = 0;
        while(file[i] >> word) {
            if ( word.find_first_of(letters_numbers) != string::npos ) { // we haven't studied find_first_of in class, so... anyways, if there is at least a single letter or number in a string, helps reduce word count of non-word symbols in code plagiarism
                
                // cout << word << endl; // debugging

                data_of_file.word_count[i]++; // count the word
            }
        }
    }

    // cout << endl << "The sum of words in all files is " << data_of_file.sum_words() << endl; // debugging
    // for (i = 0; i <= 5; i++) { cout << data_of_file.word_count[i] << endl; } // debugging
    // cout << endl; // debugging

    // ACTUAL WORD PLAGIARISM CHECK
    for (i = 1; i <= 5; i++) { // for source files 1-5
        
        file[0].clear();
        file[0].seekg(0); // clear and seek to start for test file, for iteration in the next source file i

        while( file[0] >> test_word ) { // iterate through test file, take one word then loop through whole file i

            // cout << endl << test_word << endl; // debugging

            file[i].clear();
            file[i].seekg(0); // seek file i to beginning for next word in test file to iterate through source file

            while ( file[i] >> source_word ) { // iterate through source file i, word by word

                // cout << source_word << endl; // debugging

                test_substring_position = source_word.find(test_word); // search for the test word substring in source word string, return the position of first character if substring is found, otherwise return -1
                source_substring_position = test_word.find(source_word); // search for the source word substring in test word string, return the position of first character if substring is found, otherwise return -1

                // cout << test_substring_position << " " << source_substring_position << endl; // debugging

                // cross check if substring is found in either of the two
                if(test_substring_position != string::npos || source_substring_position != string::npos) { // if either of the positions are not -1 as the substring is found

                    // cout << endl << test_word << " " << source_word << endl; // debugging
                    // cout << test_word.length() << endl << source_word.length() << endl << endl; // debugging

                    // some conditions to meet: must contain at least a letter or number, and length adjustment, for punctuation, "too small vs too large" substring exclusion and similar words (SEE KNOBS ABOVE)
                    if ( test_word.find_first_of(letters_numbers) != string::npos && source_word.find_first_of(letters_numbers) != string::npos ) {
                        if ( test_word.length() >= min_substring_len && source_word.length() >= min_substring_len ) {
                            if ( test_word.length() <= source_word.length() + substring_len_diff_tolerance && test_word.length() >= source_word.length() - substring_len_diff_tolerance ) { // works for length differences in any order

                                // cout << endl << test_word << " " << source_word << endl; // debugging
                                // cout << test_word.length() << endl << source_word.length() << endl; // debugging

                                data_of_file.similar_words[i]++; // the main thing. POWER
                                break;
                            }
                        }
                    }
                }
            }
        }
    }

    // Similarity Report for Similar Words
    cout << endl << endl << setw(0) << "Total number of similar words found = " << data_of_file.sum_similar_words() << endl;
    // test_file << endl << endl << setw(0) << "Total number of similar words found = " << data_of_file.sum_similar_words() << endl; // NOT REQUIRED IN PROBLEM SET
    for (i = 1; i <= 5; i++) {
        cout << setw(15) << data_of_file.similar_words[i] << " from file " << i << endl;
        // test_file << setw(15) << data_of_file.similar_words[i] << " from file " << i << endl; // NOT REQUIRED IN PROBLEM SET
    }

    // Similarity Report for Similarity Index Percentage
    data_of_file.calculate_similarity_index();

    cout << endl << setprecision(3) << "\t\tSimilarity Index = " << data_of_file.similarity_percentage[0] << "%" << endl;
    test_file << endl << setprecision(3) << "\t\tSimilarity Index = " << data_of_file.similarity_percentage[0] << "%" << endl;
    
    for (i = 1; i <= 5; i ++) {
        cout << setprecision(3) << "Source " << i << "\t= " << data_of_file.similarity_percentage[i] << "%" << endl;
        test_file << setprecision(3) << "Source " << i << "\t= " << data_of_file.similarity_percentage[i] << "%" << endl;    
    }
}

// create a phrase plagiarism check function
void phrase_check(ofstream& test_file) {

    string word, test_word, source_word, test_phrase, source_phrase;
    int test_substring_position, source_substring_position;

    // for (size_t i = 0; i < 100; i++)
    // {
    //     cout << endl << letters.at( i % letters.size() );
    // }

    // for (i = 1; i <= 5; i++) { // for source files 1-5
        
    //     file[0].clear();
    //     file[0].seekg(0); // clear and seek to start for test file, for iteration in the next source file i

    //     while( file[0] >> test_word ) { // iterate through test file, take one word then loop through whole file i

    //         // cout << endl << test_word << endl; // debugging

    //         while ( file[i] >> source_word ) { // iterate through source file i, word by word

    //             // cout << source_word << endl; // debugging

    //             test_substring_position = source_word.find(test_word); // search for the test word substring in source word string, return the position of first character if substring is found, otherwise return -1
    //             source_substring_position = test_word.find(source_word); // search for the source word substring in test word string, return the position of first character if substring is found, otherwise return -1

    //             // cout << test_substring_position << " " << source_substring_position << endl; // debugging

    //             // cross check if substring is found in either of the two
    //             if(test_substring_position != string::npos || source_substring_position != string::npos) { // if either of the positions are not -1 as the substring is found

    //                 // cout << endl << test_word << " " << source_word << endl; // debugging
    //                 // cout << test_word.length() << endl << source_word.length() << endl << endl; // debugging

    //                 // some conditions to meet: must contain at least a letter or number, and length adjustment, for punctuation, "too small vs too large" substring exclusion and similar words (SEE KNOBS ABOVE)
    //                 if ( test_word.find_first_of(letters_numbers) != string::npos && source_word.find_first_of(letters_numbers) != string::npos ) {
    //                     if ( test_word.length() >= min_substring_len && source_word.length() >= min_substring_len ) {
    //                         if ( test_word.length() <= source_word.length() + substring_len_diff_tolerance && test_word.length() >= source_word.length() - substring_len_diff_tolerance ) { // works for length differences in any order

    //                             // cout << endl << test_word << " " << source_word << endl; // debugging
    //                             // cout << test_word.length() << endl << source_word.length() << endl; // debugging

    //                             data_of_file.similar_phrases++; // the main thing. POWER
    //                             break;
    //                         }
    //                     }
    //                 }
    //             }
    //         }
    //     }
    // }

    // Similarity Report for Similar Phrases
    cout << endl << endl << "Total Number of Similar Phrases = " << data_of_file.similar_phrases << endl << "    Similar Phrases/Clauses    Source File" << endl << "    \"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"";
    test_file << endl << endl << "Total Number of Similar Phrases = " << data_of_file.similar_phrases << endl << "    Similar Phrases/Clauses    Source File" << endl << "    \"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"";



    // do
    // {
    //     /* code */
    // } while (test_phrase == source_phrase);
    
    
}


int main() { // main function, with int type that needs an integer to be returned at the end of the function, either by putting "return 0;" or your compiler does that for you anyways

    // input file names, create streams (1 test file, 5 source files). tried many loop methods that failed, apparently you can use: idk what that even is anymore?
    for (i = 0; i <= 5; i++) { // for loop where i starts with a value of 0, increments each time the loop finishes a cycle. the loop terminates when i exceeds 5, so the loop runs 6 times
        string text = (i == 0)? "test" : "source"; // pretty sure we did the shorthand if-else in class, YES IT WAS IN AIKMAN SERIES IF STATEMENTS NOTES
        do { // Just Do It. Seriously, a do-while loop will make sure it executes statements in it at least once, until...
            cout << "Enter file name of the " << text << " file, file " << i << ": "; // cout prints the given text in console. integer i being used for numbering, as text.
            getline(cin, file_names[0][i]); // similar to cin input, getline allows taking in a string WITH spaces as input instead of buffering inputs delimited by spaces. here, integer i is being used for indexing, and the loop means each index stores a different string.
            file[i].open(file_names[0][i]); // tries to open the file name you input, in an input stream
            if (!file[i].is_open()) cout << "Failed to open \"" << file_names[0][i] << "\".\nPlease try again, making sure the file is in the same directory as this code.\n\n"; // if file does not open, cout these statements
            else { cout << "The " << text << " file \"" << file_names[0][i] << "\" opened successfully!\n\n"; continue; } // ELSE, this file has its stream correctly opened, continue to next loop for next file
        } while (!file[i].is_open()); } // ...until the file stream is successful / WHILE the file is NOT open to input stream

    ofstream test_file(file_names[0][0], ios::app); // call a solitary output stream for test file, ios::app appends text to end of file

    // call both plagiarism check functions
    // word check: loop for all 6 files in function above
    word_check(test_file); // Passed an argument to showcase it works lol, if filestreams are global, you don't need to pass their argument, bad on security/code practice but we aren't being judged for a secure code

    // phrase check
    phrase_check(test_file);

    // close streams
    for (i = 0; i <= 5; i++) { file[i].close(); } // a for loop closes all ifstreams
    test_file.close(); // close the ofstream

    return 0; } // terminates the main function by returning code 0 to system; program ends after successful execution