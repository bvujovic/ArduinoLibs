#ifndef EASY_INI_H_
#define EASY_INI_H_

#include <Arduino.h>

#if FS_LITTLEFS
#include <LittleFS.h>
#define XFS LittleFS
#endif
#if FS_SPIFFS
#include <SPIFFS.h>
#define XFS SPIFFS
#endif

#define EINI_BUF_LEN 80
#define EINI_DEF_NUM 0
#define EINI_DEF_STR ""
#define EINI_ROW_SEP '\n'
#define EINI_VAL_SEP '='

#define PRINT_TO_FILE \
    fp.print(name);   \
    fp.print('=');    \
    fp.println(val);

// File open mode: Open or Write
enum EasyIniFileMode
{
    FMOD_READ = 1,
    FMOD_WRITE = 2,
};

// Utility class for reading/writing to .ini files on ESP's LittleFS
class EasyINI
{
private:
    File fp;
    const char *fileName;
    // Reads a line from file, if line starts with <name>= method returns substring after '='
    String procLineString(const char *);
    // Reads a line from file, if line starts with <name>= method returns pointer to char after '='
    char *procLine(const char *, char *, size_t);

public:
    // Constructor. Example: EasyINI ei("/config.ini");
    EasyINI(const char *);

    // File name set in the constructor.
    const char *getFileName() { return fileName; }
    // Open file in requested mode.
    bool open(EasyIniFileMode);
    // Is file opened or not.
    bool opened() { return fp; }
    // Close the file.
    void close() { fp.close(); }
    // Size of the file.
    size_t size() const { return fp.size(); }

    // Read int (bool) value.
    int getInt(const char *, int = EINI_DEF_NUM);
    // Read float value.
    float getFloat(const char *, float = EINI_DEF_NUM);
    // Read text (String class) value.
    String getString(const char *, String = EINI_DEF_STR);
    // Read text (char *) value.
    char *getCharArray(const char *name);
    // Returns complete contents of the file.
    String getAll();

    // Write int value.
    void setInt(const char *, int);
    // Write float value.
    void setFloat(const char *, float);
    // Write string value.
    void setString(const char *, const char *);

    void setString(const char *name, const String &val);
};

#endif