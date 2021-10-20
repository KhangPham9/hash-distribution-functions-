//Author: Khang Pham
//Programing Language: C++

#include <type_traits>
#include "boost_1_61_0/boost/math/distributions/chi_squared.hpp"
#include <cstdint>
#include <vector>
#include <fstream>
#include <iostream>
#include <cmath>


const int NUM = static_cast<int>(std::pow(2,16));


float pearson(const std::vector<int> &v)
{
	float c2 = 0;
	float exp = 99171 / 65536.0;
	for(unsigned i = 0; i < v.size(); i++)
	{
		c2 += (  (exp -  v.at(i)) * (exp - v.at(i)) ) / exp;
	}
	boost::math::chi_squared c2d(65535.0);
	float p = boost::math::cdf(c2d, c2);
	return p;

}

float length(std::vector<int> &hashes)
{
	std::fstream inFile;
	std::string s;
	inFile.open("words");
	int hash;
	while(inFile >> s)
	{
		hash = s.length() %  NUM;
		hashes.at(hash)++;
	}
	inFile.close();
	return pearson(hashes);

}

float first_char(std::vector<int> &hashes)
{
	std::fstream inFile;
	std::string s;
	inFile.open("words");
	int hash;
	while(inFile >> s)
	{
		int c = s[0] < 0 ? int(255 + s[0]) : int(s[0]);
		hash =  c;
		hashes.at(hash)++;
	}
	inFile.close();
	return pearson(hashes);

}

float char_sum(std::vector<int> &hashes)
{

	std::fstream inFile;
	std::string s;
	inFile.open("words");
	int hash;
	while(inFile >> s)
	{
		int result = 0;
		for(char c : s)
		{
			result = (c < 0) ? int(255 + c) : int(c);
			result += result;
		}
		hash = result % NUM;
		hashes.at(hash)++;
	}
	inFile.close();
	return pearson(hashes);

}

float remainder(std::vector<int> &hashes)
{
	std::fstream inFile;
	std::string s;
	inFile.open("words");
	int hash;
	while(inFile >> s)
	{
		int result = 0;
		for(char c : s)
		{
			int k = c < 0 ? int(255 + c) : int(c);
			result =  (result * 256 + k) % 65413;
		}

		hash = result;
		hashes.at(hash)++;
	}
	inFile.close();
	return pearson(hashes);

}

float multi(std::vector<int> &hashes)
{
	std::fstream inFile;
	std::string s;
	inFile.open("words");
	while(inFile >> s)
	{
		double result = 0;
		const double a =  (sqrt(5) - 1) / 2;

		for(char c : s)
		{
			int k = c < 0 ? int(255 + c) : int(c);
			result = fmod( (result * 256 + k) * a, 1) * 65413;  //using m = 65413
		}
		result = floor(result);
		hashes.at(result)++;
	}
	inFile.close();
	return pearson(hashes);
}
void print(const std::vector<int> &v)
{
	std::vector<int> sum(22, 0);

	for(unsigned i = 0; i < v.size(); i++)
	{
		if(i <= 2999)
			sum[0] += v[i];
		else if(i <= 5999)
			sum[1] += v[i];
		else if(i <= 8999)
			sum[2] += v[i];
		else if(i <= 11999)
			sum[3] += v[i];
		else if(i <= 14999)
			sum[4] += v[i];
		else if(i <= 17999)
			sum[5] += v[i];
		else if(i <= 20999)
			sum[6] += v[i];
		else if(i <= 23999)
			sum[7] += v[i];
		else if(i <= 26999)
			sum[8] += v[i];
		else if(i <= 29999)
			sum[9] += v[i];
		else if(i <= 32999)
			sum[10] += v[i];
		else if(i <= 35999)
			sum[11] += v[i];
		else if(i <= 38999)
			sum[12] += v[i];
		else if(i <= 41999)
			sum[13] += v[i];
		else if(i <= 44999)
			sum[14] += v[i];
		else if(i <= 47999)
			sum[15] += v[i];
		else if(i <= 50999)
			sum[16] += v[i];
		else if(i <= 53999)
			sum[17] += v[i];
		else if(i <= 56999)
			sum[18] += v[i];
		else if(i <= 59999)
			sum[19] += v[i];
		else if(i <= 62999)
			sum[20] += v[i];
		else if(i <= 65999)
			sum[21] += v[i];
	}

	int max = *max_element(sum.begin(), sum.end());

	int vertical_size = 20;
	int scale = floor(max / vertical_size);

	for(int i = vertical_size; i > 0; i--)
	{
		std::cout << std:: right << std::setfill(' ') << std::setw(8) << max - scale * (vertical_size - i) << std::left << std::setw(7) << '|';
		for(unsigned j = 0; j < sum.size(); j++)
		{

			if(sum[j] >= i * scale)
			{
				std::cout << '#';
				sum[j] -= scale;
			}

			else
				std::cout << ' ';
			std::cout << std::setw(7) << ' ';
		}
		std::cout << "|" << std::endl;
	}

	std::cout << "\t" << std::setfill('-') << std::setw(190) << ' ' << std::endl;
	std::cout << "\t0";
	for(unsigned i = 1; i <= sum.size(); i++)
	{
		std::cout << std::right << std::setfill(' ') << std::setw(7) << i * 3000 - 1 << ' ';
	}
	std::cout << std::endl;
}
void display()
{
	std::vector<int> slength(65536, 0);
	std::vector<int> character(65536, 0);
	std::vector<int> sum1(65536, 0);
	std::vector<int> sremainder(65536, 0);
	std::vector<int> smulti(65536, 0);
	std::cout << "string length method p value: " << length(slength) << std::endl;
	print(slength);
	std::cout << std::endl;

	std::cout << "first character method p value: " << first_char(character) << std::endl;
	print(character);
	std::cout << std::endl;

	std::cout << "character sum method p value: " << char_sum(sum1) << std::endl;
	print(sum1);
	std::cout << std::endl;

	std::cout << "remainder method p value: " << remainder(sremainder) << std::endl;
	print(sremainder);
	std::cout << std::endl;

	std::cout << "multiplicative method p value: " << multi(smulti) << std::endl;
	print(smulti);
	std::cout << std::endl;

}



int main()
{

	display();
	std::cout << "Make the terminal in fullscreen to see the results of the histograph correctly. The program is about 200 spaces horizontal in length." << std::endl;
	return 1;
}
