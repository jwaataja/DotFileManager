/*
 * Copyright (c) 2016 Jason Waataja
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include <string>

#ifndef UTIL_H
#define UTIL_H

namespace dfm {

/*
 * Waits for the user to input a yes or no input on the current line. Accepts
 * any string that starts with a "y" or "Y" as true and any string that starts
 * with a "n" or "N" as false.  Prompts the user again if they don't enter a
 * vaild input.
 *
 * Returns true if the user responded with a yes, and false if they responded
 * with a no.
 */
bool getYesOrNo();
/*
 * Outputs prompt on the current line, then waits for the user to input a yes
 * or no answer. Accepts any string that starts with a "y" or "Y" as true and
 * any string that starts with a "n" or "N" as false.
 *
 */
bool getYesOrNo(const std::string& prompt);
/*
 * WARNING: Does not return if the line is a yes or no, just if it has yes or
 * no in it. That information is stored in yesOrNo.
 *
 * Checks to see if the input is vaild and results in yes or no. If it is a
 * valid yes or no string, then yesOrNo is set to the correct result and true
 * is returned, leaves yesOrNo unchanged otherwise and returns false.
 *
 * Returns true if input is a valid yes-or-no input, false otherwise.
 */
bool lineIsYesOrNo(const std::string& input, bool& yesOrNo);
/* Returns the current working directory. */
std::string getCurrentDirectory();
/*
 * Performs shell expansion on the given path. Throws a error if it encounters
 * an errorr or if the string path expands to more than one word.
 */
std::string shellExpandPath(const std::string& path);
/*
 * Returns the current user's home directory. Throws a runtime error when
 * encountering an error.
 */
std::string getHomeDirectory();
} /* namespace dfm */

#endif /* UTIL_H */