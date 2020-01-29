#include <iostream>
#include <memory>
#include <string>
#include <windows.h>

#include "base/at_exit.h"
#include "base/command_line.h"
#include "base/files/file_util.h"
#include "base/memory/scoped_refptr.h"
#include "base/process/process_metrics.h"
#include "base/process/process.h"
#include "base/run_loop.h"
#include "base/run_loop.h"
#include "base/strings/utf_string_conversions.h"
#include "base/task_runner.h"
#include "base/task/post_task.h"
#include "base/task/thread_pool/thread_pool_instance.h"
#include "base/test/task_environment.h"
#include "base/test/test_timeouts.h"
#include "base/threading/thread_task_runner_handle.h"
#include "base/threading/thread.h"

#if 1
void GetFileContentCallback(std::string* contents) {
  std::cout << "file contents : " << std::endl;
  std::cout << contents->c_str() << std::endl;

  base::RunLoop::QuitCurrentWhenIdleDeprecated();
}

void OpenFileInNewThread(
    const base::FilePath& file_path, std::string* contents) {
  
  if (base::ReadFileToString(file_path, contents)) {

  }
}
#else
void GetFileContentCallback(const std::string& contents) {
  std::cout << "file contents : " << std::endl;
  std::cout << contents.c_str() << std::endl;

  base::RunLoop::QuitCurrentWhenIdleDeprecated();
}

void OpenFileInNewThread(
    scoped_refptr<base::SingleThreadTaskRunner> ui_task_runner,
    const base::FilePath& file_path) {
  
  std::string contents;
  if (base::ReadFileToString(file_path, &contents)) {

  }

  ui_task_runner->PostTask(FROM_HERE, base::BindOnce(GetFileContentCallback, contents));

}
#endif

int main(int argc, char** argv) {
  if (argc < 2) {
    std::cout << "usage: thread_model_example.exe file" << std::endl;
    return -1;
  }

  base::CommandLine::Init(argc, argv);

  base::AtExitManager at_exit;

  TestTimeouts::Initialize();

  base::test::TaskEnvironment task_environment(
      base::test::TaskEnvironment::MainThreadType::UI);

  auto thread =
      std::make_unique<base::Thread>("FileThread");
  thread->init_com_with_mta(false);
  if (!thread->Start())
    return 0;

  base::FilePath file_path(base::UTF8ToWide(argv[1]));

#if 1
  std::string* contents = new std::string();
  thread->task_runner()->PostTaskAndReply(FROM_HERE,
    base::BindOnce(OpenFileInNewThread, file_path, contents),
    base::BindOnce(GetFileContentCallback, base::Owned(contents)));
#else
  scoped_refptr<base::SingleThreadTaskRunner> ui_task_runner = base::ThreadTaskRunnerHandle::Get();
  thread->task_runner()->PostTask(FROM_HERE, base::BindOnce(OpenFileInNewThread, ui_task_runner, file_path));
#endif

  base::RunLoop run_loop;
  run_loop.Run();

  return 0;
}
