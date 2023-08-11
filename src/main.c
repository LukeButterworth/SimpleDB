#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

//Constant Definitions
const char* HELP_MSG = "Enter \".help\" for usage hints.\n";
const char* TRANSIENT_DB_MSG = "Connected to a transient in-memory database.\n";
const char* PERSISTENT_DB_MSG = "Use \".open FILENAME\" to reopen on a persistent database.\n";
const char* REPL_PROMPT = "simpledb > ";
const char* UNKNOWN_CMD_ERR = "Unknown Command: %s.\n";
const char* READ_INPUT_ERR = "Error reading input.\n";

enum REPL_CMDS {
	EXIT,
	HELP
};

//Constant Definitions
typedef struct {
	char* buffer;
	size_t buffer_length;
	ssize_t input_length;
} InputBuffer;

//Function Declarations
void print_welcome_msg();
InputBuffer* new_input_buffer();
bool read_input(InputBuffer* input_buffer);
void close_input_buffer(InputBuffer* input_buffer);

//Main Function
int main (int argc, char* argv) {
	print_welcome_msg();
	InputBuffer* input_buffer = new_input_buffer();
	printf(REPL_PROMPT);

	while (read_input(input_buffer)) {
		if (!strcmp(input_buffer->buffer, ".exit")) {
			close_input_buffer(input_buffer);
			exit(0);
		} else {
			printf(UNKNOWN_CMD_ERR, input_buffer->buffer);
		}

		printf(REPL_PROMPT);
	}
}

//Function Definitions
void print_welcome_msg() {
	printf(HELP_MSG);
	printf(TRANSIENT_DB_MSG);
	printf(PERSISTENT_DB_MSG);
}

InputBuffer* new_input_buffer() {
	InputBuffer* input_buffer = (InputBuffer*)malloc(sizeof(InputBuffer));
	input_buffer->buffer = NULL;
	input_buffer->buffer_length = 0;
	input_buffer->input_length = 0;

	return input_buffer;
}

bool read_input(InputBuffer* input_buffer) {
	ssize_t bytes_read = 
		getline(&(input_buffer->buffer), &input_buffer->buffer_length, stdin);

	if (bytes_read <= 0) {
		printf(READ_INPUT_ERR);
		exit(1);
	}

	input_buffer->input_length = bytes_read - 1;
	input_buffer->buffer[bytes_read - 1] = 0;
	return true;
}

void close_input_buffer(InputBuffer* input_buffer) {
	free(input_buffer->buffer);
	free(input_buffer);
}

