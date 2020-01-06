#include <iostream>
#include <string>
#include <windows.h>

#include "base/process/process_metrics.h"
#include "base/process/process.h"

int main(int argc, char** argv) {
  
  int process_id = 0;
  if (argc >= 2) {
    process_id = std::stoi(std::string(argv[1]));
  }

  std::unique_ptr<base::ProcessMetrics> metrics;
  if (process_id <= 0) {
    metrics = base::ProcessMetrics::CreateCurrentProcessMetrics();
  } else {
    base::ProcessHandle process_handle = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, process_id);
    metrics = base::ProcessMetrics::CreateProcessMetrics(process_handle);
  }

  for (int i = 0; i < 10000; i++) {
    double cpu_usage = metrics->GetPlatformIndependentCPUUsage();
    std::cout << cpu_usage << std::endl;
    Sleep(1000);
  }

  return 0;
}
