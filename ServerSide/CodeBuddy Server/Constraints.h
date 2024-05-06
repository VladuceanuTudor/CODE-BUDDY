#pragma once

#define LISTEN_PORT				5520

#define SQL_RETURN_CODE_LEN		1000
#define SQL_RESULT_LEN			240

#define BUFFER_SEND_RECV_SIZE	1024
#define COLUMNS_FOR_USERS		6

#define MAX_BUFFER_LEN			1024

#define MAX_LIVES				7
#define LIVES_REGEN_INTERVAL	1

#define DAILY_XP_GIVEN			10

#define PREMIUM_PRICE			25

#define PAYLOAD_DELIM			'#'

#define GET_LOGIN_CODE			'l'
#define ERROR_CODE				'E'
#define REGISTER_CODE			'r'
#define GET_LESSON_TITLES_CODE	'b'
#define GET_LESSON_CONTENT		'L'
#define GET_EXERCICE_CODE		'e'
#define GET_LEADERBOARD_CODE	'a'
#define LESSON_DONE_CODE		'd'
#define GET_LIVES_CODE			'i'
#define GET_PAYMENT_CODE		'p'
#define GET_CHAT_CODE			'c'
#define GET_FRIENDS_CODE		'f'