// Subscriber - User application
#include <mosquitto.h>
#include <stdio.h>
#include <thread>
#include <fstream>
#include <string>
#include <unistd.h>
#include <iostream>
#include <cstring>

using namespace std;

int flag = 0;
int day = 0;
int month = 0;
float temperature = 0.0;
float air_humidity = 0.0;
string cooler;


string readFromFile();
void on_connect(struct mosquitto *mosq, void *obj, int rc);
void on_message(struct mosquitto *mosq, void *obj, const struct mosquitto_message *msg);
void subscribe(string ip_address);
void progress_bar();


int main()
{
    string ip_address = readFromFile();

    thread t1(subscribe, ip_address);
    sleep(1);
    thread t2(subscribe, ip_address);
    sleep(1);
    thread t3(progress_bar);

    t1.join();
    t2.join();
    t3.join();

    return 0;

}

void progress_bar(){
    float progress_temp = temperature / 100;
    float progress_hum  = air_humidity / 100;
    while (progress_temp <= 1.0) {
        int barWidth = 30;

        system("clear");

        cout << "SMARTENIK© - The smart solutions for hothouses" << endl;

        cout << "Day:\t\t" << day << endl;

        switch(month){
            case 1:
                cout << "Month:\t\t" << "January" << endl;
                break;
            case 2:
                cout << "Month:\t\t" << "February" << endl;
                break;
            case 3:
                cout << "Month:\t\t" << "March" << endl;
                break;
            case 4:
                cout << "Month:\t\t" << "April" << endl;
                break;
            case 5:
                cout << "Month:\t\t" << "May" << endl;
                break;
            case 6:
                cout << "Month:\t\t" << "June" << endl;
                break;
            case 7:
                cout << "Month:\t\t" << "July" << endl;
                break;
            case 8:
                cout << "Month:\t\t" << "August" << endl;
                break;
            case 9:
                cout << "Month:\t\t" << "September" << endl;
                break;
            case 10:
                cout << "Month:\t\t" << "October" << endl;
                break;
            case 11:
                cout << "Month:\t\t" << "November" << endl;
                break;
            case 12:
                cout << "Month:\t\t" << "December" << endl;
                break;
        }

        cout << "Temperature:\t"<< "[";
        int pos1 = barWidth * progress_temp;
        for (int i = 0; i < barWidth; i++) {
            if (i < pos1) cout << "■";
            else if (i == pos1) cout << "■";
            else cout << " ";
        }
        cout << "] " << int(progress_temp * 100.0) << " °C\r" << endl;

        cout << "Air humidity:\t"<< "[";
        int pos2 = barWidth * progress_hum;
        for (int i = 0; i < barWidth; i++) {
            if (i < pos2) cout << "■";
            else if (i == pos2) cout << "■";
            else cout << " ";
        }
        cout << "] " << int(progress_hum * 100.0) << " %\r" << endl;

        cout << "Cooler power:\t" << cooler << endl;

        cout.flush();


        progress_temp = temperature / 100;
        progress_hum = air_humidity / 100;

        sleep(1);
    }
    cout << endl;
}


void on_connect(struct mosquitto *mosq, void *obj, int rc){
	printf("ID: %d\n", *(int*)obj);
	if (rc == 0) {
        if(flag == 0){
            printf("Subcribing to topic smartenik/sensors\n ");
            mosquitto_subscribe(mosq, NULL, "smartenik/sensors", 0);
            flag++;
        }else if(flag == 1){
            printf("Subcribing to topic smartenik/cooler\n ");
            mosquitto_subscribe(mosq, NULL, "smartenik/cooler", 0);
        }

	} else {
		mosquitto_disconnect(mosq);
	}
}

void on_message(struct mosquitto *mosq, void *obj, const struct mosquitto_message *msg)
{

    if(strcmp(msg->topic, "smartenik/cooler") == 0){
        // printf("New message: %s. Topic: %s \n", (char*)msg->payload, msg->topic);
        cooler = (char*)msg->payload;
    }

    if(strcmp(msg->topic, "smartenik/sensors") == 0){

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
    }

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
