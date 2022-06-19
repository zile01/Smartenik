// Publisher and Subscriber with two threads
// Cooler -> subscribing from sensors topic publishing to cooler topic
#include <stdio.h>
#include <mosquitto.h>
#include <unistd.h>
#include <thread>
#include <fstream>
#include <string>
#include <iostream>
#include <cstring>

using namespace std;

void publish(string ip_address);
void on_connect(struct mosquitto *mosq, void *obj, int rc);
void on_message(struct mosquitto *mosq, void *obj, const struct mosquitto_message *msg);
void subscribe(string ip_address);
string readFromFile();

int cooler_speed = 0;

int main() {

    string ip_address = readFromFile();

    std::thread t1(publish, ip_address);
    std::thread t2(subscribe, ip_address);

    t1.join();
    t2.join();
    return 0;
}

string readFromFile(){
	ifstream myfile;
	string text;

	myfile.open("ip.txt");
	getline(myfile, text);

	while(text.length() != 14){
        printf("Waiting for the IP...\n");
		sleep(2);
		myfile.close();
		myfile.open("ip.txt");
		getline(myfile, text);
	}

	myfile.close();

	return text;
}

void publish(string ip_address){
    int rc;
    struct mosquitto * mosq;

    mosquitto_lib_init();

    mosq = mosquitto_new(NULL, true, NULL);

    rc = mosquitto_connect(mosq, ip_address.c_str(), 1883, 60);
    if (rc != 0) {
        printf("Client could not connect to broker! Error Code: %d\n", rc);
        mosquitto_destroy(mosq);
        return;
    }

    printf("We are now connected to the broker!\n");

    while(1){
        printf("Publishing to topic smartenik/cooler..\n\n");
	string publish_message = to_string(cooler_speed);
        mosquitto_publish(mosq, NULL, "smartenik/cooler", 20, &publish_message[0], 0, false);
        sleep(1);
    }

}

void on_connect(struct mosquitto *mosq, void *obj, int rc){
	printf("ID: %d\n", *(int*)obj);
	if (rc == 0) {
		printf("Subcribing to topic -t smartenik/sensors\n ");
		mosquitto_subscribe(mosq, NULL, "smartenik/sensors", 0);
	} else {
		mosquitto_disconnect(mosq);
	}
}

void on_message(struct mosquitto *mosq, void *obj, const struct mosquitto_message *msg)
{
    string message = (char*)msg->payload;
	printf("Sensors: %s\n\n", (char*)msg->payload);

    int day = 0;
    int month = 0;
    float temperature = 0.0;
    float air_humidity = 0.0;

    int i = 0;
    char *ptr;
    ptr = strtok((char*)msg->payload, ":");
    while (ptr != NULL)
    {

        switch(i){
            case 0:
                day = stoi(ptr);
                break;
            case 1:
                month = stoi(ptr);
                break;
            case 2:
                temperature = stof(ptr);
                break;
            case 3:
                air_humidity = stof(ptr);
                break;
        }

        i++;
        ptr = strtok (NULL, ":");

    }

    ofstream file_desc("/dev/gpio_driver");

    //Change the ventilator velocity regarding the conditions

    if(temperature > 45){
    	file_desc << "2 8";
    	cooler_speed = 5;
    }else if(temperature > 40){
    	file_desc << "2 9";
    	cooler_speed = 4;
    }else if(temperature > 35){
    	file_desc << "2 10";
    	cooler_speed = 3;
    }else if(temperature > 30){
    	file_desc << "2 11";
    	cooler_speed = 2;
    }else if(temperature > 25){
    	file_desc << "2 12";
    	cooler_speed = 1;
    }else{
    	file_desc << "2 13";
    	cooler_speed = 0;
    }


    file_desc.close();
}

void subscribe(string ip_address){
    struct mosquitto *mosq;
    int rc;

    mosquitto_lib_init();

    mosq = mosquitto_new(NULL, true, NULL);
    if (mosq == NULL) {
        printf("Failed to create client instance.\n");
        return;
    }
    mosquitto_connect_callback_set(mosq, on_connect);
    mosquitto_message_callback_set(mosq, on_message);

    rc = mosquitto_connect(mosq, ip_address.c_str(), 1883, 60);
    if (rc != MOSQ_ERR_SUCCESS) {
        printf("Connect failed: %s\n", mosquitto_strerror(rc));
        return;
    }

    mosquitto_loop_forever(mosq, -1, 1);
}
