// 1999-08-11 bkoz

// Copyright (C) 1999, 2000, 2001, 2002, 2003, 2004 Free Software Foundation
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 2, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License along
// with this library; see the file COPYING.  If not, write to the Free
// Software Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307,
// USA.

// 27.6.1.3 unformatted input functions

#include <cstring> // for strncmp,...
#include <istream>
#include <sstream>
#include <testsuite_hooks.h>

void
test01()
{
  bool test __attribute__((unused)) = true;
  const std::string str_02("soul eyes: john coltrane quartet");

  std::stringbuf isbuf_03(str_02, std::ios_base::in);
  std::stringbuf isbuf_04(str_02, std::ios_base::in);

  std::istream is_00(NULL);
  std::istream is_03(&isbuf_03);
  std::istream is_04(&isbuf_04);
  std::ios_base::iostate state1, state2, statefail, stateeof;
  statefail = std::ios_base::failbit;
  stateeof = std::ios_base::eofbit;

  // istream& read(char_type* s, streamsize n)
  char carray[60] = "";
  state1 = is_04.rdstate();
  is_04.read(carray, 0);
  state2 = is_04.rdstate();
  VERIFY( state1 == state2 );

  state1 = is_04.rdstate();
  is_04.read(carray, 9);
  state2 = is_04.rdstate();
  VERIFY( state1 == state2 );
  VERIFY( !std::strncmp(carray, "soul eyes", 9) );
  VERIFY( is_04.peek() == ':' );

  state1 = is_03.rdstate();
  is_03.read(carray, 60);
  state2 = is_03.rdstate();
  VERIFY( state1 != state2 );
  VERIFY( static_cast<bool>(state2 & stateeof) ); 
  VERIFY( static_cast<bool>(state2 & statefail) ); 
  VERIFY( !std::strncmp(carray, "soul eyes: john coltrane quartet", 35) );
}

int 
main()
{
  test01();
  return 0;
}
