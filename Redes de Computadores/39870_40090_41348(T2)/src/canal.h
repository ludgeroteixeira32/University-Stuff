#include <stdbool.h>

struct canal;

struct canal* canal_new(char name[]);

void inicialize_canals(struct canal* canals[]);

void canal_insert(struct canal* list, int new_socket, char name[], char sign_on_time[]);

void canal_remove(struct canal *list, int socket_to_remove);

void list_add_to_set(struct canal *list, fd_set* rset, int* max_fd);

void see_canal_requests(struct canal* canals[], int canal_index, fd_set* rset);

