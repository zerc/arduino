/*
  URL Shortnerer

  Example of the request to short URL:

    http://192.168.0.25/short/?url=https://google.com/

  You will receive a short version of URL in the body of response.

  Example of the request to use the short URL:

    http://192.168.0.25/go/xasrew

 */

#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 0, 25);

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);

/*
 * The structure to store request's information for future use.
 */
struct HTTPRequest {
  String method;
  String baseURL;  // URL of the current page, we don't have long names.
  String url;   // URL to make shorter. Can be quite long.
};


/*
 * Parse the raw data and create a request.
 */
HTTPRequest parseRequest(EthernetClient &client) {
  HTTPRequest request;
  int part = 0;  // part of the parsing. 0 - method, 1 - base url, 2 - url
  
  while (client.connected()) {
    if (client.available()) {
      char c = client.read();
      
      // We need only the first line for now
      if (c == '\n') {
        break;
      }

      // Begin the new part
      if (c == ' ') {
        part++;
        continue;
      }

      switch (part) {
        case 0: {
          request.method += c;
          break;
        }
        case 1: {
          request.baseURL += c;
          break;
        }
        case 2: {
          request.url += c;
          break;
        }
      }
    }
  }

  return request;
}

/*
 * Make a short version of the URL given
 */
String shortURL(String url) {
  String response;
  
  Serial.println("Short URL:");
  Serial.println(url);
  
  response = "HTTP/1.1 200 OK\n";
  response += "Content-Type: text/html\n";
  response += "Connection: close\n\n";
  response += "<!DOCTYPE HTML><html><body>";
  response += "http://192.168.0.25/go/xdssaw";
  response += "</body></html>";

  return response;
}

/*
 * Return HTTP 404
 */
String notFound() {
  String response;

  response = "HTTP/1.1 404 Not Found\n";
  response += "Content-Type: text/html\n";
  response += "Connection: close\n\n";
  response += "<!DOCTYPE HTML><html><body>";
  response += "Nothing here";
  response += "</body></html>";

  return response;
}


void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}


void loop() {
  HTTPRequest request;
  EthernetClient client = server.available();

  if (client) {
    Serial.println("new client");
    request = parseRequest(client);

    // Routing
    if (request.baseURL.startsWith("/short/?url=")) {
      client.print(shortURL(request.baseURL.substring(12)));
    } else {
      client.print(notFound());
    }

    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
}

