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

#ifndef KML_BASE_LOCALEC_H
#define KML_BASE_LOCALEC_H

#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#ifndef __APPLE__
#include <locale.h>
#else
#include <xlocale.h>
#endif

namespace kmlbase {
  
  class LocaleC {
    
  public:
#if defined(_WIN32)
    typedef char* LocaleType;
#else
    typedef locale_t LocaleType;
#endif
    
    LocaleC();
    ~LocaleC();
    
  private:
    
    LocaleType previous_locale;
    LocaleC(const LocaleC&);
    LocaleC& operator=(const LocaleC&);
    
  }; //end class LocaleC
  
} //end namespace kmlbase

#endif
