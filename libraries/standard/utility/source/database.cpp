#ifndef __DATABASE_CPP__
#define __DATABASE_CPP__

	#include <database.hpp>
	
	#define __INVALID_DATABASE_PATH__ "INVALID_DATABASE_PATH"
	
	Database::Database()
	{
		_database = nullptr;
		_path = __INVALID_DATABASE_PATH__;
	}
	
	Database::Database(const String& database_name)
	{
		_path = database_name;
		if (sqlite3_open(_path.c_string(), &_database) != SQLITE_OK) 
		{
			_database = nullptr;
		}
	}
	
	String Database::query(const String& sql_query) const
	{
		sqlite3_stmt* statement = nullptr;
		if (sqlite3_prepare_v2(_database, sql_query.c_string(), -1, &statement, NULL) != SQLITE_OK)
		{
			sqlite3_finalize(statement);
			return String("Query prepare failed: ") + String(sqlite3_errmsg(_database));
		}

		String result;

		while (sqlite3_step(statement) == SQLITE_ROW)
		{
			int col_count = sqlite3_column_count(statement);
			for (int i = 0; i < col_count; ++i)
			{
				if (i > 0) result += String(", ");

				switch (sqlite3_column_type(statement, i))
				{
					case SQLITE_TEXT:
					{
						const unsigned char* text = sqlite3_column_text(statement, i);
						result += String(reinterpret_cast<const char*>(text ? text : reinterpret_cast<const unsigned char*>("NULL")));
						break;
					}
					case SQLITE_INTEGER:
					{
						int integer_value = sqlite3_column_int(statement, i);
						result += String(integer_value);
						break;
					}
					case SQLITE_FLOAT:
					{
						float float_value = static_cast<float>(sqlite3_column_double(statement, i));
						result += String(float_value);
						break;
					}
					case SQLITE_NULL:
						result += String("NULL");
						break;
					default:
						result += String("UNKNOWN");
						break;
				}
			}
			result += '\n';
		}

		sqlite3_finalize(statement);
		return result;
	}
	
	String Database::path() const
	{
		return _path;
	}
	
	Database::~Database()
	{
		if (_database != nullptr)
		{
			sqlite3_close(_database);
		}
	}
	
#endif