#ifndef DB_LOG_H
#define DB_LOG_H

#include <commons/log.h>

void db_init_logs(const char* file, const char* program_name, bool is_active_console, t_log_level log_level);
void db_delete_logs(void);

t_log* db_get_logger();

#define DB_LOG_TRACE(...)       log_trace(db_get_logger(), __VA_ARGS__);
#define DB_LOG_DEBUG(...)       log_debug(db_get_logger(), __VA_ARGS__);
#define DB_LOG_INFO(...)        log_info(db_get_logger(), __VA_ARGS__);
#define DB_LOG_WARN(...)        log_warning(db_get_logger(), __VA_ARGS__);
#define DB_LOG_ERROR(...)       log_error(db_get_logger(), __VA_ARGS__);


#endif