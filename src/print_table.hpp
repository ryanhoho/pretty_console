#ifndef PRINT_TABLE_HPP
#define PRINT_TABLE_HPP
class tableprinter {
public:
	tableprinter(std::ostream* ostream, const std::string& title) :
		out_stream_(ostream), sperator_("|"), i_(0), j_(0),
		table_witdh_(0), align_(right), title_(title)
	{}
	~tableprinter() 
	{}

	enum align
	{
		left,
		right,
		center
	};

	void addColumn(const std::string& column, int width) {
		headers_.push_back(column);
		header_widths_.push_back(width);
		table_witdh_ += width + sperator_.size();
	}

	int getColumnNums() {
		return headers_.size();
	}

	void printHLine() {
		*out_stream_ << '+';
		for (size_t i = 0; i < table_witdh_ - 1; i++)
		{
			*out_stream_ << '-';
		}
		*out_stream_ << "+\n";
	}

	void setAlign(align align) {
		align_ = align;
	}

	void printHeader() {
		printHLine();
		*out_stream_ << "|";
		int d = lenDiff(title_.c_str()) / 2;
		int pad = (table_witdh_ - 1 + d - title_.size());
		int padl = pad / 2;
		int padr = pad % 2 == 0 ? pad / 2 : pad / 2 + 1;

		std::cout << std::setw(padl) << " "<< title_ 
			<< std::setw(padr) << " " << "|\n";
		printHLine();
		*out_stream_ << "|";
		for (size_t i = 0; i < getColumnNums(); i++)
		{
			std::string& h = headers_.at(i);
			int d = lenDiff(h.c_str()) / 2;
			int pad = (header_widths_.at(i) + d - h.size());
			int padl = pad / 2;
			int padr = pad % 2 == 0 ? pad / 2 : pad / 2 + 1;
			if (align_ == left) {
				*out_stream_ << std::left;
				*out_stream_ << std::setw(header_widths_.at(i) + d)
					<< h;
			}
			else if(align_ == right){
				*out_stream_ << std::right;
				*out_stream_ << std::setw(header_widths_.at(i) + d)
					<< h;
			}
			else {
				*out_stream_ << std::setw(padl) << " "
					<< h << std::setw(padr) << " ";
			}
			
			if (i != getColumnNums() - 1) {
				*out_stream_ << sperator_;
			}
		}
		*out_stream_ << "|\n";
		printHLine();
	}

	void printFooter() {
		printHLine();
	}

	tableprinter& operator<<(align dr) {
		
		return *this;
	}

	tableprinter& operator<<(char* str) {
		if (j_ == 0) {
			*out_stream_ << "|";
		}

		int d = lenDiff(str) / 2;
		int pad = (header_widths_.at(j_) + d - strlen(str));
		int padl = pad / 2;
		int padr = pad % 2 == 0 ? pad / 2 : pad / 2 + 1;

		if (align_ == left) {
			*out_stream_ << std::left;
			*out_stream_ << std::setw(header_widths_.at(j_) + d) << str;
		}
		else if(align_ == right){
			*out_stream_ << std::right;
			*out_stream_ << std::setw(header_widths_.at(j_) + d) << str;
		}
		else {
			*out_stream_ << std::setw(padl) << " " << str << std::setw(padr) << " ";
		}

		if (j_ == getColumnNums() - 1) {
			*out_stream_ << "|\n";
			i_++;
			j_ = 0;
		}
		else {
			*out_stream_ << sperator_;
			j_++;
		}
		return *this;
	}

	tableprinter& operator<<(const char* str) {
		if (j_ == 0) {
			*out_stream_ << "|";
		}
		int d = lenDiff(str) / 2;
		int pad = (header_widths_.at(j_) + d - strlen(str));
		int padl = pad / 2;
		int padr = pad % 2 == 0 ? pad / 2 : pad / 2 + 1;

		if (align_ == left) {
			*out_stream_ << std::left;
			*out_stream_ << std::setw(header_widths_.at(j_) + d) << str;
		}
		else if (align_ == right) {
			*out_stream_ << std::right;
			*out_stream_ << std::setw(header_widths_.at(j_) + d) << str;
		}
		else {
			*out_stream_ << std::setw(padl) << " " << str << std::setw(padr) << " ";
		}

		if (j_ == getColumnNums() - 1) {
			*out_stream_ << "|\n";
			i_++;
			j_ = 0;
		}
		else {
			*out_stream_ << sperator_;
			j_++;
		}
		return *this;
	}

	template<typename T,
		typename = typename std::enable_if < !std::is_same<T, std::string>::value &&
		!std::is_same<T, char*>::value && !std::is_same<T, align>::value&&
		!std::is_same<T, char[]>::value
		>
	> 
	tableprinter& operator<< (T input) {
		if (j_ == 0) {
			*out_stream_ << "|";
		}
		if (align_ == left) {
			*out_stream_ << std::left;
		}
		else if(align_ == right) {
			*out_stream_ << std::right;
		}
		*out_stream_ << std::setw(header_widths_.at(j_))
			<< input;

		if (j_ == getColumnNums() - 1) {
			*out_stream_ << "|\n";
			i_++;
			j_ = 0;
		}
		else {
			*out_stream_ << sperator_;
			j_++;
		}
		return *this;
	}

private:

	int len(const char* str) {
		int l = 0;
		int size = strlen(str);
		for (int i = 0; i < size; ++i)
		{
			if ((str[i] & 0xC0) != 0x80) l++;
		}
		return l;
	}

	int lenDiff(const char* str) {
		int l = 0;
		int size = strlen(str);
		for (int i = 0; i < size; ++i)
		{
			if ((str[i] & 0xC0) != 0x80) l++;
		}
		return size - l;
	}

private:
	std::ostream* out_stream_;
	std::vector<std::string> headers_;
	std::vector<int> header_widths_;
	std::string sperator_;
	std::string title_;
	
	int i_;
	int j_;

	int table_witdh_;
	align align_;
};

#endif
