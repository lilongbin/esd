/*****************************************
* Copyright (C) 2019 * Ltd. All rights reserved.
* 
* File name   : file.cpp
* Author      : longbin
* Created date: 2019-01-15 13:56:43
* Description : 
*
*******************************************/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

void file_create()
{
   int gcount = 0;
   string filename = "test.txt";
   ofstream ofs(filename.c_str());

   string str = "Hello, I'm writing in C++ ofstrem.\n";
   ofs.write(str.c_str(), str.length());

   gcount = ofs.tellp();
   ofs.close();
   cout << "write ok: " << gcount << endl;
}

int file_read(string filename, int lstart, int lend)
{
   int linenm = 0;
   ifstream ifs(filename.c_str());

   if (lstart > lend)
   {
      return 1;
   }
   char buf[1024] = { 0 };
   while (!ifs.eof())
   {
      linenm++;
      ifs.getline(buf, sizeof(buf));
      if ((linenm >= lstart) && (linenm <= lend))
      {
         cout << setfill('0') << setw(3) << linenm << ": " << buf << endl;
      }
   }
}

int main() {
   string filename = "messages.0";
   file_create();
   file_read(filename, 35000, 35030);
	return 0;
}
