//-----------------------------------------------------------------------------
//    $Id$
//    Version: $Name$
//
//    Copyright (C) 2005, 2006, 2011 by the deal.II authors
//
//    This file is subject to QPL and may not be  distributed
//    without copyright and license information. Please refer
//    to the file deal.II/doc/license.html for the  text  and
//    further information on this license.
//
//-----------------------------------------------------------------------------

// test functions in namespace Utilities

#include "../tests.h"
#include <iomanip>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <sstream>

#include <deal.II/base/utilities.h>

using namespace dealii;

std::vector<std::string> split_string(const std::string &text, const char delim='|')
{
  std::vector<std::string> result;
  std::string word;
  std::stringstream stream(text);
  while( getline(stream, word, delim) )
    result.push_back(word);

  return result;
}


void test_function(const std::string &original_text,
		   const unsigned int width,
		   const char delimiter,
		   const std::string &result)
{
  std::vector<std::string> res_vec
    = Utilities::break_text_into_lines (original_text, width, delimiter);

  std::vector<std::string> should_be_vec
    = split_string(result);


  Assert(res_vec.size()==should_be_vec.size(), ExcInternalError());
  for (unsigned int i=0;i<res_vec.size();++i)
    {
      if (res_vec[i]!=should_be_vec[i])
	std::cout << "'" << res_vec[i] << "!=" << should_be_vec[i] << "'" << std::endl;
      Assert(res_vec[i]==should_be_vec[i], ExcInternalError());
    }



}


void test ()
{
  test_function("test", 80, ' ', "test");
  test_function("test it", 80, ' ', "test it");
  test_function("test it", 5, ' ', "test|it");
  test_function("test it longer", 5, ' ', "test|it|longer");
  test_function(" white  space  too long ", 14, ' ', "white  space|too long");
  test_function(" white  space ", 80, ' ', "white  space");

  test_function("new\nline", 80, ' ', "new|line");
  test_function("new\n\nline\n", 80, ' ', "new||line|");
  test_function("combining whitespace\nand new line", 10, ' ', "combining|whitespace|and new|line");


  deallog << "OK" << std::endl;
}




int main()
{
  std::ofstream logfile("utilities_04/output");
  deallog.attach(logfile);
  deallog.depth_console(0);
  deallog.threshold_double(1.e-10);

  test ();
}
