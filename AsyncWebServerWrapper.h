#pragma once

class LcdIf;

class AsyncWebServerWrapper
{
public:
    AsyncWebServerWrapper(LcdIf& lcd_);
    void create();
    void waitUntilConnectionServed();
    void destroy();
private:
    void beginOta();
    LcdIf& lcd;
};
