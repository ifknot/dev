#ifndef DEVICE_H
#define DEVICE_H

#include <sys/ioctl.h>  //ioctl
#include <string.h>     //strerror

#include <string>
#include <stdexcept>

namespace linux_util {

    /**
     * @brief linux device base class
     */
    class device {

    public:

        /**
         * file descriptor type POSIX API abstract handle to an input/output resource
         */
        using fildes_t = int;
        /**
         * ioctl device-dependent request code type
         */
        using request_t = unsigned long;

        explicit device(const std::string& device_path);

        ~device();

        /**
         * @brief exception throwing wrapper for ioctl input/output device system call
         * @param request - device dependent request code that has encoded within whether the argument is an in parameter
         * or out parameter, and the size of the argument argp in bytes
         * @param argp - untyped pointer to memory for request dependent arguments
         * @throws std::invalid_argument(strerror(errno)) on ioctl system call fail __or__ a signal occurs during it
         */
        void xioctl(request_t request, void* argp);

        /**
         * @brief EINT retrying exception throwing wrapper for ioctl input/output device system call
         * If a signal occurs while a system call is running, that signal is not ignored and a signal handler was defined
         * for it with SA_RESTART not set and this handler handles that signal...
         * Then the system call will return the EINTR error code - in which case the ioctl system call is retried.
         * @param request
         * @param argp
         */
        void retry_xioctl(request_t request, void* argp);

    private:

        std::string device_path;
        fildes_t fd{-1}; /// file descriptor POSIX API abstract handle to an input/output resource

        void open_device();

        void close_device();

    };

}


#endif //DEVICE_H
