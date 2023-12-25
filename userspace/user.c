#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define DEVICE_PATH "/dev/virtualdevice"
#define IOCTL_GET_COUNT _IOR('k', 6, int[5])
#define IOCTL_INC_1 _IO('k', 1)
#define IOCTL_INC_2 _IO('k', 2)
#define IOCTL_INC_3 _IO('k', 3)
#define IOCTL_INC_4 _IO('k', 4)
#define IOCTL_INC_5 _IO('k', 5)

int main() {
    int fd = open(DEVICE_PATH, O_RDWR);
    if (fd < 0) {
        perror("Error opening device");
        return -1;
    }
	if (ioctl(fd, IOCTL_INC_1) < 0) {
        perror("Error calling ioctl");
        close(fd);
        return -1;
	}

	if (ioctl(fd, IOCTL_INC_2) < 0) {
        perror("Error calling ioctl");
        close(fd);
        return -1;
	}
	
    int cmd_counts[5] = {0};

    // Виклик ioctl для отримання значення лічильників для всіх команд
    if (ioctl(fd, IOCTL_GET_COUNT, cmd_counts) < 0) {
        perror("Error calling ioctl");
        close(fd);
        return -1;
    }

    // Виведення значень лічильників
    printf("Count for IOCTL_INC_1: %d\n", cmd_counts[0]);
    printf("Count for IOCTL_INC_2: %d\n", cmd_counts[1]);
    printf("Count for IOCTL_INC_3: %d\n", cmd_counts[2]);
    printf("Count for IOCTL_INC_4: %d\n", cmd_counts[3]);
    printf("Count for IOCTL_INC_5: %d\n", cmd_counts[4]);

    // Закриття файлового дескриптора
    close(fd);

    return 0;
}


