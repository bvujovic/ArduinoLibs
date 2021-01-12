#include <SpiffsUtils.h>
#include "FS.h"

String SpiffsUtils::ReadFile(String fileName)
{
  // http://arduino.esp8266.com/Arduino/versions/2.0.0/doc/filesystem.html#file-object
  // https://www.youtube.com/watch?v=1coe2576Rcw

  File fp = SPIFFS.open(fileName, "r");
  String s = "";
  if (fp)
  {
    s = fp.readString();
    fp.close();
  }
  return s;
}

bool SpiffsUtils::WriteFile(String fileName, String s, const char* mode)
{
  SPIFFS.begin();
  File fp = SPIFFS.open(fileName, mode);
  if (fp)
  {
    fp.println(s);
    fp.close();
    return true;
  }
  else
    return false;
}
