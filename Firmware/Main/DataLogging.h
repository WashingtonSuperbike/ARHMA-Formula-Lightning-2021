
#ifndef DATALOG_H_
#define DATALOG_H_

#include "SdFat.h"

//Clarification on how SD card stores data: each block is generally about 512 or 1024 bytes. SdFat stores an internal buffer of 512 and when the limit is reached
//only then does it save the data onto the sd card. This is an important trade off. if we are less than that value and the bike suddenly turns off, those <512 bytes aren't stored
//unless we somehow flush the data or use file.close(); this means we should potentially implement a signal for recording values, or even just only record when the HV system is on (not for testing things like precharge obv)
//or we just periodically flush data but that uses more resources on the teensy (this depends on how long it takes + how fast we are writing data)

//Names for each of the log files
#define MOTOR_TEMP_LOG "motor_temperature_log.csv"
#define MOTOR_CONTROLLER_TEMP_LOG "motor_controller_temperature_log.csv"
#define BMS_VOLTAGE_LOG "bms_voltage_log.csv"
#define MOTOR_CONTROLLER_VOLTAGE_LOG "motor_controller_voltage_log.csv"
#define MOTOR_CURRENT_LOG "current_log.csv"
#define THERMISTOR_FILE_BASE "thermistor_temp_"
#define THERMISTOR_FILE_END "_log.csv"
#define RPM_LOG "rpm_log.csv"
#define MAX_DATA 16             //BUFFER SIZE FOR CSV DATA POINTER ARRAY

//Represents a writer to a CSV log file on the sd card
typedef struct CSVWriterStruct{
    const char *filename;
    bool open;
    int dataValuesLen;
    float *dataValues[MAX_DATA];             //array of pointers to shared variables (the data values in the csv log)
    SdFile file;
}CSVWriter;

bool startSD();
bool openFile(CSVWriter writer);
void closeFile(CSVWriter writer);
void dataLoggingTask();
void addRecordToCSV(CSVWriter writer, int sTime, float record);

#endif