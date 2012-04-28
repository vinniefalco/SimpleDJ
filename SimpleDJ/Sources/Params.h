/*
  ==============================================================================

  Copyright (c) 2012 by Vinnie Falco

  This file is provided under the terms of the MIT License:

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.

  ==============================================================================
*/

#ifndef PARAMS_HEADER
#define PARAMS_HEADER

#include "Param.h"

/** A set of named parameters.
*/
class Params
{
public:
  /** Add a parameter.
      The owner is responsible for deleting the param object.
  */
  void add (Param* param);

  /** Count the number of parameters
  */
  int size () const;

  /** Retrieve a parameter by name.
      If the parameter does not exist, nullptr is returned.
  */
  Param* find (String name) const;

  /** Retrieve a parameter by name.
      If the parameter does not exist, an exception is thrown.
  */
  Param& get (String name) const;

  /** Retrieve a parameter by index
  */
  Param& operator [] (int index) const
  {
    return *m_params [index];
  }

  /** Retrieve a parameter by name.
      If the parameter does not exist, nullptr is returned.
  */
  inline Param& operator [] (String name) const
  {
    return get (name);
  }

  /** Sugar for [].
  */
  inline Param& operator () (String name) const
  {
    return get (name);
  }

private:
  Array <Param*> m_params;
};

#endif
