#include "sm_communicator.h"
#include <cstring>
#include <iostream>
#include <thread>
#include <chrono>

SharedMemory::SharedMemory(const std::string &name, size_t size)
    : name_(name), size_(size), shm_fd_(-1), ptr_(nullptr)
{
    shm_fd_ = shm_open(name_.c_str(), O_CREAT | O_RDWR, 0666);
    if (shm_fd_ == -1)
    {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    struct stat mapstat;
    if (-1 != fstat(shm_fd_, &mapstat) && mapstat.st_size == 0)
    {
        if (ftruncate(shm_fd_, size_) == -1)
        {
            perror("ftruncate");
            exit(EXIT_FAILURE);
        }
    }

    ptr_ = mmap(0, size_, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd_, 0);
    if (ptr_ == MAP_FAILED)
    {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    sem_write_ = sem_open((name_ + "_write").c_str(), O_CREAT, 0666, 1);
    sem_read_ = sem_open((name_ + "_read").c_str(), O_CREAT, 0666, 0);
}

SharedMemory::~SharedMemory()
{
    if (sem_close(sem_write_) == -1 || sem_close(sem_read_) == -1)
    {
        perror("sem_close");
    }

    if (sem_unlink((name_ + "_write").c_str()) == -1 || sem_unlink((name_ + "_read").c_str()) == -1)
    {
        perror("sem_unlink");
    }

    if (munmap(ptr_, size_) == -1)
    {
        perror("munmap");
    }

    if (close(shm_fd_) == -1)
    {
        perror("close");
    }

    if (shm_unlink(name_.c_str()) == -1)
    {
        perror("shm_unlink");
    }
}

void *SharedMemory::mapMemory()
{
    return ptr_;
}

void SharedMemory::unmapMemory()
{
    if (munmap(ptr_, size_) == -1)
    {
        perror("munmap");
    }
}

void SharedMemory::writeData(const void *data, size_t size_)
{
    sem_wait(sem_write_);
    std::memcpy(ptr_, data, size_);
    sem_post(sem_read_);
}

void SharedMemory::readData(void *buffer, size_t size_)
{
    sem_wait(sem_read_);
    std::memcpy(buffer, ptr_, size_);
    sem_post(sem_write_);
}

static int cnt = 0;

Communicator::Communicator() : sm_("test" + std::to_string(cnt++), 1024)
{
}

Communicator::~Communicator()
{
}

void Communicator::sendByte(uint8_t byte)
{
    std::string message;
    message += byte;
    sm_.writeData(message.c_str(), message.size() + 1);
}

void Communicator::receiveByte(uint8_t &byte)
{
    sm_.readData(&byte, sizeof(byte));
}