#include <stdbool.h>

void separate_request(char* request, char* delimiter);

char* get_next_argument();

char* get_mssg();

void send_response(int response_cod, int user_fd, char* list);

