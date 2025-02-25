**NG 2/24/2025**
* public member var/const -10
* inadequate and/ insufficient test data/ not all possible cases have been tested: e.g. each record has 4 pieces of data; pow(2,4)->16  possible combinations of valid/invalid and only one of them is a valid record; all menu options should be tested;  no zeros, negative numbers, etc-5
* If a user enters a value of a wrong data type, the program goes into an infinite loop or  crashes or terminates or prints the menu multiple times ( in menu add cin.clear(); cin.ignore(...);  in  the default case of the switch); validate user input -5
* reading input file: no message to a user if there are any kind of problem, 
* #180-190 redundant -2
* text entries should be left aligned and numerical entries should be right aligned with the same number of decimal places -2
* << not needed between strings -
* poor Id(s)  and/or inconsistent naming convention; ids should be self-documenting and as short as possible; use verbs for functions and nouns for variables; use camel-casing for variables (errorMessage) enum & const should be in upper case with words separated by “_”; pointer variables should start with p( if single)  or pp( if double pointer); flags isValid ( clearly what true would mean); if copying – e.g rhsQueue or scrQueue ; do not use IDs that are same as or very similar to C++  keywords and functions; no need to call an array “array”- it is obvious -2
```
 NumberStatistics obj;
```
* missing feedback.md –2
* array class should handle the array stats -2
