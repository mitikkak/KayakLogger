#pragma once

class LcdIf;

class AsyncWebServerWrapper
{
public:
    AsyncWebServerWrapper();
    void create();
    void waitUntilConnectionServed(LcdIf& lcd);
    void destroy();
};
