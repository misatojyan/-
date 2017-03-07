#include <stdio.h>
#include "mysql.h"

#pragma comment(lib, "libmysql.lib")

typedef unsigned int uint;
typedef unsigned long ulong;

void print_error(MYSQL *conn, const char *title) {
	fprintf(stderr, "%s:\nError %u (%s)\n", title, mysql_errno(conn), mysql_error(conn));
}

void process_result_set(MYSQL *conn, MYSQL_RES *res_set) {
	MYSQL_ROW row;
	uint i;

	while ((row = mysql_fetch_row(res_set)) != NULL) {
		for (i = 0; i<mysql_num_fields(res_set); i++) {
			if (i > 0)
				fputc('\t', stdout);
			printf("%s", row[i] != NULL ? row[i] : "NULL");
		}
		fputc('\n', stdout);
	}

	if (mysql_errno(conn) != 0)
		print_error(conn, "mysql_fetch_row() failed");
	else
		printf("%lu rows returned \n", (ulong)mysql_num_rows(res_set));
}

int main(void)
{
	MYSQL mysql;
	if (NULL == mysql_init(&mysql)) {
		printf("mysql_init failed!\n");
		exit(-1);
	}
	if (NULL == mysql_real_connect(&mysql, NULL, "neptune", "nepneptune", "neptune", 0, NULL, 0)) {
		printf("mysql_real_connect failed!\n");
		printf("%u %s\n", mysql_errno(&mysql), mysql_error(&mysql));
		mysql_close(&mysql);
		exit(-1);
	}

	printf("mysql_character_set_name() = %s\n", mysql_character_set_name(&mysql));
	mysql_set_character_set(&mysql, "GBK");
	printf("mysql_character_set_name() = %s\n", mysql_character_set_name(&mysql));

	/*查询*/
	if (mysql_query(&mysql, "SELECT * FROM `研磨机数据` LIMIT 0, 1000")) {
		print_error(&mysql, "mysql_query() failed!\n");
	}
	else {
		MYSQL_RES *res_set;
		res_set = mysql_store_result(&mysql);    /*生成结果集*/
		if (res_set == NULL)
			print_error(&mysql, "mysql_store_result failed");
		else {
			process_result_set(&mysql, res_set);
			mysql_free_result(res_set);
		}
	}
	mysql_close(&mysql);
	printf("ok!\n");
	return 0;
}