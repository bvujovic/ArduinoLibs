#include <EasyFS.h>
#include "FS.h"

String EasyFS::read(const String &fileName)
{
  XFS.begin();
  File fp = XFS.open(fileName, "r");
  String s = "";
  if (fp)
  {
    s = fp.readString();
    fp.close();
  }
  return s;
}

bool EasyFS::_write(const String &fileName, const String &text, const char *mode)
{
  XFS.begin();
  File fp = XFS.open(fileName, mode);
  if (fp)
  {
    fp.println(text);
    fp.close();
    return true;
  }
  else
    return false;
}

bool EasyFS::clear(const String &fileName)
{
  XFS.begin();
  File fp = XFS.open(fileName, "w");
  if (fp)
  {
    fp.close();
    return true;
  }
  else
    return false;
}

void EasyFS::setFileName(const String &fileName, bool clearContent)
{
  EasyFS::fileName = fileName;
  if (clearContent)
    clearf();
}

String EasyFS::fileName = "";