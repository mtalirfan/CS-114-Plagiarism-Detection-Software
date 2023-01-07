#include <iostream> // input/output stream, contains basic statements e.g. cin, cout as part of the "std" (standard) namespace 
#include <string> // string library to use and manipulate strings
#include <fstream> // (both input and output) file stream to manipulate files for data handling
#include <iomanip> // contains manipulators for plagiarism report formatting (in output statements)
#include "SimilarityReporter.h" // a custom header file (that contains a custom class) that will contain code to store numerical data and prepare a similarity report using arithmetic functions and data from word check and phrase check functions
using namespace std; // standard namespace is used so if any scope used in main() isn't available elsewhere, the compiler checks standard library "std" for availability. helps with minimising repetition e.g. cout instead of std::cout

// GLOBAL VARIABLES TO USE IN ALL FUNCTIONS, CLASSES AND STUFF
int i; // size_t i; // (UNSIGNED integer and so good for indexing) (there's a high chance it can cost marks for no reason, you have to go with what you studied in course) // a simple integer named i is initialised, will be used for various loops (LITERALLY ALL OF THEM LMAO) 
string file_names[1][6]; // AH YES, an array of strings (not characters) to store file names, typical jugaar (trick). the first index, [1] WITHOUT the second index [6] would otherwise make an array of characters, which is a single string itself.
ifstream file[6]; // DAMN you can do THAT too, made stuff SO MUCH EASIER, praying that an array of (input) ifstreams is not out of the scope of the FOP course lmao
SimilarityReporter data_of_file; // the indices [6] are in the class file itself // SimilarityReporter custom class to manipulate numerical data
string similar_phrase_data[2][1000]; // stores phrases data. DON'T DECREASE FIRST INDEX: index [0] for source file number, index [1] for phrase string, CAN CHANGE SECOND INDEX: this 2d string array can store [1000] phrase strings and their file numbers

// WORD SIMILARITY CHECK KNOBS (idk what to call them, you change them according to plagiarism need?)
const string letters_numbers = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"; // a constant (that cannot be modified) string of letters and numbers, used in counting words if they contain at least one of these
int min_word_substring_len = 4; // 4 WORKS BEST FOR MOST CASES, AND 1 FOR EXACT; minimum length of substrings to calculate similarity of
int substring_len_diff_tolerance = 2; // 2 WORKS BEST FOR MOST CASES, AND 0 FOR EXACT; difference tolerance between test substring and source substring lengths: length adjustment, for punctuation, "too small vs too large" substring exclusion and similar words
// ABANDONED IDEA: I MEAN THERE'S NO POINT IN MAKING A HUGE SET LIST OF WORDS TO FILTER OUT, UNLESS YOU ARE MODERATING A COMMUNITY AND PEOPLE SPAM SLURS, NSFW AND STUFF: a list of words to ignore if they occur in our word check, but it seems wonky for plagiarism detection
// const string words_list = { "", "", "", "", "", "", "", "",  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "" }; 

// PHRASE SIMILARITY CHECK KNOBS
const string letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"; // alphabet for phrases report listing
int min_phrase_len = 2; // 2 IS REQUIRED IN PROBLEM SET: the minimum number of words to take for checking similarity of the phrase, don't worry, the code will ALWAYS take 1 word

void word_check(ofstream& test_file) { // function of type void that does not return any value to main function, takes in an output stream parameter
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
}

void phrase_check(ofstream& test_file) { // function of type void that does not return any value to main function, takes in an output stream parameter
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
                if ( !file[0].eof() ) { // ... as long as the file doesn't end.
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
                test_words_done = test_words_done + 1; // add just one to test words done, so the next loop takes in the second word from the current phrase, NOT THE FIRST WORD AGAIN AS IT WILL REPEAT THE SAME THING
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
                        test_words_done = test_words_done + 1; // add a count for test words done, because it's done.
                        test_phrase = temp_phrase; // NOW WE HAVE CONFIRMED THE PHRASE WAS SIMILAR
                        file[i].clear();
                        file[i].seekg(0); // clear stream state to goodbit and seek to start for source file i
                        break; // RUN THE WORD ADDING LOOP AGAIN SINCE THE SUBSTRING WAS FOUND, keep on doing until it's not found in which case TEMP PHRASE DOESN'T BECOME TEST PHRASE and we HAVE OUR PHRASE
            }}}

            // if the dumpload of conditions above are passed without the code getting break; or continue; or getting stuck in an infinite loop, we HAVE A SIMILAR PHRASE
            data_of_file.similar_phrase_count++; // increment similar phrase count because WE HAVE A SIMILAR PHRASE FOR THIS ITERATION
            similar_phrase_data[0][data_of_file.similar_phrase_count] = to_string(i); // convert the integer to string, store the source file number in the 2d data array at the unique index equal to current similar phrase count
            similar_phrase_data[1][data_of_file.similar_phrase_count] = test_phrase; // store the actual phrase in the 2d data array at the unique index equal to current similar phrase count
            file[0].clear();
            file[0].seekg(0); // clear stream state to goodbit and seek to position 0 (beginning of file) for test file
            file[i].clear();
            file[i].seekg(0); // clear stream state to goodbit and seek to position 0 (beginning of file) for source file i
    }}

    // Similarity Report for Similar Phrases, using manipulators setw and std::left, and data stored in the class and the 2d string array
    // cout << endl << endl << "Total Number of Similar Phrases = " << data_of_file.similar_phrase_count << endl << "    Similar Phrases/Clauses    Source File" << endl << "    \"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\""; // NOT REQUIRED IN PROBLEM SET
    test_file << endl << endl << "Total Number of Similar Phrases = " << data_of_file.similar_phrase_count << endl << "    Similar Phrases/Clauses    Source File" << endl << "    \"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"";
    
    for (i = 1; i <= data_of_file.similar_phrase_count; i++) { // for loop runs for the number of phrases stored: until all phrases stored in the 2d array are iterated
        // cout << endl << "    " << letters.at( (i - 1) % letters.size() ) << ")  "; // NOT REQUIRED IN PROBLEM SET, the .at() gives the character at the specified position in the letters string, the position is given by the remainder of (i - 1/52) : a-z is 0-25, A-Z is 26-51. i - 1 because we started i from 1, not 0 so we don't start from "b"
        // cout << setw(27) << std::left << similar_phrase_data[1][i]; // NOT REQUIRED IN PROBLEM SET, print the phrase, using formatting
        // cout << " " << similar_phrase_data[0][i]; // NOT REQUIRED IN PROBLEM SET, print the file number for the phrase
        // PRINT THE SAME TO TEST FILE
        test_file << endl << "    " << letters.at( (i - 1) % letters.size() ) << ")  "; // the .at() gives the character at the specified position in the letters string, the position is given by the remainder of (i - 1/52) : a-z is 0-25, A-Z is 26-51. i - 1 because we started i from 1, not 0 so we don't start from "b"
        test_file << setw(27) << std::left << similar_phrase_data[1][i]; // print the phrase, using formatting
        test_file << " " << similar_phrase_data[0][i]; // print the file number for the phrase
    }
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
    
    ofstream test_file(file_names[0][0], ios::app); // call a solitary output stream for test file, ios::app flag appends text to the end of file

    // call both plagiarism check functions
    word_check(test_file); // decided to make ofstream local and pass this argument to showcase it works lol, if filestreams are global, you don't need to pass so many arguments for everything (actually I was unable to pass an array of filestreams lmao), bad on security/code practice but we aren't being judged for a secure code
    phrase_check(test_file); // similarly, a phrase_check function is called after the word_check function successfully executes and control returns to the main function

    // close filestreams after both functions have executed and terminated
    for (i = 0; i <= 5; i++) { file[i].close(); } // for loop closes all ifstreams
    test_file.close(); // close the ofstream separately

    return 0; } // terminates the main function by returning code 0 to system; program ends after successful execution

		Similarity Index = 70.7%
Source 1	= 29.4%
Source 2	= 32.5%
Source 3	= 33.7%
Source 4	= 33.2%
Source 5	= 34.9%


Total Number of Similar Phrases = 1616
    Similar Phrases/Clauses       Source File
    """"""""""""""""""""""""""""""""""""""""""
    a)  #include <iostream> // input/output stream, contains basic statements e.g. cin, cout as part of the "std" (standard) namespace 1
    b)  #include <string> // string library to 1
    c)  manipulate strings             1
    d)  #include <fstream> //          1
    e)  file stream to manipulate files for data handling 1
    f)  for plagiarism                 1
    g)  // a                           1
    h)  to store                       1
    i)  word check                     1
    j)  check functions                1
    k)  using namespace std; // standard namespace is used so if any scope used in main() isn't available elsewhere, the compiler checks standard library "std" for availability. helps with minimising repetition e.g. cout instead of std::cout 1
    l)  int i; // size_t i; // (UNSIGNED integer and so good for indexing) (there's a high chance it can cost marks for no reason, you have to go with what you studied in course) // a simple integer named i is initialised, will be used for various loops (LITERALLY ALL OF THEM LMAO) 1
    m)  string file_names[1][6]; // AH YES, an array of strings (not characters) to store file names, typical jugaar (trick). the first index, [1] WITHOUT the second index [6] would otherwise make an array of characters, which is a single string itself. 1
    n)  ifstream file[6]; // DAMN you can do THAT too, made stuff SO MUCH EASIER, praying that an array of (input) ifstreams is not out of the scope of the FOP course lmao 1
    o)  in the                         1
    p)  to manipulate                  1
    q)  source file                    1
    r)  // a                           1
    s)  used in                        1
    t)  at least                       1
    u)  word check,                    1
    v)  for plagiarism                 1
    w)  of the                         1
    x)  { //                           1
    y)  does not                       1
    z)  main function,                 1
    A)  in an                          1
    B)  output stream                  1
    C)  for (i = 0; i <= 5; i++) { //  1
    D)  loop for                       1
    E)  = 0;                           1
    F)  file i                         1
    G)  in the                         1
    H)  { //                           1
    I)  a word                         1
    J)  file i                         1
    K)  in the                         1
    L)  the file                       1
    M)  if (                           1
    N)  ) { //                         1
    O)  at least                       1
    P)  a single                       1
    Q)  or number                      1
    R)  in a                           1
    S)  the file                       1
    T)  for (i =                       1
    U)  i <= 5; i++) { // for          1
    V)  source files                   1
    W)  test file                      1
    X)  test file,                     1
    Y)  in the                         1
    Z)  source file                    1
    a)  ) { //                         1
    b)  test file,                     1
    c)  file i                         1
    d)  of the                         1
    e)  source file                    1
    f)  file i                         1
    g)  for next                       1
    h)  test file                      1
    i)  source file                    1
    j)  while (                        1
    k)  ) { //                         1
    l)  source file                    1
    m)  the test                       1
    n)  { //                           1
    o)  check if                       1
    p)  of the                         1
    q)  of the                         1
    r)  at least                       1
    s)  if (                           1
    t)  ) { //                         1
    u)  check if                       1
    v)  at least                       1
    w)  if (                           1
    x)  ) { //                         1
    y)  if (                           1
    z)  ) { //                         1
    A)  the main                       1
    B)  // terminates the              1
    C)  test file                      1
    D)  from the                       1
    E)  cout << endl <<                1
    F)  endl <<                        1
    G)  " <<                           1
    H)  << endl;                       1
    I)  test_file <<                   1
    J)  endl <<                        1
    K)  endl <<                        1
    L)  " <<                           1
    M)  << endl;                       1
    N)  the same                       1
    O)  test file,                     1
    P)  for (i =                       1
    Q)  i <= 5; i++) { // for          1
    R)  source files                   1
    S)  cout <<                        1
    T)  << "                           1
    U)  file " << i <<                 1
    V)  test_file <<                   1
    W)  << "                           1
    X)  file " << i <<                 1
    Y)  the same                       1
    Z)  test file,                     1
    a)  } //                           1
    b)  from the                       1
    c)  // call                        1
    d)  in the                         1
    e)  cout << endl <<                1
    f)  endl <<                        1
    g)  " <<                           1
    h)  << endl;                       1
    i)  test_file <<                   1
    j)  endl <<                        1
    k)  endl <<                        1
    l)  " <<                           1
    m)  << endl;                       1
    n)  the same                       1
    o)  test file                      1
    p)  for (i =                       1
    q)  i <= 5; i                      1
    r)  ++) { // for                   1
    s)  source files                   1
    t)  cout <<                        1
    u)  " << i <<                      1
    v)  " <<                           1
    w)  << endl;                       1
    x)  test_file <<                   1
    y)  " << i <<                      1
    z)  " <<                           1
    A)  << endl;                       1
    B)  the same                       1
    C)  test file                      1
    D)  { //                           1
    E)  does not                       1
    F)  main function,                 1
    G)  in an                          1
    H)  output stream                  1
    I)  for various                    1
    J)  for (i =                       1
    K)  i <= 5; i++) { // for          1
    L)  source files                   1
    M)  test file                      1
    N)  source file                    1
    O)  = 0;                           1
    P)  test file                      1
    Q)  while (                        1
    R)  ) { //                         1
    S)  test file                      1
    T)  the loop runs                  1
    U)  for (                          1
    V)  ) {                            1
    W)  } //                           1
    X)  if (                           1
    Y)  // if                          1
    Z)  test file                      1
    a)  to next                        1
    b)  source file                    1
    c)  else {                         1
    d)  the first                      1
    e)  if (                           1
    f)  } //                           1
    g)  test file                      1
    h)  to next                        1
    i)  source file                    1
    j)  for (                          1
    k)  ) { //                         1
    l)  if no                          1
    m)  if (                           1
    n)  ) { //                         1
    o)  the file                       1
    p)  while (                        1
    q)  ) { //                         1
    r)  source file                    1
    s)  does not                       1
    t)  source file                    1
    u)  // check                       1
    v)  is in                          1
    w)  if (                           1
    x)  ) { //                         1
    y)  is not                         1
    z)  to the                         1
    A)  next loop                      1
    B)  source file                    1
    C)  the loop                       1
    D)  if (                           1
    E)  ) { //                         1
    F)  so the                         1
    G)  next loop                      1
    H)  in the                         1
    I)  from the                       1
    J)  test file                      1
    K)  source file                    1
    L)  continue; } //                 1
    M)  the first                      1
    N)  while (                        1
    O)  ) { //                         1
    P)  in a                           1
    Q)  if (                           1
    R)  // if                          1
    S)  test file                      1
    T)  else {                         1
    U)  } while (                      1
    V)  ) { //                         1
    W)  another loop                   1
    X)  make a                         1
    Y)  source file                    1
    Z)  // check                       1
    a)  if (                           1
    b)  ) { //                         1
    c)  source file                    1
    d)  // if                          1
    e)  in an                          1
    f)  integer to                     1
    g)  source file                    1
    h)  in the                         1
    i)  at the                         1
    j)  in the                         1
    k)  at the                         1
    l)  test file                      1
    m)  source file                    1
    n)  in the                         1
    o)  and the                        1
    p)  // cout                        1
    q)  << endl <<                     1
    r)  endl <<                        1
    s)  " <<                           1
    t)  << endl <<                     1
    u)  << endl <<                     1
    v)  test_file <<                   1
    w)  endl <<                        1
    x)  endl <<                        1
    y)  " <<                           1
    z)  << endl <<                     1
    A)  << endl <<                     1
    B)  for (i =                       1
    C)  i <=                           1
    D)  i++) { // for loop             1
    E)  in the                         1
    F)  // cout                        1
    G)  << endl <<                     1
    H)  " <<                           1
    I)  "; //                          1
    J)  at the                         1
    K)  in the                         1
    L)  of (i                          1
    M)  // cout                        1
    N)  // cout                        1
    O)  << "                           1
    P)  " <<                           1
    Q)  the file                       1
    R)  test_file <<                   1
    S)  endl <<                        1
    T)  " <<                           1
    U)  "; //                          1
    V)  at the                         1
    W)  in the                         1
    X)  of (i                          1
    Y)  test_file <<                   1
    Z)  test_file << "                 1
    a)  " <<                           1
    b)  the file                       1
    c)  int main() { // main function, with int type that needs an integer to be returned at the end of the function, either by putting "return 0;" or your compiler does that for you anyways 1
    d)  // input file names, create streams (1 test file, 5 source files). tried many loop methods that failed, apparently you can use: idk what that even is anymore? 1
    e)  for (i = 0; i <= 5; i++) { // for loop where i starts with a value of 0, increments each time the loop finishes a cycle. the loop terminates when i exceeds 5, so the loop runs 6 times 1
    f)  string text = (i == 0)? "test" : "source"; // pretty sure we did the shorthand if-else in class, YES IT WAS IN AIKMAN SERIES IF STATEMENTS NOTES 1
    g)  do { // Just Do It. Seriously, a do-while loop will make sure it executes statements in it at least once, until... 1
    h)  cout <<                        1
    i)  file name of the " << text << " file, file " << i << ": "; // cout prints the given text in console. integer i being used for numbering, as text. 1
    j)  getline(cin, file_names[0][i]); // similar to cin input, getline allows taking in a string WITH spaces as input instead of buffering inputs delimited by spaces. here, integer i is being used for indexing, and the loop means each index stores a different string. 1
    k)  file[i].open(file_names[0][i]); // tries to open the file name you input, in an input stream 1
    l)  if (!file[i].is_open()) cout << 1
    m)  to open \"" << file_names[0][i] << "\".\nPlease try again, making sure the file is in the same directory as this code.\n\n"; // if file does not open, cout these statements 1
    n)  else { cout <<                 1
    o)  " << text << " file            1
    p)  \"" << file_names[0][i] << "\" opened successfully!\n\n"; continue; } // ELSE, this file has its stream correctly opened, continue to next loop for next file 1
    q)  } while (!file[i].is_open()); } // ...until the file stream is successful / WHILE the file is NOT open to input stream 1
    r)  ofstream test_file(file_names[0][0], ios::app); 1
    s)  // call                        1
    t)  output stream                  1
    u)  test file,                     1
    v)  to the                         1
    w)  end of                         1
    x)  // call both plagiarism check functions 1
    y)  an array of                    1
    z)  for a                          1
    A)  to the                         1
    B)  main function                  1
    C)  // close                       1
    D)  for (i = 0; i <= 5; i++) { file[i].close(); } // 1
    E)  for loop closes all ifstreams  1
    F)  test_file.close(); // close the ofstream 1
    G)  return 0; } // terminates the main function by returning code 0 to system; program ends after successful execution 1
    H)  #include <iostream> // input/output stream, contains basic statements e.g. cin, cout as part of the "std" (standard) namespace 2
    I)  #include <string> // string library to 2
    J)  manipulate strings             2
    K)  #include <fstream> // (both input and output) file stream to manipulate files for data handling 2
    L)  for plagiarism                 2
    M)  #include "SimilarityReporter.h" // a custom 2
    N)  a custom                       2
    O)  that will contain code to store numerical data and prepare a similarity report using 2
    P)  data from word check and phrase check functions 2
    Q)  using namespace std; // standard namespace is used so if any scope used in main() isn't available elsewhere, the compiler checks standard library "std" for availability. helps with minimising repetition e.g. cout instead of std::cout 2
    R)  // GLOBAL VARIABLES TO USE IN ALL FUNCTIONS, CLASSES AND STUFF 2
    S)  int i; // size_t i; // (UNSIGNED integer and so good for indexing) (there's a high chance it can cost marks for no reason, you have to go with what you studied in course) // a simple integer named i is initialised, will be used for various loops (LITERALLY ALL OF THEM LMAO) 2
    T)  string file_names[1][6]; // AH YES, an array of strings (not characters) to store file names, typical jugaar (trick). the first index, [1] WITHOUT the second index [6] would otherwise make an array of characters, which is a single string itself. 2
    U)  ifstream file[6]; // DAMN you can do THAT too, made stuff SO MUCH EASIER, praying that an array of (input) ifstreams is not out of the scope of the FOP course lmao 2
    V)  in the                         2
    W)  custom class to manipulate numerical data 2
    X)  source file                    2
    Y)  // a                           2
    Z)  used in                        2
    a)  at least                       2
    b)  similar words                  2
    c)  for plagiarism                 2
    d)  number of                      2
    e)  of the                         2
    f)  { // function of type void that does not return any value to main 2
    g)  in an                          2
    h)  output stream                  2
    i)  string word, test_word, source_word; // 2
    j)  // COUNT TOTAL WORDS           2
    k)  EACH FILE                      2
    l)  for (i = 0; i <= 5; i++) { //  2
    m)  loop for                       2
    n)  = 0;                           2
    o)  // initialise                  2
    p)  file i                         2
    q)  in the                         2
    r)  of type                        2
    s)  while(file[i] >> word) { //    2
    t)  a word                         2
    u)  from file                      2
    v)  in the                         2
    w)  the file                       2
    x)  if (                           2
    y)  != string::npos                2
    z)  ) { //                         2
    A)  at least                       2
    B)  a single                       2
    C)  or number                      2
    D)  in a                           2
    E)  in code                        2
    F)  the file                       2
    G)  // ACTUAL WORD PLAGIARISM CHECK 2
    H)  for (i = 1; i <= 5; i++) {     2
    I)  // for                         2
    J)  source files                   2
    K)  test file                      2
    L)  test file,                     2
    M)  in the                         2
    N)  source file                    2
    O)  while( file[0] >> test_word ) { // 2
    P)  through test                   2
    Q)  loop through                   2
    R)  file i                         2
    S)  of the                         2
    T)  source file                    2
    U)  file i                         2
    V)  for next                       2
    W)  test file                      2
    X)  through source file            2
    Y)  while ( file[i] >> source_word ) { // 2
    Z)  through source file            2
    a)  = source_word.find(test_word); // search for 2
    b)  the test                       2
    c)  substring in                   2
    d)  // search for                  2
    e)  substring in                   2
    f)  != string::npos                2
    g)  != string::npos)               2
    h)  { //                           2
    i)  check if                       2
    j)  is found                       2
    k)  of the                         2
    l)  of the                         2
    m)  is found                       2
    n)  at least                       2
    o)  similar words                  2
    p)  if (                           2
    q)  != string::npos                2
    r)  != string::npos                2
    s)  ) { //                         2
    t)  check if                       2
    u)  at least                       2
    v)  string in                      2
    w)  if (                           2
    x)  ) { //                         2
    y)  if (                           2
    z)  ) { //                         2
    A)  similar word                   2
    B)  the main                       2
    C)  // terminates the              2
    D)  test file                      2
    E)  // Similarity Report for Similar 2
    F)  data and                       2
    G)  from the                       2
    H)  cout << endl <<                2
    I)  endl <<                        2
    J)  << "Total number of similar words found = " << 2
    K)  << endl;                       2
    L)  // test_file <<                2
    M)  endl <<                        2
    N)  endl <<                        2
    O)  << "Total number of similar words found = " << 2
    P)  << endl;                       2
    Q)  the same                       2
    R)  test file,                     2
    S)  for (i = 1; i <= 5; i++) {     2
    T)  // for                         2
    U)  source files                   2
    V)  cout <<                        2
    W)  << " from file " << i << endl; 2
    X)  // test_file <<                2
    Y)  << " from file " << i << endl; 2
    Z)  the same                       2
    a)  test file,                     2
    b)  } //                           2
    c)  Similarity Report for          2
    d)  data and                       2
    e)  from the                       2
    f)  // call                        2
    g)  in the                         2
    h)  class that                     2
    i)  cout << endl <<                2
    j)  endl <<                        2
    k)  = " <<                         2
    l)  << endl;                       2
    m)  test_file <<                   2
    n)  endl <<                        2
    o)  endl <<                        2
    p)  = " <<                         2
    q)  << endl;                       2
    r)  the same                       2
    s)  test file                      2
    t)  for (i = 1; i <= 5; i          2
    u)  ++) { // for                   2
    v)  source files                   2
    w)  cout <<                        2
    x)  " << i <<                      2
    y)  " <<                           2
    z)  << endl;                       2
    A)  test_file <<                   2
    B)  " << i <<                      2
    C)  " <<                           2
    D)  << endl;                       2
    E)  the same                       2
    F)  test file                      2
    G)  { // function of type void that does not return any value to main 2
    H)  in an                          2
    I)  output stream                  2
    J)  for various                    2
    K)  for (i = 1; i <= 5; i++) {     2
    L)  // for                         2
    M)  source files                   2
    N)  test file                      2
    O)  source file                    2
    P)  = 0;                           2
    Q)  // initialise                  2
    R)  test file                      2
    S)  while (                        2
    T)  ) { //                         2
    U)  test file                      2
    V)  the loop runs                  2
    W)  for (                          2
    X)  j =                            2
    Y)  j <=                           2
    Z)  ) {                            2
    a)  file[0] >>                     2
    b)  } //                           2
    c)  if (                           2
    d)  // if                          2
    e)  test file                      2
    f)  to next                        2
    g)  source file                    2
    h)  else {                         2
    i)  the first                      2
    j)  phrase check                   2
    k)  file[0] >>                     2
    l)  if (                           2
    m)  } //                           2
    n)  test file                      2
    o)  to next                        2
    p)  source file                    2
    q)  for (                          2
    r)  j =                            2
    s)  j <=                           2
    t)  ) { //                         2
    u)  if no                          2
    v)  if (                           2
    w)  ) { //                         2
    x)  the file                       2
    y)  file[0] >>                     2
    z)  // ACTUAL                      2
    A)  PLAGIARISM CHECK               2
    B)  while (                        2
    C)  ) { //                         2
    D)  source file                    2
    E)  does not                       2
    F)  source file                    2
    G)  // check                       2
    H)  is in                          2
    I)  if (                           2
    J)  != string::npos                2
    K)  ) { //                         2
    L)  is not                         2
    M)  number of                      2
    N)  to the                         2
    O)  next loop                      2
    P)  source file                    2
    Q)  the loop                       2
    R)  if (                           2
    S)  ) { //                         2
    T)  not found                      2
    U)  so the                         2
    V)  next loop                      2
    W)  in the                         2
    X)  from the                       2
    Y)  test file                      2
    Z)  source file                    2
    a)  continue; } //                 2
    b)  phrase check                   2
    c)  the first                      2
    d)  for word                       2
    e)  while (                        2
    f)  != string::npos                2
    g)  ) { //                         2
    h)  in a                           2
    i)  if (                           2
    j)  // if                          2
    k)  test file                      2
    l)  else {                         2
    m)  file[0] >>                     2
    n)  } while (                      2
    o)  ) { //                         2
    p)  another loop                   2
    q)  had to                         2
    r)  make a                         2
    s)  source file                    2
    t)  // check                       2
    u)  if (                           2
    v)  != string::npos                2
    w)  ) { //                         2
    x)  source file                    2
    y)  not found                      2
    z)  // if                          2
    A)  in an                          2
    B)  integer to                     2
    C)  source file                    2
    D)  in the                         2
    E)  at the                         2
    F)  in the                         2
    G)  at the                         2
    H)  test file                      2
    I)  source file                    2
    J)  // Similarity Report for Similar 2
    K)  in the                         2
    L)  and the                        2
    M)  // cout << endl <<             2
    N)  endl <<                        2
    O)  = " <<                         2
    P)  << endl <<                     2
    Q)  << endl <<                     2
    R)  test_file <<                   2
    S)  endl <<                        2
    T)  endl <<                        2
    U)  = " <<                         2
    V)  << endl <<                     2
    W)  << endl <<                     2
    X)  for (i = 1; i <=               2
    Y)  i++) { // for loop             2
    Z)  number of                      2
    a)  in the                         2
    b)  // cout << endl <<             2
    c)  " <<                           2
    d)  ) <<                           2
    e)  "; //                          2
    f)  at the                         2
    g)  in the                         2
    h)  of (i                          2
    i)  // cout <<                     2
    j)  // cout <<                     2
    k)  " <<                           2
    l)  the file                       2
    m)  test_file <<                   2
    n)  endl <<                        2
    o)  " <<                           2
    p)  ) <<                           2
    q)  "; //                          2
    r)  at the                         2
    s)  in the                         2
    t)  of (i                          2
    u)  test_file <<                   2
    v)  test_file << "                 2
    w)  " <<                           2
    x)  the file                       2
    y)  int main() { // main function, with int type that needs an integer to be returned at the end of the function, either by putting "return 0;" or your compiler does that for you anyways 2
    z)  // input file names, create streams (1 test file, 5 source files). tried many loop methods that failed, apparently you can use: idk what that even is anymore? 2
    A)  for (i = 0; i <= 5; i++) { // for loop where i starts with a value of 0, increments each time the loop finishes a cycle. the loop terminates when i exceeds 5, so the loop runs 6 times 2
    B)  string text = (i == 0)? "test" : "source"; // pretty sure we did the shorthand if-else in class, YES IT WAS IN AIKMAN SERIES IF STATEMENTS NOTES 2
    C)  do { // Just Do It. Seriously, a do-while loop will make sure it executes statements in it at least once, until... 2
    D)  cout <<                        2
    E)  file name of the " << text << " file, file " << i << ": "; // cout prints the given text in console. integer i being used for numbering, as text. 2
    F)  getline(cin, file_names[0][i]); // similar to cin input, getline allows taking in a string WITH spaces as input instead of buffering inputs delimited by spaces. here, integer i is being used for indexing, and the loop means each index stores a different string. 2
    G)  file[i].open(file_names[0][i]); // tries to open the file name you input, in an input stream 2
    H)  if (!file[i].is_open()) cout << 2
    I)  to open \"" << file_names[0][i] << "\".\nPlease try again, making sure the file is in the same directory as this code.\n\n"; // if file does not open, cout these statements 2
    J)  else { cout <<                 2
    K)  " << text << " file            2
    L)  \"" << file_names[0][i] << "\" opened successfully!\n\n"; continue; } // ELSE, this file has its stream correctly opened, continue to next loop for next file 2
    M)  } while (!file[i].is_open()); } // ...until the file stream is successful / WHILE the file is NOT open to input stream 2
    N)  ofstream test_file(file_names[0][0], ios::app); 2
    O)  // call                        2
    P)  output stream                  2
    Q)  test file,                     2
    R)  to the                         2
    S)  end of                         2
    T)  // call both plagiarism check functions 2
    U)  if filestreams are global, you don't need to pass 2
    V)  to pass                        2
    W)  an array of                    2
    X)  bad on security/code practice but we aren't being judged for a secure code 2
    Y)  to the                         2
    Z)  main function                  2
    a)  // close                       2
    b)  for (i = 0; i <= 5; i++) { file[i].close(); } // 2
    c)  for loop closes all ifstreams  2
    d)  test_file.close(); // close the ofstream 2
    e)  return 0; } // terminates the main function by returning code 0 to system; program ends after successful execution 2
    f)  #include <iostream> // input/output stream, contains basic statements e.g. cin, cout as part of the "std" (standard) namespace 3
    g)  #include <string> // string library to 3
    h)  manipulate strings             3
    i)  #include <fstream> // (both input and output) file stream to manipulate files for data handling 3
    j)  #include <iomanip> //          3
    k)  report formatting              3
    l)  #include "SimilarityReporter.h" // a custom 3
    m)  a custom                       3
    n)  that will contain code to store numerical data and prepare a similarity report using 3
    o)  data from word check and phrase check functions 3
    p)  using namespace std; // standard namespace is used so if any scope used in main() isn't available elsewhere, the compiler checks standard library "std" for availability. helps with minimising repetition e.g. cout instead of std::cout 3
    q)  // GLOBAL VARIABLES TO USE IN ALL FUNCTIONS, CLASSES AND STUFF 3
    r)  int i; // size_t i; // (UNSIGNED integer and so good for indexing) (there's a high chance it can cost marks for no reason, you have to go with what you studied in course) // a simple integer named i is initialised, will be used for various loops (LITERALLY ALL OF THEM LMAO) 3
    s)  string file_names[1][6]; // AH YES, an array of strings (not characters) to store file names, typical jugaar (trick). the first index, [1] WITHOUT the second index [6] would otherwise make an array of characters, which is a single string itself. 3
    t)  ifstream file[6]; // DAMN you can do THAT too, made stuff SO MUCH EASIER, praying that an array of (input) ifstreams is not out of the scope of the FOP course lmao 3
    u)  SimilarityReporter data_of_file; // the 3
    v)  in the class file itself //    3
    w)  custom class to manipulate numerical data 3
    x)  for source file                3
    y)  // WORD SIMILARITY CHECK KNOBS (idk what to call them, you change them according to plagiarism need?) 3
    z)  const string letters_numbers = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"; // a constant (that cannot be modified) string of letters and 3
    A)  used in                        3
    B)  contain at least               3
    C)  = 4; //                        3
    D)  minimum length of substrings to calculate similarity of 3
    E)  int substring_len_diff_tolerance = 2; // 3
    F)  difference tolerance between test substring and source substring lengths: length adjustment, for punctuation, "too small vs too large" substring exclusion and similar words 3
    G)  of words                       3
    H)  // const string                3
    I)  = {                            3
    J)  }; //                          3
    K)  PHRASE SIMILARITY CHECK KNOBS  3
    L)  const string letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"; 3
    M)  = 2; //                        3
    N)  REQUIRED IN PROBLEM            3
    O)  number of                      3
    P)  similarity of                  3
    Q)  void word_check(ofstream& test_file) { // function of type void that does not return any value to main function, takes in an output stream parameter 3
    R)  string word, test_word, source_word; // 3
    S)  int test_substring_position, source_substring_position; // 3
    T)  substring positions for searches 3
    U)  // COUNT TOTAL WORDS           3
    V)  for (i = 0; i <= 5; i++) { //  3
    W)  loop for                       3
    X)  data_of_file.word_count[i] = 0; 3
    Y)  // initialise                  3
    Z)  word count                     3
    a)  file i                         3
    b)  in the                         3
    c)  of type                        3
    d)  while(file[i] >> word) {       3
    e)  from file                      3
    f)  in the                         3
    g)  the file                       3
    h)  if ( word.find_first_of(letters_numbers) != string::npos ) { // we haven't studied find_first_of in 3
    i)  so... anyways, if there is at least a single letter or number in a string, helps reduce word count of non-word symbols in code plagiarism 3
    j)  data_of_file.word_count[i]++; // count the word 3
    k)  for the                        3
    l)  file i,                        3
    m)  // ACTUAL WORD PLAGIARISM CHECK 3
    n)  for (i = 1; i <= 5; i++) { // for source files 1-5 3
    o)  // clear                       3
    p)  test file to                   3
    q)  // seek                        3
    r)  to beginning for               3
    s)  test file, for iteration in the next source file i 3
    t)  while( file[0] >> test_word ) { // iterate through test file, take one word then loop through whole file i 3
    u)  of the                         3
    v)  // clear                       3
    w)  for source file                3
    x)  i to                           3
    y)  // seek file i to beginning for next word in test file to iterate through source file 3
    z)  while ( file[i] >> source_word ) { // iterate through source file i, word by word 3
    A)  test_substring_position = source_word.find(test_word); // search for the test word substring in source word string, return the position of first character if substring is found, otherwise return -1 3
    B)  source_substring_position = test_word.find(source_word); // search for the source word substring in test word string, return the position of first character if substring is found, otherwise return -1 3
    C)  if(test_substring_position != string::npos || source_substring_position != string::npos) { // 3
    D)  cross check if substring is found in either of the 3
    E)  if either of the positions are not -1 as the substring is found 3
    F)  // some conditions to meet: must contain at least a letter or number, and length adjustment, for punctuation, "too small vs too large" substring exclusion and similar words (SEE KNOBS ABOVE) 3
    G)  if ( test_word.find_first_of(letters_numbers) != string::npos && source_word.find_first_of(letters_numbers) != string::npos ) { 3
    H)  check if                       3
    I)  contain at least a             3
    J)  string in                      3
    K)  if ( test_word.length() >=     3
    L)  && source_word.length() >=     3
    M)  ) { //                         3
    N)  if ( test_word.length() <= source_word.length() + substring_len_diff_tolerance && test_word.length() >= source_word.length() - substring_len_diff_tolerance ) { // 3
    O)  length adjustment, for punctuation, "too small vs too large" substring exclusion and similar 3
    P)  works for length differences in any 3
    Q)  data_of_file.similar_words[i]++; // 3
    R)  similar word                   3
    S)  the main thing. POWER          3
    T)  // terminates the              3
    U)  source word                    3
    V)  the next                       3
    W)  word in test file              3
    X)  // Similarity Report for Similar 3
    Y)  data and                       3
    Z)  the class                      3
    a)  cout << endl << endl << setw(0) << "Total number of similar words found = " << data_of_file.sum_similar_words() << endl; 3
    b)  // test_file << endl << endl << setw(0) << "Total number of similar words found = " << data_of_file.sum_similar_words() << endl; // 3
    c)  the same                       3
    d)  test file,                     3
    e)  NOT REQUIRED IN PROBLEM SET    3
    f)  for (i = 1; i <= 5; i++) { // for source files 1-5 3
    g)  cout << setw(15) << data_of_file.similar_words[i] << " from file " << i << endl; 3
    h)  // test_file << setw(15) << data_of_file.similar_words[i] << " from file " << i << endl; // 3
    i)  the same                       3
    j)  test file,                     3
    k)  NOT REQUIRED IN PROBLEM SET    3
    l)  } //                           3
    m)  Similarity Report for Similarity Index 3
    n)  data and                       3
    o)  the class                      3
    p)  // call a                      3
    q)  in the class                   3
    r)  cout << endl << endl <<        3
    s)  setprecision(3) << "\t\tSimilarity Index = " << data_of_file.similarity_percentage[0] << "%" << endl; 3
    t)  test_file << endl << endl <<   3
    u)  setprecision(3) << "\t\tSimilarity Index = " << data_of_file.similarity_percentage[0] << "%" << endl; 3
    v)  the same                       3
    w)  test file                      3
    x)  for (i = 1; i <= 5; i ++) {    3
    y)  // for source files 1-5        3
    z)  cout << setprecision(3) << "Source " << i << "\t= " << data_of_file.similarity_percentage[i] << "%" << endl; 3
    A)  test_file << setprecision(3) << "Source " << i << "\t= " << data_of_file.similarity_percentage[i] << "%" << endl; 3
    B)  the same                       3
    C)  test file                      3
    D)  void phrase_check(ofstream& test_file) { 3
    E)  // function of type void that does not return any value to main function, takes in an output stream parameter 3
    F)  int test_substring_position,   3
    G)  for various                    3
    H)  for (i = 1; i <= 5; i++) { // for source files 1-5 3
    I)  file[0].seekg(0); // clear     3
    J)  and seek to                    3
    K)  for test file                  3
    L)  file[i].seekg(0); //           3
    M)  and seek to                    3
    N)  for source file                3
    O)  = 0;                           3
    P)  // initialise                  3
    Q)  in test file                   3
    R)  while (                        3
    S)  ) { //                         3
    T)  test file                      3
    U)  the loop runs                  3
    V)  for (                          3
    W)  = 1;                           3
    X)  ) {                            3
    Y)  file[0] >>                     3
    Z)  } //                           3
    a)  if (                           3
    b)  // if                          3
    c)  test file                      3
    d)  to next                        3
    e)  source file                    3
    f)  else {                         3
    g)  the first                      3
    h)  phrase check                   3
    i)  file[0] >>                     3
    j)  test_phrase =                  3
    k)  if (                           3
    l)  } //                           3
    m)  test file                      3
    n)  to next                        3
    o)  source file                    3
    p)  for (                          3
    q)  = 1;                           3
    r)  ) { // if                      3
    s)  if (                           3
    t)  ) { //                         3
    u)  as the                         3
    v)  file[0] >>                     3
    w)  test_phrase =                  3
    x)  " "                            3
    y)  // ACTUAL                      3
    z)  PLAGIARISM CHECK               3
    A)  while (                        3
    B)  ) { //                         3
    C)  source file                    3
    D)  does not                       3
    E)  source file                    3
    F)  test_substring_position =      3
    G)  check if                       3
    H)  is in                          3
    I)  if (                           3
    J)  test_substring_position != string::npos 3
    K)  ) { // if                      3
    L)  is not                         3
    M)  number of                      3
    N)  words in                       3
    O)  next loop                      3
    P)  file[i].seekg(0); //           3
    Q)  and seek to start for          3
    R)  source file i                  3
    S)  the loop                       3
    T)  if (                           3
    U)  string::npos ) { //            3
    V)  if the                         3
    W)  so the                         3
    X)  next loop                      3
    Y)  takes in                       3
    Z)  the second                     3
    a)  file[0].seekg(0); // clear     3
    b)  and seek to                    3
    c)  for test file                  3
    d)  file[i].seekg(0); //           3
    e)  and seek to                    3
    f)  for source file                3
    g)  continue; } //                 3
    h)  the next                       3
    i)  phrase check                   3
    j)  the first                      3
    k)  word in                        3
    l)  word by word                   3
    m)  while (                        3
    n)  test_substring_position != string::npos 3
    o)  ) { //                         3
    p)  string is found,               3
    q)  in a                           3
    r)  if (                           3
    s)  // if                          3
    t)  test file                      3
    u)  else {                         3
    v)  test word                      3
    w)  to a                           3
    x)  file[0] >>                     3
    y)  " "                            3
    z)  } while (                      3
    A)  ) { //                         3
    B)  loop for                       3
    C)  make a                         3
    D)  source file                    3
    E)  test_substring_position =      3
    F)  check if                       3
    G)  in any                         3
    H)  if (                           3
    I)  test_substring_position != string::npos 3
    J)  ) { // if                      3
    K)  for test                       3
    L)  test_phrase =                  3
    M)  file[i].seekg(0); //           3
    N)  and seek to start for          3
    O)  source file i                  3
    P)  found in                       3
    Q)  // if                          3
    R)  in an                          3
    S)  integer to                     3
    T)  the source                     3
    U)  number in                      3
    V)  at the                         3
    W)  in the                         3
    X)  at the                         3
    Y)  file[0].seekg(0); // clear     3
    Z)  and seek to                    3
    a)  for test file                  3
    b)  file[i].seekg(0); //           3
    c)  and seek to                    3
    d)  for source file                3
    e)  // Similarity Report for Similar 3
    f)  in the class                   3
    g)  and the                        3
    h)  // cout << endl <<             3
    i)  endl << "Total Number of Similar Phrases = " << 3
    j)  << endl << "                   3
    k)  Similar Phrases/Clauses        3
    l)  Source File" << endl << "      3
    m)  // NOT REQUIRED IN PROBLEM SET 3
    n)  test_file << endl << endl << "Total Number of Similar Phrases = " << 3
    o)  << endl << "                   3
    p)  Similar Phrases/Clauses        3
    q)  Source File" << endl << "      3
    r)  for (i = 1; i <=               3
    s)  i++) { // for loop             3
    t)  for the                        3
    u)  number of                      3
    v)  in the                         3
    w)  // cout << endl << "           3
    x)  " <<                           3
    y)  % letters.size() )             3
    z)  "; //                          3
    A)  NOT REQUIRED IN PROBLEM        3
    B)  at the                         3
    C)  in the                         3
    D)  the position                   3
    E)  of (i                          3
    F)  // cout <<                     3
    G)  // NOT REQUIRED IN PROBLEM     3
    H)  // cout <<                     3
    I)  " " <<                         3
    J)  // NOT REQUIRED IN PROBLEM     3
    K)  the file                       3
    L)  for the                        3
    M)  test_file << endl <<           3
    N)  " " <<                         3
    O)  % letters.size() )             3
    P)  "; //                          3
    Q)  at the                         3
    R)  in the                         3
    S)  the position                   3
    T)  of (i                          3
    U)  test_file <<                   3
    V)  test_file <<                   3
    W)  " " <<                         3
    X)  the file                       3
    Y)  for the                        3
    Z)  int main() { // main function, with int type that needs an integer to be returned at the end of the function, either by putting "return 0;" or your compiler does that for you anyways 3
    a)  // input file names, create streams (1 test file, 5 source files). tried many loop methods that failed, apparently you can use: idk what that even is anymore? 3
    b)  for (i = 0; i <= 5; i++) { // for loop where i starts with a value of 0, increments each time the loop finishes a cycle. the loop terminates when i exceeds 5, so the loop runs 6 times 3
    c)  string text = (i == 0)? "test" : "source"; // pretty sure we did the shorthand if-else in class, YES IT WAS IN AIKMAN SERIES IF STATEMENTS NOTES 3
    d)  do { // Just Do It. Seriously, a do-while loop will make sure it executes statements in it at least once, until... 3
    e)  cout << "Enter file name of the " << text << " file, file " << i << ": "; // cout prints the given text in console. integer i being used for numbering, as text. 3
    f)  getline(cin, file_names[0][i]); // similar to cin input, getline allows taking in a string WITH spaces as input instead of buffering inputs delimited by spaces. here, integer i is being used for indexing, and the loop means each index stores a different string. 3
    g)  file[i].open(file_names[0][i]); // tries to open the file name you input, in an input stream 3
    h)  if (!file[i].is_open()) cout << "Failed to open \"" << file_names[0][i] << "\".\nPlease try again, making sure the file is in the same directory as this code.\n\n"; // if file does not open, cout these statements 3
    i)  else { cout << "The " << text << " file \"" << file_names[0][i] << "\" opened successfully!\n\n"; continue; } // ELSE, this file has its stream correctly opened, continue to next loop for next file 3
    j)  } while (!file[i].is_open()); } // ...until the file stream is successful / WHILE the file is NOT open to input stream 3
    k)  ofstream test_file(file_names[0][0], ios::app); // call a solitary output stream for test file, ios::app 3
    l)  appends text to                3
    m)  the end of                     3
    n)  // call both plagiarism check functions 3
    o)  word_check(test_file); //      3
    p)  argument to showcase it works lol, if filestreams are global, you don't need to pass 3
    q)  to pass                        3
    r)  an array of                    3
    s)  bad on security/code practice but we aren't being judged for a secure code 3
    t)  the main function              3
    u)  // close                       3
    v)  for (i = 0; i <= 5; i++) { file[i].close(); } // 3
    w)  for loop closes all ifstreams  3
    x)  test_file.close(); // close the ofstream 3
    y)  return 0; } // terminates the main function by returning code 0 to system; program ends after successful execution 3
    z)  #include <iostream> // input/output stream, contains basic statements e.g. cin, cout as part of the "std" (standard) namespace 4
    A)  #include <string> // string library to 4
    B)  manipulate strings             4
    C)  #include <fstream> // (both input and output) file stream to manipulate files for data handling 4
    D)  #include <iomanip> //          4
    E)  report formatting              4
    F)  #include "SimilarityReporter.h" // a custom 4
    G)  a custom                       4
    H)  that will contain code to store numerical data and prepare a similarity report using 4
    I)  data from word check and phrase check functions 4
    J)  using namespace std; // standard namespace is used so if any scope used in main() isn't available elsewhere, the compiler checks standard library "std" for availability. helps with minimising repetition e.g. cout instead of std::cout 4
    K)  // GLOBAL VARIABLES TO USE IN ALL FUNCTIONS, CLASSES AND STUFF 4
    L)  int i; // size_t i; // (UNSIGNED integer and so good for indexing) (there's a high chance it can cost marks for no reason, you have to go with what you studied in course) // a simple integer named i is initialised, will be used for various loops (LITERALLY ALL OF THEM LMAO) 4
    M)  string file_names[1][6]; // AH YES, an array of strings (not characters) to store file names, typical jugaar (trick). the first index, [1] WITHOUT the second index [6] would otherwise make an array of characters, which is a single string itself. 4
    N)  ifstream file[6]; // DAMN you can do THAT too, made stuff SO MUCH EASIER, praying that an array of (input) ifstreams is not out of the scope of the FOP course lmao 4
    O)  SimilarityReporter data_of_file; // the 4
    P)  in the class file itself //    4
    Q)  custom class to manipulate numerical data 4
    R)  string similar_phrase_data[2][1000]; // 4
    S)  index [0] for source file number, index [1] for phrase 4
    T)  // WORD SIMILARITY CHECK KNOBS (idk what to call them, you change them according to plagiarism need?) 4
    U)  const string letters_numbers = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"; // a constant (that cannot be modified) string of letters and 4
    V)  used in                        4
    W)  contain at least               4
    X)  = 4; //                        4
    Y)  minimum length of substrings to calculate similarity of 4
    Z)  int substring_len_diff_tolerance = 2; // 4
    a)  difference tolerance between test substring and source substring lengths: length adjustment, for punctuation, "too small vs too large" substring exclusion and similar words 4
    b)  of words                       4
    c)  // const string                4
    d)  = {                            4
    e)  }; //                          4
    f)  PHRASE SIMILARITY CHECK KNOBS  4
    g)  const string letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"; 4
    h)  int min_phrase_len =           4
    i)  2; //                          4
    j)  REQUIRED IN PROBLEM            4
    k)  number of                      4
    l)  similarity of                  4
    m)  void word_check(ofstream& test_file) { // function of type void that does not return any value to main function, takes in an output stream parameter 4
    n)  string word, test_word, source_word; // 4
    o)  int test_substring_position, source_substring_position; // 4
    p)  substring positions for searches 4
    q)  // COUNT TOTAL WORDS OF EACH FILE 4
    r)  for (i = 0; i <= 5; i++) { //  4
    s)  loop for                       4
    t)  data_of_file.word_count[i] = 0; 4
    u)  // initialise                  4
    v)  word count                     4
    w)  file i                         4
    x)  in the                         4
    y)  of type                        4
    z)  while(file[i] >> word) {       4
    A)  from file                      4
    B)  in the                         4
    C)  the file                       4
    D)  if ( word.find_first_of(letters_numbers) != string::npos ) { // we haven't studied find_first_of in 4
    E)  so... anyways, if there is at least a single letter or number in a string, helps reduce word count of non-word symbols in code plagiarism 4
    F)  data_of_file.word_count[i]++; // count the word 4
    G)  for the                        4
    H)  file i,                        4
    I)  // ACTUAL WORD PLAGIARISM CHECK 4
    J)  for (i = 1; i <= 5; i++) { // for source files 1-5 4
    K)  // clear                       4
    L)  test file to                   4
    M)  // seek                        4
    N)  to beginning for               4
    O)  test file, for iteration in the next source file i 4
    P)  while( file[0] >> test_word ) { // iterate through test file, take one word then loop through whole file i 4
    Q)  of the                         4
    R)  // clear                       4
    S)  for source file i              4
    T)  // seek file i to beginning for next word in test file to iterate through source file 4
    U)  while ( file[i] >> source_word ) { // iterate through source file i, word by word 4
    V)  test_substring_position = source_word.find(test_word); // search for the test word substring in source word string, return the position of first character if substring is found, otherwise return -1 4
    W)  source_substring_position = test_word.find(source_word); // search for the source word substring in test word string, return the position of first character if substring is found, otherwise return -1 4
    X)  if(test_substring_position != string::npos || source_substring_position != string::npos) { // 4
    Y)  cross check if substring is found in either of the 4
    Z)  if either of the positions are not -1 as the substring is found 4
    a)  // some conditions to meet: must contain at least a letter or number, and length adjustment, for punctuation, "too small vs too large" substring exclusion and similar words (SEE KNOBS ABOVE) 4
    b)  if ( test_word.find_first_of(letters_numbers) != string::npos && source_word.find_first_of(letters_numbers) != string::npos ) { 4
    c)  check if                       4
    d)  contain at least a             4
    e)  string in                      4
    f)  if ( test_word.length() >=     4
    g)  && source_word.length() >=     4
    h)  ) { //                         4
    i)  if ( test_word.length() <= source_word.length() + substring_len_diff_tolerance && test_word.length() >= source_word.length() - substring_len_diff_tolerance ) { // 4
    j)  length adjustment, for punctuation, "too small vs too large" substring exclusion and similar 4
    k)  works for length differences in any 4
    l)  data_of_file.similar_words[i]++; // 4
    m)  similar word                   4
    n)  the main thing. POWER          4
    o)  // terminates the              4
    p)  source word                    4
    q)  the next                       4
    r)  word in test file              4
    s)  // Similarity Report for Similar 4
    t)  data and                       4
    u)  the class                      4
    v)  cout << endl << endl << setw(0) << "Total number of similar words found = " << data_of_file.sum_similar_words() << endl; 4
    w)  // test_file << endl << endl << setw(0) << "Total number of similar words found = " << data_of_file.sum_similar_words() << endl; // 4
    x)  the same                       4
    y)  test file,                     4
    z)  NOT REQUIRED IN PROBLEM SET    4
    A)  for (i = 1; i <= 5; i++) { // for source files 1-5 4
    B)  cout << setw(15) << data_of_file.similar_words[i] << " from file " << i << endl; 4
    C)  // test_file << setw(15) << data_of_file.similar_words[i] << " from file " << i << endl; // 4
    D)  the same                       4
    E)  test file,                     4
    F)  NOT REQUIRED IN PROBLEM SET    4
    G)  } //                           4
    H)  Similarity Report for Similarity Index 4
    I)  data and                       4
    J)  the class                      4
    K)  // call a                      4
    L)  in the class                   4
    M)  cout << endl << endl <<        4
    N)  setprecision(3) << "\t\tSimilarity Index = " << data_of_file.similarity_percentage[0] << "%" << endl; 4
    O)  test_file << endl << endl <<   4
    P)  setprecision(3) << "\t\tSimilarity Index = " << data_of_file.similarity_percentage[0] << "%" << endl; 4
    Q)  the same                       4
    R)  test file                      4
    S)  for (i = 1; i <= 5; i ++) {    4
    T)  // for source files 1-5        4
    U)  cout << setprecision(3) << "Source " << i << "\t= " << data_of_file.similarity_percentage[i] << "%" << endl; 4
    V)  test_file << setprecision(3) << "Source " << i << "\t= " << data_of_file.similarity_percentage[i] << "%" << endl; 4
    W)  the same                       4
    X)  test file                      4
    Y)  void phrase_check(ofstream& test_file) { 4
    Z)  // function of type void that does not return any value to main function, takes in an output stream parameter 4
    a)  test_phrase, source_line, temp_phrase; 4
    b)  int test_substring_position,   4
    c)  for various                    4
    d)  for (i = 1; i <= 5; i++) { // for source files 1-5 4
    e)  file[0].seekg(0); // clear     4
    f)  and seek to                    4
    g)  for test file                  4
    h)  file[i].seekg(0); // clear     4
    i)  and seek to                    4
    j)  for source file i              4
    k)  test_words_done = 0;           4
    l)  // initialise                  4
    m)  in test file                   4
    n)  while (                        4
    o)  file[0].good() ) { //          4
    p)  test file                      4
    q)  the loop runs                  4
    r)  for ( j = 1; j <=              4
    s)  test_words_done; j++           4
    t)  ) {                            4
    u)  file[0] >> test_word; }        4
    v)  if ( file[0].eof() ) break;    4
    w)  // if                          4
    x)  test file                      4
    y)  to next                        4
    z)  source file                    4
    A)  else {                         4
    B)  the first                      4
    C)  for phrase                     4
    D)  file[0] >> test_word;          4
    E)  test_phrase = test_word;       4
    F)  if ( file[0].eof() ) break;    4
    G)  } //                           4
    H)  test file                      4
    I)  to next                        4
    J)  source file                    4
    K)  for ( j = 1; j <= min_phrase_len - 1; j++ 4
    L)  ) { // if                      4
    M)  if (                           4
    N)  !file[0].eof() ) { //          4
    O)  as the                         4
    P)  file[0] >> test_word;          4
    Q)  test_phrase = test_phrase + " " + test_word; 4
    R)  // ACTUAL                      4
    S)  PLAGIARISM CHECK               4
    T)  while ( !file[i].eof() ) { //  4
    U)  source file                    4
    V)  does not                       4
    W)  getline(file[i], source_line); 4
    X)  source file                    4
    Y)  test_substring_position = source_line.find(test_phrase); 4
    Z)  check if                       4
    a)  is in                          4
    b)  if ( test_substring_position != string::npos ) { 4
    c)  // if                          4
    d)  is not                         4
    e)  test_words_done =              4
    f)  number of                      4
    g)  words in                       4
    h)  next loop                      4
    i)  file[i].seekg(0); // clear     4
    j)  and seek to start for source file i 4
    k)  the loop                       4
    l)  if ( test_substring_position   4
    m)  == string::npos ) {            4
    n)  // if                          4
    o)  test_words_done =              4
    p)  so the                         4
    q)  next loop                      4
    r)  takes in                       4
    s)  the second                     4
    t)  file[0].seekg(0); // clear     4
    u)  and seek to                    4
    v)  for test file                  4
    w)  file[i].seekg(0); // clear     4
    x)  and seek to                    4
    y)  for source file i              4
    z)  continue; } //                 4
    A)  the next                       4
    B)  phrase check                   4
    C)  the first                      4
    D)  word in                        4
    E)  word by word                   4
    F)  while ( test_substring_position != string::npos ) { 4
    G)  string is found,               4
    H)  in a                           4
    I)  if ( file[0].eof() ) break;    4
    J)  // if                          4
    K)  test file                      4
    L)  else {                         4
    M)  test word                      4
    N)  to a                           4
    O)  file[0] >> test_word;          4
    P)  temp_phrase = test_phrase + " " + test_word; 4
    Q)  } while (                      4
    R)  !file[i].eof() ) { //          4
    S)  loop for                       4
    T)  make a                         4
    U)  getline(file[i], source_line); 4
    V)  source file                    4
    W)  test_substring_position = source_line.find(temp_phrase); 4
    X)  check if                       4
    Y)  in any                         4
    Z)  if ( test_substring_position != string::npos ) { 4
    a)  // if                          4
    b)  test_words_done =              4
    c)  for test                       4
    d)  test_phrase = temp_phrase;     4
    e)  file[i].seekg(0); // clear     4
    f)  and seek to start for source file i 4
    g)  found in                       4
    h)  // if                          4
    i)  in an                          4
    j)  integer to                     4
    k)  the source                     4
    l)  file number                    4
    m)  in the                         4
    n)  at the                         4
    o)  test_phrase; //                4
    p)  in the                         4
    q)  at the                         4
    r)  file[0].seekg(0); // clear     4
    s)  and seek to                    4
    t)  for test file                  4
    u)  file[i].seekg(0); // clear     4
    v)  and seek to                    4
    w)  for source file i              4
    x)  // Similarity Report for Similar 4
    y)  in the class                   4
    z)  and the                        4
    A)  // cout << endl <<             4
    B)  endl << "Total Number of Similar Phrases = " << data_of_file.similar_phrase_count << endl << " 4
    C)  Similar Phrases/Clauses        4
    D)  Source File" << endl << "      4
    E)  // NOT REQUIRED IN PROBLEM SET 4
    F)  test_file << endl << endl << "Total Number of Similar Phrases = " << data_of_file.similar_phrase_count << endl << " 4
    G)  Similar Phrases/Clauses        4
    H)  Source File" << endl << "      4
    I)  for (i = 1; i <=               4
    J)  data_of_file.similar_phrase_count; i++) 4
    K)  { // for loop                  4
    L)  for the                        4
    M)  number of                      4
    N)  in the                         4
    O)  // cout << endl << "           4
    P)  " << letters.at(               4
    Q)  % letters.size() ) << ")       4
    R)  "; //                          4
    S)  NOT REQUIRED IN PROBLEM        4
    T)  at the                         4
    U)  in the                         4
    V)  the position                   4
    W)  of (i                          4
    X)  - 1                            4
    Y)  // cout <<                     4
    Z)  setw(27) << std::left <<       4
    a)  // NOT REQUIRED IN PROBLEM     4
    b)  // cout <<                     4
    c)  " " <<                         4
    d)  // NOT REQUIRED IN PROBLEM     4
    e)  the file                       4
    f)  for the                        4
    g)  test_file << endl <<           4
    h)  " " <<                         4
    i)  % letters.size() ) << ")       4
    j)  "; //                          4
    k)  at the                         4
    l)  in the                         4
    m)  the position                   4
    n)  of (i                          4
    o)  - 1                            4
    p)  test_file <<                   4
    q)  setw(27) << std::left <<       4
    r)  test_file <<                   4
    s)  " " <<                         4
    t)  the file                       4
    u)  for the                        4
    v)  int main() { // main function, with int type that needs an integer to be returned at the end of the function, either by putting "return 0;" or your compiler does that for you anyways 4
    w)  // input file names, create streams (1 test file, 5 source files). tried many loop methods that failed, apparently you can use: idk what that even is anymore? 4
    x)  for (i = 0; i <= 5; i++) { // for loop where i starts with a value of 0, increments each time the loop finishes a cycle. the loop terminates when i exceeds 5, so the loop runs 6 times 4
    y)  string text = (i == 0)? "test" : "source"; // pretty sure we did the shorthand if-else in class, YES IT WAS IN AIKMAN SERIES IF STATEMENTS NOTES 4
    z)  do { // Just Do It. Seriously, a do-while loop will make sure it executes statements in it at least once, until... 4
    A)  cout << "Enter file name of the " << text << " file, file " << i << ": "; // cout prints the given text in console. integer i being used for numbering, as text. 4
    B)  getline(cin, file_names[0][i]); // similar to cin input, getline allows taking in a string WITH spaces as input instead of buffering inputs delimited by spaces. here, integer i is being used for indexing, and the loop means each index stores a different string. 4
    C)  file[i].open(file_names[0][i]); // tries to open the file name you input, in an input stream 4
    D)  if (!file[i].is_open()) cout << "Failed to open \"" << file_names[0][i] << "\".\nPlease try again, making sure the file is in the same directory as this code.\n\n"; // if file does not open, cout these statements 4
    E)  else { cout << "The " << text << " file \"" << file_names[0][i] << "\" opened successfully!\n\n"; continue; } // ELSE, this file has its stream correctly opened, continue to next loop for next file 4
    F)  } while (!file[i].is_open()); } // ...until the file stream is successful / WHILE the file is NOT open to input stream 4
    G)  ofstream test_file(file_names[0][0], ios::app); // call a solitary output stream for test file, ios::app 4
    H)  appends text to                4
    I)  the end of                     4
    J)  // call both plagiarism check functions 4
    K)  word_check(test_file); //      4
    L)  argument to showcase it works lol, if filestreams are global, you don't need to pass 4
    M)  to pass                        4
    N)  an array of                    4
    O)  bad on security/code practice but we aren't being judged for a secure code 4
    P)  the main function              4
    Q)  // close                       4
    R)  for (i = 0; i <= 5; i++) { file[i].close(); } // 4
    S)  for loop closes all ifstreams  4
    T)  test_file.close(); // close the ofstream 4
    U)  return 0; } // terminates the main function by returning code 0 to system; program ends after successful execution 4
    V)  #include <iostream> // input/output stream, contains basic statements e.g. cin, cout as part of the "std" (standard) namespace 5
    W)  #include <string> // string library to 5
    X)  manipulate strings             5
    Y)  #include <fstream> // (both input and output) file stream to manipulate files for data handling 5
    Z)  #include <iomanip> //          5
    a)  report formatting              5
    b)  #include "SimilarityReporter.h" // a custom header file (that contains a custom class) that will contain code to store numerical data and prepare a similarity report using arithmetic functions and data from word check and phrase check functions 5
    c)  using namespace std; // standard namespace is used so if any scope used in main() isn't available elsewhere, the compiler checks standard library "std" for availability. helps with minimising repetition e.g. cout instead of std::cout 5
    d)  // GLOBAL VARIABLES TO USE IN ALL FUNCTIONS, CLASSES AND STUFF 5
    e)  int i; // size_t i; // (UNSIGNED integer and so good for indexing) (there's a high chance it can cost marks for no reason, you have to go with what you studied in course) // a simple integer named i is initialised, will be used for various loops (LITERALLY ALL OF THEM LMAO) 5
    f)  string file_names[1][6]; // AH YES, an array of strings (not characters) to store file names, typical jugaar (trick). the first index, [1] WITHOUT the second index [6] would otherwise make an array of characters, which is a single string itself. 5
    g)  ifstream file[6]; // DAMN you can do THAT too, made stuff SO MUCH EASIER, praying that an array of (input) ifstreams is not out of the scope of the FOP course lmao 5
    h)  SimilarityReporter data_of_file; // the 5
    i)  in the class file itself //    5
    j)  custom class to manipulate numerical data 5
    k)  string similar_phrase_data[2][1000]; // 5
    l)  FIRST INDEX: index [0] for source file number, index [1] for phrase string, CAN CHANGE SECOND INDEX: this 5
    m)  can store [1000] phrase strings and their file numbers 5
    n)  // WORD SIMILARITY CHECK KNOBS (idk what to call them, you change them according to plagiarism need?) 5
    o)  const string letters_numbers = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"; // a constant (that cannot be modified) string of letters and 5
    p)  used in                        5
    q)  contain at least               5
    r)  = 4; //                        5
    s)  minimum length of substrings to calculate similarity of 5
    t)  int substring_len_diff_tolerance = 2; // 5
    u)  difference tolerance between test substring and source substring lengths: length adjustment, for punctuation, "too small vs too large" substring exclusion and similar words 5
    v)  of words                       5
    w)  const string                   5
    x)  // PHRASE SIMILARITY CHECK KNOBS 5
    y)  const string letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"; 5
    z)  int min_phrase_len = 2;        5
    A)  REQUIRED IN PROBLEM            5
    B)  number of                      5
    C)  similarity of                  5
    D)  void word_check(ofstream& test_file) { // function of type void that does not return any value to main function, takes in an output stream parameter 5
    E)  string word, test_word, source_word; // 5
    F)  int test_substring_position, source_substring_position; // 5
    G)  substring positions for searches 5
    H)  // COUNT TOTAL WORDS OF EACH FILE 5
    I)  for (i = 0; i <= 5; i++) { //  5
    J)  loop for                       5
    K)  data_of_file.word_count[i] = 0; 5
    L)  // initialise                  5
    M)  word count                     5
    N)  file i                         5
    O)  in the                         5
    P)  of type                        5
    Q)  while(file[i] >> word) {       5
    R)  from file                      5
    S)  in the                         5
    T)  the file                       5
    U)  if ( word.find_first_of(letters_numbers) != string::npos ) { // we haven't studied find_first_of in 5
    V)  so... anyways, if there is at least a single letter or number in a string, helps reduce word count of non-word symbols in code plagiarism 5
    W)  data_of_file.word_count[i]++; // count the word 5
    X)  for the                        5
    Y)  file i,                        5
    Z)  // ACTUAL WORD PLAGIARISM CHECK 5
    a)  for (i = 1; i <= 5; i++) { // for source files 1-5 5
    b)  // clear                       5
    c)  test file to                   5
    d)  // seek                        5
    e)  to beginning for               5
    f)  test file, for iteration in the next source file i 5
    g)  while( file[0] >> test_word ) { // iterate through test file, take one word then loop through whole file i 5
    h)  of the                         5
    i)  // clear                       5
    j)  for source file i              5
    k)  // seek file i to beginning for next word in test file to iterate through source file 5
    l)  while ( file[i] >> source_word ) { // iterate through source file i, word by word 5
    m)  test_substring_position = source_word.find(test_word); // search for the test word substring in source word string, return the position of first character if substring is found, otherwise return -1 5
    n)  source_substring_position = test_word.find(source_word); // search for the source word substring in test word string, return the position of first character if substring is found, otherwise return -1 5
    o)  if(test_substring_position != string::npos || source_substring_position != string::npos) { // 5
    p)  cross check if substring is found in either of the 5
    q)  if either of the positions are not -1 as the substring is found 5
    r)  // some conditions to meet: must contain at least a letter or number, and length adjustment, for punctuation, "too small vs too large" substring exclusion and similar words (SEE KNOBS ABOVE) 5
    s)  if ( test_word.find_first_of(letters_numbers) != string::npos && source_word.find_first_of(letters_numbers) != string::npos ) { 5
    t)  check if                       5
    u)  contain at least a             5
    v)  string in                      5
    w)  if ( test_word.length() >=     5
    x)  && source_word.length() >=     5
    y)  ) { //                         5
    z)  if ( test_word.length() <= source_word.length() + substring_len_diff_tolerance && test_word.length() >= source_word.length() - substring_len_diff_tolerance ) { // 5
    A)  length adjustment, for punctuation, "too small vs too large" substring exclusion and similar 5
    B)  works for length differences in any 5
    C)  data_of_file.similar_words[i]++; // 5
    D)  similar word                   5
    E)  the main thing. POWER          5
    F)  // terminates the              5
    G)  source word                    5
    H)  the next                       5
    I)  word in test file              5
    J)  // Similarity Report for Similar 5
    K)  data and                       5
    L)  the class                      5
    M)  header file                    5
    N)  cout << endl << endl << setw(0) << "Total number of similar words found = " << data_of_file.sum_similar_words() << endl; 5
    O)  // test_file << endl << endl << setw(0) << "Total number of similar words found = " << data_of_file.sum_similar_words() << endl; // 5
    P)  the same                       5
    Q)  test file,                     5
    R)  NOT REQUIRED IN PROBLEM SET    5
    S)  for (i = 1; i <= 5; i++) { // for source files 1-5 5
    T)  cout << setw(15) << data_of_file.similar_words[i] << " from file " << i << endl; 5
    U)  // test_file << setw(15) << data_of_file.similar_words[i] << " from file " << i << endl; // 5
    V)  the same                       5
    W)  test file,                     5
    X)  NOT REQUIRED IN PROBLEM SET    5
    Y)  } //                           5
    Z)  Similarity Report for Similarity Index 5
    a)  data and                       5
    b)  the class                      5
    c)  header file                    5
    d)  // call a                      5
    e)  in the class                   5
    f)  cout << endl << endl << setprecision(3) << "\t\tSimilarity Index = " << data_of_file.similarity_percentage[0] << "%" << endl; 5
    g)  test_file << endl << endl << setprecision(3) << "\t\tSimilarity Index = " << data_of_file.similarity_percentage[0] << "%" << endl; 5
    h)  the same                       5
    i)  test file                      5
    j)  for (i = 1; i <= 5; i ++) {    5
    k)  // for source files 1-5        5
    l)  cout << setprecision(3) << "Source " << i << "\t= " << data_of_file.similarity_percentage[i] << "%" << endl; 5
    m)  test_file << setprecision(3) << "Source " << i << "\t= " << data_of_file.similarity_percentage[i] << "%" << endl; 5
    n)  the same                       5
    o)  test file                      5
    p)  void phrase_check(ofstream& test_file) { 5
    q)  // function of type void that does not return any value to main function, takes in an output stream parameter 5
    r)  test_word, test_phrase, source_line, temp_phrase; 5
    s)  int test_substring_position, j, test_words_done; 5
    t)  for various                    5
    u)  for (i = 1; i <= 5; i++) { // for source files 1-5 5
    v)  file[0].seekg(0); // clear     5
    w)  and seek to                    5
    x)  for test file                  5
    y)  file[i].seekg(0); // clear     5
    z)  and seek to                    5
    A)  for source file i              5
    B)  test_words_done = 0;           5
    C)  // initialise                  5
    D)  in test file                   5
    E)  while ( file[0].good() ) {     5
    F)  test file                      5
    G)  the loop runs                  5
    H)  for ( j = 1; j <= test_words_done; j++ ) 5
    I)  { file[0] >> test_word; }      5
    J)  if ( file[0].eof() ) break;    5
    K)  // if                          5
    L)  test file                      5
    M)  to next                        5
    N)  source file                    5
    O)  else {                         5
    P)  the first                      5
    Q)  for phrase                     5
    R)  file[0] >> test_word;          5
    S)  test_phrase = test_word;       5
    T)  if ( file[0].eof() ) break;    5
    U)  } //                           5
    V)  test file                      5
    W)  to next                        5
    X)  source file                    5
    Y)  for ( j = 1; j <= min_phrase_len - 1; j++ ) { 5
    Z)  // if                          5
    a)  if ( !file[0].eof() ) {        5
    b)  // ...                         5
    c)  as the                         5
    d)  file[0] >> test_word;          5
    e)  test_phrase = test_phrase + " " + test_word; 5
    f)  // ACTUAL                      5
    g)  PLAGIARISM CHECK               5
    h)  while ( !file[i].eof() ) {     5
    i)  source file                    5
    j)  does not                       5
    k)  getline(file[i], source_line); 5
    l)  source file                    5
    m)  test_substring_position = source_line.find(test_phrase); 5
    n)  check if                       5
    o)  is in                          5
    p)  if ( test_substring_position != string::npos ) { 5
    q)  // if                          5
    r)  is not                         5
    s)  test_words_done = test_words_done + min_phrase_len; 5
    t)  number of                      5
    u)  words in                       5
    v)  next loop                      5
    w)  file[i].seekg(0); // clear     5
    x)  and seek to start for source file i 5
    y)  the loop                       5
    z)  if ( test_substring_position == string::npos ) { 5
    A)  // if                          5
    B)  test_words_done = test_words_done + 1; 5
    C)  so the                         5
    D)  next loop                      5
    E)  takes in                       5
    F)  the second                     5
    G)  file[0].seekg(0); // clear     5
    H)  and seek to                    5
    I)  for test file                  5
    J)  file[i].seekg(0); // clear     5
    K)  and seek to                    5
    L)  for source file i              5
    M)  continue; } //                 5
    N)  the next                       5
    O)  phrase check                   5
    P)  the first                      5
    Q)  word in                        5
    R)  word by word                   5
    S)  while ( test_substring_position != string::npos ) { 5
    T)  string is found,               5
    U)  in a                           5
    V)  if ( file[0].eof() ) break;    5
    W)  // if                          5
    X)  test file                      5
    Y)  else {                         5
    Z)  test word                      5
    a)  file[0] >> test_word;          5
    b)  temp_phrase = test_phrase + " " + test_word; 5
    c)  } while (                      5
    d)  !file[i].eof() ) {             5
    e)  loop for                       5
    f)  make a                         5
    g)  getline(file[i], source_line); 5
    h)  source file                    5
    i)  test_substring_position = source_line.find(temp_phrase); 5
    j)  check if                       5
    k)  in any                         5
    l)  if ( test_substring_position != string::npos ) { 5
    m)  // if                          5
    n)  test_words_done = test_words_done + 1; 5
    o)  for test                       5
    p)  test_phrase = temp_phrase;     5
    q)  file[i].seekg(0); // clear     5
    r)  and seek to start for source file i 5
    s)  found in                       5
    t)  // if                          5
    u)  in an                          5
    v)  similar_phrase_data[0][data_of_file.similar_phrase_count] = to_string(i); 5
    w)  integer to                     5
    x)  the source                     5
    y)  file number                    5
    z)  in the                         5
    A)  at the                         5
    B)  similar_phrase_data[1][data_of_file.similar_phrase_count] = test_phrase; 5
    C)  in the                         5
    D)  at the                         5
    E)  file[0].seekg(0); // clear     5
    F)  and seek to                    5
    G)  for test file                  5
    H)  file[i].seekg(0); // clear     5
    I)  and seek to                    5
    J)  for source file i              5
    K)  // Similarity Report for Similar 5
    L)  and data                       5
    M)  in the class                   5
    N)  and the                        5
    O)  // cout << endl << endl <<     5
    P)  "Total Number of Similar Phrases = " << data_of_file.similar_phrase_count << endl << " 5
    Q)  Similar Phrases/Clauses        5
    R)  Source File" << endl << "      5
    S)  // NOT REQUIRED IN PROBLEM SET 5
    T)  test_file << endl << endl << "Total Number of Similar Phrases = " << data_of_file.similar_phrase_count << endl << " 5
    U)  Similar Phrases/Clauses        5
    V)  Source File" << endl << "      5
    W)  for (i = 1; i <= data_of_file.similar_phrase_count; i++) { 5
    X)  // for loop                    5
    Y)  for the                        5
    Z)  number of                      5
    a)  in the                         5
    b)  // cout << endl << "           5
    c)  " << letters.at( (i - 1) % letters.size() ) << ") 5
    d)  "; //                          5
    e)  NOT REQUIRED IN PROBLEM        5
    f)  at the                         5
    g)  in the                         5
    h)  the position                   5
    i)  of (i                          5
    j)  i - 1                          5
    k)  // cout <<                     5
    l)  setw(27) << std::left << similar_phrase_data[1][i]; 5
    m)  // NOT REQUIRED IN PROBLEM     5
    n)  // cout <<                     5
    o)  " " << similar_phrase_data[0][i]; 5
    p)  // NOT REQUIRED IN PROBLEM     5
    q)  the file                       5
    r)  for the                        5
    s)  test_file << endl << "         5
    t)  " << letters.at( (i - 1) % letters.size() ) << ") 5
    u)  "; //                          5
    v)  at the                         5
    w)  in the                         5
    x)  the position                   5
    y)  of (i                          5
    z)  i - 1                          5
    A)  test_file << setw(27) << std::left << similar_phrase_data[1][i]; 5
    B)  test_file << " " << similar_phrase_data[0][i]; 5
    C)  the file                       5
    D)  for the                        5
    E)  int main() { // main function, with int type that needs an integer to be returned at the end of the function, either by putting "return 0;" or your compiler does that for you anyways 5
    F)  // input file names, create streams (1 test file, 5 source files). tried many loop methods that failed, apparently you can use: idk what that even is anymore? 5
    G)  for (i = 0; i <= 5; i++) { // for loop where i starts with a value of 0, increments each time the loop finishes a cycle. the loop terminates when i exceeds 5, so the loop runs 6 times 5
    H)  string text = (i == 0)? "test" : "source"; // pretty sure we did the shorthand if-else in class, YES IT WAS IN AIKMAN SERIES IF STATEMENTS NOTES 5
    I)  do { // Just Do It. Seriously, a do-while loop will make sure it executes statements in it at least once, until... 5
    J)  cout << "Enter file name of the " << text << " file, file " << i << ": "; // cout prints the given text in console. integer i being used for numbering, as text. 5
    K)  getline(cin, file_names[0][i]); // similar to cin input, getline allows taking in a string WITH spaces as input instead of buffering inputs delimited by spaces. here, integer i is being used for indexing, and the loop means each index stores a different string. 5
    L)  file[i].open(file_names[0][i]); // tries to open the file name you input, in an input stream 5
    M)  if (!file[i].is_open()) cout << "Failed to open \"" << file_names[0][i] << "\".\nPlease try again, making sure the file is in the same directory as this code.\n\n"; // if file does not open, cout these statements 5
    N)  else { cout << "The " << text << " file \"" << file_names[0][i] << "\" opened successfully!\n\n"; continue; } // ELSE, this file has its stream correctly opened, continue to next loop for next file 5
    O)  } while (!file[i].is_open()); } // ...until the file stream is successful / WHILE the file is NOT open to input stream 5
    P)  ofstream test_file(file_names[0][0], ios::app); // call a solitary output stream for test file, ios::app 5
    Q)  appends text to                5
    R)  the end of                     5
    S)  // call both plagiarism check functions 5
    T)  word_check(test_file); //      5
    U)  argument to showcase it works lol, if filestreams are global, you don't need to pass 5
    V)  to pass                        5
    W)  an array of                    5
    X)  bad on security/code practice but we aren't being judged for a secure code 5
    Y)  the main function              5
    Z)  // close                       5
    a)  for (i = 0; i <= 5; i++) { file[i].close(); } // 5
    b)  for loop closes all ifstreams  5
    c)  test_file.close(); // close the ofstream 5
