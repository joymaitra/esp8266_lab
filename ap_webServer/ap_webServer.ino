#include <ESP8266WiFi.h>        // Include the Wi-Fi library
#include <ESP8266WebServer.h>
#include <FS.h>

const char *ssid = "ESP8266 Access Point"; // The name of the Wi-Fi network that will be created
const char *password = "thereisnospoon";   // The password required to connect to it, leave blank for an open network

IPAddress ip(192,168,11,4);
IPAddress gateway(192,168,11,1);
IPAddress subnet(255,255,255,0);

void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println('\n');
  SPIFFS.begin();

  WiFi.softAPConfig(ip, gateway, subnet);
  WiFi.softAP(ssid, password);             // Start the access point
  
  Serial.print("Access Point \"");
  Serial.print(ssid);
  Serial.println("\" started");

  Serial.print("IP address:\t");
  Serial.println(WiFi.softAPIP());         // Send the IP address of the ESP8266 to the computer

  server.on("/",serveIndexFile);
  server.on("/ledstate",getLEDState);
  server.begin();


}

void loop() { 
  server.handleClient();
}

void serveIndexFile()
{
  File file = SPIFFS.open("/index.html","r");
  server.streamFile(file, "text/html");
  file.close();
}
