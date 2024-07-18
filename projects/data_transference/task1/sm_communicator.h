#include "../icommunicator.h"
#include <iostream>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <string>

class SharedMemory
{
public:
    SharedMemory(const std::string &name, size_t size);
    ~SharedMemory();

    void *mapMemory();
    void unmapMemory();
    void writeData(const void *data, size_t size);
    void readData(void *buffer, size_t size);

private:
    std::string name_;
    size_t size_;
    int shm_fd_;
    void *ptr_ = nullptr;
    sem_t *sem_write_ = nullptr;
    sem_t *sem_read_ = nullptr;
};

class Communicator : public IntfCommunicator
{
public:
    Communicator();
    ~Communicator();
    void sendByte(uint8_t byte) override;
    void receiveByte(uint8_t &byte) override;
    void send(const std::vector<uint8_t> &data) {}
    void receive(std::vector<uint8_t> &data) {}

    std::string what() const
    {
        return "Na";
    }
    bool isConnected() const
    {
        return false;
    }

private:
    SharedMemory sm_;
};