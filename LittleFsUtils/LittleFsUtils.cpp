#include <LittleFsUtils.h>

String LittleFsUtils::ReadFile(String fileName)
{
  // http://arduino.esp8266.com/Arduino/versions/2.0.0/doc/filesystem.html#file-object
  // https://www.youtube.com/watch?v=1coe2576Rcw

  File fp = LittleFS.open(fileName, "r");
  String s = "";
  if (fp)
  {
    s = fp.readString();
    fp.close();
  }
  return s;
}

bool LittleFsUtils::WriteFile(String fileName, String s)
{
  File fp = LittleFS.open(fileName, "w");
  if (fp)
  {
    fp.print(s);
    fp.close();
    return true;
  }
  else
    return false;
}
