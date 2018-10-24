#pragma once
#include<iostream>
#include<sstream>
#include<vector>

extern const int WORD_SET_SIZE = 57;
extern const double OFF_SET;

int word_set_size = WORD_SET_SIZE;
std::vector<double> word_frequency(WORD_SET_SIZE, 0);
int spam_ham = 0;
int num_words = 0;



int isHam() { return spam_ham; }

double numWords() {return num_words;}

const std::vector<double>& wordFreq() {return word_frequency;}

void setEmailData(std::string &email_data)
{
	std::stringstream ss(email_data);

	std::string s;

	for(int i=0; i<word_set_size+1; i++)
	{
		getline(ss,s,',');
		std::stringstream toNumber(s);
		if(i == word_set_size)
		{
			toNumber>>spam_ham;
		}
		else
		{
			toNumber>>word_frequency[i];
			word_frequency[i] += OFF_SET;
			num_words += word_frequency[i];
		}
	}
}