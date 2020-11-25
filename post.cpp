/*
  ____          _____               _ _           _       
 |  _ \        |  __ \             (_) |         | |      
 | |_) |_   _  | |__) |_ _ _ __ _____| |__  _   _| |_ ___ 
 |  _ <| | | | |  ___/ _` | '__|_  / | '_ \| | | | __/ _ \
 | |_) | |_| | | |  | (_| | |   / /| | |_) | |_| | ||  __/
 |____/ \__, | |_|   \__,_|_|  /___|_|_.__/ \__, |\__\___|
         __/ |                               __/ |        
        |___/                               |___/         
    
____________________________________
/ Si necesitas ayuda, contáctame en \
\ https://parzibyte.me               /
 ------------------------------------
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
                ||----w |
                ||     ||
Creado por Parzibyte (https://parzibyte.me).
------------------------------------------------------------------------------------------------
Si el código es útil para ti, puedes agradecerme siguiéndome: https://parzibyte.me/blog/sigueme/
Y compartiendo mi blog con tus amigos
También tengo canal de YouTube: https://www.youtube.com/channel/UCroP4BTWjfM0CkGB6AFUoBg?sub_confirmation=1
------------------------------------------------------------------------------------------------
*/
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

// Credentials to connect to the wifi network
const char *ssid = "YOUR_SSID";
const char *password = "YOUR_PASSWORD";
/*
The ip or server address. If you are on localhost, put your computer's IP (for example http://192.168.1.65)
If the server is online, put the server's domain for example https://parzibyte.me
*/
const String SERVER_ADDRESS = "http://192.168.1.77/esp8266_api";
void setup()
{
  Serial.begin(9600); // Initialize serial communications with the PC. Just for debug
  while (!Serial)
    ;

  // Connect to wifi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting...");
  }
  Serial.println("Connected!");
}

void loop()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("Wifi is unavailable");
    return;
  }
  // Make request each 5 seconds

  HTTPClient http;

  // This value can come from a sensor
  String value = "Hello. This is a post request";
  String another_value = "Hello world! :)";
  String full_url = SERVER_ADDRESS + "/save_data_post.php";
  http.begin(full_url);

  // Make request
  Serial.println("Making request to " + full_url);
  // We send the data in JSON format. Something like:
  /*
  {"value":"some_value","another_value":"another_value"}
  */
  int httpCode = http.POST(
      "{\"value\":\"" + value + "\"" +
      ",\"another_value\":\"" +
      another_value + "\"" +
      "}");
  if (httpCode > 0)
  {
    if (httpCode == HTTP_CODE_OK)
    {

      String payload = http.getString(); //Get the request response payload
      Serial.println("Request is OK! The server says: ");
      Serial.println(payload);
    }
    else
    {
      Serial.println("Error: httpCode was " + http.errorToString(httpCode));
    }
  }
  else
  {
    Serial.println("Request failed: " + http.errorToString(httpCode));
  }

  http.end(); //Close connection
  // And wait 5 seconds
  delay(5000);
}