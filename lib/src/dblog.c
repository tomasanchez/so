#include <dblog.h>

static t_log* DB_LOGGER;

void db_init_logs(const char* file, const char* program_name, bool is_active_console, t_log_level log_level)
{
    DB_LOGGER = log_create((char*)file, (char*)program_name, is_active_console, log_level);
}

void db_delete_logs(void)
{
    log_destroy(DB_LOGGER);
}

t_log* db_get_logger(void)
{
    return DB_LOGGER;
}