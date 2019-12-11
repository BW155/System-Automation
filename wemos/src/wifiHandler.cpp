#include <wifiHandler.h>

const char* ssid = "de Berlijnse muur";
const char* password = "adolfhitler";

WiFiServer wifiServer(8080);


void wifiSetup() {
    delay(10);

    // Wifi connection
    Serial.println();
    Serial.println("==================");
    Serial.print("Connecting to: ");
    Serial.println(ssid);
    
    connectWifi();


    Serial.println("Server starts...");
    wifiServer.begin();
    Serial.println("==================");
}

void handleWifi(DomObject* object) {
    // Check if wifi is still connected, if not, reconnect
    if (WiFi.status() != WL_CONNECTED) {
        connectWifi();
    }

    WiFiClient client = wifiServer.available();
    String data = "";

    // Check if client is connected
    if (client && client.connected()) {
        Serial.println("Client connected");
        delay(60);

        while (client.available() > 0) {
            data += (char) client.read();
        }

        if (data == "") {
            Serial.print("NoDataReceived");
            client.print(constructErrorResult("NoDataReceived"));
            return;
        }

        Serial.print("Data: ");
        Serial.println(data);

        if (data == "hello") {
            Serial.println("HELLO");
            client.print(object->getId());
            client.stop();
            return;
        }
            
        // Deserializing json
        DynamicJsonDocument doc(1024);
        DeserializationError error = deserializeJson(doc, data);

        // If there is an error, send error result back to client
        if (error) {
            Serial.println(error.c_str());
            String result = constructErrorResult(error.c_str());
            client.print(result);
            return;
        }

        // Check if message is meant for me
        if (doc[String("id")] == object->getId()) {
            JsonArray actuators = doc["actuators"];
            object->writeActuators(actuators);

            Serial.println("This message is for me");
            DynamicJsonDocument resultDoc(1024);

            resultDoc["error"] = "";

            JsonObject root = resultDoc.createNestedObject("result");
            JsonArray arr = root.createNestedArray("sensors");
            object->getSensors(arr);

            String result;
            serializeJson(resultDoc, result);
            Serial.println("Sending: " + result);
            client.print(result);
        } else {
            Serial.println("This message is not for me");
            String error = constructErrorResult("MessageNotForMe");
            client.print(error);
        }

        Serial.println();
        client.stop();
    }
}

String constructErrorResult(const char* error) {
    const size_t capacity = JSON_OBJECT_SIZE(0) + JSON_OBJECT_SIZE(2);
    DynamicJsonDocument doc(capacity);

    doc["error"] = error;
    doc.createNestedObject("result");

    String output;
    serializeJson(doc, output);
    return output;
}

void connectWifi() {
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println();
    Serial.println("WiFi connected");  
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}
