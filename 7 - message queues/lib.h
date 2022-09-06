#include <mqueue.h>
#define QUEUE_NAME "/ababc"
int odlaczKomunikat(const char *name);
int zamknijKomunikat(mqd_t des);
mqd_t otworzKomunikat(const char *name, int oflag, struct mq_attr *attrs);
int otrzymajKomunikat(mqd_t mqdes, char *msg_ptr, size_t msg_len, unsigned int *msg_prio);
int wyslijKomunikat(mqd_t mqdes, const char *msg_ptr, size_t msg_len, unsigned int msg_prio);
