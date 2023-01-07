class SimilarityReporter { // class declaration of name SimilarityReporter

    private: // private stuff cannot be accessed directly by PlagiarismDetector.cpp file, but notice how sum_word_count can be accessed when the public sum_words() function is called
        int i; // simple integer i for loops
        int sum_word_count = 0;  // a simple sum of word counts integer

    public: // public stuff can be accessed by PlagiarismDetector.cpp, these variables have been called in it to store values
        int word_count[6] = {0}; // index [0] is TEST FILE word count, initialise all values with zero
        int similar_words[6] = {0}; // index [0] is overall similar words, initialise all values with zero
        double similarity_percentage[6] = {0}; // index [0] is overall similarity percentage, initialise all values with zero

        int similar_phrase_count = 0; // a simple similar phrases counter integer

        int sum_words() { // a function to sum up word count of all files
            sum_word_count = 0; // start with zero each time the function is called, otherwise it'll be having the sum previously calculated
            for (i = 0; i <= 5; i++) { sum_word_count += word_count[i]; } // count words from each file, using array iteration
            return sum_word_count; // return the value of the variable
        };

        int sum_similar_words() { // a function to sum up similar word count of all files
            similar_words[0] = 0; // start with zero each time the function is called (for reasons above), will be storing the value in index zero of the array
            for (i = 1; i <= 5; i++) { similar_words[0] += similar_words[i]; } // notice how i starts with 1, the sum of 1 to 5 stores in index 0
            return similar_words[0]; // return the value of 0 index of the variable
        };

        void calculate_similarity_index() { // a function to calculate similarity index using formulae, void data type so doesn't return anything, just performs statements inside it
            similarity_percentage[0] = ( (double)sum_similar_words() / (double)sum_words() )  * 100; // index zero again for overall similarity. and notice how the above two functions are being called in this function. and they are being typecasted from integer datatype to double, for accurate arithmetic.
            for (i = 1; i <= 5; i++) { similarity_percentage[i] = ( (double)similar_words[i] / ( (double)word_count[0] + (double)word_count[i] ) ) * 100; } // a loop for individual similarities with corresponding indices, the integer values are typecasted to double again for arithmetic.
        }; // no, nothing is returned to the function this function was called from. this one just performs math
};