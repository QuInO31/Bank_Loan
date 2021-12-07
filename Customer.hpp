#pragma once
#include "LinkedList.hpp"
#include <string>
#include <iostream>

class Customer
{
	std::string id_;
	int			age_ = 0;
	std::string sex_;
	std::string	region_;
	double		income_ = 0;
	std::string married_;
	int			children_ = 0;
	std::string car_;
	std::string	save_act_;
	std::string current_act_;
	std::string mortgage_;

public:
	std::string get_id() { return id_; }
	int			get_age() { return age_; }
	std::string get_sex() { return sex_; }
	std::string get_region() { return region_; }
	double		get_income() { return income_; }
	std::string get_married() { return married_; }
	int			get_children() { return children_; }
	std::string get_car() { return car_; }
	std::string get_save_act() { return save_act_; }
	std::string get_current_act() { return current_act_; }
	std::string get_mortgage() { return mortgage_; }

	double ageRisk_ = 0;
	double sexRisk_ = 0;
	double regionRisk_ = 0;
	double incomeRisk_ = 0;
	double marriedRisk_ = 0;
	double childrenRisk_ = 0;
	double carRisk_ = 0;
	double save_actRisk_ = 0;
	double current_actRisk_ = 0;
	double mortgageRisk_ = 0;
	bool isApproved = false;
	double totalRisk = 0;

	bool operator == (const Customer& rhs) const {
		return id_ == rhs.id_;
	}

	bool operator > (const Customer& rhs) const {
		return totalRisk > totalRisk;
	}

	Customer() = default;
	/*Customer(std::string name) : name_(name)
	{

	}*/
	Customer(std::string id, int age, std::string sex, std::string region, double income, std::string married, 
		int children, std::string car, std::string save_act, std::string current_act, std::string mortgage)
		: id_(id), age_(age), sex_(sex), region_(region), income_(income), married_(married), children_(children),
			car_(car), save_act_(save_act), current_act_(current_act), mortgage_(mortgage)
	{

	}

	/*void setScore(int a, int b, int c)
	{
		score_ = a + b + c;
	}
	
	std::string tostring() {
		std::string result = id_ + ", " + std::to_string(age_) + ", " + sex_ + ", " + region_ + ", " + std::to_string(income_) + ", " + married_ + ", " + std::to_string(children_) + ", " + car_ + ", " + save_act_ + ", " + current_act_ + ", " + mortgage_;
		return result;
	}
	*/

	std::string tostring() {
		std::string ia;
		if (isApproved)
		{
			ia = "true";
		}
		else
		{
			ia = "false";
		}
		std::string result = id_ + "," + std::to_string(age_) + "," + sex_ + "," + region_ + "," + std::to_string(income_) + "," + married_ + "," + std::to_string(children_) + "," + car_ + "," + save_act_ + "," + current_act_ + "," + mortgage_ + ", Total Risk: " + std::to_string(totalRisk) + ", Approved: " + ia;
		return result;
	}
	
	std::string toFile() {
		std::string ia;
		if (isApproved)
		{
			ia = "true";
		}
		else
		{
			ia = "false";
		}
		std::string result = id_ + "," + std::to_string(age_) + "," + sex_ + "," + region_ + "," + std::to_string(income_) + "," + married_ + "," + std::to_string(children_) + "," + car_ + "," + save_act_ + "," + current_act_ + "," + mortgage_ + "," + std::to_string(totalRisk) + "," + ia;
		return result;
	}

};
