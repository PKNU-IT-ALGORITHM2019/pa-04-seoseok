#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#define NWEBLOGS 20000
#define MAX 1000
#define BUFFER_LENGTH 100

typedef struct webLog {
	char ip[BUFFER_LENGTH];
	char time[BUFFER_LENGTH];
	char URL[BUFFER_LENGTH];
	char status[BUFFER_LENGTH];
}Log;

void load();

int sort_time(const void *first, const void *second);
int month_to_num(char month[]);
int sort_ip(const void *first, const void *second);
void print(int sorting_type);

Log* log;
int n = 0;

int main() {

	log = (Log *)malloc(NWEBLOGS * sizeof(Log));
	int sorting_type = 0; 

	while (1) {
		char command[BUFFER_LENGTH];
		char type[BUFFER_LENGTH];

		printf("명령어를 입력해주세요 (1.파일 불러오기 2. 정렬할 타입 정하기 3. 출력 4. 종료\n");

		scanf("%s", command);
		if (strcmp(command, "1") == 0) load();
		else if (strcmp(command, "2") == 0) {
			printf("정렬할 방식을 입력해주세요 (1.시간순서 2.ip 순서)\n ");
			scanf("%s", type);
			if (strcmp(type, "1") == 0) {
				qsort(log, n, sizeof(Log), sort_time);
				sorting_type = 1;
			}
			else if (strcmp(type, "2") == 0) {
				qsort(log, n, sizeof(Log), sort_ip);
				sorting_type = 2;
			}
			else printf("다시 입력해주세요.\n");
		}
		else if (strcmp(command, "3") == 0) print(sorting_type);
		else if (strcmp(command, "4") == 0) break;
		else printf("다시 입력헤주세요.\n");
	}
	free(log);

	getchar();
	return 0;
}



int sort_time(const void *first, const void *second) {
	char tmp_first[BUFFER_LENGTH], tmp_second[BUFFER_LENGTH];
	strcpy(tmp_first, ((Log *)first)->time);
	strcpy(tmp_second, ((Log *)second)->time);
	char time1[4][BUFFER_LENGTH];
	char time2[4][BUFFER_LENGTH];
	char *token_first = strtok(tmp_first, "/ ");
	strcpy(time1[0], token_first);
	token_first = strtok(NULL, "/ ");

	strcpy(time1[1], token_first);
	token_first = strtok(NULL, "/: ");

	strcpy(time1[2], token_first);
	token_first = strtok(NULL, "/ ");

	strcpy(time1[3], token_first);

	char *token_second = strtok(tmp_second, "/ ");
	strcpy(time2[0], token_second);
	token_second = strtok(NULL, "/ ");

	strcpy(time2[1], token_second);
	token_second = strtok(NULL, "/: ");

	strcpy(time2[2], token_second);
	token_second = strtok(NULL, "/ ");

	strcpy(time2[3], token_second);

	int result = strcmp(time1[2], time2[2]);        
	if (result != 0) return result;

	int day1 = month_to_num(time1[1]);               
	int day2 = month_to_num(time2[1]);
	result = day1 - day2;
	if (result != 0)return result;

	result = strcmp(time1[0], time2[0]);           
	if (result != 0)return result;

	return strcmp(time1[3], time2[3]);             

}
void load()
{
	char filename[BUFFER_LENGTH];
	printf("파일 이름을 입력해주세요 (ex: weblog.csv)\n");

	scanf("%s", filename);

	FILE *fp = fopen(filename, "r");
	char str[MAX];
	fgets(str, MAX, fp);
	while (!feof(fp)) {
		fgets(str, MAX, fp);

		char *token = strtok(str, ",");
		strcpy(log[n].ip, token);
		token = strtok(NULL, "[,");
		strcpy(log[n].time, token);
		token = strtok(NULL, ",");
		strcpy(log[n].URL, token);
		token = strtok(NULL, ",");
		strcpy(log[n].status, token);
		n++;
	}
	fclose(fp);
}

int month_to_num(char month[])
{
	if (strcmp(month, "Jan") == 0)
		return 1;
	if (strcmp(month, "Feb") == 0) 
		return 2;
	if (strcmp(month, "Mar") == 0)
		return 3;
	if (strcmp(month, "Apr") == 0) 
		return 4;
	if (strcmp(month, "May") == 0)
		return 5;
	if (strcmp(month, "Jun") == 0)
		return 6;
	if (strcmp(month, "Jul") == 0)
		return 7;
	if (strcmp(month, "Aug") == 0)
		return 8;
	if (strcmp(month, "Sep") == 0)
		return 9;
	if (strcmp(month, "Oct") == 0)
		return 10;
	if (strcmp(month, "Nov") == 0)
		return 11;
	if (strcmp(month, "Dec") == 0)
		return 12;
	return -1;
}

int sort_ip(const void *first, const void *second) {
	int result = strcmp(((Log *)first)->ip, ((Log *)second)->ip);
	if (result != 0) return result;
	return sort_time(first, second);
}

void print(int sorting_type)
{
	if (sorting_type == 1) {
		for (int i = 0; i < n; i++) {
			printf("%s\n", log[i].time);
			printf("\tIP: %s\n", log[i].ip);
			printf("\tURL: %s\n", log[i].URL);
			printf("\tStatus: %s", log[i].status);
		}
	}

	else if (sorting_type == 2) {
		for (int i = 0; i < n; i++) {
			printf("%s\n", log[i].ip);
			printf("\tTime: %s\n", log[i].time);
			printf("\tURL: %s\n", log[i].URL);
			printf("\tStatus: %s", log[i].status);
		}
	}

}