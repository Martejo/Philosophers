### Philosophers

The “Philosophers” project trains us to solve the classic problem of philosophers around a table, using threads and mutexes.  
This exercise focuses on learning the basics of threading, process synchronization and deadlock prevention.  
We have to create a simulation in which several threads of philosophers have to share resources (such as forks)  
without getting into deadlock situations, ensuring that all philosophers can eat, think and sleep without starving.  

## Resources:
https://medium.com/@ruinadd/philosophers-42-guide-the-dining-philosophers-problem-893a24bc0fe2  
https://www.youtube.com/watch?v=zOpzGHwJ3MU

## How to use  
```
git clone https://github.com/Martejo/Philosophers
cd Philosophers
make
./philo [number_of_philosophers] [time_to_die time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]
```
