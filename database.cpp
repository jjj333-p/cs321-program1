#include "personal.h"
#include "student.h"
#include "database.h"

template<class T>
Database<T>::Database() {
}

template<class T>
Database<T>::~Database() {
	const string tmp_fName = "tmp_" + string(fName, 20);

	//open a temporary database to write to
	fstream tmpDatabase;
	tmpDatabase.open(tmp_fName, ios::in | ios::out | ios::binary | ios::trunc);
	tmpDatabase.clear();

	//same as modify() sample code
	T tmp;
	database.open(fName, ios::in | ios::out | ios::binary);
	database.clear();
	while (!database.eof()) {

		//read from existing database file
		tmp.readFromFile(database);

		//only write if not tombstoned
		if (tmp.isNull())
			continue;

		//seek and write to new file
		tmpDatabase.seekp(tmp.size(), ios::cur);
		tmp.writeToFile(tmpDatabase);
	}

	//close databases
	tmpDatabase.close();
	database.close();

	//move tmp file to main file
	std::remove(fName);
	std::rename(tmp_fName.c_str(), fName);
}


template<class T>
void Database<T>::add(T& d) {
	database.open(fName, ios::in | ios::out | ios::binary);
	database.clear();
	database.seekp(0, ios::end);
	d.writeToFile(database);
	database.close();
}

template<class T>
void Database<T>::modify(const T& d) {
	T tmp;
	database.open(fName, ios::in | ios::out | ios::binary);
	database.clear();
	while (!database.eof()) {
		tmp.readFromFile(database);
		if (tmp == d) {  // overloaded ==
			cin >> tmp; // overloaded >>
			database.seekp(-d.size(), ios::cur);
			tmp.writeToFile(database);
			database.close();
			return;
		}
	}
	database.close();
	cout << "The record to be modified is not in the database\n";
}

template<class T>
void Database<T>::remove(const T& d) {
	T tmp;
	database.open(fName, ios::in | ios::out | ios::binary);
	database.clear();
	while (!database.eof()) {
		tmp.readFromFile(database);
		if (tmp == d) {  // overloaded ==
			database.seekp(-d.size(), ios::cur);
			tmp.writeNullToFile(database);
			database.close();
			return;
		}
	}
	database.close();
	cout << "The record to be removed is not in the database\n";
}

template<class T>
bool Database<T>::find(const T& d) {
	T tmp;
	database.open(fName, ios::in | ios::binary);
	database.clear();
	while (!database.eof()) {
		tmp.readFromFile(database);
		if (tmp == d) { // overloaded ==
			database.close();
			return true;
		}
	}
	database.close();
	return false;
}

template<class T>
ostream& Database<T>::print(ostream& out) {
	T tmp;
	database.open(fName, ios::in | ios::binary);
	database.clear();
	while (true) {
		tmp.readFromFile(database);
		if (database.eof())
			break;
		//tombstoned value
		if (tmp.isNull())
			continue;
		out << tmp << endl; // overloaded <<
	}
	database.close();
	return out;
}

template<class T>
void Database<T>::run() {
	cout << "File name: ";
	cin >> fName;
	cin.ignore();	// skip '\n';
	database.open(fName, ios::in);
	if (database.fail())
		database.open(fName, ios::out);
	database.close();
	char option[5];
	T rec;
	cout << "1. Add 2. Find 3. Modify a record; 4. Remove a record; 5. Exit\n";
	cout << "Enter an option: ";
	while (cin.getline(option, 5)) {

		switch (*option) {
			case '1':
				cin >> rec;   // overloaded >>
				add(rec);
				break;
			case '2':
				rec.readKey();
				cout << "The record is ";
				if (find(rec) == false)
					cout << "not ";
				cout << "in the database\n";
				break;
			case '3':
				rec.readKey();
				modify(rec);
				break;
			case '4':
				rec.readKey();
				remove(rec);
				break;
			case '5':
				return;
			default:
				cout << "Invalid option\n";
		}
		cout << *this;   // overloaded <<
		cout << "Enter an option: ";
	}
}

int main() {
	Database<Personal>().run();
	// Database<Student>().run();
	return 0;
}
