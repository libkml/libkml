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
    m_CurrentLocale(NULL)
  {
    /* Create a new locale object, with LC_NUMERIC=C  */
#if defined(_WIN32)
    m_CurrentLocale = _create_locale(LC_NUMERIC, "C");
#else  
    m_CurrentLocale = newlocale(LC_NUMERIC_MASK, "C", (locale_t) 0);
    uselocale(m_CurrentLocale);
#endif
    
    if (m_CurrentLocale == NULL)
      printf("Cannot create an instance of locale_t\n");
    
  }
  
  LocaleC::~LocaleC()
  {
    if (m_CurrentLocale == NULL)
      return;
#if defined(_WIN32)
    _free_locale(m_CurrentLocale);
#else
    freelocale(m_CurrentLocale);
#endif
  }
 
}
