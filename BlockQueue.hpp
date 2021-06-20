#ifndef __QUEUE_BLOCK_H_
#define __QUEUE_BLOCK_H_

#include<iostream>
#include<queue>
#include<pthread.h>
#include<unistd.h>

class BlockQueue
{
private:
    std::queue<int> q;
    size_t cap;
    pthread_mutex_t lock;
    pthread_cond_t c_cond;//������������㣬��ô����������������µȣ�
    pthread_cond_t p_cond;//������������㣬��ô����������������µȣ�
public:
    bool IsFull()
    {
        return q.size() >= cap;
    }

    bool IsEmpty()
    {
        return q.empty();
    }

    void LockQueue()
    {
        pthread_mutex_lock(&lock);
    }

    void UnlockQueue()
    {
        pthread_mutex_unlock(&lock);
    }

    void WakeUpPruductor()
    {
        pthread_cond_signal(&p_cond);
    }

    void WakeUpComsumer()
    {
        pthread_cond_signal(&c_cond);
    }

    void ProducterWait()
    {
        pthread_cond_wait(&p_cond, &lock);
    }

    void ComsumerWait()
    {

        pthread_cond_wait(&c_cond, &lock);
    }

public:
    BlockQueue(size_t _cap)
        :cap(_cap)
    {
        pthread_mutex_init(&lock, nullptr);
        pthread_cond_init(&c_cond, nullptr);
        pthread_cond_init(&p_cond, nullptr);
    }

    void Put(int in)
    {
        LockQueue();
        while (IsFull())//������ｫif����while
        {
            WakeUpComsumer();
            ProducterWait();//����������ܻ����ʧ�ܣ����ʧ�ܾͻ�û�й��𣬾ͻ�������
        }
        q.push(in);
        UnlockQueue();
    }

    void Get(int& out)
    {
        LockQueue();
        while (IsEmpty())
        {
            WakeUpPruductor();
            ComsumerWait();
        }
        out = q.front();
        q.pop();
        UnlockQueue();
    }
    ~BlockQueue()
    {
        pthread_mutex_destroy(&lock);
        pthread_cond_destroy(&c_cond);
        pthread_cond_destroy(&p_cond);
    }
};

#endif
