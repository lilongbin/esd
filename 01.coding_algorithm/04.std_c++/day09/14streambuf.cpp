/*****************************************
 * File name   : 14streambuf.cpp
 *******************************************/
#include <iostream>
#include <string>

#include <fstream>
#include <sstream>

using namespace std;

void ostringstreambuf()
{
   cout << __func__ << "#################" << endl;
   std::ostringstream oss;
   std::stringbuf *pbuf = oss.rdbuf();

   // using stringbuf directly
   pbuf->sputn("Sample string", 13);
   std::cout << "pbuf: " << pbuf->str();
   std::cout << endl;
   std::cout << "oss: " << oss.str();
   std::cout << endl;
   cout << __func__ << "#################" << endl;
}

void istringstreambuf()
{
   cout << __func__ << "#################" << endl;
   std::istringstream iss;
   std::stringbuf *pbuf = iss.rdbuf();

   // using stringbuf directly:
   pbuf->str("Example string");

   int size = pbuf->in_avail();

   while (pbuf->in_avail()>0)
      std::cout << static_cast<char>(pbuf->sbumpc());
   std::cout << endl;
   std::cout << "pbuf: " << pbuf->str();
   std::cout << endl;
   std::cout << "iss: " << iss.str();
   std::cout << endl;
   cout << __func__ << "#################" << endl;
}

void ifilebuf()
{
   cout << __func__ << "#################" << endl;
   std::ifstream ifs("config.txt", std::ifstream::binary);
   std::filebuf *pbuf = ifs.rdbuf(); // get pointer to associated buffer object

   // get file size using buffer's members
   std::size_t size = pbuf->pubseekoff(0, ifs.end, ifs.in);
   pbuf->pubseekpos(0, ifs.in);

   // allocate memory to contain file data
   char *buffer = new char[size];

   pbuf->sgetn(buffer, size); // get file data: visit filebuf and copy to buffer
   ifs.close(); //close filebuf

   // write content to stdout
   std::cout.write(buffer, size);
   delete[] buffer; 
   cout << __func__ << "#################" << endl;
}

void ofilebuf()
{
   cout << __func__ << "#################" << endl;
   std::ifstream ifs ("config.txt");
   std::ofstream ofs ("copy.txt");

   std::filebuf *inbuf  = ifs.rdbuf();
   std::filebuf *outbuf = ofs.rdbuf();

   /*
    * int sbumpc();       Get current character and advance to next position
    * int sputc (char c); Store character at current put position and increase put pointer
    */

   char c = inbuf->sbumpc();
   while (c != EOF)
   {
      cout << "write to outbuf: " << c << endl;
      outbuf->sputc(c);
      c = inbuf->sbumpc();
   }

   ofs.close();
   ifs.close();
   cout << __func__ << "#################" << endl;
}

int main() {
   ostringstreambuf();
   istringstreambuf();
   ifilebuf();
   ofilebuf();
   return 0;
}

