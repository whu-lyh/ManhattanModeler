
#include "basic_types.h"

#include <cmath>
#include <cctype>

#ifdef WIN32
#include <cfloat> // for ::_isnan()
#else
#include <cstdlib>
#endif



namespace Numeric {
	const float big_float = 1e10f ;
	const float small_float = 1e-10f ;
	const double big_double = 1e20 ;
	const double small_double = 1e-20 ;

	// Note: do not add global scole (::isnan) for calling this function, 
	// since it is a macro in some implementations. 

	bool is_nan(float32 x) {
#ifdef WIN32
		return (_isnan(x) != 0) || (_finite(x) == 0) ;
#else
		return isnan(x) || !finite(x);
#endif
	}

	bool is_nan(float64 x) {
#ifdef WIN32
		return (_isnan(x) != 0) || (_finite(x) == 0) ;
#else
		return isnan(x) || !finite(x);
#endif
	}    

	int32 random_int32() {
#ifdef WIN32
		return rand() ;
#else
		return random() ;
#endif        
	}

	float32 random_float32() {
#ifdef WIN32
		return float(rand()) / float(RAND_MAX);
#else
		return float(drand48()) ;
#endif        
	}

	float64 random_float64() {
#ifdef WIN32
		return double(rand()) / double(RAND_MAX);
#else
		return double(drand48()) ;
#endif        
	}


}

namespace String {

	void split_string(
		const std::string& in, 
		char separator,
		std::vector<std::string>& out,
		bool skip_empty_fields/* = true */) 
	{
		size_t length = in.length() ;
		size_t start = 0 ;
		size_t end = 0 ;

		while(start < length) {

			end = in.find(separator,start) ;
			if(end == std::string::npos) {
				end = length ;
			}

			if(!skip_empty_fields || (end - start > 0)) {
				out.push_back(in.substr(start, end - start)) ;
			}
			start = end + 1 ;
		}
	}


	void join_strings(
		const std::vector<std::string>& in,
		char separator,
		std::string& out
		) {
			out = "" ;
			for(unsigned int i=0; i<in.size(); i++) {
				if(out.length() != 0) {
					out += separator ;
				}
				out += in[i] ;
			}
	}

	void join_strings(
		const std::vector<std::string>& in,
		const std::string& separator,
		std::string& out
		) {
			out = "" ;
			for(unsigned int i=0; i<in.size(); i++) {
				if(out.length() != 0) {
					out += separator ;
				}
				out += in[i] ;
			}
	}

	std::string join_strings(
		const std::vector<std::string>& in,
		char separator
		) {
			std::string result ;
			join_strings(in, separator, result) ;
			return result ;
	}

	std::string join_strings(
		const std::vector<std::string>& in,
		const std::string& separator
		) {
			std::string result ;
			join_strings(in, separator, result) ;
			return result ;
	}

	void to_lowercase(std::string& in) {
		for(unsigned int i=0; i<in.length(); i++) {
			if(isupper(in[i])) {
				in[i] = tolower(in[i]) ;
			}
		}
	}

	void to_uppercase(std::string& in) {
		for(unsigned int i=0; i<in.length(); i++) {
			if(islower(in[i])) {
				in[i] = toupper(in[i]) ;
			}
		}
	}        

	std::string quote(const std::string& s, char quotes) {
		return char_to_string(quotes) + s + char_to_string(quotes) ;
	}
}

