#include "rogue.h"

typedef struct Message
{
	char* text;
} Message;

Message message_log[10] = { "" };
int message_count = 0;

void addMessage(char* text)
{
	for (int i = 0; i < message_count; i++)
	{
		message_log[message_count - i] = message_log[message_count - i - 1];
	}

	Message newMessage = { text };
	message_log[0] = newMessage;

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


