// Using Semaphore

#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>

sem_t semaphore;

int num = 2;

void* threadF1(void* arg)
{
    int i;
    if (num != 0)
    {
        num--;
        sem_wait(&semaphore);
        printf("������ 1�� ȭ����� �̿��ϱ� �����մϴ�.\n");

        // ȭ��� �̿��ϴ� �ð��̶� ����
        for (i = 0; i < 1000000; i++) {}

        printf("������ 1�� ȭ��� �̿��� ���ƽ��ϴ�.\n");
        num++;
        sem_post(&semaphore);
    }

    else if (num == 0)
    {
        printf("ȭ����� �� �� ������ 1�� ��ٸ��� �ֽ��ϴ�.\n");

        while (num == 0) {}

        printf("������ 1�� ȭ��� �̿��� �ϰ� ���ƽ��ϴ�.\n");
        num++;
        sem_post(&semaphore);
    }

    return NULL;
}

void* threadF2(void* arg)
{
    int i;
    if (num != 0)
    {
        num--;
        sem_wait(&semaphore);
        printf("������ 2�� ȭ����� �̿��ϱ� �����մϴ�.\n");

        // ȭ��� �̿��ϴ� �ð��̶� ����
        for (i = 0; i < 1000000; i++) {}

        printf("������ 2�� ȭ��� �̿��� ���ƽ��ϴ�.\n");
        num++;
        sem_post(&semaphore);
    }

    else if (num == 0)
    {
        printf("ȭ����� �� �� ������ 2�� ��ٸ��� �ֽ��ϴ�.\n");
        while (num == 0) {}

        printf("������ 2�� ȭ��� �̿��� �ϰ� ���ƽ��ϴ�.\n");
        num++;
        sem_post(&semaphore);
    }


    return NULL;
}

void* threadF3(void* arg)
{
    int i;
    if (num != 0)
    {
        num--;
        sem_wait(&semaphore);
        printf("������ 3�� ȭ����� �̿��ϱ� �����մϴ�.\n");

        // ȭ��� �̿��ϴ� �ð��̶� ����
        for (i = 0; i < 1000000; i++) {}

        printf("������ 3�� ȭ��� �̿��� ���ƽ��ϴ�.\n");
        num++;
        sem_post(&semaphore);
    }

    else if (num == 0)
    {
        printf("ȭ����� �� �� ������ 3�� ��ٸ��� �ֽ��ϴ�.\n");
        while (num == 0) {}

        printf("������ 3�� ȭ��� �̿��� �ϰ� ���ƽ��ϴ�.\n");
        sem_post(&semaphore);
        num++;
    }


    return NULL;
}

int main()
{

    pthread_t thread1, thread2, thread3;


    sem_init(&semaphore, 0, 2); // return :: 0 -> success , others -> fail


    printf("Semaphore test Start!\n");
    // ������ ����
    pthread_create(&thread1, NULL, threadF1, NULL);
    pthread_create(&thread2, NULL, threadF2, NULL);
    pthread_create(&thread3, NULL, threadF3, NULL);

    // ������ ����
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    printf("��� �����尡 ȭ��� �̿��� ���½��ϴ�.\n");

    // �������� ��ü �Ҹ�
    sem_destroy(&semaphore);

    return 0;
}