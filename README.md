---
title: Homework 7

due: Thursday December 6th, 11:59:59 PM

---
# {{ page.title }}: Measuring thread and process performance

All of our other homeworks have primarily been concerned with correctness rather than performance. This assignment will teach you both how to measure performance and show you the difference between different implementation choices: in this case, using threads vs. processes vs. a pre-spawned thread worker pool.

The skeleton code can be downloaded [here]().

## Microbenchmarks vs. macrobenchmarks

When measuring performance, there are two basic approaches: from the bottom up, or from the top down. Both are important. If you're choosing between two implementations of the same task, you'll probably want to see how long the entire process takes: for this, you'd use a _macrobenchmark_. Macrobenchmarks will measure how long it takes from program start to program end. You can do this using tools internal to C, or tools like the shell's `time` builtin, or `/usr/bin/time`.

The other approach is _microbenchmarks_, or testing the time it takes to perform specific actions. For microbenchmarks, because they take so little time, it's important both to ensure that you are only measuring exactly the action you intend to, and to repeat the measurement many times to ensure an accurate estimate of how long it takes to do something.

## Provided code

`macro_processes.c`, `macro_threadpool.c`, and `macro_threads.c` each implement a parallel fibonacci solver, where fib(26) is computed 25,000 times. `macro_processes.c` creates one process for each computation, `macro_threads.c` creates one thread for each computation, and `macro_threadpool.c` creates a pool of threads (default to 2, but you can change it via the first argument to the executable) to perform the tasks. Each program exits as soon as it finishes.

`microbenchmarks.c` spawns 50,000 threads and joins on them immediately after spawning them, and likewise spawns 50,000 child processes and waits on them immediately after spawning them. The threads/processes don't do anything, but are set up so that you can add code that will collect timing information about how fast each of those tasks can be completed. Pay special attention to the `malloc_shared` function and its description. Remember that by default, memory is not shared between child processes and parent processes, so you'll need to use that function to communicate between the two processes.

`statistics.c` is a helper library that includes a data structure that you can use to keep track of many measurements at once, and then compute statistics like the mean, min, max, and standard deviation of the measurements after completing whatever benchmark you were working on.

`examples.c` includes code which shows both how to use the `CLOCK_REALTIME` timer to take high resolution time measurements, and how to use the statistics library.


#### Your tasks

1. Add timing instrumentation to `microbenchmarks.c` that measures:
    * How long it takes to spawn a new thread.
    * How long it takes to start running a new thread.
    * How long it takes to spawn a new process.
    * How long it takes to start running a new process.
   Because each of these tasks is very short, you'll want to repeat the task over and over again and then report your best guess of the overhead of each of those tasks. Hint: you won't need to change any of the actions that the code does, you'll only need to add instrumentation code to keep track of how long each task takes. The challenge for you is to ensure that you are putting the measurements in the right place, and reporting the right thing.

2. Add timing instrumentation to `macro_processes.c`, `macro_threadpool.c`, and `macro_threads.c` - either via shell scripts or via in-program timing, your choice.

3. Create a GCP Virtual machine with 8 cores. Run the thread-per-task and process-per-task macrobenchmarks once each on the VM and record how long they took. Then run the threadpool macrobenchmark, varying the # of worker threads between 1 and 12, and record the execution time for each.

4. Run all of the timing experiments (micro and macro) once each a CS lab desktop machine, systems1, and your Google Cloud Platform Virtual Machine. You will learn how to create VMs in lab on Friday, November 30th. **Note**: when running on systems1, run `top` first to see if anyone else is doing their own experiment. While we can't require you to wait for others to finish, try to do your measurements when no one else is putting the machine under load, otherwise the measurements will not be accurate. Record the execution time for all four measurements in the microbenchmarks, and the overall execution time for each of the macrobenchmarks.


#### Deliverables

1. Code: perform task 1 and task 2 on the code in your github repository. We will manually inspect the code to ensure that you've done the required tasks.

2. Writeup: You must upload a writeup (pdf preferred) that answers the following questions, one per page:

    1. Provide a link to your github repository.
    2. Give any description of how to run the code in task 4 to perform the macrobenchmark - for instance, if you added a script that does the timing measurement, tell how to invoke the script, or if you created one master script to do everything at once, explain what it does and how to use it.
    3. Create a table that reports all of the benchmarks across all three machines. I.e. create a table with columns:
        * Machine name
        * Machine's processor model (read from `/proc/cpuinfo`)
        * Machine's # of cores (count the entries in `/proc/cpuinfo`)
        * thread spawn time
        * thread start time
        * process spawn time
        * process start time
        * process-per-task macrobenchmark
        * thread-per-task macrobenchmark
        * threadpool macrobenchmark (use 8 threads)
        Then, on each machine, run each of those experiments and put the result in the proper cell.
    4. Using your results from task 3, draw a line graph with # of threads in thread pool on the X axis and execution time on the Y axis for the threads, threadpool, and processes macrobenchmarks. You can draw the thread-per-task and process-per-task lines as horizontal lines (this is just so you can compare yoru result against the threadpool results).

#### Due date

This assignment is due {{md due }}.
