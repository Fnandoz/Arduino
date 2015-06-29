#include <SPI.h>
#include <Ethernet.h>

#define led1 8
#define led2 9


byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 192, 168, 0, 177 };
     
EthernetServer server(80);
  
String readString;

  
void setup(){
  
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

  
  Ethernet.begin(mac, ip);
  server.begin();
}
  
void loop(){
  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
  
        if (readString.length() < 100) {
          readString += c;             
        }
 
        if (c == '\n') {
         client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();
           
          client.println("<HTML>");
          client.println("<BODY>");
          client.println("<H1>Arduino Ethernet LED</H1>");
          client.println("<hr />");
          client.println("<br />");
          
          client.println("<a href=\"/?ledon1\"\><button>Turn on Led 1</button></a>");
          client.println("<a href=\"/?ledon2\"\><button>Turn on Led 2</button></a>");;
          client.println("<p>");
          client.println("<a href=\"/?ledoff1\"\><button>Turn off Led 1</button></a>");
          client.println("<a href=\"/?ledoff2\"\><button>Turn off Led 2</button></a>");
          client.println("<\p>");

          client.println("</BODY>");
          client.println("</HTML>");
           
          delay(1);
          client.stop();
          
          if(readString.indexOf("?ledon1") > 0)
          {
            digitalWrite(led1, HIGH);
          }
          else {
            if(readString.indexOf("?ledoff1") > 0)
            {
              digitalWrite(led1, LOW);
            }
          }
          
          if(readString.indexOf("?ledon2") > 0)
          {
            digitalWrite(led2, HIGH);
          }
          else {
            if(readString.indexOf("?ledoff2") > 0)
            {
              digitalWrite(led2, LOW);
            }
          }     
      
         
                   
          readString="";    
        }
      }
    }
  }
}
