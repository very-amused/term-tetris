#pragma once
#include <cstddef>
#include <string>
#include <sqlite3.h>
#include <stdint.h>

// schema.sql
// included via schema.s (John Ripley's fantastic trick) 
// ref https://stackoverflow.com/a/4910421
extern "C" {
extern const char DB_schema[];
extern const uint64_t DB_schema_len;
}

// Get the full filepath to term-tetris.db:
// ~/.local/share/term-tetris.db
const std::string DB_path();

struct Stmt;

// Database connection
struct DB {
	~DB();

public:
	int init();
	// Null terminated error message,
	// set after calling sqlite3 functions
	char *errmsg;

	// Prepare the next statement for execution
	int prepare_stmt(std::string query, Stmt &stmt);

private:
	sqlite3 *db = NULL;

	// DB file path
	static const std::string path();
};

// sqlite3_stmt wrapper providing RAII for sqlite3_finalize
struct Stmt {
	~Stmt();

public:
	sqlite3_stmt *stmt = NULL;
};
