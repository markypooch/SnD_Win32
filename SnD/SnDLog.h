#pragma once
#include <exception>
#include <fstream>

namespace log_exceptions
{
	class SnDLog : public std::exception
	{
		const char*    file;
		const int      line;
		const char*    func;
		const char*    info;
		std::ofstream  outputStream;

	public:
		SnDLog(const char* msg, const char* file_, int line_, const char* func_, const char* info_ = "") : std::exception(msg),
			file(file_),
			line(line_),
			func(func_),
			info(info_) {}
		~SnDLog();
	public:
		const char* get_file()             const { return file; }
		const int   get_line()             const { return line; }
		const char* get_func()             const { return func; }
		const char* get_info()             const { return info; }
#
		void        writeExceptionToFile() const;
	};
};