#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

String api_key = "1f178a1a3bc6ac3a97994e00cd775672";
String toggle_id = "ENTER_TOGGLE_WIDGET_ID";
String text_id = "435a933371b5eddb";

int t,h;
void setup() 
{
  Serial.begin(9600);
  WiFi.begin("IOT", "7537879858"); //WiFi connection

  Serial.println("Waiting for connection");
    while (WiFi.status() != WL_CONNECTED)
    { //Wait for the WiFI connection completion
        delay(500);
        Serial.println(".");
    }
}

void loop() 
{
//  postText(text_id, "101");
//  
//  delay(3000);

  if (WiFi.status() == WL_CONNECTED) {
    
     if (Serial.available()<1)
        return;
      
     String R=Serial.readString();
     Serial.println(getValue(R,':', 0));
     Serial.println(getValue(R,':', 1));
     // Serial.println(getValue(R,':', 2));
//  Serial.println(R);                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
     //Serial.println(postText("ef409973a76822df", getValue(R,':', 0)));
     Serial.println(postText("be9b732f8ae1498b", getValue(R,':', 0)));
     Serial.println(postText("c1ae00b5b30ca7a0", getValue(R,':', 1)));

     if( getValue(R,':', 0).toInt() > 50 || getValue(R,':', 2).toInt() > 5) {
      
        Serial.println(postText("4ad3589baf81bff1", "Unsafe"));
        digitalWrite(D7,HIGH);
     } else {
      Serial.println(postText("4ad3589baf81bff1", "Safe"));
     }
  }
}

String postText(String text_id, String text_value)
{
    HTTPClient http;
    http.begin("http://api.iotsardar.com/v1/user/post/text");            //Specify request destination
    http.addHeader("Content-Type", "application/x-www-form-urlencoded"); //Specify content-type header

    int httpCode = http.POST("api_key=" + api_key + "&text_id=" + text_id + "&text_value=" + text_value); //Send the request
//    int httpCode = http.POST("api_key=" + api_key); //Send the request

    if (httpCode == 200)
    {                                           // code 200 means data received successfully
        String textReturn = http.getString(); //Get the request response payload
        return textReturn;
    }
    else
    {
        String textReturn = "error"; // return error
        Serial.println(httpCode);
        return textReturn;
    }

    http.end(); //Close connection
}

String getValue(String data, char separator, int index) {
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }
  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}
