#ifndef LIB_HPP
# define LIB_HPP

# include <iostream>
  using namespace std;

# define RESET      "\033[0m"
# define BOLD       "\033[1m"
# define UNDERSCORE "\033[4m"
# define BLACK      "\033[30m"
# define RED        "\033[31m"
# define GREEN      "\033[32m"
# define YELLOW     "\033[33m"
# define BLUE       "\033[34m"
# define MAGENTA    "\033[35m"
# define CYAN       "\033[36m"
# define WHITE      "\033[37m"
# define GREY       "\033[90m"
# define BBLACK      "\033[40m"
# define BRED        "\033[41m"
# define BGREEN      "\033[42m"
# define BYELLOW     "\033[43m"
# define BBLUE       "\033[44m"
# define BMAGENTA    "\033[45m"
# define BCYAN       "\033[46m"
# define BWHITE      "\033[47m"
# define BGREY       "\033[100m"

# define SUPERSCRIPTS string supersripts[10] = {"⁰","¹","²","³","⁴","⁵","⁶","⁷","⁸","⁹"}

namespace lib
{
    // =====  MATH  ===== //

    double  fabs(double nbr);
    double  floor(double value);
    double  frexp(double x, int &exp);
    double  ldexp (double x, int exp);
    double  pgcd(double a, double b);
    double  pow(double base, double exponent);
    double  sqrt(double x);

    // ===== STRING ===== //

    int     count_char(char const *str, char c);

    // ===== PRINT ===== //

    template <typename T>
    void    print(T str) 
    { 
        cout << str << RESET;
    }
    template <typename T, typename ...U>
    void    print(T str, U ...u)
    {
        cout << str;
        print(u...);
    }

    template <typename T>
    void    printendl(T str) 
    { 
        cout << str << RESET << endl;
    }
    template <typename T, typename ...U>
    void    printendl(T str, U ...u)
    {
        cout << str;
        printendl(u...);
    }

    template <typename T>
    int    printerr(T str) 
    { 
        cerr << str << RESET << endl;
        return (1);
    }
    template <typename T, typename ...U>
    int    printerr(T str, U ...u)
    {
        cerr << str;
        printerr(u...);
        return (1);
    }

}

#endif
