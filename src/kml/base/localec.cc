// Copyright 2016, Rashad Kanavath <mohammedrashadkm@gmail.com>.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//  1. Redistributions of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//  2. Redistributions in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
//  3. Neither the name of Google Inc. nor the names of its contributors may be
//     used to endorse or promote products derived from this software without
//     specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
// EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
// ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "kml/base/localec.h"

namespace kmlbase {
  
  LocaleC::LocaleC() :
   previous_locale(NULL)
  {
#if defined(_WIN32)    
    // Configure per-thread locale to cause all subsequently created 
    // threads to have their own locale.
    _configthreadlocale(_ENABLE_PER_THREAD_LOCALE);
    // read current locale and save it to m_CurrentLocale
    previous_locale = setlocale(LC_NUMERIC, NULL);
    //set LC_NUMERIC locale category to C
    setlocale(LC_NUMERIC, "C");
    
#else
    //create a new C locale for LC_NUMERIC_MASK
    LocaleType c_locale;
    c_locale = newlocale(LC_NUMERIC_MASK, "C", (locale_t) 0);
    //apply c_locale and save previous locale value to m_CurrentLocale
    previous_locale = uselocale(c_locale); 
#endif 

  }

  LocaleC::~LocaleC() {
    
    if (previous_locale == NULL) {
      return;
    }
    
   #if defined(_WIN32)
      setlocale(LC_NUMERIC, previous_locale);
      free(previous_locale);
    #else
      locale_t c_locale = uselocale(previous_locale);
      freelocale(c_locale);
    #endif
  }
 
}
