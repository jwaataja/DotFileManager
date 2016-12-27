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

#include <stdlib.h>

#include <iostream>
#include <string>
#include <vector>

#include "configfilereader.h"
#include "options.h"

int
main(int argc, char* argv[])
{
    std::shared_ptr<dfm::DfmOptions> options(new dfm::DfmOptions());
    options->loadFromArguments(argc, argv);
    /* std::cout << "prompt " << options->promptForDependenciesFlag << std::endl; */

    dfm::ConfigFileReader reader("testfile.txt");
    reader.setOptions(options);
    /* std::cout << reader.isOpen() << std::endl; */

    std::vector<dfm::Module> modules;
    bool status = reader.readModules(std::back_inserter(modules));
    /* std::cout << "status: " << status << std::endl; */
    /* std::cout << "size: " << modules.size() << std::endl; */

    for (dfm::Module module : modules) {
        module.update();
    }

    return EXIT_SUCCESS;
}
