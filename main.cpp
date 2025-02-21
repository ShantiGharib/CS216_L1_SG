//Shanti Gharib
//Lab #1
#include <iostream>
#include <fstream>
#include <iomanip>

class NumsArray {
public:
	static constexpr const int ARRAY_MAX_CAPACITY = 10, EMPTY = 0;
private:
	int nums[ARRAY_MAX_CAPACITY];
	bool isSorted = false;
public:
	NumsArray();
	void AddElement(const int val);
	size_t length = EMPTY;
	bool IsNotFull() const;
	bool IsSorted() const;
	long long FindSum() const;
	double GetAverage() const;
	double GetAverage(long long sum) const;
	double GetMedian();
	int GetElement(int index) const;
	void DisplayValuesToConsole(std::ostream &stream) const;
	void SortArray();
};

bool GetInputFileInteger(std::ifstream &File, int &destination);

class NumberStatistics {
private:
	void ImportData();
	void PrintArraysSeparatelyHelper(NumsArray &source, std::ostream &stream);
	void PrintAllValuesHelper(NumsArray &A1, int &indexA1, NumsArray &A2, int &indexA2);
	void PrintOneElementToConsole(NumsArray &nums, int &index);
public:
	static constexpr const int TOTAL_NUMBER_OF_ARRAYS = 3;
	NumsArray Mod5, Mod9, ModNull;
	NumberStatistics();
	void PrintArraysSeparately(std::ostream &stream);
	void PrintAllValues();
	void ExportData();
};

const std::string INPUT_FILE  =  "in_numbers.txt", 
		           OUTPUT_FILE = "out_numbers.txt";
int main() {
	std::fixed; std::setprecision(2);
	NumberStatistics obj = NumberStatistics();
	static constexpr const int PRINT_STATS = 1, PRINT_ALL_VALUES = 2, QUIT_AND_SAVE = 3; 
	int option = 0;
	while ( option != QUIT_AND_SAVE ) {
		std::cout << "\n\nChoose an option:\n"
			  << "    1: Print numbers' sum, average, and median.\n"
			  << "    2: Print numbers in sorted order.\n"
			  << "    3: Quit program and save stats to external file.\n\n";
		std::cin >> option;
		std::cout << "\n";
		switch (option) {
			case PRINT_STATS: {
				obj.PrintArraysSeparately(std::cout);
				break;
			}
			case PRINT_ALL_VALUES: {
				obj.PrintAllValues();
				break;
			}
			case QUIT_AND_SAVE: {
				obj.ExportData();
				break;
			}
			default: {
				std::cout << "Not valid option.\n";
				break;
			}
		}    
	}
}

NumsArray::NumsArray() {}
inline bool NumsArray::IsNotFull() const { return length != ARRAY_MAX_CAPACITY; }
inline bool NumsArray::IsSorted() const { return isSorted; }
inline int NumsArray::GetElement(int index) const { return nums[index]; }
void NumsArray::AddElement(const int val) {
	nums[length] = val;
	++length;
}
void NumsArray::SortArray() {
	while (!isSorted) {
		isSorted = 1;
		for (int i = 1; i < length; ++i) {
			if (nums[i-1] > nums[i]) {
				isSorted = 0;
				const int temp = nums[i-1];
				nums[i-1] = nums[i]; 
				nums[i] = temp;
			}
		}
	}
}
long long NumsArray::FindSum() const {
	int sum = 0;
	for (int i = 0; i < length; ++i) {
		sum += nums[i];
	}
	return sum;
}
double NumsArray::GetAverage() const {
	long long sum = FindSum();
	return ( 1.0 * sum ) / length;
}
inline double NumsArray::GetAverage(long long sum) const {
	return ( 1.0 * sum ) / length;
}
double NumsArray::GetMedian() {
	const bool evenSized = ( length % 2 == 0 );
	const size_t half = length / 2;
	if ( isSorted == false ) SortArray();
	return ( evenSized ? 0.5 * ( nums[half-1] + nums[half] ) : nums[half] ); 
}
void NumsArray::DisplayValuesToConsole(std::ostream &stream) const {
	for (int i = 0; i < length; ++i) {
		stream << nums[i] << " ";
	}
	stream << "\n";
}
bool GetInputFileInteger(std::ifstream &File, int &destination) {
	File >> destination;
	return File.good();
}
void NumberStatistics::ImportData() {
	std::ifstream File(INPUT_FILE);
	if ( !File.is_open() ) {
		std::cout << "Cannot open input file.\n";
		exit(EXIT_FAILURE);
	}
	int val, count = NumberStatistics::TOTAL_NUMBER_OF_ARRAYS * NumsArray::ARRAY_MAX_CAPACITY;
	while (GetInputFileInteger(File, val) && count != 0) {
		const bool divisibleByNine = ( val % 9 == 0 ), divisibleByFive = ( val % 5 == 0 );
		if ( divisibleByNine != true && divisibleByFive != true) {
			if ( ModNull.IsNotFull() ) {
				ModNull.AddElement(val);
				--count;
			}
		}
		if ( divisibleByFive ) {
			if ( Mod5.IsNotFull() ) {
				Mod5.AddElement(val);
				--count;
			}
		}
		if ( divisibleByNine ) {
			if ( Mod9.IsNotFull() ) {
				Mod9.AddElement(val);
				--count;
			}
		}
	}
	File.close();
}
void NumberStatistics::ExportData() {
	std::ofstream fileOutput(OUTPUT_FILE);
	if ( fileOutput.is_open() ) {
		PrintArraysSeparately(fileOutput);
		fileOutput.close();
	}
}
void NumberStatistics::PrintArraysSeparatelyHelper(NumsArray &source, std::ostream &stream) {
	source.DisplayValuesToConsole(stream);
	stream << "\n";
	const long long sum = source.FindSum();
	const double average = source.GetAverage(sum);
	const double median = source.GetMedian();
	stream << "Sum: "       << sum 
	       << "\nAverage: " << average 
	       << "\nMedian: "  << median
	       << "\n\n\n";
}
void NumberStatistics::PrintArraysSeparately(std::ostream &stream) {
	if ( Mod5.length != 0 ) {
		stream << "Numbers divisible by five:\n    ";
		PrintArraysSeparatelyHelper(Mod5, stream);
	}
	if ( Mod9.length != 0 ) {
		stream << "Numbers divisible by nine:\n    ";
		PrintArraysSeparatelyHelper(Mod9, stream);
	}
	if ( ModNull.length != 0 ) {
		stream << "Numbers not divisible by five nor nine:\n    ";
		PrintArraysSeparatelyHelper(ModNull, stream);
	}
}
void NumberStatistics::PrintAllValues() {
	Mod5.SortArray(); 
	Mod9.SortArray(); 
	ModNull.SortArray();
	std::cout << "Numbers: ";
	{
		int Mod5Idx = 0, Mod9Idx = 0, ModNullIdx = 0;
		while (Mod5Idx < Mod5.length || Mod9Idx < Mod9.length || ModNullIdx < ModNull.length) {
			if (Mod5Idx == Mod5.length) {
				PrintAllValuesHelper(Mod9, Mod9Idx, ModNull, ModNullIdx);
			}
			else if (Mod9Idx == Mod9.length) {
				PrintAllValuesHelper(Mod5, Mod5Idx, ModNull, ModNullIdx);
			}
			else if (ModNullIdx == ModNull.length) {
				PrintAllValuesHelper(Mod5, Mod5Idx, Mod9, Mod9Idx);
			}
			else if (Mod5.GetElement(Mod5Idx) <= Mod9.GetElement(Mod9Idx) && Mod5.GetElement(Mod5Idx) <= ModNull.GetElement(ModNullIdx)) {
				PrintOneElementToConsole(Mod5, Mod5Idx);
			}
			else if (Mod9.GetElement(Mod9Idx) <= Mod5.GetElement(Mod5Idx) && Mod9.GetElement(Mod9Idx) <= ModNull.GetElement(ModNullIdx)) {
				PrintOneElementToConsole(Mod9, Mod9Idx);
			}
			else {
				PrintOneElementToConsole(ModNull, ModNullIdx);
			}
			std::cout << " ";
		}
		std::cout << "\n\n";
	}
}
void NumberStatistics::PrintOneElementToConsole(NumsArray &nums, int &index) {
	std::cout << nums.GetElement(index);
	++index;
}
void NumberStatistics::PrintAllValuesHelper(NumsArray &A1, int &indexA1, NumsArray &A2, int &indexA2) {
	if (indexA1 != A1.length && indexA2 != A2.length) {
		if (A1.GetElement(indexA1) <= A2.GetElement(indexA2)) {
			PrintOneElementToConsole(A1, indexA1);
		}
		else {
			PrintOneElementToConsole(A2, indexA2);
		}
	}
	else if (indexA1 != A1.length) {
		PrintOneElementToConsole(A1, indexA1);
	}
	else {
		PrintOneElementToConsole(A2, indexA2);
	}
}
NumberStatistics::NumberStatistics() { ImportData(); }
/*
TestCase1: Random Values
Input: "5 19 234 -19 129 394 340 -78 -333333 44444 100  392304 -123294 230 503 777 76777 666 5544 44532452  234523 -32324 -1998772 120 0 0 0 0 1234 1094 9239 329190  08 -08 12"
Output:


Choose an option:
	1: Print numbers' sum, average, and median.
	2: Print numbers in sorted order.
	3: Quit program and save stats to external file.

1

Numbers divisible by five:
	5 340 100 230 120 0 0 0 0 329190

Sum: 329985
Average: 32998.5
Median: 52.5


Numbers divisible by nine:
	234 -333333 666 5544 0 0 0 0

Sum: -326889
Average: -40861.1
Median: 0


Numbers not divisible by five nor nine:
	19 -19 129 394 -78 44444 392304 -123294 503 777

Sum: 315179
Average: 31517.9
Median: 261.5




Choose an option:
	1: Print numbers' sum, average, and median.
	2: Print numbers in sorted order.
	3: Quit program and save stats to external file.

2

Numbers: -333333 -123294 -78 -19 0 0 0 0 0 0 0 0 5 19 100 120 129 230 234 340 394 503 666 777 5544 44444 329190 392304



Choose an option:
	1: Print numbers' sum, average, and median.
	2: Print numbers in sorted order.
	3: Quit program and save stats to external file.

3


*/
/*
Output Document:
Numbers divisible by five:
	5 340 100 230 120 0 0 0 0 329190

Sum: 329985
Average: 32998.5
Median: 52.5


Numbers divisible by nine:
	234 -333333 666 5544 0 0 0 0

Sum: -326889
Average: -40861.1
Median: 0


Numbers not divisible by five nor nine:
	19 -19 129 394 -78 44444 392304 -123294 503 777

Sum: 315179
Average: 31517.9
Median: 261.5
*/

/*
TestCase2: Random Values with one specific value outside INT range
Input: "5 19 234 -19 129 394 340 -78 -33333333333 44444 100  392304 -123294 230 503 777 76777 666 5544 44532452  234523 -32324 -1998772 120 0 0 0 0 1234 1094 9239 329190  08 -08 12"
Output:


Choose an option:
	1: Print numbers' sum, average, and median.
	2: Print numbers in sorted order.
	3: Quit program and save stats to external file.

1

Numbers divisible by five:
	5 340

Sum: 345
Average: 172.5
Median: 172.5


Numbers divisible by nine:
	234

Sum: 234
Average: 234
Median: 234


Numbers not divisible by five nor nine:
	19 -19 129 394 -78

Sum: 445
Average: 89
Median: 19




Choose an option:
	1: Print numbers' sum, average, and median.
	2: Print numbers in sorted order.
	3: Quit program and save stats to external file.

2

Numbers: -78 -19 5 19 129 234 340 394



Choose an option:
	1: Print numbers' sum, average, and median.
	2: Print numbers in sorted order.
	3: Quit program and save stats to external file.

3
*/

/*
Output Document:
Numbers divisible by five:
	5 340 

Sum: 345
Average: 172.5
Median: 172.5


Numbers divisible by nine:
	234 

Sum: 234
Average: 234
Median: 234


Numbers not divisible by five nor nine:
	-78 -19 19 129 394 

Sum: 445
Average: 89
Median: 19
*/

/*
TestCase3: Empty Input
Input: ""
Output:


Choose an option:
	1: Print numbers' sum, average, and median.
	2: Print numbers in sorted order.
	3: Quit program and save stats to external file.

1



Choose an option:
	1: Print numbers' sum, average, and median.
	2: Print numbers in sorted order.
	3: Quit program and save stats to external file.

2

Numbers:



Choose an option:
	1: Print numbers' sum, average, and median.
	2: Print numbers in sorted order.
	3: Quit program and save stats to external file.

3


*/
/*
Output Document:
""
*/
/*
TestCase 4: All numbers divisible by 5 and 9
Input: "45 90 -45 -90 135 270 -270 -135 540 -540 450 -450 900 -900"
Output:


Choose an option:
	1: Print numbers' sum, average, and median.
	2: Print numbers in sorted order.
	3: Quit program and save stats to external file.

1

Numbers divisible by five:
	45 90 -45 -90 135 270 -270 -135 540 -540

Sum: 0
Average: 0
Median: 0


Numbers divisible by nine:
	45 90 -45 -90 135 270 -270 -135 540 -540

Sum: 0
Average: 0
Median: 0




Choose an option:
	1: Print numbers' sum, average, and median.
	2: Print numbers in sorted order.
	3: Quit program and save stats to external file.

2

Numbers: -540 -540 -270 -270 -135 -135 -90 -90 -45 -45 45 45 90 90 135 135 270 270 540 540



Choose an option:
	1: Print numbers' sum, average, and median.
	2: Print numbers in sorted order.
	3: Quit program and save stats to external file.

3


*/
/*
Output Document:
Numbers divisible by five:
	-540 -270 -135 -90 -45 45 90 135 270 540 

Sum: 0
Average: 0
Median: 0


Numbers divisible by nine:
	-540 -270 -135 -90 -45 45 90 135 270 540 

Sum: 0
Average: 0
Median: 0
*/
/*
TestCase5: All numbers not divisible by 5 nor 9
Input: "46 91 -46 -91 136 271 -271 -136 541 -541 451 -451 901 -901"
Output:


Choose an option:
	1: Print numbers' sum, average, and median.
	2: Print numbers in sorted order.
	3: Quit program and save stats to external file.

1

Numbers not divisible by five nor nine:
	46 91 -46 -91 136 271 -271 -136 541 -541

Sum: 0
Average: 0
Median: 0




Choose an option:
	1: Print numbers' sum, average, and median.
	2: Print numbers in sorted order.
	3: Quit program and save stats to external file.

2

Numbers: -541 -271 -136 -91 -46 46 91 136 271 541



Choose an option:
	1: Print numbers' sum, average, and median.
	2: Print numbers in sorted order.
	3: Quit program and save stats to external file.

3


*/
/*
Output Document:
Numbers not divisible by five nor nine:
	-541 -271 -136 -91 -46 46 91 136 271 541 

Sum: 0
Average: 0
Median: 0
*/
