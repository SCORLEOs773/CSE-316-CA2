#include <stdio.h>

#define MAX_PROCESSES 100

struct process
{
    int pid;
    int priority;
    int remainingTime;
};

int main()
{

    struct process queue1[MAX_PROCESSES];
    struct process queue2[MAX_PROCESSES];
    int queue1Size = 0;
    int queue2Size = 0;

    int numProcesses;
    printf("Enter the number of processes you want to execute - ");
    scanf("%d", &numProcesses);

    for (int i = 0; i < numProcesses; i++)
    {
        struct process p;
        printf("Enter the Process ID, Priority Value, and Remaining Time for the process %d -  ", i + 1);
        scanf("%d %d %d", &p.pid, &p.priority, &p.remainingTime);
        if (p.priority == 0)
        {
            queue1[queue1Size++] = p;
        }
        else
        {
            queue2[queue2Size++] = p;
        }
    }

    int time = 0;
    while (queue1Size > 0 || queue2Size > 0)
    {
        if (queue1Size > 0)
        {
            int highest_priority = 0;
            int highest_priority_index = -1;
            for (int i = 0; i < queue1Size; i++)
            {
                if (queue1[i].priority > highest_priority)
                {
                    highest_priority = queue1[i].priority;
                    highest_priority_index = i;
                }
            }

            struct process p = queue1[highest_priority_index];

            printf("Time %d: Running process %d\n", time, p.pid);
            p.remainingTime -= 2;
            time += 2;

            if (p.remainingTime == 0)
            {
                for (int i = highest_priority_index; i < queue1Size - 1; i++)
                {
                    queue1[i] = queue1[i + 1];
                }
                queue1Size--;

                printf("Time %d: Process %d finished\n", time, p.pid);
            }
            else
            {
                queue2[queue2Size++] = p;
                for (int i = highest_priority_index; i < queue1Size - 1; i++)
                {
                    queue1[i] = queue1[i + 1];
                }
                queue1Size--;
            }
        }

        if (queue2Size > 0)
        {
            int shortest_time = 0;
            int shortest_time_index = -1;
            for (int i = 0; i < queue2Size; i++)
            {
                if (shortest_time_index == -1 || queue2[i].remainingTime < shortest_time)
                {
                    shortest_time = queue2[i].remainingTime;
                    shortest_time_index = i;
                }
            }

            struct process p = queue2[shortest_time_index];

            printf("Time %d: Running process %d\n", time, p.pid);
            time += p.remainingTime;
            p.remainingTime = 0;

            for (int i = shortest_time_index; i < queue2Size - 1; i++)
            {
                queue2[i] = queue2[i + 1];
            }
            queue2Size--;

            printf("Time %d: Process %d finished\n", time, p.pid);
        }
    }

    return 0;
}