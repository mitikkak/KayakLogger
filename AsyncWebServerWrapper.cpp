
#include "AsyncWebServerWrapper.h"
#include "ESPAsyncWebServer.h"
#include "SdWrapper.h"
#include "LcdIf.h"

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
<title>Sarmarin ohjaus</title>
</head>
<body>
)rawliteral";
static const char INDEX_MIDDLE_HTML[] = R"rawliteral(
<form method="post" action="/createProgram" >
<p><span style="font-size:24px;"><strong>Luo ohjelma:</strong></span></p>
<br><input name="line" type="text" size="16000" value="" ><br><br>
<input type="submit" name="clk_action" value="Luo ohjelma">
</form>
<form method="post" action="runProgram">
<p><span style="font-size:24px;"><strong>Aja ohjelma:</strong></span></p>
<br><input name="line" type="text" size="1" value="" ><br><br>
<input type="submit" name="clk_action" value="Aja ohjelma">
</form>
<form method="post" action="deleteProgram">
<p><span style="font-size:24px;"><strong>Poista ohjelma:</strong></span></p>
<br><input name="line" type="text" size="1" value="" ><br><br>
<input type="submit" name="clk_action" value="Poista ohjelma">
</form>
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
<form method="post" action="/download">
<br><button id=\"downloadAll\">Download all</button>
</form>)rawliteral";

int getLogsToMessageArea()
{
    memset(logsMessageArea, 0, sizeof(logsMessageArea));
    SdWrapper sdWrapper;
    return sdWrapper.printCardContent(logsMessageArea, logsMessageAreaSize);
}
void handleRoot(AsyncWebServerRequest *request) {
    cnt++;
    serverAccessed = true;
    int writtenBytes = snprintf(&htmlResponse[0], sizeof(INDEX_HEAD_HTML), INDEX_HEAD_HTML);
    //writtenBytes += snprintf(&htmlResponse[writtenBytes-1], sizeof(INDEX_MIDDLE_HTML), INDEX_MIDDLE_HTML);
#if 0
    //
    Settings settings;
    getSettings(settings);
    writtenBytes += snprintf(&htmlResponse[writtenBytes-1], sizeof(settingsHeading), settingsHeading);
    writtenBytes += snprintf(&htmlResponse[writtenBytes-1], sizeof(currentDelayHeading), currentDelayHeading);
    itoa(settings.delay, itoaBuffer, 10);
    writtenBytes += snprintf(&htmlResponse[writtenBytes-1], sizeof(itoaBuffer), itoaBuffer);
    writtenBytes += snprintf(&htmlResponse[writtenBytes-1], sizeof(closeParagraph), closeParagraph);
    writtenBytes += snprintf(&htmlResponse[writtenBytes-1], sizeof(inputDelay), inputDelay);
    writtenBytes += snprintf(&htmlResponse[writtenBytes-1], sizeof(endForm), endForm);

    getPrograms();
    writtenBytes += snprintf(&htmlResponse[writtenBytes-1], sizeof(openParagraphBigBoldFont), openParagraphBigBoldFont);
    writtenBytes += snprintf(&htmlResponse[writtenBytes-1], sizeof(programsHeading), programsHeading);
    writtenBytes += snprintf(&htmlResponse[writtenBytes-1], sizeof(closeParagraphBigBoldFont), closeParagraphBigBoldFont);
    writtenBytes += snprintf(&htmlResponse[writtenBytes-1], sizeof(textAreaStartAndColumns), textAreaStartAndColumns);
    itoa(programMaxLength, itoaBuffer, 10);
    writtenBytes += snprintf(&htmlResponse[writtenBytes-1], sizeof(itoaBuffer), itoaBuffer);
    writtenBytes += snprintf(&htmlResponse[writtenBytes-1], sizeof(textAreaNameAndRows), textAreaNameAndRows);
    itoa(numOfPrograms, itoaBuffer, 10);
    writtenBytes += snprintf(&htmlResponse[writtenBytes-1], sizeof(itoaBuffer), itoaBuffer);
    writtenBytes += snprintf(&htmlResponse[writtenBytes-1], sizeof(textAreaRowsCloser), textAreaRowsCloser);
    writtenBytes += snprintf(&htmlResponse[writtenBytes-1], programsMessageAreaSize, programsMessageArea);
    writtenBytes += snprintf(&htmlResponse[writtenBytes-1], sizeof(textAreaEnd), textAreaEnd);
    FSInfo fs_info;
    SPIFFS.info(fs_info);
    writtenBytes += snprintf(&htmlResponse[writtenBytes-1], sizeof(openParagraphBigBoldFont), openParagraphBigBoldFont);
    writtenBytes += snprintf(&htmlResponse[writtenBytes-1], sizeof(fsInfoHeading), fsInfoHeading);
    writtenBytes += snprintf(&htmlResponse[writtenBytes-1], sizeof(closeParagraphBigBoldFont), closeParagraphBigBoldFont);
    writtenBytes += snprintf(&htmlResponse[writtenBytes-1], sizeof(openParagraph), openParagraph);
    writtenBytes += snprintf(&htmlResponse[writtenBytes-1], sizeof(bytesMsgStr), bytesMsgStr);
    itoa(fs_info.usedBytes, itoaBuffer, 10);
    writtenBytes += snprintf(&htmlResponse[writtenBytes-1], sizeof(itoaBuffer), itoaBuffer);
    writtenBytes += snprintf(&htmlResponse[writtenBytes-1], sizeof(slashStr), slashStr);
    itoa(fs_info.totalBytes, itoaBuffer, 10);
    writtenBytes += snprintf(&htmlResponse[writtenBytes-1], sizeof(itoaBuffer), itoaBuffer);
    writtenBytes += snprintf(&htmlResponse[writtenBytes-1], sizeof(closeParagraph), closeParagraph);
    Serial.print("after fsInfo sendResp: "); Serial.println(writtenBytes);
#endif
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
    // Downloading of all logs
    writtenBytes += snprintf(&htmlResponse[writtenBytes-1], sizeof(downloadButton), downloadButton);
    writtenBytes += snprintf(&htmlResponse[writtenBytes-1], sizeof(INDEX_TAIL_HTML), INDEX_TAIL_HTML);
    Serial.print("sendResp: "); Serial.println(writtenBytes);
    Serial.println(htmlResponse);
    request->send(200, "text/html", htmlResponse);
}
void handleDownload(AsyncWebServerRequest *request)
{
//    SdWrapper sdWrapper;
//    File content = sdWrapper.getFirst();
//    File root = SD.open("/");
//    File first = root.openNextFile();
//    const String& path("/tmp/");
//    Serial.printf("handleDownload %s \n\r", first.name());
    //request->send(first, path);
}
void handleDisconnect(AsyncWebServerRequest *request) {

}

AsyncWebServerWrapper::AsyncWebServerWrapper()
{

}
void AsyncWebServerWrapper::create()
{
    serverImpl.on("/", HTTP_GET, handleRoot);
    serverImpl.on("/download", handleDownload);
    serverImpl.on("/disconnect", handleDisconnect);
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
