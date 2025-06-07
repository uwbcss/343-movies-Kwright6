# Self-Evaluation

## Name(s): 

Out of 25 points. Use output.txt created using 
`./create-output.sh > output.txt 2>&1` for guidance.

Complete all questions with "Q:"

Q: Does the program compile and run to completion: Yes

- If the program does not compile or gives a segmentation error when run, 
the maximum possible grade is 50%. No need to continue with the rest of self-evaluation

Q: All public functions have been implemented: 0

- -2 for each functionality not implemented

For each command, state Full, Partial or None to indicate 
if it has been fully, partially or not implemented at all.
Explain any partial implementations.

Inventory: Full
History: Full
Borrow: Full
Return: Full


Q: -1 for each compilation warning, min -3: 0

- Check under *1. Compiles without warnings*
- If the warning message is addressed in README.md, including how the programmer tried to address it, no deductions

Q: -1 for each clang-tidy warning, min -3: 0

- Check under *3. clang-tidy warnings*
- If the warning message is addressed in README.md, including how the programmer tried to address it, no deductions

Q: -1 for each clang-format warning, min -3: 0

- Check under *4. clang-format does not find any formatting issues*


Q: -2 for any detected memory leak: 0

- Check under *5. No memory leaks using g++*
- Check under *6. No memory leaks using valgrind*

Q: Do the tests sufficiently test the code: 0

- -1 for each large block of code not executed
- -2 for each function that is never called when testing
- Check under *7. Tests have full code coverage* paying attention to *The lines below were never executed*

Q: Are all functions in .h and .cpp file documents (min -3): 0

- -1 for each function not documented

## Location of error message or functionality

State the file and function where the information can be found

invalid command code: command.cpp create()

invalid movie type: borrowCmd.cpp execute()

invalid customer ID: borrowCmd.cpp execute()
 
invalid movie: borrowCmd.cpp execute()

factory classes: borrowCmd.h/.cpp BorrowCmdFactory(), returnCmd.h/.cpp ReturnCmdFactory(), inventoryCmd.h/.cpp InventoryCmdFactory(), historyCmd.h/.cpp HistoryCmdFactory()

hashtable: movieStore.h/.cpp (used to store vectors of movies in a fixed 'A'-'Z' table. Holds up to 26 different genres, which are more genres than awards are given to. Uses Movie genre(D,F,C, or future genres) as key.)

container used for comedy movies: vector<Movie*> movieStore.h/.cpp

function for sorting comedy movies: movieStore.h/.cpp sortInventory()

function where comedy movies are sorted: comedy.h/.cpp lessthan()

functions called when retrieving a comedy movie based on title and year: borrowCmd.cpp execute(), inventoryCmd.cpp execute(), returnCmd.cpp execute(), 

functions called for retrieving and printing customer history: historyCmd.cpp execute(), customer.cpp printHistory()

container used for customer history: vector<string> customer.h/.cpp

functions called when borrowing a movie: borrowCmd.cpp execute(), custmer.cpp borrowMovie()

explain borrowing a movie that does not exist: after searching through our inventory for a matching movie, movieToBorrow will equal nullptr. if it does, that means the movie doesn't exist and outputs invalid movie for customer

explain borrowing a movie that has 0 stock: if the stock of our movie object isn't greater than 0, then the movie is out of stock and won't be borrowed, the stock remains 0, and we output who could not borrow what title, out of stock and failed to execute Borrow on who and on what title

explain returning a movie that customer has not checked out: in Customer::returnMovie(), if the movie is not found in the customer's borrowedMovies unordered_map<string, Movie*>, it outputs who couldnt return the title, never borrowed, and failed to execute Return on who and on what title

any static_cast or dynamic_cast used: dynamic_cast used in borrowCmd.cpp to get classic movies; Used in returnCmd.cpp to get classic movies; Used in comedy.cpp to sort comedies; Used in classics.cpp to sort classics;

## Bonus +5

Are there multiple files, of the form runit-without-XXX, where the same set of files will compile and run excluding some of the commands or genres? Yes, runit-without-D.sh, runit-without-I.sh, runit-without-B.sh, runit-without-R.sh, runit-without-H.sh




Q: Total points: 30