
#include "SdWrapper.h"
#include "Arduino.h"
#include <SD.h>

void saveToBuffer(const String& name, char* const buffer, const int maxSize, int& writtenBytes)
{
    for (int i = 0; i < name.length(); i++)
    {
        buffer[writtenBytes] = name[i];
        if (writtenBytes < maxSize) { writtenBytes++; }
    }
    if (writtenBytes < maxSize)
    {
        buffer[writtenBytes] = '\n';
        if (writtenBytes < maxSize) { writtenBytes++; }
    }
}
#ifdef ESP32
int listDir(fs::FS &fs, const char * dirname, char* const buffer, const int maxSize){
#else
int listDir(SDClass &fs, const char * dirname, char* const buffer, const int maxSize){
#endif
    int numOfFiles{0};
    int writtenBytes{0};
    Serial.printf("Listing directory: %s\n\r", dirname);

    File root = fs.open(dirname);
    if(!root){
        Serial.println("Failed to open directory");
        return 0;
    }
    if(!root.isDirectory()){
        Serial.println("Not a directory");
        return 0;
    }

    File file = root.openNextFile();
    Serial.printf("1st next: %s \n\r", file.name());
    while(file){
        numOfFiles++;
        if(file.isDirectory()){
            Serial.print("  DIR : ");
            Serial.println(file.name());
        }
        else
        {
            saveToBuffer(file.name(), buffer, maxSize, writtenBytes);
            Serial.print("  FILE: ");
            Serial.print(file.name());
            Serial.print("  SIZE: ");
            Serial.println(file.size());
        }
        file = root.openNextFile();
    }
    return numOfFiles;
}
int SdWrapper::printCardContent(char* const area, const int maxSize) const
{
    return listDir(SD, "/", area, maxSize);
}
//File SdWrapper::getFirst()
//{
//    File root = SD.open("/");
//    File first = root.openNextFile();
//}
