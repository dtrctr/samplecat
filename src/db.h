
gboolean	db_connect();
int         db_insert(char *qry);
int         mysql_exec_sql(MYSQL *mysql, const char *create_definition);
int         db_update_path(const char* old_path, const char* new_path);
