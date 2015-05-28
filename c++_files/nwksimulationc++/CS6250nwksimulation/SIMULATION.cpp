#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<math.h>
#include<vector>
#include<unordered_map>
using namespace std;



bool httppacket_inspector(string input_file)
{	
	unsigned int size;
	char * memblock;
	unsigned int * memblock2;
	ifstream file;
	file.open(input_file, ios::in | ios::binary);
	bool found=false;
	if (file.is_open())
	{	
		
		file.seekg(0, ios::beg);
		int beginning = file.tellg();
		file.seekg(0, ios::end);
		int end = file.tellg();
		size = end - beginning;
		memblock = new char[size];
		memblock2 = new unsigned int[size];

		file.seekg(0, ios::beg);
		file.read(memblock, size);
		file.close();

		for (int i = 0; i < size; i++)
		{
			file >> memblock[i];
			memblock2[i] = (unsigned int)(unsigned char)memblock[i];


		}

		//cout << "checking if http \n" << endl;

		int a[8] = { 72, 84, 84, 80, 47, 49, 46, 49};
		for (int i = 0; i < size; i++)
		{
			//cout << memblock2[i] << " ";
			if (memblock2[i] == 72)
			{
				int k = i;
				for (int j = 0; j < 8 && (i+j)<size; j++)
				{
					if (memblock2[k] == a[j])
					{
						k++;
						if (j == 7)
							found = true;
					}
					else
						break;
				}
				if (found)
					break;
			}
		}


		if (found)
		{
			//cout << "http packet found \n";
			return true;
		}
		else
			
			return false;

		

	}
	else { cout << "Unable to open file"; }
}

bool ftp_inspector(string input_file)
{
	unsigned int size;
	char * memblock;
	unsigned int * memblock2;
	ifstream file;
	file.open(input_file, ios::in | ios::binary);
	bool found = false;
	if (file.is_open())
	{

		file.seekg(0, ios::beg);
		int beginning = file.tellg();
		file.seekg(0, ios::end);
		int end = file.tellg();
		size = end - beginning;
		memblock = new char[size];
		memblock2 = new unsigned int[size];

		file.seekg(0, ios::beg);
		file.read(memblock, size);
		file.close();

		for (int i = 0; i < size; i++)
		{
			file >> memblock[i];
			memblock2[i] = (unsigned int)(unsigned char)memblock[i];


		}

		//cout << "checking if ftp \n" << endl;

		int a[3] = { 102, 116 ,112};
		int b[3] = { 70, 84, 80 };
		for (int i = 0; i < size; i++)
		{
			
			if (memblock2[i] == 102)
			{
				int k = i;
				for (int j = 0; j < 3 && (i + j)<size; j++)
				{
					if (memblock2[k] == a[j])
					{
						k++;
						if (j == 2)
							found = true;
					}
					else
						break;
				}
				if (found)
					break;
			}
			else if (memblock2[i] ==116)
			{
				int k = i;
				for (int j = 0; j < 3 && (i + j)<size; j++)
				{
					if (memblock2[k] == b[j])
					{
						k++;
						if (j == 2)
							found = true;
					}
					else
						break;
				}
				if (found)
					break;
			}
		}


		if (found)
		{
			//cout << "ftp packet found \n";
			return true;
		}
		else
			return false;



	}
	else { cout << "Unable to open file"; }
}


int main(int argc, char *argv[]) {
	

	unsigned int size;
	char * memblock;
	unsigned int * memblock2;
	int rule = 0;
	fstream s3file,s4file,s5file,s6file,s7file,receiverfile;
	string datainfo = "";
	int prevhisory = 0;
	
	string httpsrcip="", httpdestip="",ftpsrcip="",ftpdestip="",srcip="",destip="",historysrcip="",historydestip="";
	cout << "Setting up sender and receiver";
	cout << "Setting up" << endl << " s1 - for sender" << endl
		<< "s1-s3-s2 for http " << endl
		<< "s1-s4-s2 for udp" << endl
		<< "s1-s5-s2 for icmp" << endl
		<< "s1-s6-s2 for ftp" << endl
		<< "s1-s7-s2 for other tcp" << endl;

	
	

	do
	{
		string flow;
		cout << "\nenter flow type \n";
		cin >> flow;
		if (flow == "stop")
			break;
		cout << "\nenter number of packets in flow \n";
		int numflow;
		cin >> numflow;
		

		
		string simulation_name = "";
		simulation_name = "\n*************************New SIMULATION with flow ";
		simulation_name.append(flow);
		simulation_name.append("************************************\n");
		receiverfile.open("receiverfile", ios::out | ios::binary | ios::app);
		receiverfile.write(simulation_name.c_str(), simulation_name.size());
		receiverfile.close();
		rule = 0;
		while (numflow != 0)
		{
			
			ifstream file;
			srcip = "";
			destip = "";
			
			char* input_file = new char[20];

			for (int i = 0; i < flow.length(); i++)
			{
				input_file[i] = flow[i];
			}
			input_file[flow.length()] = '\0';
			//cout << "Flow used for simulation is " << input_file << endl;
			//cout << "output file is" << output_file << endl;
			file.open(input_file, ios::in | ios::binary);



			//reading the file and storing everything in a buffer
			if (file.is_open())
			{
				file.seekg(0, ios::beg);
				int beginning = file.tellg();
				file.seekg(0, ios::end);
				int end = file.tellg();
				size = end - beginning;
				memblock = new char[size];
				memblock2 = new unsigned int[size];

				file.seekg(0, ios::beg);
				file.read(memblock, size);
				file.close();

				for (int i = 0; i < size; i++)
				{
					file >> memblock[i];
					memblock2[i] = (unsigned int)(unsigned char)memblock[i];


				}

				//cout << "size of flow in bytes is " << size << endl;
				cout << "source ip from packet is " << endl;
				for (int i = 26; i < 30; i++)
				{
					if (i < 29)
					{
						//cout << memblock2[i] << ".";
						srcip.append(to_string(memblock2[i]));
						srcip.append(".");
					}
					else
						srcip.append(to_string(memblock2[i]));
					//cout << memblock2[i] << endl;
				}
				cout << srcip << endl;
				cout << "destination ip from packet is" << endl;
				for (int i = 30; i < 34; i++)
				{
					if (i < 33)
						//cout << memblock2[i] << ".";
					{
						destip.append(to_string(memblock2[i]));
						destip.append(".");
					}
					else
						destip.append(to_string(memblock2[i]));
					//cout << memblock2[i] << endl;

				}

				cout << destip << endl;
				int checker = memblock2[23];
				switch (checker)
				{
				case 6:if (httppacket_inspector(input_file))
					rule = 3;
					   else if (ftp_inspector(input_file) || prevhisory==6)
						   rule = 6;
					   else
						   rule = 7;
					break;
				case 17:if (httppacket_inspector(input_file))
					rule = 3;
						else rule = 4;
					break;
				case 1:rule = 5; break;
				default:break;

				}
				
			 if (rule != prevhisory)
				{
					rule = 0;
				}
				
				if ((!strcmp(historysrcip.c_str(), srcip.c_str())) && rule!=0)
				{
					
					switch (rule)

					{
					case 3: cout << "Switch 1 sending data to receiver through switch 3 \n";
						s3file.open("s3switchdata", ios::out | ios::binary | ios::app);
						s3file.write(memblock, size);
						s3file.close();
						cout << "Switch 3: Data received, forwarding data to receiver \n"<<endl;
						receiverfile.open("receiverfile", ios::out | ios::binary | ios::app);
						datainfo = "received http data from switch 3 \n";
						receiverfile.write(datainfo.c_str(), datainfo.size());
						receiverfile.write(memblock, size);
						receiverfile.close();
						break;
					case 4: cout << "Switch 1 sending data to receiver through switch 4 \n";
						s4file.open("s4switchdata", ios::out | ios::binary | ios::app);
						s4file.write(memblock, size);
						s4file.close();
						cout << "Switch 4: Data received, forwarding data to receiver \n"<<endl;
						receiverfile.open("receiverfile", ios::out | ios::binary | ios::app);
						datainfo = "received udp data from switch 4 \n";
						receiverfile.write(datainfo.c_str(), datainfo.size());
						receiverfile.write(memblock, size);
						receiverfile.close();
						break;
					case 5: cout << "Switch 1 sending data to receiver through switch 5 \n";
						s5file.open("s5switchdata", ios::out | ios::binary | ios::app);
						s5file.write(memblock, size);
						s5file.close();
						cout << "Switch 5: Data received, forwarding data to receiver \n"<<endl;
						receiverfile.open("receiverfile", ios::out | ios::binary | ios::app);
						datainfo = "received icmp data from switch 5 \n";
						receiverfile.write(datainfo.c_str(), datainfo.size());
						receiverfile.write(memblock, size);
						receiverfile.close();

						break;
					case 6: cout << "Switch 1 sending data to receiver through switch 6 \n";
						s6file.open("s6switchdata", ios::out | ios::binary | ios::app);
						s6file.write(memblock, size);
						s6file.close();
						cout << "Switch 6: Data received, forwarding data to receiver \n"<<endl;
						receiverfile.open("receiverfile", ios::out | ios::binary | ios::app);
						datainfo = "received ftp data from switch 6 \n";
						receiverfile.write(datainfo.c_str(), datainfo.size());
						receiverfile.write(memblock, size);
						receiverfile.close();
						break;
					case 7: cout << "Switch 1 sending data to receiver through switch 7 \n";
						s7file.open("s7switchdata", ios::out | ios::binary | ios::app);
						s7file.write(memblock, size);
						s7file.close();
						cout << "Switch 7: Data received, forwarding data to receiver \n"<<endl;
						receiverfile.open("receiverfile", ios::out | ios::binary | ios::app);
						datainfo = "received tcp data from switch 7 \n";
						receiverfile.write(datainfo.c_str(), datainfo.size());
						receiverfile.write(memblock, size);
						receiverfile.close();
						break;
					default:break;

					}
				}
				else
				{
					cout << "*********************************************************************************\n" << "			Controller called         \n" << "			setting rules				\n" << "********************************************************** \n";
					historysrcip = srcip;
					historydestip = destip;
					//cout << "flow type detected \n";
					if (memblock2[23] == 06)
					{
						//cout << "tcp \n";
						if (httppacket_inspector(input_file))
						{
							//cout << "http packet found" << endl;
							rule = 3;
							prevhisory = 3;
							
								cout << "asking controller \n" << endl;
								httpsrcip = srcip;
								httpdestip = destip;
								cout << "setting new rules for http forwarding \n" << endl;
							



							
							cout << "switch 1 sending data to receiver through switch 3 \n";
							s3file.open("s3switchdata", ios::out | ios::binary | ios::app);
							s3file.write(memblock, size);
							s3file.close();
							cout << "Switch 3: Data received, forwarding data to receiver \n"<<endl;
							receiverfile.open("receiverfile", ios::out | ios::binary | ios::app);
							datainfo = "received http data from switch 3 \n";
							receiverfile.write(datainfo.c_str(), datainfo.size());
							receiverfile.write(memblock, size);
							receiverfile.close();
						}
						else if (ftp_inspector(input_file))
						{
							cout << "asking controller \n" << endl;
							httpsrcip = srcip;
							httpdestip = destip;
							cout << "setting new rules for ftp forwarding \n" << endl;
							cout << "switch 1 sending data to receiver through switch 6 \n";
							rule = 6;
							prevhisory = 6;
							s6file.open("s6switchdata", ios::out | ios::binary | ios::app);
							s6file.write(memblock, size);
							s6file.close();
							cout << "Switch 6: Data received, forwarding data to receiver \n"<<endl;
							receiverfile.open("receiverfile", ios::out | ios::binary | ios::app);
							datainfo = "received ftp data from switch 6 \n";
							receiverfile.write(datainfo.c_str(), datainfo.size());
							receiverfile.write(memblock, size);
							receiverfile.close();
						}
						else
						{
							//cout << "not http packet" << endl;
							cout << "asking controller \n" ;
							httpsrcip = srcip;
							httpdestip = destip;
							cout << "setting new rules for tcp forwarding \n" << endl;
							cout << "switch 1 sending data to receiver through switch 7 \nn";
							rule = 7;
							prevhisory = 7;
							s7file.open("s7switchdata", ios::out | ios::binary | ios::app);
							s7file.write(memblock, size);
							s7file.close();
							cout << "Switch 7: Data received, forwarding data to receiver \n"<<endl;
							receiverfile.open("receiverfile", ios::out | ios::binary | ios::app);
							datainfo = "received tcp data from switch 7 \n";
							receiverfile.write(datainfo.c_str(), datainfo.size());
							receiverfile.write(memblock, size);
							receiverfile.close();
						}

					}
					else if (memblock[23] == 01)
					{
						cout << "asking controller \n";
						cout << "setting new rules for icmp forwarding \n" << endl;
						cout << "switch 1 sending data to receiver through switch 5 \n";
						historysrcip = srcip;
						historydestip = destip;
						rule = 5;
						prevhisory = 5;
						s5file.open("s5switchdata", ios::out | ios::binary | ios::app);
						s5file.write(memblock, size);
						s5file.close();
						receiverfile.open("receiverfile", ios::out | ios::binary | ios::app);

						cout << "Switch 5: Data received, forwarding data to receiver \n" << endl;
						datainfo = "received icmp data from switch 5 \n";
						receiverfile.write(datainfo.c_str(), datainfo.size());
						receiverfile.write(memblock, size);
						receiverfile.close();
					}
					else if (memblock[23] == 17)
					{
						//cout << "udp";
						if (httppacket_inspector(input_file))
						{
							//cout << "http packet found" << endl;
							rule = 3;
							prevhisory = 3;
						
								cout << "asking controller \n" << endl;
								httpsrcip = srcip;
								httpdestip = destip;
								cout << "setting rules for new http forwarding \n" << endl;
								cout << "sending packet through switch s3 \n";
								cout << "switch 1 sending data to receiver. Sending data through switch 3 \n";


							
							
							s3file.open("s3switchdata", ios::out | ios::binary | ios::app);
							s3file.write(memblock, size);
							s3file.close();
							cout << "Switch 3: Data received, forwarding data to receiver \n" << endl;
							receiverfile.open("receiverfile", ios::out | ios::binary | ios::app);
							datainfo = "received http data from switch 3 \n";
							receiverfile.write(datainfo.c_str(), datainfo.size());
							receiverfile.write(memblock, size);
							receiverfile.close();

						}
						else if (ftp_inspector(input_file))
						{
							//cout << "ftp";
							cout << "asking controller \n" << endl;
							rule=6;
							prevhisory = 6;
							httpsrcip = srcip;
							httpdestip = destip;
							cout << "setting rules for new ftp forwarding \n" << endl;
							cout << "switch 1 sending data to receiver through switch 6 \n";
							s6file.open("s6switchdata", ios::out | ios::binary | ios::app);
							s6file.write(memblock, size);
							s6file.close();
							cout << "Switch 6: Data received, forwarding data to receiver \n" << endl;
							receiverfile.open("receiverfile", ios::out | ios::binary | ios::app);
							datainfo = "received ftp data from switch 6 \n";
							receiverfile.write(datainfo.c_str(), datainfo.size());
							receiverfile.write(memblock, size);
							receiverfile.close();
						}
						else
						{
							//cout << "not http packet" << endl;
							cout << "asking controller \n" << endl;
							historysrcip = srcip;
							historydestip = destip;
							rule = 4;
							prevhisory = 4;
							cout << "setting rules for udp forwarding \n" << endl;
							cout << "switch 1 sending data to receiver through switch 4 \n";
							s5file.open("s4switchdata", ios::out | ios::binary | ios::app);
							s5file.write(memblock, size);
							s5file.close();
							cout << "Switch 4: Data received, forwarding data to receiver \n" << endl;
							receiverfile.open("receiverfile", ios::out | ios::binary | ios::app);
							datainfo = "\n received udp data from switch 4 \n";
							receiverfile.write(datainfo.c_str(), datainfo.size());
							receiverfile.write(memblock, size);
							receiverfile.close();
						}
					}


				}



			}
			else { cout << "Unable to open file"; }

			numflow--; }
	}while (true);


	char ch;
	cin >> ch;
}




