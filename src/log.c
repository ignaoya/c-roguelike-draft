#include "rogue.h"

const int LOG_SIZE = 10;

Message** createLog(void)
{
	Message** new_log;
	new_log = malloc(sizeof(Message*) * LOG_SIZE);

	for (int i = 0; i < LOG_SIZE; i++)
	{
		Message* newMessage;
		newMessage = malloc(sizeof(Message));
		snprintf(newMessage->text, sizeof(newMessage->text), " ");
		new_log[i] = newMessage;
	}

	return new_log;
}

void addMessage(char text[1024])
{
	for (int i = 0; i < message_count; i++)
	{
		memcpy(message_log[message_count - i]->text, 
				   message_log[message_count - i - 1]->text, 
					 sizeof(char) * 1024);
	}

	memcpy(message_log[0]->text, text, sizeof(char) * 1024);

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
		mvprintw(37 - i, 5, message_log[i]->text);
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




