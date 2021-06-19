#include"BlockQueue.hpp"

using namespace std;

void* consumer_run(void* arg)
{
    BlockQueue* bq = (BlockQueue*)arg;
    while (true)
    {
        //Ҫ��ʵ�ֶ��߳�֮���������������ģ��
        //ֻ��Ҫ���������
        int n = 0;
        bq->Get(n);
        cout << "consumer data is :" << endl;
    }
}

void* productor_run(void* arg)
{
    BlockQueue* bq = (BlockQueue*)arg;
    while (true)
    {
        //Ҫ��ʵ�ֶ��߳�֮���������������ģ��
        //ֻ��Ҫ���������
        int data = rand() % 10 + 1;
        bq->Put(data);
        cout << "product data is :" << data << endl;
    }
}

int main()
{
    BlockQueue* bq = new BlockQueue(5);
    pthread_t c, p;
    pthread_create(&c, nullptr, consumer_run, (void*)bq);
    //pthread_create(&c,nullptr,consumer_run,(void*)bq);
    pthread_create(&p, nullptr, productor_run, (void*)bq);
    //pthread_create(&p,nullptr,productor_run,(void*)bq);


    pthread_join(c, nullptr);
    pthread_join(p, nullptr);

    delete bq;
    return 0;
}
