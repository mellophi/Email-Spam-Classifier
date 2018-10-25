#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<math.h>
#include<vector>
#include"../Headers/preprocess.h"

//declaration of the off_set value
const double OFF_SET = 1.0/4000;

std::vector<double> operator+(std::vector<double>& A, const std::vector<double>& B)
{
    if(A.size() != B.size())
        throw "The vectors can not be added :(";
    std::vector<double> res;
    for(unsigned i=0; i<A.size(); i++)
        res.push_back(A[i]+B[i]);
    return res;
}

int main()
{
    std::vector<double> num_words_spam(WORD_SET_SIZE, 0);
    std::vector<double> num_words_ham(WORD_SET_SIZE, 0);
    std::vector<double> word_probability_size(WORD_SET_SIZE, 0);
    std::vector<double> word_probability_ham(WORD_SET_SIZE, 0);
    std::vector<double> word_probability_spam(WORD_SET_SIZE, 0);

    int num_spam = 0;
    int num_ham = 0;

    std::ifstream file;
    file.open("training_set.data");
    if(!file)
    {
        std::cerr<<"file cannot be opened";
        exit(1);
    }
    std::string email_data;
    while(!file.eof())
    {
        std::getline(file, email_data);
        setEmailData(email_data);
        if(isHam() == 1){
			num_spam++;
			num_words_spam = num_words_spam + wordFreq();
		}
		if(isHam() == 0){
			num_ham++;
			num_words_ham = num_words_ham + wordFreq();
		}
	}
	file.close();

	double total_words_spam = 0;
	double total_words_ham = 0;

	for(int i=0; i<57; i++)
    	{
		total_words_spam += num_words_spam[i];
		total_words_ham += num_words_ham[i];
	}

	for(int i=0;i<57;i++)
    	{
		word_probability_spam[i] = log(num_words_spam[i]/total_words_spam);
		word_probability_ham[i] = log(num_words_ham[i]/total_words_ham);
	}


	int num_test_email = 0;
	int num_ham_in_test = 0;
	int num_spam_in_test = 0;

	int ham_predict_as_ham = 0;
	int spam_predict_as_spam = 0;
	int ham_predict_as_spam = 0;
	int spam_predict_as_ham = 0;

	std::ifstream test;
	test.open("test_set.data");
	if(!test){
		std::cerr<<"cannot open the test set";
		exit(1);
	}

	while(!test.eof()){
		std::getline(test,email_data);
		setEmailData(email_data);
		num_test_email++;
		double log_ratio=0;

		for(int i=0;i<57;i++){
			log_ratio += word_probability_spam[i]*((wordFreq())[i]) - word_probability_ham[i]*((wordFreq())[i]);
		}
		log_ratio += log((double)num_spam) - log((double)num_ham);

		if(!isHam()) {num_ham_in_test++;}
		else {num_spam_in_test++;}
		if(log_ratio<0 && isHam()) ham_predict_as_ham++;
		if(log_ratio<0 && !isHam()) spam_predict_as_ham++;
		if(log_ratio>0 && isHam()) ham_predict_as_spam++;
		if(log_ratio>0 && !isHam()) spam_predict_as_spam++;
	}
	test.close();


	std::cout<<"The training set has "<<(num_ham + num_spam)<<" emails\n";
	std::cout<<"Spam emails: "<<num_spam<<"\n";
	std::cout<<"Ham emails: "<<num_ham<<"\n";
	
	std::cout<<"The test set has "<<num_test_email<<" emails\n";
	std::cout<<"Spam emails: "<<num_spam_in_test<<"\n";
	std::cout<<"Ham emails: "<<num_ham_in_test<<"\n";
	std::cout<<"Ham predicted as ham: "<<ham_predict_as_ham<<"\n";
	std::cout<<"Spam predicted as spam: "<<spam_predict_as_spam<<"\n";
	std::cout<<"Spam predicted as ham: "<<spam_predict_as_ham<<"\n";
	std::cout<<"Ham predicted as spam: "<<ham_predict_as_spam<<"\n";
	std::cout<<"The prediction accurary is: "<<(ham_predict_as_ham+spam_predict_as_spam)*1.0/num_test_email*100<<" percents\n";
	//system("pause");
	return 1;
}
