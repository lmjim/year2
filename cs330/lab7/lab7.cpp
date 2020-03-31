#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;

void printNums(vector<int> &nums){
	vector<int>::const_iterator it = nums.begin();
	for(it; it != nums.end(); it++){
		cout << (*it) << endl;
	}
	return;
}

int main(){
	default_random_engine generator;
	uniform_int_distribution<int> distribution(1, 100);
	vector<int> nums;
	for(int i=0; i < 15; i++){
		nums.push_back(distribution(generator));
	}
	cout << "Unsorted:" << endl;
	printNums(nums);
	auto iB = nums.begin();
	auto iE = nums.end();
	sort(iB, iE);
	cout << "Sorted:" << endl;
	printNums(nums);
	return 0;
}
