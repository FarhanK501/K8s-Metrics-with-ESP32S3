#ifndef NETWORK_MANAGER_H
#define NETWORK_MANAGER_H

#include <Arduino.h>
#include "MetricsData.h"


class NetworkManager
{
public:
    void setupWiFi();
    MetricsData fetchK8sMetrics();
};

#endif
