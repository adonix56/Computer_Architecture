//#include <fstream>
//#include <string>
//#include <iostream>
//#include <iomanip>
//
//using namespace std;
//
//class memRAM {
//	public:
//		string address;
//		bool usebit;
//		int number;
//		memRAM() {
//			usebit = false;
//		}
//};
//
//class VM {
//	public:
//		memRAM pages[4];
//		memRAM* fp;
//		VM() {
//			fp = &pages[0];
//			for(int i = 0; i < 4; i++)
//				pages[i].number = i;
//		}
//		bool fault(const string s) {
//			for(int i = 0; i < 4; i++) {
//				if(!s.compare(pages[i].address)) {
//					pages[i].usebit = true;
//					return false;
//				}
//			}
////			cout << "FAULT" << endl;
//			return true;
//		}
//		void set(const string s) {
////			cout << "current number " << fp->number << " usebit " << fp->use << endl;
//			if(fp->usebit == true) {
//				fp->usebit = false;
////				cout << "set " << fp->number << " to 0" << endl;
//				if(fp->number == 3)
//					fp = &pages[0];
//				else
//					fp = &pages[fp->number + 1];
//			}
//			fp->address = s;
//			fp->usebit = true;
////			cout << "changed " << fp->number << " usebit " << fp->use << endl;
//			if(fp->number == 3)
//				fp = &pages[0];
//			else
//				fp = &pages[fp->number + 1];
//		}
//		friend ostream& operator<< (ostream& os, const VM& v);
//};
//
//ostream& operator << (ostream& os, const VM& v) {
//	for(int i = 0; i < 4 && !v.pages[i].address.empty(); i++) {
//		os << v.pages[i].address;
//		if(i == 3)
//			os << endl;
//		else if(!v.pages[i + 1].address.empty())
//			os << " ";
//		else
//			os << endl;
//	}
//	return os;
//}
//
//int main(int argc, char* argv[]) {
//	string input_FileName;
//	cout << "Please enter the file name to read: \n";
//	getline(cin, input_FileName);
//	ifstream input;
//	input.open(input_FileName.c_str());
//	ofstream output("vm-out.txt");
//	string addresses[16];
//	string check[16];
//	VM vm;
//	string temp;
//	
//	for(int i = 0; i < 16; i++) {
//		getline(input, addresses[i]);
//		check[i] = addresses[i];
//		while(check[i][check[i].length()-1] == '0')
//			check[i].erase(check[i].length()-1);
//	}
//	
//	while(getline(input,temp)) {
//		for(int j = 0; j < 16; j++) {
//			if(!temp.compare(0,check[j].length(),check[j],0,check[j].length())) {
//				temp = addresses[j];
//				break;
//			}
//		}
//		if(vm.fault(temp))
//			vm.set(temp);
//		output << vm;
//	}
//		
//	
//	input.close();
//	output.close();
//	
//	return 0;
//}

// William Lu wxlu
// Justin Salanga jmsalanga
// Aung Kyaw apkyaw
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

class Page {
	public:
		string address;
		int use;
		int number;
		Page() {
			use = 0;
		}
};

class VM {
	public:
		Page pages[4];
		Page* fp;
		VM() {
			fp = &pages[0];
			for(int i = 0; i < 4; i++)
				pages[i].number = i;
		}
		bool fault(const string s) {
			for(int i = 0; i < 4; i++) {
				if(!s.compare(pages[i].address)) {
					pages[i].use = 1;
					return false;
				}
			}
//			cout << "FAULT" << endl;
			return true;
		}
		void set(const string s) {
//			cout << "current number " << fp->number << " usebit " << fp->use << endl;
			while(fp->use == 1) {
				fp->use = 0;
//				cout << "set " << fp->number << " to 0" << endl;
				if(fp->number == 3)
					fp = &pages[0];
				else
					fp = &pages[fp->number + 1];
			}
			fp->address = s;
			fp->use = 1;
//			cout << "changed " << fp->number << " usebit " << fp->use << endl;
			if(fp->number == 3)
				fp = &pages[0];
			else
				fp = &pages[fp->number + 1];
		}
		friend ostream& operator<< (ostream& os, const VM& v);
};

ostream& operator << (ostream& os, const VM& v) {
	for(int i = 0; i < 4 && !v.pages[i].address.empty(); i++) {
		os << v.pages[i].address;
		if(i == 3)
			os << endl;
		else if(!v.pages[i + 1].address.empty())
			os << " ";
		else
			os << endl;
	}
	return os;
}

int main(int argc, char* argv[]) {
	string input_FileName;
	cout << "Please enter the file name to read: \n";
	getline(cin, input_FileName);
	ifstream input;
	input.open(input_FileName.c_str());
	ofstream output("vm-out.txt");
	string addresses[16];
	string check[16];
	VM vm;
	string temp;
	
	for(int i = 0; i < 16; i++) {
		getline(input, addresses[i]);
		check[i] = addresses[i];
		while(check[i][check[i].length()-1] == '0')
			check[i].erase(check[i].length()-1);
	}
	
	while(getline(input,temp)) {
		for(int j = 0; j < 16; j++) {
			if(!temp.compare(0,check[j].length(),check[j],0,check[j].length())) {
				temp = addresses[j];
				break;
			}
		}
		if(vm.fault(temp))
			vm.set(temp);
		output << vm;
	}
		
	
	input.close();
	output.close();
	
	return 0;
}