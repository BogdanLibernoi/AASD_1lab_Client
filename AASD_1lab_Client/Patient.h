#pragma once
#include <string>
#include <iostream>
#include <sstream>

enum Gender {
	male,
	female,
	not_selected_gender
};
enum Condition {
	normal,
	critical,
	dispensary,
	not_secelted_condition
};

class Patient
{
private:
	Gender gender;
	Condition condition;
	std::string firstName;
	std::string secondName;
	std::string patronymic;

	unsigned short int age;

public:
#pragma region Getters

	std::string GetFirstName() const {
		return firstName;
	}
	std::string GetSecontName() const {
		return secondName;
	}
	std::string GetPatronymic() const {
		return patronymic;
	}
	unsigned short GetAge() const {
		return age;
	}
	Gender GetGender() const {
		return gender;
	}
	Condition GetCondition() const {
		return condition;
	}

#pragma endregion

#pragma region Setters

	void SetFirstName(std::string firstN) {
		firstName = firstN;
	}
	void SetSecondName(std::string secondN) {
		secondName = secondN;
	}
	void setPatronymic(std::string patron) {
		patronymic = patron;
	}
	void setAge(int _age) {
		if (_age < 150)
		{
			age = _age;
		}
		else
			age = 18;

	}
	void setGender(Gender gen) {
		if (gen == male || gen == female)
			gender = gen;
		else
			gender = not_selected_gender;
	}
	void setCondition(Condition _con) {
		if (_con == dispensary || _con == normal || _con == critical)
			condition = _con;
		else
			condition = not_secelted_condition;
	}
#pragma endregion	

	std::string GetStringPatientInfo()
	{
		std::string patientInfo = "";
		patientInfo += (gender == 0 ? "male" : gender == 1 ? "female" : "not selected");
		patientInfo += " ";
		patientInfo += (condition == 0 ? "normal" : condition == 1 ? "critical" : condition == 2 ? "dispensary" : "not selected");
		patientInfo += " " + firstName + " " + secondName + " " + patronymic + " " + std::to_string(age);

		return patientInfo;
	}


#pragma region Constructors

	Patient()
		:gender(not_selected_gender), condition(not_secelted_condition),
		patronymic("Unknown"), secondName("Unknown"), firstName("Unknown"),
		age(18)
	{}

	Patient(Gender gender_, Condition condition_,
		std::string firstN, std::string secondN, std::string patronymic_, unsigned short int  age_)

		:gender(gender_), condition(condition_),
		firstName(firstN), secondName(secondN), patronymic(patronymic_),
		age(age_)
	{}

	Patient(Patient *pat)
		:gender(pat->gender), condition(pat->condition),
		patronymic(pat->patronymic), secondName(pat->secondName), firstName(pat->firstName),
		age(pat->age)
	{}

	Patient(std::string patientInfo_) 
	{
		//Парсинг строки в пациента	


			std::string tempString[6];
			std::stringstream readerStr(patientInfo_);

			int i = 0;
			while (std::getline(readerStr, patientInfo_, ' ')) 
			{
				tempString[i] = patientInfo_;
				i++;
			}
			
			gender = (tempString[0] == "male" ? male : female);

			condition = (tempString[1] == "normal" ? normal : tempString[1] == "dispensary" ? dispensary : critical);

			firstName = (tempString[2]); secondName = (tempString[3]); patronymic = (tempString[4]);

			age = (std::stoi(tempString[5]));
	}
#pragma endregion

}; 

inline std::ostream& operator<<(std::ostream &os, const Patient& pat)
{
	return os
		<< "Gender: " << (pat.GetGender() == 0 ? "male" : pat.GetGender() == 1 ? "female" : "not selected")
		<< " Condition: " << (pat.GetCondition() == 0 ? "normal" : pat.GetCondition() == 1 ? "critical" : pat.GetCondition() == 2 ? "dispensary" : "not selected")
		<< " Age: " << pat.GetAge() 
		<< " " << pat.GetFirstName() << " " << pat.GetSecontName() << " " << pat.GetPatronymic() << std::endl;
}



