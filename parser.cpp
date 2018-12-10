#include <iostream>
#include <string>
#include <vector>
#include <assert.h>

#include "parser.h"
#include "reader.h"

using std::string;
using std::vector;


#define CHECK(cond, msg) \
  do { \
    if (not cond) { \
      std::cerr << "Assertion `" #cond "` failed in " << __FILE__ << ":" << __LINE__ << "\n" \
        << "   " << msg << "\n"; \
      std::exit(0); \
    } \
  } while(0);


Texp::Texp(const string& value) : Texp(value, {}) {};
Texp::Texp(const string& value, const std::initializer_list<Texp>& children) 
    : _value(value), _children(children) {}

bool Texp::empty() const 
  { return _children.empty(); }

void Texp::push(Texp t) 
  { _children.push_back(t); }

std::ostream& operator<<(std::ostream& out, Texp texp) 
  {
    if (texp.empty()) 
      {
        out << texp._value;
      } 
    else
      {
        out << "(" << texp._value << " ";
        for (auto iter = texp._children.begin(); iter < texp._children.end(); ++iter) 
          {
            auto& child = *iter;
            out << child;
            if (iter != texp._children.end() - 1) {
              out << " ";
            }
          }
        out << ")";
      }
    return out;
  }


Texp Parser::_char()
  {
    std::string s = "";
    assert (*_r == '\'');
    while (not (*_r == '\'' && _r.prev() != '\\')) 
      {
        CHECK(_r.hasNext(), "backbone: reached end of file while parsing character");
        s += *_r++;
      }
    assert(*_r == '\'');
    s += *_r++;
    return Texp(s);
  }

Texp Parser::_string()
  {
    std::string s = "";
    assert (*_r == '\"');
    while (not (*_r == '\"' && _r.prev() != '\\')) 
      {
        CHECK(_r.hasNext(), "reached end of file while parsing string");
        s += *_r++;
      }
    assert(*_r == '\"');
    s += *_r++;
    return Texp(s);
  }

Parser::Parser(string v): _r(v) {}

void Parser::whitespace() 
  { while (std::isspace(*_r)) _r++; }

Texp Parser::texp() 
  {
    whitespace();
    if (*_r == '(') return list();
    return atom();
  }

Texp Parser::atom() 
  {
    if (*_r == '\'') return _char();
    if (*_r == '\"') return _string();
    return Texp(word());
  }

Texp Parser::list()
  {
    assert(*_r++ == '(');
    
    auto curr = Texp(word());
    while (*_r != ')') 
      {
        CHECK(_r.hasNext(), "reached end of file when parsing list");
        curr.push(texp());
        whitespace();
      }
    
    assert(*_r++ == ')');
    return curr;
  }

std::string Parser::word()
  {
    whitespace();
    std::string s = "";
    CHECK(_r.hasNext(), "reached end of file when parsing word");
    while (_r.hasNext() && *_r != '(' && *_r != ')' && not std::isspace(*_r)) {
      s += *_r++;
    }
    return s;
  }

char Parser::operator*() 
  { return *_r; }

string::iterator Parser::end() 
  { return _r.end(); }

const string::iterator Parser::curr() 
  { return _r.curr(); }