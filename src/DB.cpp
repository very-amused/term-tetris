#include "DB.hpp"
#include <cstdlib>
#include <string>

using std::string;

const string DB::path() {
	static const char relative_path[] = ".local/share/term-tetris.db";
	return string(getenv("HOME")) + "/" + relative_path;
}

int DB::init() {
	// Open DB file
	int status = sqlite3_open(DB::path().c_str(), &db);
	if (status != 0) {
		return status;
	}

	// Exec schema 
	return sqlite3_exec(db, DB_schema, NULL, NULL, &errmsg);
}

DB::~DB() {
	if (db != NULL) {
		while (sqlite3_close(db) == SQLITE_BUSY) {};
		sqlite3_close(db);
	}
}
