For the most part we follow the [Google C++ style guide](http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml). The exceptions are:

  * We prefix getters with `get_` for clarification.
  * We use "string" as the type where we would otherwise say "std::string". A global define in kml/base/util.h declares "using std::string". This permits direct use of libkml in codebases that have their own (STL-compatible) string implementation.
  * For the same reason we don't `#include <string>` everywhere string is used.