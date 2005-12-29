/*

  set_tag::read::ID3v2

  (c) 2004, 2005 squell ^ zero functionality!
  see the file 'COPYING' for license conditions

  Usage:

  The read::ID3v2 class implements the reader interface for ID3v2 tags

*/

#ifndef __ZF_GETID3V2
#define __ZF_GETID3V2

#include <string>
#include <cctype>
#include "set_base.h"

namespace set_tag {
    namespace read {

        class ID3v2 : public reader {
            void* const tag;
        public:
            explicit ID3v2(const char* fn);
           ~ID3v2();
            value_string operator[](ID3field field) const;
            array listing() const;

            static bool has_lang(const std::string field)  // implies has_enc
            { return field == "COMM" || field == "COM" ||
                     field == "USLT" || field == "ULT" ||
                     field == "USER"; }

            static bool has_desc(const std::string field)  // implies has_enc
            { return field == "TXXX" || field == "TXX" ||
                     field == "WXXX" || field == "WXX" ||
                     field == "COMM" || field == "COM" ||
                     field == "USLT" || field == "ULT"; }

            static bool is_counter(const std::string field)
            { return field == "PCNT" || field == "CNT"; }

            static bool is_url(const std::string field)
            { return field[0] == 'W'; }

            static bool is_text(const std::string field)
            { return field[0] == 'T' || field == "IPLS" || field == "IPL"; }

            static bool is_valid(const std::string field)
            {
                 using namespace std;
                 string::size_type n;
                 for(n = 0; n < field.length(); ++n) {
                     if(!isupper(field[n]) && !isdigit(field[n]))
                         return false;
                 }
                 return n == 3 || n == 4;
            }
        };

    }
}

#endif

