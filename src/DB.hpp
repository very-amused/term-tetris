#pragma once
#include <cstddef>
#include <string>
#include <sqlite3.h>
#include <stdint.h>

// sqlite database schema
extern "C" {
extern const char *DB_schema;
extern const uint64_t DB_schema_len;
}

// Get the full filepath to term-tetris.db:
// ~/.local/share/term-tetris.db
const std::string DB_path();

// Database connection
struct DB {
	~DB();

public:
	int init();
	// Null terminated error message,
	// set after calling sqlite3 functions
	char *errmsg;

private:
	sqlite3 *db = NULL;

	// DB file path
	static const std::string path();
};
