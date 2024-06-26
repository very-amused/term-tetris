#include "DB.hpp"
#include <cstdlib>
#include <string>
#include <sys/stat.h>
#include <unistd.h>

using std::string;

// Return the directory to create term-tetris.db inside of
static const string DB_path_dir() {
	static const string relative_path = ".local/share/term-tetris";
	return string(getenv("HOME")) + "/" + relative_path;
}

// Return the full path of the term-tetris.db file
const string DB::path() {
	return DB_path_dir() + "/term-tetris.db";
}

int DB::init() {
	// Ensure DB file parent dir exists
	// ref https://stackoverflow.com/a/7430262
	const string db_dir = DB_path_dir();
	struct stat st = {0};
	int status;
	if (stat(db_dir.c_str(), &st) == -1) {
		status = mkdir(db_dir.c_str(), 0755);
		if (status != 0) {
			return status;
		}
	}
	

	// Open DB file
	status = sqlite3_open(DB::path().c_str(), &db);
	if (status != 0) {
		return status;
	}

	// Exec schema 
	return sqlite3_exec(db, DB_schema, NULL, NULL, &errmsg);
}

DB::~DB() {
	if (db != NULL) {
		while (sqlite3_close(db) == SQLITE_BUSY) {};
	}
}

int DB::prepare_stmt(string query, Stmt &stmt) {
	return sqlite3_prepare_v2(db, query.c_str(), query.size(), &stmt.stmt, NULL);
}

Stmt::~Stmt() {
	if (stmt != NULL) {
		sqlite3_finalize(stmt);
	}
}
