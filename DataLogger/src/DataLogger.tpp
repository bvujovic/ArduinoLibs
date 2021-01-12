#include "DataLogger.h"

template <typename T, size_t S>
DataLogger<T, S>::DataLogger(const char *fileName, void (*saveFunc)(void *, File &), bool clearFile, int saveDelay)
{
    XFS.begin();
    this->fileName = fileName;
    if (saveFunc != NULL)
        this->saveFunc = saveFunc;
    if (clearFile)
        this->clearFile();
    this->msSaveDelay = saveDelay;
}

template <typename T, size_t S>
void DataLogger<T, S>::forEach(void (*f)(void *))
{
    for (int i = 0; i < size(); i++)
    {
        T obj = buf[i];
        f(&obj);
    }
}

template <typename T, size_t S>
void DataLogger<T, S>::saveToFile(bool clearBuffer)
{
    File fp = XFS.open(fileName, "a");
    for (int i = 0; i < size(); i++)
    {
        T obj = buf[i];
        saveFunc(&obj, fp);
    }
    if (clearBuffer)
        buf.clear();
    fp.close();
}

template <typename T, size_t S>
void DataLogger<T, S>::addSave(T el, bool clearBuffer)
{
    add(el);
    saveToFile(clearBuffer);
}

template <typename T, size_t S>
void DataLogger<T, S>::addSaveDelayed(T el)
{
    add(el);
    msSave = millis() + msSaveDelay;
}

template <typename T, size_t S>
void DataLogger<T, S>::refresh(ulong ms)
{
    if (ms > msSave)
    {
        saveToFile(true);
        msSave = UINT32_MAX;
    }
}

template <typename T, size_t S>
void DataLogger<T, S>::clearFile()
{
    File fp = XFS.open(fileName, "w");
    if (fp)
        fp.close();
}

template <typename T, size_t S>
String DataLogger<T, S>::readFromFile()
{
    String s;
    File f = XFS.open(getFileName(), "r");
    if (f)
    {
        s = f.readString();
        f.close();
    }
    return s;
}

template <typename T, size_t S>
void DataLogger<T, S>::forEachInFile(void (*func)(String))
{
    File f = XFS.open(getFileName(), "r");
    if (f)
    {
        while (f.available())
            func(f.readStringUntil('\n'));
        f.close();
    }
}

template <typename T, size_t S>
void DataLogger<T, S>::stringToFile(void *obj, File &fp)
{
    String *s = (String *)obj;
    fp.printf("%s\n", s->c_str());
}
