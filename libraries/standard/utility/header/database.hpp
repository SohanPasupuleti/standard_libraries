#ifndef __DATABASE_HPP__
#define __DATABASE_HPP__

	#include <sqlite3.h>
	#include <string.hpp>
	
	struct Database
	{
		public:
			Database();
			Database(const String&);
			~Database();
			
			String query(const String&) const;
			String path() const;
		
		private:
			sqlite3* _database;
			String _path;
	};

#endif