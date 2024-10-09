#ifndef METRICS_DATA_H
#define METRICS_DATA_H

#include <Arduino.h>

class MetricsData
{
public:
    int pods = 0;
    int nodes = 0;
    String memoryUsage = "";
    String cpuUsage = "";
    String status = "Good";
    int numberOfTimesInformationFetched = 0;
    String clusterName = "GKE";
};

#endif