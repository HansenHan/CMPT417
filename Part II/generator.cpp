#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <algorithm>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <bits/stdc++.h>
#include <assert.h>
#include <ctime>
#include <time.h>
#include <chrono> 

using namespace std;

int main(){

	int num, cap, refill, K;
	string name, tmp_str;
	int number;

for(int n = 0; n < 40; n++){
	for(int m = 0; m < 10; m++){

	num = 60000;
	cap = 600;
	refill = 20 + 20*n;
	K = 100000;

	// num = 60000;
	// cap = 100 + 50*n;
	// refill = 20;
	// K = 100000;

	stringstream ss;
	number = n*10 + m;
	ss << number;
	ss >> tmp_str;
	name = "test_" + tmp_str;

	vector<int> fun;
	
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> dis(-9999, 9999);
	// normal_distribution<> dis(-9999, 9999);

	int num_neg=0; 
	int sum_neg=0;
	int num_pos=0;
	int sum_pos=0; 
	int zero=0; 
	int tmp;
	for(int i = 0; i < num; i++){
		tmp = int(dis(gen));
		if(tmp < 0){
			num_neg++;
			sum_neg = sum_neg + num_neg;
		}
		else if(tmp > 0){
			num_pos++;
			sum_pos = sum_pos + num_pos;
		}
		else{
			zero++;
		}
		fun.push_back(tmp);
	}
	
	

	ofstream myfile("data/"+name);
	if(myfile.is_open()){
		myfile << "% test "+tmp_str << endl;
		myfile << "\n";
		myfile << "num = " << num << endl;
		myfile << "cap = " << cap << endl;
		myfile << "refill = " << refill << endl;
		myfile << "K = " << K << endl;
		myfile << "num_neg = " << num_neg << endl;
		myfile << "num_pos = " << num_pos << endl;
		myfile << "sum_neg = " << sum_neg << endl;
		myfile << "sum_pos = " << sum_pos << endl;
		myfile << "fun = [";
		for(int i = 0; i < num-1; i++){
			myfile << fun[i] << ", ";
		}
		myfile << fun[num-1] << "];";
		
		myfile.close();
	}


	}
}


	return 0;
}


// Citation:
// https://www.cnblogs.com/egmkang/archive/2012/09/06/2673253.html
