//
//		File access to source file.
//
#ifndef _FILEACCESS_H // This is the way that multiple inclusions are defended
                      // against often used in UNIX
#define _FILEACCESS_H // We use pragmas in Visual Studio and g++.  See other
                      // include files

#include <fstream>
#include <string>

class FileAccess
{
  public:
    // Opens the file.
    explicit FileAccess(const std::string& file_path);

    // Closes the file.
    ~FileAccess();

    // Get the next line from the source file
    std::string get_next_line();

    bool end_of_file() const { return _source_file.eof(); };

    // Put the file pointer back to the beginning of the file.
    void rewind();

  private:
    std::ifstream _source_file;
};
#endif
