
/**
 * @file con_load.h
 * @brief Configuration file loader utility
 *
 * This module provides macros for loading configuration values from a file.
 * It supports loading integers, strings, and enumerations from a simple
 * configuration file format.
 */

#include <stdio.h>
#include <string.h>
#include <strings.h>

/**
 * @brief Load values from a configuration file
 * 
 * Key-value pairs in the config file are assumed to be of the form:
 * "--key value"
 * Lines not starting in "--" are ignored.
 * Keys are *not* case-sensitive.
 * Enum values are *not* case-sensitive.
 *
 * @param file Name of the file to load
 * @param cases One or more instances of `con_val()` or `con_enum()`
 *              The cases must *not* be separated by commas
 *
 * Example:
 * @code
 *     // Content of "config.con":
 *     // --integer 5
 *     // --greeting hello
 *     // --enumeration En2
 *     
 *     typedef enum { En1, En2, En3 } En;
 *     int     i;
 *     char    s[16];
 *     En      en;
 *
 *     con_load("config.con",
 *         con_val("integer", &i, "%d")
 *         con_val("greeting", s, "%[^\n]")
 *         con_enum("enumeration", &en, 
 *             con_match(En1)
 *             con_match(En2)
 *             con_match(En3)
 *         )
 *     )
 *     printf("%s, %d, %d\n", s, i, en);   // Should print "hello, 5, 1"
 * @endcode
 */
#define con_load(file, cases)                               \
{                                                           \
    FILE* _f = fopen(file, "r");                            \
    if(_f){                                                 \
        char _line[128] = {0};                              \
        while(fgets(_line, 128, _f)){                       \
            if(!strncmp(_line, "--", 2)){                   \
                char _key[64];                              \
                char _val[64];                              \
                sscanf(_line, "--%s %s", _key, _val);       \
                cases                                       \
            }                                               \
        }                                                   \
    } else {                                                \
        printf("Unable to open config file %s\n", file);    \
    }                                                       \
}

/**
 * @brief Parse a single value from configuration
 * 
 * @param key The key to match (case-insensitive)
 * @param var Pointer to variable where the value should be stored
 * @param fmt Format string for parsing the value (printf-style)
 */
#define con_val(key, var, fmt)                              \
    if(!strcasecmp(_key, key)){                             \
        sscanf(_val, fmt, var);                             \
    }

/**
 * @brief Parse an enumeration value from configuration
 * 
 * @param key The key to match (case-insensitive)
 * @param var Pointer to enum variable where the value should be stored
 * @param match_cases One or more instances of con_match() for enum values
 */
#define con_enum(key, var, match_cases)                     \
    if(!strcasecmp(_key, key)){                             \
        typeof(*var) _v;                                    \
        match_cases                                         \
        *var = _v;                                          \
    }

/**
 * @brief Match a specific enum identifier in configuration
 * 
 * @param id The enum identifier to match (case-insensitive)
 */
#define con_match(id)                                       \
    if(!strcasecmp(_val, #id)){                             \
        _v = id;                                            \
    }

