
#ifdef ESP8266
#define ESP8266_OLD_ARDUINO_USED // TODO: update to 2.5.2 or newer
#endif

#include "AsyncWebServerWrapper.h"
#include "ESPAsyncWebServer.h"
#include "LcdIf.h"
#ifndef ESP8266_OLD_ARDUINO_USED
#include "SdWrapper.h"
#endif

static const int server_port = 80;
AsyncWebServer serverImpl(server_port);
bool serverFinished{false};
bool serverAccessed{false};

unsigned int cnt{0};
int constexpr htmlResponseSize{3000};
char htmlResponse[htmlResponseSize]{};

static const char INDEX_HEAD_HTML[] = R"rawliteral( 
<!DOCTYPE html>
<html>
<head>
<title>Kayak logger web server</title>
</head>
<body>
)rawliteral";
static const char INDEX_TAIL_HTML[] = R"rawliteral(
</body>
</html>
)rawliteral";
static const char openParagraph[] = R"rawliteral(<p>)rawliteral";
static const char closeParagraph[] = R"rawliteral(</p>)rawliteral";
static const char sdContentHeading[] = R"rawliteral(Logs on SD card:)rawliteral";
static const char textAreaStartAndColumns[] = R"rawliteral(<p><textarea cols=)rawliteral";
static const char textAreaNameAndRows[] = R"rawliteral( name="Logs" rows=)rawliteral";
static const char textAreaRowsCloser[] = R"rawliteral(>)rawliteral";
static const char textAreaEnd[] = R"rawliteral(</textarea></p>
)rawliteral";
int constexpr maxNumOfLogs{11};
char itoaBuffer[33];
unsigned int numOfLogs{0};
int constexpr logNameMaxLength{300};
int constexpr logsMessageAreaSize{logNameMaxLength*maxNumOfLogs};
char logsMessageArea[logsMessageAreaSize];

static const char downloadButton[] = R"rawliteral(
<form method="post" action="/downloadFirst">
<br><button id=\"downloadFirst\">Download first</button>
</form>)rawliteral";

static const char deleteButton[] = R"rawliteral(
<form method="post" action="/deleteFirst">
<br><button id=\"deleteFirst\">Delete first</button>
</form>)rawliteral";

int getLogsToMessageArea()
{
    int retVal{0};
    memset(logsMessageArea, 0, sizeof(logsMessageArea));
#ifndef ESP8266_OLD_ARDUINO_USED
    SdWrapper sdWrapper;
    retVal = sdWrapper.printCardContent(logsMessageArea, logsMessageAreaSize);
#endif
    return retVal;
}
void handleRoot(AsyncWebServerRequest* request) {
    cnt++;
    serverAccessed = true;
    int writtenBytes = snprintf(&htmlResponse[0], sizeof(INDEX_HEAD_HTML), INDEX_HEAD_HTML);
    // SD logs listed
    numOfLogs = getLogsToMessageArea();
    writtenBytes += snprintf(&htmlResponse[writtenBytes-1], sizeof(openParagraph), openParagraph);
    writtenBytes += snprintf(&htmlResponse[writtenBytes-1], sizeof(sdContentHeading), sdContentHeading);
    writtenBytes += snprintf(&htmlResponse[writtenBytes-1], sizeof(closeParagraph), closeParagraph);

    writtenBytes += snprintf(&htmlResponse[writtenBytes-1], sizeof(textAreaStartAndColumns), textAreaStartAndColumns);
    itoa(maxNumOfLogs, itoaBuffer, 10);
    writtenBytes += snprintf(&htmlResponse[writtenBytes-1], sizeof(itoaBuffer), itoaBuffer);
    writtenBytes += snprintf(&htmlResponse[writtenBytes-1], sizeof(textAreaNameAndRows), textAreaNameAndRows);
    itoa(numOfLogs, itoaBuffer, 10);
    writtenBytes += snprintf(&htmlResponse[writtenBytes-1], sizeof(itoaBuffer), itoaBuffer);
    writtenBytes += snprintf(&htmlResponse[writtenBytes-1], sizeof(textAreaRowsCloser), textAreaRowsCloser);
    writtenBytes += snprintf(&htmlResponse[writtenBytes-1], logsMessageAreaSize, logsMessageArea);
    writtenBytes += snprintf(&htmlResponse[writtenBytes-1], sizeof(textAreaEnd), textAreaEnd);
    // Downloading
    writtenBytes += snprintf(&htmlResponse[writtenBytes-1], sizeof(downloadButton), downloadButton);
    // Deleting
    writtenBytes += snprintf(&htmlResponse[writtenBytes-1], sizeof(deleteButton), deleteButton);
    writtenBytes += snprintf(&htmlResponse[writtenBytes-1], sizeof(INDEX_TAIL_HTML), INDEX_TAIL_HTML);
//    Serial.print("sendResp: "); Serial.println(writtenBytes);
//    Serial.println(htmlResponse);
    request->send(200, "text/html", htmlResponse);
}
void handleDownload(AsyncWebServerRequest* request)
{
#ifndef ESP8266_OLD_ARDUINO_USED
    SdWrapper sdWrapper;
    File first = sdWrapper.getFirst();
//    Serial.printf("handleDownload %s \n\r", first.name());
    request->send(first, first.name(), String(), true);
#endif
}
void handleDelete(AsyncWebServerRequest* request) {
#ifndef ESP8266_OLD_ARDUINO_USED
    SdWrapper sdWrapper;
    sdWrapper.deleteFirst();
#endif
    handleRoot(request);
}
void handleDisconnect(AsyncWebServerRequest* request) {

}

AsyncWebServerWrapper::AsyncWebServerWrapper()
{

}
void AsyncWebServerWrapper::create()
{
    serverImpl.on("/", HTTP_GET, handleRoot);
    serverImpl.on("/downloadFirst", handleDownload);
    serverImpl.on("/disconnect", handleDisconnect);
    serverImpl.on("/deleteFirst", handleDelete);
    serverImpl.begin();
}
void AsyncWebServerWrapper::waitUntilConnectionServed(LcdIf& lcd)
{
    serverFinished = false;
    serverAccessed = false;
    unsigned long const startTime = millis();
    unsigned long deltaTime{0};
    do
    {
        deltaTime = (millis() - startTime) / 1000;
        lcd.clear();
        lcd.smallText();
        lcd.print("Wifi: ");
        lcd.print(String(deltaTime));
        if (serverAccessed)
        {
            lcd.row(1);
            lcd.print("accessed");
        }
        delay(1000);
        if (serverFinished) { break; }
    }
    while(deltaTime < 60 or serverAccessed);
}
void AsyncWebServerWrapper::destroy()
{
    serverImpl.reset();
}
