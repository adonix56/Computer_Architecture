#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

class mem
{
public:
	string page;
	bool usebit;
};

class type
{
public:
	string address;
};

int addClk(int clk)
{
	int ret;
	if(clk == 3)
		ret = 0;
	else
		ret = clk + 1;
	return ret;
}

int main(int arg, char* args[]) {
	ifstream input;
	input.open(args[1]);
	ofstream output_File ("vm-out.txt");

	mem RAM[4];
	for(int i = 0; i < 4; i++)
		RAM[i].usebit = true;
	type RAM_Types[16];

	int clk = 0;

	if(input_File.is_open() && output_File.is_open())
	{
		for(int i = 0; i < 16; i++)
			getline(input_File, RAM_Types[i].address);
		while(!input_File.eof())
		{
			string address;
			getline(input_File, address);
			if(address.length() > 2)
			{
				address = address.substr(0,5);

				for(int i = 0; i < 16; i++)
				{
					if(!address.compare(RAM_Types[i].address.substr(0,5))) //find the address
					{
						if(RAM[0].page.compare(RAM_Types[i].address) &&  //if address not in RAM
							RAM[1].page.compare(RAM_Types[i].address) &&
							RAM[2].page.compare(RAM_Types[i].address) &&
							RAM[3].page.compare(RAM_Types[i].address))
						{
							if(RAM[0].usebit == true && //if address not in RAM
								RAM[1].usebit == true && //and all use bits set to true
								RAM[2].usebit == true &&
								RAM[3].usebit == true)
							{
								RAM[clk].page = RAM_Types[i].address; //go around circle
								clk = addClk(clk);
								for(int j = 0; j < 3; j++)
								{
									RAM[clk].usebit = false;
									clk = addClk(clk);
								}
								clk = addClk(clk);
							}
							else  //if address not in RAM
							{     //there is a 0 use bit
								bool write = false;
								if(RAM[clk].usebit == 1)
								{
									RAM[clk].usebit = false;
									clk = addClk(clk);
								}
								while(!write)
								{
									if(RAM[clk].usebit == 0)
									{
										RAM[clk].page = RAM_Types[i].address;
										RAM[clk].usebit = true;
										clk = addClk(clk);
										write = true;
									}
									else
										clk = addClk(clk);
								}
							}
						}
						else if(!RAM[0].page.compare(RAM_Types[i].address))
						{
							RAM[0].usebit = true;
							//clk = 0;
						}
						else if(!RAM[1].page.compare(RAM_Types[i].address))
						{
							//clk = 1;
							RAM[1].usebit = true;
						}
						else if(!RAM[2].page.compare(RAM_Types[i].address))
						{
							//clk = 2;
							RAM[2].usebit = true;
						}
						else
						{
							//clk = 3;
							RAM[3].usebit = true;
						}
					}
				}
				// output
				string Final;
				Final = RAM[0].page;
				for(int j = 1; j < 4; j++)
				{
					if(RAM[j].page.length() > 2)
						Final = Final + " " + RAM[j].page;
				}
				output_File << Final << "\n";
			}
		}
	}
	else
		cout << "File Open Failed!\n";

	for(int i = 0; i < 16; i++)
		cout << RAM_Types[i].address << endl;

	system("PAUSE");
	return 0;
}