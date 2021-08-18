#ifndef KAREN_H
# define KAREN_H

#include<iostream>
#include<string>
#include<map>

class Karen
{
private:
    static void debug( void );
    static void info( void );
    static void warning( void );
    static void error( void );

    typedef void                        (*fct_karen)(void);
    std::map<std::string, fct_karen>   fct_map = {
         {"debug", &Karen::debug}
    };
    // {
    //     {"debug", &Karen::debug}, {"info", &Karen::info}, {"warning", &Karen::warning}, {"error", &Karen::error}
    // };

public:
    Karen();
    ~Karen();

    void complain( std::string level );
};

#endif