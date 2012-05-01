/*============================================================================*/
// 
// Copyright (C) 2008 by Vinnie Falco, this file is part of VFLib.
// 
// Based on SOCI - The C++ Database Access Library:
//   http://soci.sourceforge.net/
// 
// This file is distributed under the following terms:
// 
// Boost Software License - Version 1.0, August 17th, 2003
// 
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
// 
// This file incorporates work covered by the following copyright
// and permission notice:
// 
// Copyright (C) 2004 Maciej Sobczak, Stephen Hutton, Mateusz Loskot,
// Pawel Aleksander Fedorynski, David Courtney, Rafal Bobrowski,
// Julian Taylor, Henning Basold, Ilia Barahovski, Denis Arnaud,
// Daniel Lidstr�m, Matthieu Kermagoret, Artyom Beilis, Cory Bennett,
// Chris Weed, Michael Davidsaver, Jakub Stachowski, Alex Ott, Rainer Bauer,
// Martin Muenstermann, Philip Pemberton, Eli Green, Frederic Chateau,
// Artyom Tonkikh, Roger Orr, Robert Massaioli, Sergey Nikulov,
// Shridhar Daithankar, S�ren Meyer-Eppler, Mario Valesco.
// 
/*============================================================================*/

#ifndef VF_DB_TYPE_CONVERSION_TRAITS_VFHEADER
#define VF_DB_TYPE_CONVERSION_TRAITS_VFHEADER

namespace db {

// default conversion (copy in to out)
template<typename T>
struct type_conversion
{
  typedef T base_type;

  static void from_base(base_type const& in, indicator ind, T& out )
  {
    // null not allowed
    if( ind == i_null )
       Throw (Error().fail (__FILE__, __LINE__));
    out = in;
  }

  static void to_base(T const& in, base_type& out, indicator& ind )
  {
    out = in;
    ind = i_ok;
  }
};

// Time
template <>
struct type_conversion <Time>
{
  //typedef sqlite3_int64 base_type;
  typedef int64 base_type;

  static void from_base (const base_type v, indicator ind, Time& result)
  {
    if (ind == i_null)
    {
      // jassertfalse
      result = Time (0);
    }
    else
    {
      result = Time (v);
    }
  }

  static void to_base (const Time& v, base_type& result, indicator& ind)
  {
    result = v.toMilliseconds ();
    ind = i_ok;
  }
};

}

#endif
