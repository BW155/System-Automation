#include <wifi.h>

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

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");  
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    Serial.println("Server starts...");
    wifiServer.begin();
    Serial.println("==================");
}

void handleWifi(DomObject* object) {
    WiFiClient client = wifiServer.available();
    String data = "";

    if (client && client.connected()) {
        Serial.println("Client connected");

        while (client.available() > 0) {
            data += (char) client.read();
        }
            
        Serial.println("Data:    " + data);
        DynamicJsonDocument doc(1024);
        DeserializationError error = deserializeJson(doc, data);
        if (error) {
            Serial.println(error.c_str());
            String result = constructErrorResult(error.c_str());
            client.print(result);
            return;
        }

        if (doc[String("name")] == object->getName()) {
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
        }
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

