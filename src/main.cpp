#include <Arduino.h>
#include <Firebase.h>
#include <Wake.h>
#include <WiFiUdp.h>
#include <ESP8266WiFi.h>


#define WIFI_SSID "CaioPeres_2G"
#define WIFI_PASSWORD "caioperes102030"

#define DATABASE_URL "ligarpc-871bd-default-rtdb.firebaseio.com"
#define API_KEY "mNWUnHMzWW92P7nhWiEjCQpW826tgE5nYJnecr2j"

FirebaseData firebaseData;
FirebaseAuth auth;
FirebaseConfig config;


Wake wake;
WiFiUDP Udp;


void setup() {
	
	Serial.begin(115200);

	WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

	Serial.print("Connecting to Wi-Fi");

	while (WiFi.status() != WL_CONNECTED){
		Serial.print(".");
		delay(300);
	}

	Serial.println();
	Serial.print("Connected with IP: ");
	Serial.println(WiFi.localIP());
	Serial.println();

	config.api_key = API_KEY;
	config.database_url = DATABASE_URL;
	config.signer.test_mode = true;

	Firebase.begin(&config, &auth);
	Firebase.reconnectWiFi(true);

}

void loop() {
	
	Firebase.RTDB.getBool(&firebaseData, "/Ligar");
	
	if(firebaseData.boolData()){
		Serial.println("Turning on");

		unsigned char* magicPacket = wake.getMagicPacket();

		// Dont know why, but it cant send packet to specific interface IP, only to Broadcast IP. I did the same thing in an android application and it sent the same packet to specific IP.
		IPAddress ip(192, 168, 0, 255);

		// sending 
		Udp.beginPacket(ip, 9);
		Udp.write(magicPacket, wake.getPacketLength());
		Udp.endPacket();
	

		Firebase.RTDB.setBool(&firebaseData, "/Ligar", false);
	}
	else{
		Serial.println("Wont try to turn on");
	}

	delay(1000);
}

