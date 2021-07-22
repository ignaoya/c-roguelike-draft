#include "rogue.h"

const int LOG_SIZE = 10;
int message_count = 0;

Message* createLog(void)
{
	Message* new_log;
	new_log = calloc(LOG_SIZE, sizeof(Message));

	for (int i = 0; i < LOG_SIZE; i++)
	{
		snprintf(new_log[i].text, sizeof(new_log[i].text), " ");
	}

	return new_log;
}

void addMessage(char text[1024])
{
	for (int i = 0; i < message_count; i++)
	{
		memcpy(message_log[message_count - i].text, 
				   message_log[message_count - i - 1].text, 
					 sizeof(char) * 1024);
	}

	memcpy(message_log[0].text, text, sizeof(char) * 1024);

	if (message_count < 4)
	{
		message_count++;
	}
}

void printMessages(void)
{
	for (int i = 0; i < message_count; i++)
	{
		move(37 - i, 5);
		clrtoeol();
		mvprintw(37 - i, 5, message_log[i].text);
	}
}

void freeLog(void)
{
	for (int i = 0; i < LOG_SIZE; i++)
	{
		free(message_log[i]);
	}
	free(message_log);
}




