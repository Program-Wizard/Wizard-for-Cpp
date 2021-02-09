#include<string>
#include<vector>
/**
 * @file Keywords.hpp
 * @author Program-Wizard Organisation
 * @brief API for C++ code generation
 **/

/**
 * @name namespace Wizard
 * @brief Super namespace for all wizards
 **/
namespace Wizard
{
    /**
     * @name namespace Cpp
     * @brief Namespace for Cpp code generation
     **/
    namespace Cpp
    {
        /**
         * @name namespace API
         * @brief Namespace for C++ wizard's API
         **/
        namespace API
        {
            /**
             * @name STRUCT Keywords
             * @brief Structure for C++ keywords
             **/
            struct Keywords
            {
                /**
                 * @name FUNCTION Include
                 * @return Line with include directive
                 * @param lib Library to include
                 * @param has_space Determines whether add space between "#include" and "<" or not
                 * @brief Checks whether @arg has_space is true or not. If it is true then returns "#include <lib>\n" else returns "#include<lib>\n".
                 **/
                static std::string Include(std::string lib, bool has_space)
                {
                    return (has_space ? ("#include <" + lib + ">\n") : ("#include<" + lib + ">\n"));
                }
                /**
                 * @name FUNCTION BasicInclude
                 * @return 6 common libraries to include
                 * @param math_defs Adds "#define USE_MATH_DEFINES" before adding cmath
                 * @param has_space Same as in Wizard::Cpp::API::Keywords::Include function
                 * @brief Invokes Wizard::Cpp::API::Keywords::Include with following libraries: iostream, string, vector, cmath, array. If @arg math_defs is true then defines USE_MATH_DEFINES.
                 **/
                static std::string BasicInclude(bool math_defs, bool has_space)
                {
                    std::string ret = "";
                    ret += Keywords::Include("iostream", has_space);
                    ret += Keywords::Include("string", has_space);
                    ret += Keywords::Include("vector", has_space);
                    if(math_defs)
                    {
                        Keywords::Define("USE_MATH_DEFINES", 1);
                        ret += Keywords::Include("cmath", has_space);
                    }
                    else ret += Keywords::Include("cmath", has_space);
                    ret += Keywords::Include("array", has_space);
                    return ret;
                }
                /**
                 * @name Using
                 * @return using namespace @arg str or using alias
                 * @param str Namespace name or new using alias
                 * @param u Determines whether this is "using namespace" or using alias
                 * @brief u can be NS for "using namespace" or ALIAS for using alias. If u is something else, then exception is throw.
                 **/
                static std::string Using(std::string str, enum USING u)
                {
                    if(u == NS) return "using namespace " + str + ";\n";
                    else if(u == ALIAS) return "using " + str + " = ";
                    else throw "Exception: Not implemented! Keywords.hpp.74: enum USING { NS, ALIAS };\n";
                }
                template<typename T>
                static std::string Define(std::string def, T val)
                {
                    return "#define " + def + " " + val + "\n";
                }
                template<typename T>
                static std::string Main(enum TYPE t, std::vector<std::string> content, T ret)
                {
                    auto ret_f = "";
                    for(size_t i = 0; i < content.size(); i++)
                    {
                        ret_f += "\t" + content[i];
                    }
                    if(t == Keywords::INT) return "int main()\n{\n" + ret_f + "\n\treturn " + ret + ";\n}\n";
                    else if(t == Keywords::VOID) return "void main()\n{\n" + ret_f + "\n\treturn " + ret + ";\n}\n";
                    else throw "Exception: Not implemented! Keywords.hpp.43: std::string Main(enum TYPE, std::vector<std::string>, auto)\n";
                }
                static std::string Stdout(std::string text, bool is_std_used, bool is_new_line)
                {
                    if(is_std_used)
                    {
                        if(is_new_line) return "cout << " + text + " << \"\\n\";\n";
                        else return "cout << " + text + ";\n";
                    }
                    else
                    {
                        if(is_new_line) return "std::cout << " + text + " << \"\\n\";\n";
                        else return "std::cout << " + text + ";\n";
                    }
                }
                static std::string Stdin(std::string cinned, bool is_std_used)
                {
                    if(is_std_used) return "cin >> " + cinned + ";\n";
                    else return "std::cin >> " + cinned + ";\n";
                }
                static std::string Stderr(std::string text, bool is_std_used, bool is_new_line)
                {
                    if(is_std_used)
                    {
                        if(is_new_line) return "cerr << " + text + " << \"\\n\";\n";
                        else return "cerr << " + text + ";\n";
                    }
                    else
                    {
                        if(is_new_line) return "std::cerr << " + text + " << \"\\n\";\n";
                        else return "std::cerr << " + text + ";\n";
                    }
                }
                static std::string Stdlog(std::string text, bool is_std_used, bool is_new_line)
                {
                    if(is_std_used)
                    {
                        if(is_new_line) return "clog << " + text + " << \"\\n\";\n";
                        else return "clog << " + text + ";\n";
                    }
                    else
                    {
                        if(is_new_line) return "std::clog << " + text + " << \"\\n\";\n";
                        else return "std::clog << " + text + ";\n";
                    }
                }
                enum USING { NS, ALIAS };
                enum TYPE
                {
                    // num
                    INT, UNS,
                    SHORT, UNSSHORT,
                    LONG, UNSLONG,
                    LONGLONG, UNSLONGLONG,
                    // floating-point
                    FLOAT, DOUBLE, LONGDOUBLE,
                    // STL Types
                    SIZE_T, TIME_T,
                    // other
                    CHAR, SIGNCHAR, BOOL,
                    // compound; meta types
                    ENUM, UNION, CLASS, STRUCT,
                    // basic containers
                    STRING, VEC, ARR,
                    // non-data
                    VOID
                };
            };
        }
    }
}