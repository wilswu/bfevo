#include "funct.h"
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#define MEM 1000000

//runs brainfuck program
std::string run(std::string bf, std::string in){
	int pos = 0;
	int cpos = MEM/2;
	int ipos = 0;
	int cells[MEM];
	int layer;
	std::string out = "";
	while (pos < bf.length()){
		switch(bf.at(pos)){
		case '+':
			cells[cpos]++;
			break;
		case '-':
			cells[cpos]--;
			break;
		case '>':
			cpos++;
			break;
		case '<':
			cpos--;
			break;
		case '.':
			out += cells[cpos];
			break;
		case ',':
			if(ipos >= in.length())
				break;
			cells[cpos] = in.at(ipos);
			ipos++;
			break;
		case '[':
			if(cells[cpos] != 0)
				break;
			layer = 0;
			pos++;
			while(layer != 0 || bf.at(pos) != ']'){
				if(bf.at(pos) == '[')
					layer ++;
				if(bf.at(pos) == ']')
					layer --;
				pos ++;
			}
			break;
		case ']':
			if(cells[cpos] == 0)
				break;
			layer = 0;
			pos--;
			while(layer != 0 || bf.at(pos) != '['){
				if(bf.at(pos) == ']')
					layer ++;
				if(bf.at(pos) == '[')
					layer --;
				pos --;
			}
			break;
		default:
			break;
		}
		pos++;
	}
	return out;
}

//n = 8 for all symbols
//n = 6 to exclude brackets
char randsym(int n){
	char a;
	switch(rand() % n){
		case 0:
			a = '+';
			break;
		case 1:
			a = '-';
			break;
		case 2:
			a = '>';
			break;
		case 3:
			a = '<';
			break;
		case 4:
			a = '.';
			break;
		case 5:
			a = ',';
			break;
		case 6:
			a = '[';
			break;
		case 7:
			a = ']';
			break;
		default:
			break;
		}
	return a;
}

//Generates a random brainfuck program
std::string gen(){
	std::string bf = "";
	char a;
	for (int i = 0; i < 20; i++){
		a = randsym();
		if(i % 2 == 0)
			bf += a;
		else
			bf = a + bf;
		if(a == '[')
			bf += ']';
		if(a == ']')
			bf = '[' + bf;
	}
	return bf;
}

std::string mut(std::string in){
	char a;
	int layer;
	int pos;
	for(int i = 0; i < in.length(); i++){
		if(rand() % 15 == 0){
			a = randsym();
			if(a == '['){
				layer = 0;
				pos = i;
				while(layer != 0 || in.at(pos) != ']'){
					if(in.at(pos) == '[')
						layer ++;
					if(in.at(pos) == ']')
						layer --;
					pos ++;
				}
			}
		}
	}
}

//levenshtein distance between two strings
int dist(std::string a, std::string b){
	int m = a.length();
	int n = b.length();
	int dp[m + 1][n + 1];
	for(int i = 0; i < m; i++)
		for(int j = 0; j < n; j++)
			dp[i][j] = 0;
	for(int i = 0; i <= m; i++)
		dp[i][0] = i;
	for(int i = 0; i <= n; i++)
		dp[0][i] = i;
	for(int j = 1; j <= n; j++){		
		for(int i = 1; i <= m; i++){
			if(a.at(i - 1) == b.at(j - 1))
				dp[i][j] = dp[i - 1][j - 1];
			else
				dp[i][j] = std::min(dp[i - 1][j] + 1, std::min(dp[i - 1][j - 1] + 1, dp[i][j - 1] + 1));
		}
	}
	return dp[m][n];
}

int main(){
	srand(time(NULL));
	std::string str;
	for(int i = 0; i < 10; i++){
		str = gen();
		std::cout << str <<  ' ' << str.length() << std::endl;
	}
}
