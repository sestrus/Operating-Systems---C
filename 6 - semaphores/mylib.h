
#include <semaphore.h>
/*biblioteka funkcji*/

/*tworze semafor...*/
void zamknijSemafor(sem_t *sem);
void pozyskajWartosc(sem_t *sem, int *sval);
int podniesSemafor(sem_t *sem);
int opuscSemafor(sem_t *sem);
int odlaczSemafor(const char *name);
sem_t *stworzSemafor(const char *name);
sem_t *otworzSemafor(const char *name);