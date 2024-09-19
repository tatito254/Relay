#include <WiFi.h>        
#include <WebServer.h>      

// Configura el SSID y la contraseña de la red Wi-Fi
const char* ssid = "IoTB";
const char* password = "inventaronelVAR";

// Configura el pin del relay
const int relayPin = 12;

// Crea una instancia del servidor web en el puerto 80
WebServer server(80);

// Función para manejar la solicitud de encendido del relay
void handleRelayOn() {
  digitalWrite(relayPin, HIGH);  // Enciende el relay
  String html = "<html>\
                  <body>\
                    <h1>Relay encendido</h1>\
                    <p><a href=\"/\">Volver a las opciones</a></p>\
                  </body>\
                </html>";
  server.send(200, "text/html", html);
}

// Función para manejar la solicitud de apagado del relay
void handleRelayOff() {
  digitalWrite(relayPin, LOW);   // Apaga el relay
  String html = "<html>\
                  <body>\
                    <h1>Relay apagado</h1>\
                    <p><a href=\"/\">Volver a las opciones</a></p>\
                  </body>\
                </html>";
  server.send(200, "text/html", html);
}

// Función para la raíz del servidor web
void handleRoot() {
  // Página HTML básica para controlar el relay
  String html = "<html>\
                  <body>\
                    <h1>Control de Relay</h1>\
                    <p><a href=\"/on\">Encender</a></p>\
                    <p><a href=\"/off\">Apagar</a></p>\
                  </body>\
                </html>";
  server.send(200, "text/html", html);
}

void setup() {
  // Configura el pin del relay como salida
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW); // Asegura que el relay esté apagado al iniciar

  // Inicializa la conexión serie para el monitoreo
  Serial.begin(115200);

  // Conecta a la red Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Conectando a WiFi...");
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Conectado a la red WiFi!");

  // Imprime la dirección IP asignada
  Serial.print("IP asignada: ");
  Serial.println(WiFi.localIP());

  // Configura las rutas del servidor web
  server.on("/", handleRoot);
  server.on("/on", handleRelayOn);
  server.on("/off", handleRelayOff);

  // Inicia el servidor
  server.begin();
  Serial.println("Servidor web iniciado.");
}

void loop() {
  // Maneja las solicitudes entrantes del servidor web
  server.handleClient();
}
