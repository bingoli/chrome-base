#include <iostream>
#include <windows.h>

#include "base/process/process_metrics.h"
#include "base/process/process.h"

int main(int argc, char** argv) {
  
  auto my_metrics = base::ProcessMetrics::CreateCurrentProcessMetrics();

  for (int i = 0; i < 10000; i++) {

    for (int j = 0; j < 10000; j++) {
      for (int k = 0; k < 10000; k++) {

      }
    }

    double cpu_usage = my_metrics->GetPlatformIndependentCPUUsage();
    std::cout << cpu_usage << std::endl;
    Sleep(1000);
  }

  return 0;
}
