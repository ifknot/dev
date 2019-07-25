#include "device.h"

linux_util::device::device(const std::string &device_path) : device_path(device_path) {
    open_device();
}

void linux_util::device::xioctl(linux_util::device::request_t request, void *argp) {
    if (ioctl(fd, request, argp)) {
        throw std::invalid_argument(strerror(errno));
    }
}

linux_util::device::~device() {
    close_device();
}

void linux_util::device::retry_xioctl(linux_util::device::request_t request, void *argp) {
    while(true) {
        if (ioctl(fd, request, argp)) {
            if (errno == EINTR) {
                continue; //fail but interrupted so retry
            } else {
                throw std::invalid_argument(strerror(errno));
            }
        } else {
            break; //ioctl success
        }
    }
}

void linux_util::device::open_device() {
    //TODO
}

void linux_util::device::close_device() {
    //TODO
}


