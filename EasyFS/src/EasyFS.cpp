#include <EasyFS.h>
#include "FS.h"

String EasyFS::read(String fileName)
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

bool EasyFS::_write(String fileName, String text, const char* mode)
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

String EasyFS::fileName = "";