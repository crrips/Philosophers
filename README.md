# Philosophers

## Contents

- [Introduction](#introduction)
- [Project Description](#project-description)
- [Usage](#usage)
- [Implementation Details](#implementation-details)
- [Contributing](#contributing)

## Introduction

This repository contains the "Philosophers" project, which is part of the curriculum at 42 School (École 42). The project is designed to explore the concepts of multithreading, synchronization, and concurrency in C. This README provides an overview of the project, its purpose, and how to use it.

## Project Description

The "Philosophers" project challenges students to solve the dining philosophers problem using multithreading and synchronization techniques. The problem involves a group of philosophers who sit at a circular dining table with bowls of spaghetti. To eat, a philosopher must pick up both the left and right forks (chopsticks) that are next to their plate. However, only one philosopher can pick up a fork at a time, and they must release the forks when they're done eating to allow other philosophers to use them.

The objectives of the project include:

- Implementing a solution that prevents deadlocks and ensures that philosophers can eat safely.
- Using multithreading to represent each philosopher as a separate thread.
- Implementing a user-defined delay to control how often philosophers attempt to eat.

## Usage

To compile and run the "Philosophers" project, follow these steps:

1. Clone the repository to your local machine.
   ```sh
   git clone https://github.com/your-username/philosophers.git
   ```

2. Navigate to the project directory.
   ```sh
   cd philosophers
   ```

3. Compile the project using the provided Makefile.
   ```sh
   make
   ```

4. Run the program with the desired number of philosophers, time to die, time to eat, time to sleep, and an optional number of times each philosopher must eat.
   ```sh
   ./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [optional: number_of_times_each_philosopher_must_eat]
   ```

For example, to run the program with 5 philosophers, a time to die of 800 milliseconds, a time to eat of 200 milliseconds, and a time to sleep of 200 milliseconds, you can use the following command:

```sh
./philo 5 800 200 200
```

## Implementation Details

The "Philosophers" project uses the pthread library for creating and managing threads. The main challenge is to prevent deadlocks and ensure that philosophers can eat without conflicting with each other. The code implements the following key components:

- **Mutex Locks**: Mutex locks are used to protect critical sections of code where access to shared resources (forks) is controlled. Philosophers must lock and unlock forks when picking them up and releasing them.

- **Thread Creation**: Each philosopher is represented as a separate thread. Thread creation and management are essential for simulating the dining philosophers problem.

- **Timed Wait**: The code uses the `pthread_mutex_timedlock` function to implement a time limit for acquiring forks. If a philosopher cannot acquire both forks within the specified time, they release any acquired forks and exit to prevent deadlock.

- **Monitoring and Reporting**: The program monitors and reports the state of each philosopher, including when they start eating, sleeping, or thinking, as well as when they have finished their meals. It also keeps track of the number of times each philosopher has eaten.

## Contributing

Contributions to the project are welcome. If you have suggestions, improvements, or bug fixes, please fork the repository, create a new branch, make your changes, and submit a pull request.
