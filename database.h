#ifndef DATABASE
#define DATABASE

template<class T>
class Database {
public:
	Database();
	~Database();
	void run();
private:
	fstream database;
	char fName[20];
	ostream& print(ostream&);
	void add(T&);
	bool find(const T&);
	void modify(const T&);
	void remove(const T&);
	friend ostream& operator<<(ostream& out, Database& db) {
		return db.print(out);
	}
};

#endif
