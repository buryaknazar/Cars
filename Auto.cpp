// Nazar Buryak Andriyovuch
// Home Work - 028

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

class Car {
public:
	string name;
	string year;
	string v;
	string price;

	Car(string name, string year, string v, string price) : name{ name }, year{ year }, v{ v }, price{price}{}
	~Car() {}

	bool operator>(const Car& other) {
		int ThisPrice = atoi(price.c_str());
		int OtherPrice = atoi(other.price.c_str());

		if (ThisPrice > OtherPrice) return true;
		return false;
	}

	bool operator<(const Car& other) {
		int ThisPrice = atoi(price.c_str());
		int OtherPrice = atoi(other.price.c_str());

		if (ThisPrice < OtherPrice) return true;
		return false;
	}
};

class CarShowroom {
protected:
	vector<Car> cars;

public:

	CarShowroom() {}

	void AddCar(Car car) {
		cars.push_back(car);
		Save();
	}

	void Save() {
		ofstream save;

		save.open("cars.txt");

		if (!save.is_open()) {
			throw exception("Error, cannot write data!");
			return;
		}
		else {
			for (auto it : cars) {
				save << it.name << "," << it.year << "," << it.v << "," << it.price << endl;
			}
		}

		save.close();
	}

	void Load() {
		fstream load;
		
		load.open("cars.txt");

		if (!load.is_open()) {
			throw exception("Error, cannot read file!");
			return;
		}
		else {
			string tmp;
			while (getline(load, tmp)) {
				vector<string> cars_string;
				string car_string = "";
				for (char it : tmp) {
					if (it == ',') {
						cars_string.push_back(car_string);
						car_string = "";
					}
					else {
						car_string += it;
					}
				}
				cars_string.push_back(car_string);
				Car LoadedCar(cars_string[0], cars_string[1], cars_string[2], cars_string[3]);
				cars.push_back(LoadedCar);
			}
		}

		load.close();
	}

	void DeleteCar(string name) {
		bool Delete = false;
		for (int i = 0; i < cars.size(); ++i) {
			if (cars[i].name == name) {
				cars.erase(cars.begin() + i);
				Save();

				Delete = true;
				cout << "The car was deleted!" << endl;

				return;
			}
		}

		if (!Delete) {
			cout << "Didnt find car!" << endl;
			return;
		}

	}

	vector<Car> searchByYear(string year) {
		vector<Car> res;
		for (auto it : cars) {
			if (it.year == year)
				res.push_back(it);
		}
		return res;
	}
	
	vector<Car> searchByName(string name) {
		vector<Car> res;
		for (auto it : cars) {
			if (it.name == name)
				res.push_back(it);
		}
		return res;
	}

	vector<Car> searchByVolume(string volume) {
		vector<Car> res;
		for (auto it : cars) {
			if (it.v == volume)
				res.push_back(it);
		}
		return res;
	}

	vector<Car> searchByPrice(string price) {
		vector<Car> res;
		for (auto it : cars) {
			if (it.price == price)
				res.push_back(it);
		}
		return res;
	}

	void SortByPrice() {
		sort(cars.begin(), cars.end());
		Save();
	}

	void Print() {
		for (auto c : cars) {
			cout << "Name: " << c.name << endl;
			cout << "Year: " << c.year << endl;
			cout << "Volume: " << c.v << endl;
			cout << "Price: " << c.price << endl;
			cout << endl;
		}
	}

	void operator() (vector<Car> cars) {
		for (auto c : cars) {
			cout << "Name: " << c.name << endl;
			cout << "Year: " << c.year << endl;
			cout << "Volume: " << c.v << endl;
			cout << "Price: " << c.price << endl;
			cout << endl;
		}
	}
};

int main() {
	CarShowroom cars;
	cars.Load();

	while (true) {
		int choose;
		cout << "What do you want to do?" << endl;
		cout << "0 - print cars, 1 - add car, 2 - delete car, 3 - search car by name, 4 - search car by year, 5 - search car by price, 6 - search car by volume, 7 - exit : ";
		cin >> choose;

		if (choose == 0) {
			cout << "All cars:" << endl;
			cars.Print();
		}
		if (choose == 1) {
			string name, year, v, price;

			cout << "Enter name: ";
			cin >> name;
			cout << "Enter year: ";
			cin >> year;
			cout << "Enter volume: ";
			cin >> v;
			cout << "Enter price: ";
			cin >> price;

			Car car(name, year, v, price);
			cars.AddCar(car);
		}
		if (choose == 2) {
			string name;

			cout << "Enter name of car that you want to delete:";
			cin >> name;

			cars.DeleteCar(name);
		}
		if (choose == 3) {
			string name;

			cout << "Enter name of car that you want to find:";
			cin >> name;

			vector<Car> find = cars.searchByName(name);
			cars(find);
		}
		if (choose == 4) {
			string year;

			cout << "Enter year of car that you want to find:";
			cin >> year;

			vector<Car> find = cars.searchByYear(year);
			cars(find);
		}
		if (choose == 5) {
			string volume;

			cout << "Enter volume of car that you want to find:";
			cin >> volume;

			vector<Car> find = cars.searchByVolume(volume);
			cars(find);
		}
		if (choose == 6) {
			string price;

			cout << "Enter price of car that you want to find:";
			cin >> price;

			vector<Car> find = cars.searchByYear(price);
			cars(find);
		}
		if (choose == 7) {
			break;
		}
	}

	return 0;
}
