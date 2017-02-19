#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>

int main(int argc, char** argv)
{
    int fd, bytes;
    unsigned char data[3];
    const char *pDevice = argv[1];//"/dev/input/mice";
    struct input_event ie;

    // Open Mouse
    fd = open(pDevice, O_RDWR);
    if(fd == -1)
    {
        printf("ERROR Opening %s\n", pDevice);
        return -1;
    }
    
    ioctl(fd, EVIOCGRAB, 1);

    int left, middle, right;
    signed char x, y;
    int asd = 0;
    while(1)
    {
        // Read Mouse     
        bytes = read(fd, &ie, sizeof(struct input_event));

        if(bytes > 0)
        {
            //https://gist.github.com/uobikiemukot/457338b890e96babf60b
            unsigned char *ptr = (unsigned char*)&ie;
            for(int i=0; i<sizeof(ie); i++)
                printf("%02X ", *ptr++);
            printf("\n");

            printf("type=%d, code=%d, value=%d\n", ie.type, ie.code, ie.value);

            /*left = ((char*)(&ie.value))[0] & 0x1;
            right = ((char*)(&ie.value))[0] & 0x2;
            middle = ((char*)(&ie.value))[0] & 0x4;

            x = ((char*)(&ie.value))[1];
            y = ((char*)(&ie.value))[2];
            printf("x=%d, y=%d, left=%d, middle=%d, right=%d\n", x, y, left, middle, right);*/

            /*left = data[0] & 0x1;
            right = data[0] & 0x2;
            middle = data[0] & 0x4;

            x = data[1];
            y = data[2];
            printf("x=%d, y=%d, left=%d, middle=%d, right=%d\n", x, y, left, middle, right);*/
        } else {
            printf("empty read\n");
        }
        if(asd++ > 100000) break;
    }
    return 0; 
}