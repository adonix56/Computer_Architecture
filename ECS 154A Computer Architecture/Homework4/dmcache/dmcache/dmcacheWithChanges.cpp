// Name: dmcache.cpp
//
// Author: Justin Salanga
//
// 256 byte Direct-mapped Cache
// 
// C = 256 bytes
// L = 8 bytes
// A = 16 bits
// Lines = C / L = 32
// Offset = log2(32) = 5 bits
//

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

class mem
{
public:
	string tag;
	string set;
	string offset;
	string data;
	bool dirty;
	bool valid;
};

string HextoBin (string sHex)
{
	string sReturn = "";
	for (int i = 0; i < sHex.length (); ++i)
	{
		switch (sHex [i])
		{
			case '0': sReturn.append ("0000"); break;
			case '1': sReturn.append ("0001"); break;
			case '2': sReturn.append ("0010"); break;
			case '3': sReturn.append ("0011"); break;
			case '4': sReturn.append ("0100"); break;
			case '5': sReturn.append ("0101"); break;
			case '6': sReturn.append ("0110"); break;
			case '7': sReturn.append ("0111"); break;
			case '8': sReturn.append ("1000"); break;
			case '9': sReturn.append ("1001"); break;
			case 'A': sReturn.append ("1010"); break;
			case 'B': sReturn.append ("1011"); break;
			case 'C': sReturn.append ("1100"); break;
			case 'D': sReturn.append ("1101"); break;
			case 'E': sReturn.append ("1110"); break;
			case 'F': sReturn.append ("1111"); break;
		}
	}
	return sReturn;
}

string DectoBin (int number)
{
	string answer;
	if (number == 0) return "0";
	if (number == 1) return "1";
	if (number % 2 == 0) return DectoBin(number / 2) + "0";
	else return DectoBin(number / 2) + "1";
}

int BintoDec(string number)
{
	int result = 0, pow = 1;
	for (int i = number.length() - 1; i >= 0; --i, pow <<= 1)
		result += (number[i] - '0') * pow;
	return result;
}

int main()
{
	string input_FileName;
	cout << "Please enter the file name to read: \n";
	getline(cin, input_FileName);
	cout << "Loading...\n";

	ifstream input_File;
	input_File.open(input_FileName);
	ofstream output_File ("dm-out.txt");
	
	string output;
	string address;
	string rw;
	string data;
	int hit;
	bool did_write = false;
	bool did_read = false;///////////v2.0
	bool dirty = false;

	int const cache_size = 256;
	int const memory_size = 65536;
	string* memdata = new string[memory_size];

	mem cache[cache_size];

	for(int i = 0; i < memory_size; i++)
	{
		ostringstream ss;
		address = DectoBin(i);
		ss << setw(16) << setfill('0') << address;
		address = ss.str();

		memdata[i] = "00";

		if(i < cache_size)
		{
			cache[i].tag = address.substr(0,8); // TAG = bits 8:15
			cache[i].set = address.substr(8,5); // SET = bits 3:7
			cache[i].offset = address.substr(13,3); //OFFSET = bits 0:2
			cache[i].data = "00";
			cache[i].dirty = false;
			cache[i].valid = false;
		}
	}

	if(input_File.is_open() && output_File.is_open())
	{
		while (!input_File.eof())
		{
			getline(input_File, output);

			if(output.size() > 2)
			{
				address = output.substr(0,4);
				address = HextoBin(address);
				rw = output.substr(5,2);
				data = output.substr(8,2);

				if(!rw.compare("FF")) //WRITE
				{
					did_write = false;
					for(int i = 0; i < cache_size;i++)
					{
						if(!did_write)
						{
							if(!cache[i].set.compare(address.substr(8,5))) //find SET
							{
								for (int j = i - 8; j < i + 8; j++)//set to dirty ///////////v2.0
								{                                                 ///////////v2.0
									if(j < 0) j = 0;                              ///////////v2.0
									if(j >= cache_size)                           ///////////v2.0
									{                                             ///////////v2.0
										int jnew = cache_size - 1;                ///////////v2.0
										if(!cache[jnew].set.compare(cache[i].set))///////////v2.0
											cache[j].dirty = true;                ///////////v2.0
									}                                             ///////////v2.0
									else                                          ///////////v2.0
									{                                             ///////////v2.0
										if(!cache[j].set.compare(cache[i].set))   ///////////v2.0
											cache[j].dirty = true;                ///////////v2.0
									}                                             ///////////v2.0
								}                                                 ///////////v2.0
								if(cache[i].tag.compare(address.substr(0,8))) //if TAG different
								{
									for(int j = i - 8; j < i + 8; j++) //set all new TAGs
									{
										if (j < 0) j = 0;
										if (j >= cache_size) 
										{
											int jnew = cache_size - 1;
											if(!cache[jnew].set.compare(cache[i].set))//within set confides
											{
												int memadd = BintoDec(cache[jnew].tag + cache[jnew].set + cache[jnew].offset);
												if(cache[jnew].dirty)
												{
													memdata[memadd] = cache[jnew].data; //move cache data to mem
													//cache[jnew].dirty = false;     ///////////v2.0
												}
												cache[jnew].tag = address.substr(0,8); //remove old tags,set new tags
												memadd = BintoDec(cache[jnew].tag + cache[jnew].set + cache[jnew].offset);
												cache[jnew].data = memdata[memadd]; //move mem data to cache
											}
										}
										else
										{
											if(!cache[j].set.compare(cache[i].set))//within set confides
											{
												int memadd = BintoDec(cache[j].tag + cache[j].set + cache[j].offset);
												if(cache[j].dirty)
												{
													memdata[memadd] = cache[j].data; //move cache data to mem
													//cache[j].dirty = false;     ///////////v2.0
												}
												cache[j].tag = address.substr(0,8); //remove old tags,set new tags
												memadd = BintoDec(cache[j].tag + cache[j].set + cache[j].offset);
												cache[j].data = memdata[memadd]; //move mem data to cache
											}
										}
									}
									if(!cache[i].offset.compare(address.substr(13,3))) //find OFFSET
									{
										cache[i].data = data;  //set data
										cache[i].valid = true; //Valid
										//for(int j = i - 8; j < i + 8; j++) //set all new TAGs   ///////////v2.0         
										//{                                 ///////////v2.0
										//	if (j < 0) j = 0;       ///////////v2.0
										//	if (j >= cache_size) ///////////v2.0
										//	{     ///////////v2.0
										//		int jnew = cache_size - 1;///////////v2.0
										//		if(!cache[jnew].set.compare(cache[i].set))//within set confides///////////v2.0
										//			//cache[jnew].dirty = true;    ///////////v2.0
										//	}///////////v2.0
										//	else///////////v2.0
										//	{///////////v2.0
										//		if(!cache[j].set.compare(cache[i].set))//within set confides///////////v2.0
										//			//cache[j].dirty = true;    ///////////v2.0
										//	}///////////v2.0
										//}///////////v2.0
										did_write = true;
									}
								}
								else  //if TAG the same
								{ 
									if(!cache[i].offset.compare(address.substr(13,3))) //find OFFSET
									{
										cache[i].data = data;  //set data
										cache[i].valid = true; //Valid
										//for(int j = i - 8; j < i + 8; j++) //set all new TAGs///////////v2.0
										//{///////////v2.0
										//	if (j < 0) j = 0;///////////v2.0
										//	if (j >= cache_size)///////////v2.0
										//	{///////////v2.0
										//		int jnew = cache_size - 1;///////////v2.0
										//		if(!cache[jnew].set.compare(cache[i].set))//within set confides///////////v2.0
										//			//cache[jnew].dirty = true;    ///////////v2.0
										//	}///////////v2.0
										//	else///////////v2.0
										//	{///////////v2.0
										//		if(!cache[j].set.compare(cache[i].set))///////////v2.0
										//			//cache[j].dirty = true;      ///////////v2.0
										//	}///////////v2.0
										//}///////////v2.0
										did_write = true;
									}
								}
							}
						}
					}
				}
				else if(!rw.compare("00")) //READ
				{
					did_read = false; ///////////v2.0
					for(int i = 0; i < cache_size;i++)
					{
						if(!cache[i].set.compare(address.substr(8,5))) //find SET
						{
							if(!cache[i].tag.compare(address.substr(0,8))) //if TAG is the same
							{
								if(!cache[i].offset.compare(address.substr(13,3))) //find OFFSET
								{
									if(cache[i].valid == true)
										output_File << cache[i].data << " " << 1 << " " << cache[i].dirty << "\n"; //valid
									else
										output_File << cache[i].data << " " << 0 << " " << cache[i].dirty << "\n"; //no data
									did_read = true;///////////v2.0
								}
							}
							else if(cache[i].tag.compare(address.substr(0,8))) //if TAG is different
							{
								if(!cache[i].offset.compare(address.substr(13,3))) //find OFFSET
								{
									for(int j = i - 8; j < i + 8; j++)
									{
										if (j < 0) j = 0;
										if (j >= cache_size) 
										{
											int jnew = cache_size - 1;
											if(!cache[jnew].set.compare(address.substr(8,5)))
											{
												int memadd = BintoDec(cache[jnew].tag + cache[jnew].set + cache[jnew].offset);
												if (cache[jnew].dirty)
												{
													memdata[memadd] = cache[jnew].data;
													//cache[jnew].dirty = false;   ///////////v2.0
												}
												cache[jnew].tag = address.substr(0,8);
												memadd = BintoDec(cache[jnew].tag + cache[jnew].set + cache[jnew].offset);
												cache[jnew].data = memdata[memadd];
												//cache[jnew].dirty = false; ///////////v2.0
											}
										}
										else
										{
											if(!cache[j].set.compare(address.substr(8,5)))
											{
												int memadd = BintoDec(cache[j].tag + cache[j].set + cache[j].offset);
												if (cache[j].dirty)
												{
													memdata[memadd] = cache[j].data;
													//cache[j].dirty = false; ///////////v2.0
												}
												cache[j].tag = address.substr(0,8);
												memadd = BintoDec(cache[j].tag + cache[j].set + cache[j].offset);
												cache[j].data = memdata[memadd];
												//cache[j].dirty = false; ///////////v2.0
											}
										}
									}
									output_File << cache[i].data << " " << 0 << " " << cache[i].dirty << "\n"; //valid

									for (int j = i - 8; j < i + 8; j++)//set to not dirty ///////////v2.0
									{                                                     ///////////v2.0
										if(j < 0) j = 0;                                  ///////////v2.0
										if(j >= cache_size)                               ///////////v2.0
										{                                                 ///////////v2.0
											int jnew = cache_size - 1;                    ///////////v2.0
											if(!cache[jnew].set.compare(cache[i].set))    ///////////v2.0
												cache[j].dirty = false;                   ///////////v2.0
										}                                                 ///////////v2.0
										else                                              ///////////v2.0
										{                                                 ///////////v2.0
											if(!cache[j].set.compare(cache[i].set))       ///////////v2.0
												cache[j].dirty = false;                   ///////////v2.0
										}                                                 ///////////v2.0
									}                                                     ///////////v2.0
									did_read = true;                                      ///////////v2.0
								}
							}
						}
					}
				}
			}

		}

		input_File.close();
		output_File.close();
	}
	else
		cout << "Open Failed!\n";

	system("PAUSE");
	return 0;
}