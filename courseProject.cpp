/*
	Team 5 - A1 batch
	
	Problem statement : A company wants to build a fitness app that tracks walking, sleeping
			    and water consumption details. Help the company in building the app;
	
	Authors :
		1) Amogh Shrikant Dodawad - 01FE21BCS114 - 120
		2) Abhishek Pravin Teli   - 01FE21BCS120 - 124
		
	Under the guidance of :
		Prof. Manjunath Gonal
*/

#include <iostream>
#include <string>
#include <utility>
#include <set>
#include <unordered_map>
#include <memory>

using namespace std;

class Activity {
	public :
		virtual void print () = 0;
};

class WalkingTracker : public Activity {
	private :
		int stepsPerDayWalked;
		int goalForStepsPerDay;
		
		WalkingTracker() {
			this->stepsPerDayWalked = 0;
			this->goalForStepsPerDay = 0;
		}
		
		WalkingTracker(int steps, int goals) : stepsPerDayWalked(steps), goalForStepsPerDay(goals) {
		
		}
		
	public :
		void print(){
			cout << "-----------------Printing Walking Details---------------\n";
			cout << "Steps walked today = " << this->stepsPerDayWalked << "\n";
			cout << "Steps goals today = " << this->goalForStepsPerDay << "\n";
			cout << "--------------------------------------------------------\n";
		}
		
		bool updateStepsWalked(int stepsWalked){
			if(stepsWalked < 0){
				return false;
			}
			this->stepsPerDayWalked = stepsWalked;
			return true;
		}
		
		bool updateGoals(int goals){
			if(goals < 0){
				return false;
			}
			this->goalForStepsPerDay = goals;
			return true;
		}
		
		friend class FeatureFactory;
};

class WaterConsumptionTracker : public Activity {
	private :
		int litresPerDayDrank;
		int goalForLitresPerDay;
		
		WaterConsumptionTracker() {
			this->litresPerDayDrank = 0;
			this->goalForLitresPerDay = 0;
		}
		
		WaterConsumptionTracker(int litres, int goals) : litresPerDayDrank(litres), goalForLitresPerDay(goals){
		
		}
		
	public :
		void print(){
			cout << "-----------Printing Water Consumption Details-----------\n";
			cout << "Litres drank today = " << this->litresPerDayDrank << "\n";
			cout << "Goal in litres today = " << this->goalForLitresPerDay << "\n";
			cout << "--------------------------------------------------------\n";
		}
		
		bool updateLitresDrank(int litres){
			if(litres < 0){
				return false;
			}
			this->litresPerDayDrank = litres;
			return true;
		}
		
		bool updateGoals(int goals){
			if(goals < 0){
				return false;
			}
			this->goalForLitresPerDay = goals;
			return true;
		}
		
		friend class FeatureFactory;
};

class SleepTracker : public Activity {
	private :
		int hoursSlept;
		int goalForHoursSlept;
		
		SleepTracker() {
			this->hoursSlept = 0;
			this->goalForHoursSlept = 0;
		}
		
		SleepTracker(int hours, int goals): hoursSlept(hours), goalForHoursSlept(goals) {
		
		}
		
	public :
		void print(){
			cout << "---------------Printing Sleeping Details----------------\n";
			cout << "Hours slept today = " << this->hoursSlept << "\n";
			cout << "Goal in hours today = " << this->goalForHoursSlept << "\n";
			cout << "--------------------------------------------------------\n";
		}
		
		bool updateHoursSlept(int hoursSlept){
			if(hoursSlept < 0){
				return false;
			}
			this->hoursSlept = hoursSlept;
			return true;
		}
		
		bool updateGoals(int goals){
			if(goals < 0){
				return false;
			}
			this->goalForHoursSlept = goals;
			return true;
		}
		
		friend class FeatureFactory;
};


class FeatureFactory {
	private :
		FeatureFactory() {}
		static std::shared_ptr<FeatureFactory> instance;
		
	public : 
		static std::shared_ptr<FeatureFactory> getInstance(){
			class Enabler : public FeatureFactory{};
			if(!instance){
				instance = std::make_shared<Enabler>();
			}
			return instance;
		}
		
		Activity* addActivity(string event){
		
			if(event == "Walking"){
				return new WalkingTracker;
			} else if (event == "DrinkingWater"){
				return new WaterConsumptionTracker;
			} else if (event == "Sleeping"){
				return new SleepTracker;
			}
			return NULL;
		}
		
		Activity* addActivityWithParams(string event,int count, int goal){
		
			if(event == "Walking"){
				return new WalkingTracker(count,goal);
			} else if (event == "DrinkingWater"){
				return new WaterConsumptionTracker(count,goal);
			} else if (event == "Sleeping"){
				return new SleepTracker(count,goal);
			}
			return NULL;
		}
		
};

std::shared_ptr<FeatureFactory> FeatureFactory::instance = NULL;

class User {
	private :
		int userId;
		unordered_map<string,Activity*> activities; 
		std::shared_ptr<FeatureFactory> factory;
		
	public :
		User(){
			this->userId = -1;
			this->factory = FeatureFactory::getInstance();
			this->activities["Walking"] = NULL;
			this->activities["DrinkingWater"] = NULL;
			this->activities["Sleeping"] = NULL;
		}
		
		User(int userId){
			this->factory = FeatureFactory::getInstance();
			this->activities["Walking"] = NULL;
			this->activities["DrinkingWater"] = NULL;
			this->activities["Sleeping"] = NULL;
			this->userId = userId;
		}
		
		bool setWalkingDetails(){
						
			try {
				if(!factory){
					throw "Factory not accessible : Walking tracker couldn't be set\n";
				}
				
				int numberOfSteps,goal;
				cout << "Enter the number of steps that you would like to walk each day\n";
				cin >> goal;
				if(goal < 0){
					throw "Goal should be greater than 0\n";
				}
				
				cout << "Enter the number of steps you walked today\n";
				cin >>numberOfSteps;
				
				if(numberOfSteps < 0){
					throw "Number of steps cannot be less than 0\n";
				}
				
				this->activities["Walking"] = factory->addActivityWithParams("Walking",numberOfSteps,goal);

			} catch (const char *msg){
				cout << msg;
				return false;
			}
			return true;
		}
		
		bool setWaterConsumptionDetails(){
			
			try {
				if(!factory){
					throw "Factory not accessible : Water consumption tracker couldn't be set\n";
				}	
						
				int numberOfLitres,goal;
				cout << "Enter the number of litres of water that you would like to drink each day\n";
				cin >> goal;
				if(goal < 0){
					throw "Goal should be greater than 0\n";
				}
				
				cout << "Enter the number of litres of water you drank today\n";
				cin >>numberOfLitres;
				
				if(numberOfLitres < 0){
					throw "Number of litres cannot be less than 0\n";
				}
				
				this->activities["DrinkingWater"] = factory->addActivityWithParams("DrinkingWater",numberOfLitres,goal);
				
			} catch (const char *msg){
				cout << msg;
				return false;
			}
			return true;
		}
		
		bool setSleepDetails(){
			
			try {
				if(!factory){
					throw "Factory not accessible : Sleep tracker couldn't be set\n";
				}
								
				int numberOfHours,goal;
				cout << "Enter the number of hours that you would like to sleep each day\n";
				cin >> goal;
				if(goal < 0){
					throw "Goal should be greater than 0\n";
				}
				
				cout << "Enter the number of hours you slept today\n";
				cin >>numberOfHours;
				
				if(numberOfHours < 0){
					throw "Number of hours cannot be less than 0\n";
				}
				
				this->activities["Sleeping"] = factory->addActivityWithParams("Sleeping",numberOfHours,goal);
				
			} catch (const char *msg){
				cout << msg;
				return false;
			}
			return true;
		}
		
		bool setDetails(){
			if(!this->setWalkingDetails()){
				return false;
			}
			
			if(!this->setWaterConsumptionDetails()){
				return false;
			}
			
			if(!this->setSleepDetails()){
				return false;
			}
			
			return true;
		}
		
		bool updateStepsWalked(int metric){
			if(!activities["Walking"]){
				activities["Walking"] = factory->addActivityWithParams("Walking",metric,metric);
				return true;
			}
			return ((WalkingTracker*)this->activities["Walking"])->updateStepsWalked(metric);
		}
		
		bool updateStepsWalkedGoals(int metric){
			if(!activities["Walking"]){
				activities["Walking"] = factory->addActivityWithParams("Walking",metric,metric);
				return true;
			}
			return ((WalkingTracker*)this->activities["Walking"])->updateGoals(metric);
		}
		
		bool updateLitresDrank(int metric){
			if(!activities["DrinkingWater"]){
				activities["DrinkingWater"] = factory->addActivityWithParams("DrinkingWater",metric,metric);
				return true;
			}
			return ((WaterConsumptionTracker*)this->activities["DrinkingWater"])->updateLitresDrank(metric);
		}
		
		bool updateLitresDrankGoals(int metric){
			if(!activities["DrinkingWater"]){
				activities["DrinkingWater"] = factory->addActivityWithParams("DrinkingWater",metric,metric);
				return true;
			}
			return ((WaterConsumptionTracker*)this->activities["DrinkingWater"])->updateGoals(metric);
		}
		
		bool updateHoursSlept(int metric){
			if(!activities["Sleeping"]){
				activities["Sleeping"] = factory->addActivityWithParams("Sleeping",metric,metric);
				return true;
			}
			return ((SleepTracker*)this->activities["Sleeping"])->updateHoursSlept(metric);
		}
		
		bool updateHoursSleptGoals(int metric){
			if(!activities["Sleeping"]){
				activities["Sleeping"] = factory->addActivityWithParams("Sleeping",metric,metric);
				return true;
			}
			return ((SleepTracker*)this->activities["Sleeping"])->updateGoals(metric);
		}	
		
		void printWalkingDetails(){
			try {
				if(!this->activities["Walking"]){
					throw "Walking tracker not set\n";
				}
				this->activities["Walking"]->print();
			}
			catch (const char *msg){
				cout << msg;
			}
		}
		
		
		void printWaterConsumptionDetails(){
			try {
				if(!this->activities["DrinkingWater"]){
					throw "Water consumption tracker not set\n";
				}
				this->activities["DrinkingWater"]->print();
			}
			catch (const char *msg){
				cout << msg;
			}
		}
		
		void printSleepDetails(){
			try {
				if(!this->activities["Sleeping"]){
					throw "Sleep tracker not set\n";
				}
				this->activities["Sleeping"]->print();
			}
			catch (const char *msg){
				cout << msg;
			}
			
		}
		
		void print(){
			this->printWalkingDetails();
			this->printWaterConsumptionDetails();
			this->printSleepDetails();
		}
		
		int getUserId(){
			return this->userId;
		}
};

class Menu {
	public : 
		void display(){
		
			cout << "1: If you are a new user\n";
			cout << "2: If you are an existing user\n";
			return;
		}
		
		void displayOptionsForNewUser(){
		
			cout << "We have the option of tracking walking, sleep and water consumption per day\n";
			cout << "1: If you want to track all of them\n";
			cout << "2: If you want to track only walking\n";
			cout << "3: If you want to track only sleeping\n";
			cout << "4: If you want to track only water consumption\n";
			return;
		}
		
		void displayOptionsForExisitingUser(){
		
			cout << "We have the option of updating and printing walking, sleep and water consumption per day\n";
			cout << "1: If you want to update only walking\n";
			cout << "2: If you want to update only sleeping\n";
			cout << "3: If you want to update only water consumption\n";
			cout << "4: If you want to print all details\n";
			cout << "5: If you want to print walking details\n";
			cout << "6: If you want to print sleeping details\n";
			cout << "7: If you want to print water details\n";
			return;
		}
		
		void displayUpdateOptions(){
		
			cout << "1: To update the metric\n";
			cout << "2: To update the goals\n";
		}
};

int main(){
	
	unordered_map<int,User*> users;
	int choice;
	int userId;
	int metric,goal;
	Menu menu;
	
	while(true){
		User *user;
		menu.display();
		cin >> choice;
		if(choice < 1 || choice > 2){
			cout << "Wrong choice entered\n";
			continue;
		}
		cout << "Enter the user id\n";
		cin >> userId;
		
		if(choice == 1){
			if(users[userId]){
				cout << "User already exists\n";
				continue;
			}
			
			user = new User(userId);
			menu.displayOptionsForNewUser();
			cin >> choice;
			int flag = 0;
			switch(choice){
				case 1 : flag = user->setDetails();
					 if(!flag){
					 	cout << "User tracking could not be initialised\n";
					 }
					 break;
					 
				case 2 : flag = user->setWalkingDetails();
					 if(!flag){
					 	cout << "User walking tracker could not be initialised\n";
					 }
					 break;
					 
				case 3 : flag = user->setSleepDetails();
					 if(!flag){
					 	cout << "User sleep tracker could not be initialised\n";
					 }
					 break;
					 
				case 4 : flag = user->setWaterConsumptionDetails();
					 if(!flag){
					 	cout << "User water consumption tracker could not be initialised\n";
					 }
					 break;
				default : cout << "Wrong Choice entered\n";
					  break; 
			}
			if(flag){
				users[userId] = user;
				user = NULL;
			} else {
				cout << "Error in processing: please restart again\n";
				free(user);
			}
			
		} else if(choice == 2){
			int flag = 0;
			
			if(!users[userId]){
				cout << "User doesn't exist\n";
				continue;
			}
			menu.displayOptionsForExisitingUser();
			cin >> choice;
			if(choice > 0 && choice < 4){
				menu.displayUpdateOptions();
			}
			
			switch(choice){
				case 1 : cin >> choice;
					 if(choice == 1){
					 
					 	cout << "Enter the metric\n";
					 	cin >> metric;
					 	flag = users[userId]->updateStepsWalked(metric);
					 	
					 } else if(choice == 2){
					 
					 	cout << "Enter the goal\n";
					 	cin >> goal;
					 	flag = users[userId]->updateStepsWalkedGoals(goal);
					 	
					 } else {
					 	cout << "Wrong choice entered\n";
					 }
					 break;
					 
				case 2 : cin >> choice;
					 if(choice == 1){
					 
					 	cout << "Enter the metric\n";
					 	cin >> metric;
					 	flag = users[userId]->updateHoursSlept(metric);
					 	if(!flag){
							cout << "Wrong choice entered\n";
							cout << "Re enter details again\n";
						}
					 	
					 } else if(choice == 2){
					 
					 	cout << "Enter the goal\n";
					 	cin >> goal;
					 	flag = users[userId]->updateHoursSleptGoals(goal);
					 	if(!flag){
							cout << "Wrong choice entered\n";
							cout << "Re enter details again\n";
						}
					 	
					 } else {
					 	cout << "Wrong choice entered\n";
					 }
					 break;
					 
				case 3 : cin >> choice;
					 if(choice == 1){
					 
					 	cout << "Enter the metric\n";
					 	cin >> metric;
					 	flag = users[userId]->updateLitresDrank(metric);
					 	if(!flag){
							cout << "Wrong choice entered\n";
							cout << "Re enter details again\n";
						}
					 	
					 } else if(choice == 2){
					 
					 	cout << "Enter the goal\n";
					 	cin >> goal;
					 	flag = users[userId]->updateLitresDrankGoals(goal);
					 	if(!flag){
							cout << "Wrong choice entered\n";
							cout << "Re enter details again\n";
						}
					 	
					 } else {
					 	cout << "Wrong choice entered\n";
					 }
					 break;
					 
				case 4 : users[userId]->print();
					 break;
					 
				case 5 : users[userId]->printWalkingDetails();
					 break;
					
				case 6 : users[userId]->printSleepDetails();
					 break;
					 
				case 7 : users[userId]->printSleepDetails();
					 break;
					 
				default : cout << "Wrong choice entered\n";
					 
			}
			
		} else {
			cout << "Wrong choice entered\n";
			cout << "Re enter details again\n";
		}
	}
		
	return 0;
}
