

#ifndef CONFIG_FILE_READER_H
#define CONFIG_FILE_READER_H

#include <boost/filesystem.hpp>
#include <err.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "installaction.h"
#include "messageaction.h"
#include "module.h"
#include "removeaction.h"
#include "shellaction.h"

namespace dfm {

const char COMMENT_DELIMITER = '#';

class ConfigFileReader {
public:
    ConfigFileReader(const std::string& path);
    ConfigFileReader(const boost::filesystem::path& path);
    /* TODO: Write destructor that closes file. */
    const boost::filesystem::path& getPath() const;
    void setPath(const std::string& path);
    void setPath(const boost::filesystem::path& path);

    bool isOpen();
    /*
     * Read the modules in the given file and write them to the given iterator,
     * which must contain elements of type Module.
     *
     * Returns true on success, false on failure.
     */
    template <class OutputIterator> bool readModules(OutputIterator output);

private:
    boost::filesystem::path path;
    std::ifstream reader;

    bool isEmptyLine(const std::string& line) const;
    bool isComment(const std::string& line, int expectedIndents) const;
    int indentCount(const std::string& line) const;
    int getExpectedIndents() const;
    /*
     * Tests to see if the line starts a module and sets moduleName to the name
     * if this is so.
     */
    bool isModuleLine(const std::string& line, std::string& moduleName);
    bool isUninstallLine(const std::string& line);
    bool isShellLine(const std::string& line);



    bool inModuleInstall;
    bool inModuleUninstall;
    Module* currentModule;
    bool inShell;
    ShellAction* currentShellAction;
    int currentLineNo;

    template <class OutputIterator>
    bool processLine(const std::string& line, OutputIterator output);
};

template <class OutputIterator>
bool
ConfigFileReader::readModules(OutputIterator output)
{
    if (!isOpen()) {
        warnx("Attempting to read from non-open file reader");
        return false;
    }

    currentLineNo = 1;
    inModuleInstall = false;
    inModuleUninstall = false;
    currentModule = nullptr;
    inShell = false;
    currentShellAction = nullptr;

    bool noErrors = true;
    std::string line;
    /* Don't read a line if processing the last line wasn't successful. */
    while (noErrors && getline(reader, line)) {
        noErrors = processLine<OutputIterator>(line, output);
        if (noErrors)
            currentLineNo++;
    }

    if (!noErrors) {
        warnx("Failed to read config file %s, line %i: %s", getPath(),
            currentLineNo, line.c_str());
    }

    return noErrors;
}

template <class OutputIterator>
bool
ConfigFileReader::processLine(const std::string& line, OutputIterator output)
{
    if (isEmptyLine(line))
        return true;

    int expectedIndents = getExpectedIndents();
    if (isComment(line, expectedIndents))
        return true;

    return true;
}
}

#endif /* CONFIG_FILE_READER_H */
