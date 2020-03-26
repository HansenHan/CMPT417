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

// https://www.geeksforgeeks.org/extract-integers-string-c
// https://www.cnblogs.com/egmkang/archive/2012/09/06/2673253.html
// https://stackoverflow.com/questions/25201131/writing-csv-files-from-c


using namespace std;
using namespace std::chrono;

int test, num, cap, refill, K;
vector<int> fun;

// int read_file1(vector<char> &v, string name){
// 	if (FILE *fp = fopen(name, "r")){
// 		char buf[1024];
// 		while (size_t len = fread(buf, 1, sizeof(buf), fp))
// 			v.insert(v.end(), buf, buf + len);
// 		fclose(fp);
// 	}
// 	for(int i = 0; i < v.size(); i++){
// 		cout << v[i];
// 	}
// 	cout << endl;
// 	cout << v.size() << endl;
// 	return 0;
// }


int read_file2(vector<string> &v, string name){
	string line;
	ifstream myfile (name);
	if(myfile.is_open()){
		while(getline(myfile, line)){
			// cout << line << endl;
			v.push_back(line);
		}
		myfile.close();
	}
	else cout << "Unable to open file." << endl;
	return 0;
}


int get_data(vector<string> &v){
	int signal;
	stringstream ss;
	for(int i = 0; i < v.size(); i++){
		signal = 0;
		ss.clear();
		ss << v[i];
		string str;
		int data;
		while(!ss.eof()){
			ss >> str;
			if(str == "num") {signal = 1;}
			if(str == "cap") {signal = 2;}
			if(str == "refill") {signal = 3;}
			if(str == "K") {signal = 4;}
			if(str == "fun") {signal = 5;}
			if(str == "test") {signal = 6;}

			if(str[0] == '['){
				str.erase(0, 1);
			}

			if(stringstream(str) >> data){
				switch(signal){
					case 1:
					num = data;
					break;

					case 2:
					cap = data;
					break;

					case 3:
					refill = data;
					break;

					case 4:
					K = data;
					break;

					case 5:
					fun.push_back(data);
					break;

					case 6:
					test = data;
					break;
				}
			}
		}
	}
}


int main(){
	vector<string> v;
	int signal = 1;

// do{
	// string name;
	// cout << "Enter your test file name: ";
	// cin >> name;
	// if(name == "end" || name == "exit"){
	// 	signal = 0;
	// 	break;
	// }

	v.clear();
	fun.clear();

	read_file2(v, name);

	// check what we get:
	// for(int i = 0; i < v.size(); i++){
	// 	cout << i << ":" << v[i] << endl;
	// }
	// cout << "----------" << endl;

	get_data(v);

	// check what we get:
	// cout << "test: " << test << endl;
	// cout << "num: " << num << endl;
	// cout << "cap: " << cap << endl;
	// cout << "refill: " << refill << endl;
	// cout << "K: " << K << endl;
	// cout << "fun: ";
	// for(int i = 0; i < fun.size(); i++){
	// 	cout << fun[i] << ", ";
	// }
	// cout << endl;
	// cout << "----------" << endl;

	assert(num == fun.size());

	// ready to solve:
	vector<int> play(num,0);
	int tmp_token = cap;
	int next_token = 0;
	int total_fun = 0;
	int save = 0;

	// time_t start_time, finish_time;
	// time(&start_time);
	// ios_base::sync_with_stdio(false);

	auto start = high_resolution_clock::now(); 
	
	for(int i = 0; i < num; i++){
		tmp_token--;
		play[i]++;

		if(fun[i] < 0){
			total_fun = total_fun + fun[i];
			tmp_token = min(tmp_token+refill, cap);
		}
		else{
			int next;
			next = i+1;
			next_token = refill;
			
			while(next_token < cap){
				if(next < num){
					if(fun[next] > fun[i]){
						save = cap - next_token;
						if(save > tmp_token){
							save = tmp_token;
						}
						break;
					}
				}
				else{
					break;
				}
				next++;
				next_token = next_token + refill - 1;
			}
			tmp_token = tmp_token - save;
			play[i] = play[i] + tmp_token;
			total_fun = total_fun + (play[i]*fun[i]);
			tmp_token = min(save + refill, cap);
			save = 0;
		}
	}

	// time(&finish_time);

	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start); 

	cout << "play list: ";
	for(int i = 0; i < play.size(); i++){
		cout << play[i] << ", ";
	}
	cout << endl;

	cout << "The optimal solution of total fun: " << total_fun << endl;

	cout << "Execution time: " << duration.count() << endl;

	cout << "--------Seperate Line--------" << endl;
}while(signal == 1);

return 0;
}

