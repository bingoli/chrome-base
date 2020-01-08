#include <iostream>
#include <string>
#include <windows.h>

#include "base/at_exit.h"
#include "base/command_line.h"
#include "base/task/post_task.h"
#include "base/process/process_metrics.h"
#include "base/process/process.h"
#include "base/run_loop.h"
#include "base/task_runner.h"
#include "base/task/thread_pool/thread_pool_instance.h"
#include "base/test/task_environment.h"
#include "base/test/test_timeouts.h"

void GetProcessCpuUsage(int process_id) {
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
}


int main(int argc, char** argv) {
  
  int process_id = 0;
  if (argc >= 2) {
    process_id = std::stoi(std::string(argv[1]));
  }

  base::CommandLine::Init(argc, argv);

  base::AtExitManager at_exit;

  TestTimeouts::Initialize();

  base::test::TaskEnvironment task_environment(
      base::test::TaskEnvironment::MainThreadType::UI);

  scoped_refptr<base::TaskRunner> task_runner = base::CreateTaskRunner({base::ThreadPool()});
  task_runner->PostTask(FROM_HERE, base::BindOnce(GetProcessCpuUsage, process_id));

  base::RunLoop run_loop;
  run_loop.Run();

  return 0;
}
