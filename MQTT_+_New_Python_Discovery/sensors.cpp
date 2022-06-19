// Publisher - Sensors
#include <stdio.h>
#include <mosquitto.h>
#include <unistd.h>
#include <iostream>
#include <random>
#include <fstream>
#include <string>

using namespace std;

//Global variables
int element_counter = 0;
int day_counter = 0;
int flag = 0;
int month = 6;

//Defines
#define NUMBER_OF_DAYS   365
#define NUMBER_OF_MONTHS 12
#define TEMP_CONST 1.66

#define JANUARY     31
#define FEBRUARY    28
#define MARCH       31
#define APRIL       30
#define MAY         31
#define JUNE        30
#define JULY        31
#define AUGUST      31
#define SEPTEMBER   30
#define OCTOBER     31
#define NOVEMBER    30
#define DECEMBER    31

//Enums
typedef enum{
    january,
    february,
    march,
    april,
    may,
    june,
    july,
    august,
    september,
    october,
    november,
    december
}enum_months;

//Structs
typedef struct{
    enum_months month;
    int day;
    float temperature;
    float air_humidity;
}day;

//Functions
float measure_temperature(enum_months month);
float measure_humidity();
string readFromFile();


int main() {

    string ip_address = readFromFile();

	int rc;
	struct mosquitto * mosq;

	mosquitto_lib_init();

	mosq = mosquitto_new(NULL, true, NULL);

	rc = mosquitto_connect(mosq, ip_address.c_str(), 1883, 60);
	if (rc != 0) {
		printf("Client could not connect to broker! Error Code: %d\n", rc);
		mosquitto_destroy(mosq);
		return -1;
	}

	printf("We are now connected to the broker!\n");

    //Fake sensor implementation

    day day_array[NUMBER_OF_DAYS];

    //Fullfilling array of structures for each day of the year
    while(1){
        flag = 0;

        while(1){
            switch(month){
                case 0:
                    day_array[element_counter].month = january;
                    day_array[element_counter].day = day_counter + 1;

                    day_array[element_counter].temperature = round(measure_temperature(january) * 100) / 100 ;
                    day_array[element_counter].air_humidity = round(measure_humidity() * 100) / 100;
                    if(day_array[element_counter].day == JANUARY){
                        flag = 1;
                    }
                    break;
                case 1:
                    day_array[element_counter].month = february;
                    day_array[element_counter].day = day_counter + 1;
                    day_array[element_counter].temperature = round(measure_temperature(february) * 100) / 100;
                    day_array[element_counter].air_humidity = round(measure_humidity() * 100) / 100;
                    if(day_array[element_counter].day == FEBRUARY){
                        flag = 1;
                    }
                    break;
                case 2:
                    day_array[element_counter].month = march;
                    day_array[element_counter].day = day_counter + 1;
                    day_array[element_counter].temperature = round(measure_temperature(march) * 100) / 100;
                    day_array[element_counter].air_humidity = round(measure_humidity() * 100) / 100;
                    if(day_array[element_counter].day == MARCH){
                        flag = 1;
                    }
                    break;
                case 3:
                    day_array[element_counter].month = april;
                    day_array[element_counter].day = day_counter + 1;
                    day_array[element_counter].temperature = round(measure_temperature(april) * 100) / 100;
                    day_array[element_counter].air_humidity = round(measure_humidity() * 100) / 100;
                    if(day_array[element_counter].day == APRIL){
                        flag = 1;
                    }
                    break;
                case 4:
                    day_array[element_counter].month = may;
                    day_array[element_counter].day = day_counter + 1;
                    day_array[element_counter].temperature = round(measure_temperature(may) * 100) / 100;
                    day_array[element_counter].air_humidity = round(measure_humidity() * 100) / 100;
                    if(day_array[element_counter].day == MAY){
                        flag = 1;
                    }
                    break;
                case 5:
                    day_array[element_counter].month = june;
                    day_array[element_counter].day = day_counter + 1;
                    day_array[element_counter].temperature = round(measure_temperature(june) * 100) / 100;
                    day_array[element_counter].air_humidity = round(measure_humidity() * 100) / 100;
                    if(day_array[element_counter].day == JUNE){
                        flag = 1;
                    }
                    break;
                case 6:
                    day_array[element_counter].month = july;
                    day_array[element_counter].day = day_counter + 1;
                    day_array[element_counter].temperature = round(measure_temperature(july) * 100) / 100;
                    day_array[element_counter].air_humidity = round(measure_humidity() * 100) / 100;
                    if(day_array[element_counter].day == JULY){
                        flag = 1;
                    }
                    break;
                case 7:
                    day_array[element_counter].month = august;
                    day_array[element_counter].day = day_counter + 1;
                    day_array[element_counter].temperature = round(measure_temperature(august) * 100) / 100;
                    day_array[element_counter].air_humidity = round(measure_humidity() * 100) / 100;
                    if(day_array[element_counter].day == AUGUST){
                        flag = 1;
                    }
                    break;
                case 8:
                    day_array[element_counter].month = september;
                    day_array[element_counter].day = day_counter + 1;
                    day_array[element_counter].temperature = round(measure_temperature(september) * 100) / 100;
                    day_array[element_counter].air_humidity = round(measure_humidity() * 100) / 100;
                    if(day_array[element_counter].day == SEPTEMBER){
                        flag = 1;
                    }
                    break;
                case 9:
                    day_array[element_counter].month = october;
                    day_array[element_counter].day = day_counter + 1;
                    day_array[element_counter].temperature = round(measure_temperature(october) * 100) / 100;
                    day_array[element_counter].air_humidity = round(measure_humidity() * 100) / 100;
                    if(day_array[element_counter].day == OCTOBER){
                        flag = 1;
                    }
                    break;
                case 10:
                    day_array[element_counter].month = november;
                    day_array[element_counter].day = day_counter + 1;
                    day_array[element_counter].temperature = round(measure_temperature(november) * 100) / 100;
                    day_array[element_counter].air_humidity = round(measure_humidity() * 100) / 100;
                    if(day_array[element_counter].day == NOVEMBER){
                        flag = 1;
                    }
                    break;
                case 11:
                    day_array[element_counter].month = december;
                    day_array[element_counter].day = day_counter + 1;
                    day_array[element_counter].temperature = round(measure_temperature(december) * 100) / 100;
                    day_array[element_counter].air_humidity = round(measure_humidity() * 100) / 100;
                    if(day_array[element_counter].day == DECEMBER){
                        flag = 1;
                    }
                    break;
                default:
                    break;
            }

            string publish_message =    to_string(day_array[element_counter].day) + ":" +
                                        to_string(day_array[element_counter].month + 1) + ":" +
                                        to_string(day_array[element_counter].temperature) + ":" +
                                        to_string(day_array[element_counter].air_humidity);

            printf("Publishing to topic smartenik/sensors: %s\n", &publish_message[0]);
            mosquitto_publish(mosq, NULL, "smartenik/sensors", 50, &publish_message[0], 0, false);
            sleep(5);

            if(++element_counter == 366){
                element_counter = 0;
            }

            if(flag == 1){
                day_counter = 0;

                if(++month == 12){
                    month = 0;
                }

                break;
            }else{
                day_counter++;
            }
        }
    }

	return 0;
}

float measure_temperature(enum_months month){
    float temperature = 0.0;
    float upper_bound = 0.0;
    float lower_bound = 0.0;

    switch(month){
        case january:
            upper_bound = 16.5;
            lower_bound = -20.2;
            break;
        case february:
            upper_bound = 20.2;
            lower_bound = -21.7;
            break;
        case march:
            upper_bound = 24.8;
            lower_bound = -20.4;
            break;
        case april:
            upper_bound = 31.9;
            lower_bound = -5.8;
            break;
        case may:
            upper_bound = 32.5;
            lower_bound = 0.2;
            break;
        case june:
            upper_bound = 39.5;
            lower_bound = 6.0;
            break;
        case july:
            upper_bound = 38.9;
            lower_bound = 6.6;
            break;
        case august:
            upper_bound = 40.4;
            lower_bound = 0.0;
            break;
        case september:
            upper_bound = 36.4;
            lower_bound = -1.1;
            break;
        case october:
            upper_bound = 28.0;
            lower_bound = -6.1;
            break;
        case november:
            upper_bound = 23.4;
            lower_bound = -8.3;
            break;
        case december:
            upper_bound = 18.1;
            lower_bound = -16.7;
            break;
        default:
            break;
    }

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dist(lower_bound, upper_bound);

    temperature = dist(gen);

    if(temperature > 0){
        temperature *= TEMP_CONST;
    }

    return temperature;
}

float measure_humidity(){
    float humidity = 0.0;
    float upper_bound = 100.0;
    float lower_bound = 0.0;

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dist(lower_bound, upper_bound);

    humidity = dist(gen);

    return humidity;
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
