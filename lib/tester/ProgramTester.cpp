#include "lib.hpp"

lib::ProgramTester::ProgramTester( std::string testName, std::string executableName ) : m_testName(testName), m_executableName(executableName)
{}
lib::ProgramTester::ProgramTester( std::string testName, std::string executableName, std::vector<std::vector<std::string>> test) : m_testName(testName), m_executableName(executableName)
{ m_tests.insert( m_tests.end(), test.begin(), test.end() ); }

void    lib::ProgramTester::setTest( std::vector<std::string> test ){ m_tests.push_back( test ); }
void    lib::ProgramTester::setTests( std::vector<std::vector<std::string>> test ) { m_tests.insert( m_tests.end(), test.begin(), test.end() ); }

void    lib::ProgramTester::executeTests(){
    printendl(BOLD, BLUE, "  ===============  ", CYAN, m_testName, BLUE, "  ===============  ", RESET, "\n");
    for ( auto &test : m_tests )
    {
        std::string     command("./" + m_executableName);
        for ( auto &argument : test )
            command += " \"" + argument + "\"";
        printendl(BOLD, UNDERSCORE, command, RESET, " : ");
        std::system(command.c_str());
        printendl("");
    }
}