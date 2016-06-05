#ifndef MESSAGE_H
typedef struct message
{
	int msg_pos;
	char user[15];
	char msg[128];
	char cat[20];
	unsigned int type : 1;
	int reply_id;
	int offset;
}Message;
void addMessage();
int deleteMessage();
void loadReplies();
void loadMessages();
void addReply();
void deleteThread(long offset);
int deleteReply();
#endif