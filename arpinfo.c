#include <stdio.h>
#include <stdlib.h>

struct arp_record {
    char ip[16];
    char type[6];
    char flags[6];
    char mac[18];
    char mask[4];
    char dev[16];
};

int main( int argc, char* argv[] ) {
    FILE *fp;

    /* Open /proc/net/arp */
    if ((fp = fopen("/proc/net/arp", "r")) == NULL) {
        perror("ARP file error");
        exit(1);
    }


    /* Move the cursor past the first (header) line */
    int c;
    do {
       c = fgetc (fp);
    } while (c != 0x0A && c != EOF);


    /* Read and print ARP items */
    struct arp_record r = {"", "", "", "", "", ""};
    int tok_read = 0;
    do {
        if(tok_read == 0)
            printf("IP Address\tHardware Address\tDevice\n");
        else
            printf("%s\t%s\t%s\n", r.ip, r.mac, r.dev);

        tok_read = fscanf(fp, "%s%s%s%s%s%s", r.ip, r.type, r.flags, r.mac, r.mask, r.dev);
    } while (tok_read >= 6 && !feof(fp));


    /* Close file */
    if (fclose(fp)) {
        perror("ARP file error");
        exit(1);
    }

    return 0;
}

