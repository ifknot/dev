#include "device.h"

linux_util::device::device(const std::string &device_path) : device_path(device_path) {
    open_device();
}

void linux_util::device::xioctl(linux_util::device::request_t request, void *argp) {
    if (ioctl(fd_, request, argp) == -1) {
        throw std::invalid_argument(ERR + __func__ + " " + strerror(errno));
    }
}

linux_util::device::~device() {
    close_device();
}

void linux_util::device::retry_xioctl(linux_util::device::request_t request, void *argp) {
    while(true) {
        if (ioctl(fd_, request, argp)  == -1) {
            if (errno == EINTR) {
                continue; //fail but interrupted so retry
            } else {
                throw std::invalid_argument(ERR + __func__ + " " + strerror(errno));
            }
        } else {
            break; //ioctl success
        }
    }
}

void linux_util::device::open_device() {
    fd_ = open(device_path.c_str(), O_RDWR);
    if(fd_ == -1) {
        throw std::invalid_argument(ERR + __func__ + " " + device_path + " " + strerror(errno));
    }
}

void linux_util::device::close_device() {
    if (close(fd_) == -1) {
        throw std::invalid_argument(ERR + __func__ + " " + device_path + " " + strerror(errno));
    }
}

linux_util::device::fildes_t linux_util::device::fd() {
    return fd_;
}




